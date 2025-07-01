// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/TowerBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Monster/MonsterBase_TowerDefence.h"
#include "PlayerController_TowerDefence.h"
#include "Net/UnrealNetwork.h"

#include "Utils/TDLogChannel.h"


ATowerBase::ATowerBase()
	: CurState(ETowerState::IDLE), AttackRange(0.0), AttackCoolTime(0.f)
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	bUseControllerRotationYaw = true;

	const float fHalfHeight = 50.f;	// Only for init // TODO: 피드백

	UCapsuleComponent* pCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComp"));
	if (pCapsule)
	{
		pCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		pCapsule->SetCollisionObjectType(ECC_Pawn);
		pCapsule->SetCollisionResponseToAllChannels(ECR_Block);
		pCapsule->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
		pCapsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

		pCapsule->InitCapsuleSize(30.f, fHalfHeight);
		pCapsule->SetRelativeLocation(FVector(0.f, 0.f, fHalfHeight));
		pCapsule->SetMobility(EComponentMobility::Movable);
		pCapsule->SetSimulatePhysics(false);

		RootComponent = pCapsule;
	}

	SKMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	if (SKMesh)
	{
		SKMesh->SetupAttachment(RootComponent);
		SKMesh->SetRelativeLocation(FVector(0.f, 0.f, -fHalfHeight));
		SKMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
}

void ATowerBase::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator(0.0, 180.0, 0.0));

	if (HasAuthority())	// Self possess, only server side
	{
		AActor* pExpectedOwner = GetOwner();
		if (Controller == nullptr)
		{
			if (TowerAsset->AI_Controller)
			{
				AAIController* AIController = GetWorld()->SpawnActor<AAIController>(
					TowerAsset->AI_Controller, GetActorLocation(), GetActorRotation());
				if (AIController)
				{
					AIController->Possess(this);
					SetOwner(pExpectedOwner);	// when possess work, owner covered - 중요!
				}
			}
		}
	}
}

void ATowerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATowerBase, TowerAsset);
	DOREPLIFETIME(ATowerBase, CurState);
}

void ATowerBase::OnAttackFinish()
{
	if (HasAuthority())
	{
		SetState(ETowerState::IDLE);
	}
}

void ATowerBase::SetState(ETowerState newState)
{
	if (HasAuthority())
	{
		CurState = newState;
	}
}

void ATowerBase::OnRep_TowerAsset()
{
	if (IsValid(SKMesh) && IsValid(TowerAsset))	// Set mesh infoes
	{
		if (TowerAsset->TowerMesh.IsValid())
		{
			TowerAsset->TowerMesh.LoadSynchronous();
			SKMesh->SetSkeletalMeshAsset(TowerAsset->TowerMesh.Get());
		}
		SKMesh->SetAnimInstanceClass(TowerAsset->AnimInstance);

		if (TowerAsset->MontageAttack.IsValid())
		{
			MontageAttack = TowerAsset->MontageAttack.LoadSynchronous();
		}

		AttackCoolTime = TowerAsset->AttackCoolTime;
		AttackRange = TowerAsset->AttackRange;
	}
}

void ATowerBase::OnRep_StateChanged()
{
	switch (CurState)
	{
	case ETowerState::ATTACK:
		if (IsValid(MontageAttack))
		{
			SKMesh->GetAnimInstance()->Montage_Play(MontageAttack);
		}
		break;
	default:
		if (SKMesh->GetAnimInstance()->IsAnyMontagePlaying())
		{
			SKMesh->GetAnimInstance()->StopAllMontages(0.f);
		}
		break;
	}
}

void ATowerBase::SetupAsset(TObjectPtr<UTowerAsset> towerAsset)
{
	if (HasAuthority())
	{
		TowerAsset = towerAsset;

		AttackRange = TowerAsset->AttackRange;
		AttackCoolTime = TowerAsset->AttackCoolTime;
	}
}

bool ATowerBase::Attack(AActor* pTarget)
{
	if (false == IsValid(pTarget))
	{
		return false;
	}
	if (AttackCoolTime == 0.f)
	{
		return false;
	}

	if (HasAuthority())
	{
		if (ETowerState::ATTACK != CurState)
		{
			SetState(ETowerState::ATTACK);
			pTarget->TakeDamage(10.f, FPointDamageEvent{}, Cast<APlayerController_TowerDefence>(GetOwner()), this);

			// Cool down timer
			GetWorldTimerManager().SetTimer(
				TimerCoolDown,
				this,
				&ThisClass::OnAttackFinish,
				AttackCoolTime,
				false,
				AttackCoolTime
			);

			return true;
		}
	}

	return false;
}

void ATowerBase::OnFocused()
{
	// TODO: Render Range 
}

void ATowerBase::OnMoveTo(const FVector& vTargetPos)
{
}

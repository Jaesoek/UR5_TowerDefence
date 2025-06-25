// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/TowerBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Monster/MonsterBase_TowerDefence.h"

ATowerBase::ATowerBase()
	: m_fAttackRange(0.0)
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	bUseControllerRotationYaw = true;

	const float fHalfHeight = 50.f;	// Only for init

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

	m_SKMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	if (m_SKMesh)
	{
		m_SKMesh->SetupAttachment(RootComponent);
		m_SKMesh->SetRelativeLocation(FVector(0.f, 0.f, -fHalfHeight));
		m_SKMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
}

void ATowerBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsValid(m_SKMesh) && IsValid(m_TowerAsset))	// Set mesh infoes
	{
		if (false == m_TowerAsset->TowerMesh.IsValid())
		{
			m_TowerAsset->TowerMesh.LoadSynchronous();
		}
		m_SKMesh->SetSkeletalMeshAsset(m_TowerAsset->TowerMesh.Get());
		m_SKMesh->SetAnimInstanceClass(m_TowerAsset->AnimInstance);

		m_fAttackRange = m_TowerAsset->AttackRange;
	}
}

void ATowerBase::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator(0.0, 180.0, 0.0));

	if (HasAuthority())	// Self possess, only server side
	{
		if (Controller == nullptr)
		{
			if (m_TowerAsset->AI_Controller)
			{
				AAIController* AIController = GetWorld()->SpawnActor<AAIController>(
					m_TowerAsset->AI_Controller, GetActorLocation(), GetActorRotation());
				if (AIController)
				{
					AIController->Possess(this);
				}
			}
		}
	}
}

bool ATowerBase::Attack(AActor* pTarget)
{
	if (!m_TowerAsset)
	{
		return false;
	}

	if (IsValid(pTarget) && IsValid(m_TowerAsset->AttackMontage) && !m_SKMesh->GetAnimInstance()->Montage_IsPlaying(m_TowerAsset->AttackMontage))
	{
		m_SKMesh->GetAnimInstance()->Montage_Play(m_TowerAsset->AttackMontage);
		pTarget->TakeDamage(10.f, FPointDamageEvent{}, GetController(), this);
		return true;
	}

	return false;
}

void ATowerBase::FollowTo(FVector& vTargetPos)
{
	//if (m_eStatus != ETowerState::STATE_READY)
	//{
	//	return;
	//}

	//if ((vTargetPos - GetActorLocation()).SizeSquared() > 2.f)
	//{
	//	SetActorLocation(vTargetPos);
	//}
}

void ATowerBase::OnFocused()
{
	// TODO: Render Range 
}

void ATowerBase::OnMoveTo(const FVector& vTargetPos)
{
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/BaseTower.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

ABaseTower::ABaseTower()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SKMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	if (m_SKMesh)
	{
		m_SKMesh->SetupAttachment(RootComponent);
	}

	m_pAttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	if (m_pAttackRange)
	{
		m_pAttackRange->SetupAttachment(RootComponent);
		m_pAttackRange->OnComponentBeginOverlap.AddDynamic(this, &ABaseTower::OnMonsterEnter);
		m_pAttackRange->OnComponentEndOverlap.AddDynamic(this, &ABaseTower::OnMonsterExit);
	}
}

void ABaseTower::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(
		-1, 1.0f, FColor::Green,
		TEXT("Tower BeginPlay!")
	);
}

void ABaseTower::OnMonsterEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Monster"))
	{
		if (!IsValid(m_pCurTarget))
		{
			SetCurTarget(OtherActor);
		}
	}
}

void ABaseTower::OnMonsterExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (m_pCurTarget == OtherActor)
	{
		SetCurTarget();
	}
}

bool ABaseTower::Attack()
{
	//IsValid(m_pCurTarget) &&
	if (IsValid(AttackMontage) && !m_SKMesh->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
	{
		m_SKMesh->GetAnimInstance()->Montage_Play(AttackMontage);
		return true;
	}

	return false;
}

void ABaseTower::FollowTo(FVector& vTargetPos)
{
	if (m_eStatus != ETowerState::STATE_READY)
	{
		return;
	}

	double fLengthSq = (vTargetPos - GetActorLocation()).SizeSquared();
	if (fLengthSq > 2.f)
	{
		SetActorLocation(vTargetPos);
	}
}

void ABaseTower::SetCurTarget(AActor* pActor)
{
	if (pActor != nullptr)
	{
		m_pCurTarget = pActor;

		return;
	}

	TArray<AActor*> arrActors;
	m_pAttackRange->GetOverlappingActors(arrActors);
	for (auto iter = arrActors.CreateIterator(); iter; ++iter)
	{
		if (IsValid(*iter))
		{
			m_pCurTarget = *iter;
		}
	}
}

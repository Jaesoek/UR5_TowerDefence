// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/TowerBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MonsterBase_TowerDefence.h"

ATowerBase::ATowerBase()
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
		m_pAttackRange->OnComponentBeginOverlap.AddDynamic(this, &ATowerBase::OnMonsterEnter);
		m_pAttackRange->OnComponentEndOverlap.AddDynamic(this, &ATowerBase::OnMonsterExit);
	}
}

void ATowerBase::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(
		-1, 1.0f, FColor::Green,
		TEXT("Tower BeginPlay!")
	);
}

void ATowerBase::OnMonsterEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && Cast<AMonsterBase_TowerDefence>(OtherActor))
	{
		if (!IsValid(m_pCurTarget))
		{
			SetCurTarget(OtherActor);
		}
	}
}

void ATowerBase::OnMonsterExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (m_pCurTarget == OtherActor)
	{
		SetCurTarget();
	}
}

bool ATowerBase::Attack()
{
	//IsValid(m_pCurTarget) &&
	if (IsValid(AttackMontage) && !m_SKMesh->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
	{
		m_SKMesh->GetAnimInstance()->Montage_Play(AttackMontage);
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

void ATowerBase::SetCurTarget(AActor* pActor)
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

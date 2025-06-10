// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/TowerBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Monster/MonsterBase_TowerDefence.h"

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

void ATowerBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsValid(m_SKMesh) && IsValid(m_TowerAsset))	// Set mesh infoes
	{
		m_SKMesh->SetSkeletalMeshAsset(m_TowerAsset->TowerMesh.Get());
		m_SKMesh->SetAnimInstanceClass(m_TowerAsset->AnimInstance);
	}
}

void ATowerBase::OnMonsterEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && Cast<AMonsterBase_TowerDefence>(OtherActor))
	{
		if (!IsValid(m_pCurTarget.Get()))
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
	if (!m_TowerAsset)
	{
		return false;
	}

	//IsValid(m_pCurTarget) &&
	if (IsValid(m_TowerAsset->AttackMontage) && !m_SKMesh->GetAnimInstance()->Montage_IsPlaying(m_TowerAsset->AttackMontage))
	{
		m_SKMesh->GetAnimInstance()->Montage_Play(m_TowerAsset->AttackMontage);
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

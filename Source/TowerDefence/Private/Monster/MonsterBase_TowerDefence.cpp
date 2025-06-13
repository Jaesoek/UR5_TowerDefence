#include "Monster/MonsterBase_TowerDefence.h"
#include "../Public/GameState_TowerDefence.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterAsset.h"
#include "Components/CapsuleComponent.h"

AMonsterBase_TowerDefence::AMonsterBase_TowerDefence()
{
	PrimaryActorTick.bCanEverTick = false; // ���� �Ⱦ��� ��Ȱ��ȭ

	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	const float fHalfHeight = 50.f;	// Only for init

	UCapsuleComponent* pCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComp"));
	if (IsValid(pCapsule))
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

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	if (IsValid(SkeletalMeshComponent))
	{
		SkeletalMeshComponent->SetupAttachment(RootComponent);
		SkeletalMeshComponent->SetRelativeLocation(FVector{ 0.f, 0.f, -fHalfHeight });
	}
}

void AMonsterBase_TowerDefence::SetupAsset(const UMonsterAsset* InMonsterAsset)
{
	if (!IsValid(InMonsterAsset))
	{
		return;
	}
	
	if (InMonsterAsset->MonsterMesh.ToSoftObjectPath().IsValid())
	{
		USkeletalMesh* SkelMesh = InMonsterAsset->MonsterMesh.LoadSynchronous();
		if (IsValid(SkelMesh))
		{
			SkeletalMeshComponent->SetSkeletalMesh(SkelMesh);
		}
	}

	Health = InMonsterAsset->Health;
}

void AMonsterBase_TowerDefence::Destroyed()
{
	Super::Destroyed();

	AGameState_TowerDefence* pGameState = GetWorld()->GetGameState<AGameState_TowerDefence>();
	if (IsValid(pGameState))
	{
		pGameState->DecreaseMonster();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("GameState doesnt' exist"));
	}
}



#include "Monster/MonsterBase_TowerDefence.h"
#include "../Public/GameState_TowerDefence.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterAsset.h"

AMonsterBase_TowerDefence::AMonsterBase_TowerDefence()
{
	PrimaryActorTick.bCanEverTick = false; // ���� �Ⱦ��� ��Ȱ��ȭ
	
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
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



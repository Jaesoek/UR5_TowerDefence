#include "MonsterBase_TowerDefence.h"
#include "../Public/GameState_TowerDefence.h"


AMonsterBase_TowerDefence::AMonsterBase_TowerDefence()
{
	PrimaryActorTick.bCanEverTick = true;

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



#include "SpawnerMonster_TowerDefence.h"
#include "../Public/GameState_TowerDefence.h"


ASpawnerMonster_TowerDefence::ASpawnerMonster_TowerDefence()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ASpawnerMonster_TowerDefence::BeginPlay()
{
	Super::BeginPlay();

	AGameState_TowerDefence* pGameState = GetWorld()->GetGameState<AGameState_TowerDefence>();
	pGameState->GetStartRoundEvent().AddUObject(this, &ASpawnerMonster_TowerDefence::SpawnMonsters);
}

void ASpawnerMonster_TowerDefence::SpawnMonsters()
{
	
}

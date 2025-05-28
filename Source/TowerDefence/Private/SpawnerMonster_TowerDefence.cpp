#include "SpawnerMonster_TowerDefence.h"
#include "../Public/GameState_TowerDefence.h"


ASpawnerMonster_TowerDefence::ASpawnerMonster_TowerDefence()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ASpawnerMonster_TowerDefence::SpawnMonsters()
{
	auto pGameState = GetWorld()->GetGameState<AGameState_TowerDefence>();
	pGameState->GetStartRoundEvent().AddUObject(this, &ASpawnerMonster_TowerDefence::SpawnMonsters);
}

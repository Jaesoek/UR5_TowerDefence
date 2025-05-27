#include "SpawnerMonster_TowerDefence.h"


ASpawnerMonster_TowerDefence::ASpawnerMonster_TowerDefence()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnerMonster_TowerDefence::BeginPlay()
{
	Super::BeginPlay();	
}

void ASpawnerMonster_TowerDefence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerMonster_TowerDefence::StartSpawning(int32 iLevel)
{
	if (m_eCurState == ESpawnerState::Spawning)
		return;

	m_eCurState = ESpawnerState::Spawning;
	
	// 몇 마리
	// 어떤놈?
	// log(iLevel) * 10 + 10;
	// Timer 동작 시켜서 돌려시발거
}


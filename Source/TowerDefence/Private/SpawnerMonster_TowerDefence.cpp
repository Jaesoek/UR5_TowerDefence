#include "SpawnerMonster_TowerDefence.h"
#include "../Public/GameState_TowerDefence.h"


ASpawnerMonster_TowerDefence::ASpawnerMonster_TowerDefence()
	: m_fTimeInterval_Spawning{ 1.f }
	, m_iCurNum_SpawnedMonster{ 0 }
{
	PrimaryActorTick.bCanEverTick = false;

}

void ASpawnerMonster_TowerDefence::BeginPlay()
{
	Super::BeginPlay();

	if (false == HasAuthority())
		return;

	AGameState_TowerDefence* pGameState = GetWorld()->GetGameState<AGameState_TowerDefence>();
	if (IsValid(pGameState))
	{
		pGameState->RegistEvent_StartRound(this, &ASpawnerMonster_TowerDefence::StartSpawning);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("GameState doesnt' exist"));
	}
}

void ASpawnerMonster_TowerDefence::StartSpawning()
{
	if (false == HasAuthority())
		return;

	AGameState_TowerDefence* pGameState = GetWorld()->GetGameState<AGameState_TowerDefence>();
	if (IsValid(pGameState))
	{
		m_iCurNum_SpawnedMonster = 0;

		pGameState->SetMonsterNum(m_iMonsterNum_Test);
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_StartRound,
			this,
			&ASpawnerMonster_TowerDefence::SpawnMonster,
			m_fTimeInterval_Spawning,
			true
		);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("GameState doesnt' exist"));
	}
}

void ASpawnerMonster_TowerDefence::SpawnMonster()
{
	if (false == HasAuthority())
		return;

	static const FActorSpawnParameters spawnParams = [] {
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		return params;
	}();
	if (nullptr != GetWorld()->SpawnActor(m_MonsterMap[TEXT("default")], &GetTransform(), spawnParams))
	{
		++m_iCurNum_SpawnedMonster;
	}
	if (m_iCurNum_SpawnedMonster == m_iMonsterNum_Test)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_StartRound);
	}
}

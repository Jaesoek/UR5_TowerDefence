#include "GameState_TowerDefence.h"
#include "EngineUtils.h"
#include "TimerManager.h"
#include "../Public/SpawnerMonster_TowerDefence.h"

AGameState_TowerDefence::AGameState_TowerDefence()
{
	m_curGameState = ERoundState::WaitingToStart;
}

void AGameState_TowerDefence::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	for (TActorIterator<ASpawnerMonster_TowerDefence> It(GetWorld()); It; ++It)
		m_arrSpawners.Add(*It);

	WaitRound();
}

void AGameState_TowerDefence::WaitRound()
{
	if (m_arrSpawners.IsEmpty())
		return;

	m_curGameState = ERoundState::RoundWaiting;

	GetWorld()->GetTimerManager().SetTimer(
		m_TimerHandle_StartRound,
		this,
		&AGameState_TowerDefence::StartRound,
		m_fRoundWaitTime,
		false
	);
}

void AGameState_TowerDefence::StartRound()
{
	m_iCurLevel += 1;

	m_curGameState = ERoundState::RoundInProgress;

	for (auto& pSpawnerRef : m_arrSpawners)
	{
		if (ASpawnerMonster_TowerDefence* pSpawner = Cast<ASpawnerMonster_TowerDefence>(pSpawnerRef))
		{
			pSpawner->StartSpawning(m_iCurLevel);
			pSpawner->OnWaveFinished.AddUObject(this, &AGameState_TowerDefence::WaveFinished);
		}
	}
}

void AGameState_TowerDefence::EndGame()
{
	m_curGameState = ERoundState::WaitingToStart;

	// 모든 객체가 뒤졌거나 게임 종료시 처리

}

void AGameState_TowerDefence::WaveFinished(bool isSurvive)
{
	if (isSurvive)
		WaitRound();
	else
		EndGame();
}

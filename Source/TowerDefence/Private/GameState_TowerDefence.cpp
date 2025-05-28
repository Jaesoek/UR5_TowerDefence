#include "GameState_TowerDefence.h"
#include "EngineUtils.h"
#include "TimerManager.h"

AGameState_TowerDefence::AGameState_TowerDefence()
	: m_fRoundWaitTime(2.f)
	, m_iCurLevel(0)
{
}

void AGameState_TowerDefence::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	WaitRound();
}

void AGameState_TowerDefence::WaitRound()
{
	SetGameState(ERoundState::Round_Waiting);

	FTimerHandle TimerHandle_StartRound;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_StartRound,
		this,
		&AGameState_TowerDefence::StartRound,
		m_fRoundWaitTime,
		false
	);
}

void AGameState_TowerDefence::StartRound()
{
	m_iCurLevel += 1;

	SetGameState(ERoundState::Round_InProgress);
}

void AGameState_TowerDefence::EndGame()
{
	SetGameState(ERoundState::Round_Waiting);
}

void AGameState_TowerDefence::WaveFinished(bool isSurvive)
{
	if (isSurvive)
	{
		WaitRound();
	}		
	else
	{
		EndGame();
	}
}

void AGameState_TowerDefence::SetGameState(ERoundState InRoundState)
{
	if (m_curRoundState != InRoundState)
	{
		m_curRoundState = InRoundState;

		if (OnStateChangedEvent[(uint8)m_curRoundState].IsBound())
		{
			OnStateChangedEvent[(uint8)m_curRoundState].Broadcast();
		}
	}
}

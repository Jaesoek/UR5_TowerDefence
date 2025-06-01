#include "GameState_TowerDefence.h"
#include "EngineUtils.h"
#include "TimerManager.h"

AGameState_TowerDefence::AGameState_TowerDefence()
	: m_fRoundWaitTime{ 2.f }
	, m_iCurLevel{ 0 }
	, m_iRemainNum_Monsters{ 0 }
	, m_curRoundState{ ERoundState::Default }
{
}

void AGameState_TowerDefence::WaitRound()
{
	if (false == HasAuthority())
		return;

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
	if (false == HasAuthority())
		return;

	m_iCurLevel += 1;

	SetGameState(ERoundState::Round_InProgress);
}

void AGameState_TowerDefence::EndGame()
{
	if (false == HasAuthority())
		return;

	SetGameState(ERoundState::Round_Finished);
}

void AGameState_TowerDefence::SetGameState(ERoundState InRoundState)
{
	if (false == HasAuthority())
		return;

	if (m_curRoundState != InRoundState)
	{
		m_curRoundState = InRoundState;

		if (OnStateChangedEvent[(uint8)m_curRoundState].IsBound())
		{
			OnStateChangedEvent[(uint8)m_curRoundState].Broadcast();
		}
	}
}

void AGameState_TowerDefence::SetMonsterNum(int32 iNumMonsters)
{
	if (HasAuthority())
	{
		m_iRemainNum_Monsters = iNumMonsters;
	}
}

void AGameState_TowerDefence::DecreaseMonster()
{
	if (HasAuthority())
	{
		--m_iRemainNum_Monsters;
	}

	if (m_iRemainNum_Monsters == 0)
	{
		WaitRound();
	}
}

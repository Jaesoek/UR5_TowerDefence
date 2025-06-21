#include "GameState_TowerDefence.h"
#include "EngineUtils.h"
#include "TimerManager.h"
#include "UI/UI_Manager.h"

AGameState_TowerDefence::AGameState_TowerDefence()
	: m_iCurLevel(-1)
	, m_curRoundState{ ERoundState::Default }
	, m_iRemainNum_Monsters(0)
	, m_fRoundWaitTime(2.f)
{
}

void AGameState_TowerDefence::StartRound()
{
	if (false == HasAuthority())
		return;

	m_iCurLevel += 1;

	if (UUI_Manager* pUIManager = GetGameInstance()->GetSubsystem<UUI_Manager>())
	{
		pUIManager->OpenInProgress();
	}
}

void AGameState_TowerDefence::SetGameState(ERoundState InRoundState)
{
	if (false == HasAuthority())
		return;

	switch (InRoundState)	// Doing Job in GameState
	{
		case ERoundState::Round_InProgress:
			StartRound();
			break;
	}

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
		OnMonsterNumChanged.Broadcast(m_iRemainNum_Monsters);
	}
}

void AGameState_TowerDefence::DecreaseMonster()
{
	if (HasAuthority())
	{
		--m_iRemainNum_Monsters;
		OnMonsterNumChanged.Broadcast(m_iRemainNum_Monsters);
	}

	if (m_iRemainNum_Monsters == 0)
	{
		// TODO: Stage finish
	}
}

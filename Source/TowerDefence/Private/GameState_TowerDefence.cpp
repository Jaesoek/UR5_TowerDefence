#include "GameState_TowerDefence.h"
#include "EngineUtils.h"
#include "TimerManager.h"
#include "UI/UI_Manager.h"
#include "Net/UnrealNetwork.h"

AGameState_TowerDefence::AGameState_TowerDefence()
	: m_iCurLevel(-1)
	, m_curRoundState{ ERoundState::Default }
	, m_iRemainNum_Monsters(0)
	, m_fRoundWaitTime(2.f)
{
}

void AGameState_TowerDefence::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameState_TowerDefence, m_iCurLevel);
	DOREPLIFETIME(AGameState_TowerDefence, m_curRoundState);
	DOREPLIFETIME(AGameState_TowerDefence, m_iRemainNum_Monsters);
}

void AGameState_TowerDefence::OnRep_RoundState()
{
	switch (m_curRoundState)	// Doing Client Job
	{
	case ERoundState::Round_Waiting:
		if (UUI_Manager* pUIManager = GetGameInstance()->GetSubsystem<UUI_Manager>())
		{
			pUIManager->OpenWait();
		}
		break;
	case ERoundState::Round_InProgress:
		if (UUI_Manager* pUIManager = GetGameInstance()->GetSubsystem<UUI_Manager>())
		{
			pUIManager->OpenInProgress();
		}
		break;
	}
}

void AGameState_TowerDefence::OnRep_MonsterNum()
{
	OnMonsterNumChanged.Broadcast(m_iRemainNum_Monsters);
}

void AGameState_TowerDefence::SetGameState(ERoundState InRoundState)
{
	if (false == HasAuthority())
		return;

	if (m_curRoundState != InRoundState)
	{
		m_curRoundState = InRoundState;

		switch (m_curRoundState)	// Doing Server Job
		{
		case ERoundState::Round_InProgress:
			m_iCurLevel += 1;
			break;
		}

		if (OnStateChangedEvent[(uint8)m_curRoundState].IsBound())
		{
			OnStateChangedEvent[(uint8)m_curRoundState].Broadcast();
		}
	}
}

void AGameState_TowerDefence::AddMonster()
{
	if (HasAuthority())
	{
		++m_iRemainNum_Monsters;
	}
}

void AGameState_TowerDefence::DecreaseMonster()
{
	if (HasAuthority())
	{
		--m_iRemainNum_Monsters;

		if (m_iRemainNum_Monsters == 0)
		{
			// TODO: Stage finish
		}
	}
}

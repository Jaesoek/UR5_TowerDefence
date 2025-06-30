// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget_InProgress.h"
#include "GameState_TowerDefence.h"
#include "Player/PlayerState_TowerDefence.h"

void UWidget_InProgress::NativeConstruct()
{
	Super::NativeConstruct();

	AGameState_TowerDefence* pGameState = GetWorld()->GetGameState<AGameState_TowerDefence>();

	pGameState->RegistEvent_MonsterNumChanged(this, &UWidget_InProgress::MonsterNumChanged);
	m_iRemainNum = pGameState->GetMonsterNum();

	APlayerState_TowerDefence* pPlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState_TowerDefence>();
	pPlayerState->RegistEvent_ScoreChanged(this, &UWidget_InProgress::ScoreChanged);
	m_iCurScore = pPlayerState->GetCurScore();
}

void UWidget_InProgress::MonsterNumChanged(int32 iRemainNum)
{
	m_iRemainNum = iRemainNum;
}

void UWidget_InProgress::ScoreChanged(int32 iCurScore)
{
	m_iCurScore = iCurScore;
}


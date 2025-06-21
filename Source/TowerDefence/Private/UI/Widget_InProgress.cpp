// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget_InProgress.h"
#include "GameState_TowerDefence.h"

void UWidget_InProgress::NativeConstruct()
{
	Super::NativeConstruct();

	AGameState_TowerDefence* pGameState = GetWorld()->GetGameState<AGameState_TowerDefence>();

	pGameState->RegistEvent_MonsterNumChanged(this, &UWidget_InProgress::MonsterNumChanged);
	m_iRemainNum = pGameState->GetMonsterNum();
}

void UWidget_InProgress::MonsterNumChanged(int32 iRemainNum)
{
	m_iRemainNum = iRemainNum;
}


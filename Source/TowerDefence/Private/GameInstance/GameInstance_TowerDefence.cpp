// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/GameInstance_TowerDefence.h"
#include "UI/UIAsset.h"
#include "UI/UI_Manager.h"


void UGameInstance_TowerDefence::Init()
{
	Super::Init();

	if (UUI_Manager* UISubsystem = GetSubsystem<UUI_Manager>())
	{
		if (IsValid(UISettings))
		{
			UISubsystem->UI_Asset = UISettings;
		}
	}
}




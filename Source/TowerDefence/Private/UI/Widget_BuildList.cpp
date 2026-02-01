// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget_BuildList.h"
#include "UI/CustomImageBtn.h"
#include "Animation/WidgetAnimation.h"
#include "PlayerController_TowerDefence.h"
#include "Components/Button.h"

void UWidget_BuildList::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Button가져와서 처리하자
}

void UWidget_BuildList::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(BoxAppear))
	{
		UUMGSequencePlayer* Player = PlayAnimation(BoxAppear);
		if (Player)
		{
			Player->OnSequenceFinishedPlaying().AddUObject(this, &ThisClass::PlayContentAppear);
		}
	}

	// 
	BtnArray.Add(Button_0);
	BtnArray.Add(Button_1);
	BtnArray.Add(Button_2);

	for (int32 i = 0; i < 3; ++i)
	{
		BtnArray[i]->OnClicked.AddDynamic(this, &UWidget_BuildList::OnBtnClicked);
	}
}

void UWidget_BuildList::PlayContentAppear(UUMGSequencePlayer& Player)
{
	if (ContentAppear)
	{
		PlayAnimation(ContentAppear);
	}
}

void UWidget_BuildList::OnBtnClicked()
{
	for (int32 i = 0; i < BtnArray.Num(); ++i)
	{
		if (BtnArray[i]->HasKeyboardFocus())
		{
			if (auto pLocalPC = Cast<APlayerController_TowerDefence>(GetWorld()->GetFirstPlayerController()))
			{
				//pLocalPC->ReadyToSpawnTower(TowerTable.Get()->GetImplementingOuter<>);
			}
		}
	}
}

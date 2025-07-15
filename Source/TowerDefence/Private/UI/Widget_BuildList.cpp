// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget_BuildList.h"
#include "Animation/WidgetAnimation.h"

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
}

void UWidget_BuildList::PlayContentAppear(UUMGSequencePlayer& Player)
{
	if (ContentAppear)
	{
		PlayAnimation(ContentAppear);
	}
}

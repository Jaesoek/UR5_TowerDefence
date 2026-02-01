// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem_UI_SC_Test.h"
#include "UI/UIAsset.h"
#include "Blueprint/UserWidget.h"

bool USubSystem_UI_SC_Test::ShouldCreateSubsystem(UObject* Outer) const
{
	// Only create on client side
	if (const UGameInstance* GameInstance = Cast<UGameInstance>(Outer))
	{
		UWorld* World = GameInstance->GetWorld();
		if (World && (World->GetNetMode() == NM_Client || World->GetNetMode() == NM_Standalone))
		{
			return true;
		}
	}
	return false;
}

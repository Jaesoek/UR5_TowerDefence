// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UI_Manager.h"
#include "UI/UIAsset.h"
#include "Blueprint/UserWidget.h"

bool UUI_Manager::ShouldCreateSubsystem(UObject* Outer) const
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

void UUI_Manager::OpenLogo()
{
	if (!IsValid(UI_Asset) || !UI_Asset->UI_Logo) return;

	OpenUI(UI_Asset->UI_Logo);
}

void UUI_Manager::OpenInProgress()
{
	if (!IsValid(UI_Asset) || !UI_Asset->UI_InProgress) return;

	OpenUI(UI_Asset->UI_InProgress);
}

void UUI_Manager::OpenUI(TSubclassOf<UUserWidget> userWidget)
{
	if (UWorld* World = GetWorld())
	{
		if (IsValid(CurrentWidget))
		{
			CurrentWidget->RemoveFromViewport();
		}

		CurrentWidget = CreateWidget<UUserWidget>(World, userWidget);
		CurrentWidget->AddToViewport();
	}
}



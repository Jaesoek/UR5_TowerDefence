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

void UUI_Manager::OpenWait()
{
	if (!IsValid(UI_Asset) || !UI_Asset->UI_Wait) return;

	OpenUI(UI_Asset->UI_Wait);
}

void UUI_Manager::OpenInProgress()
{
	if (!IsValid(UI_Asset) || !UI_Asset->UI_InProgress) return;

	OpenUI(UI_Asset->UI_InProgress);
}

FString UUI_Manager::OpenBuildList()
{
	if (!IsValid(UI_Asset) || !UI_Asset->UI_BuildList) return TEXT("");

	OpenUIWith(UI_Asset->UI_BuildList);
	return UI_Asset->UI_BuildList->GetName();
}

void UUI_Manager::DisableUI(FString KeyUI)
{
	if (UWorld* World = GetWorld())
	{
		if (nullptr == OpenWidgets.Find(KeyUI))
		{
			return;
		}

		if (OpenWidgets[KeyUI]->IsInViewport())
		{
			OpenWidgets[KeyUI]->RemoveFromViewport();
		}
	}
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

void UUI_Manager::OpenUIWith(TSubclassOf<UUserWidget> userWidget)
{
	if (UWorld* World = GetWorld())
	{
		if (nullptr == OpenWidgets.Find(userWidget->GetName()))
		{
			OpenWidgets.Emplace(
				userWidget->GetName(), CreateWidget<UUserWidget>(World, userWidget));
		}

		if (false == OpenWidgets[userWidget->GetName()]->IsInViewport())
		{
			OpenWidgets[userWidget->GetName()]->AddToViewport();
		}
	}
}

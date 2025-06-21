#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UIAsset.generated.h"

UCLASS()
class TOWERDEFENCE_API UUIAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI List")
	TSubclassOf<UUserWidget>	UI_Logo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI List")
	TSubclassOf<UUserWidget> UI_Wait;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI List")
	TSubclassOf<UUserWidget> UI_InProgress;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI List")
	TSubclassOf<UUserWidget> UI_Result;
};

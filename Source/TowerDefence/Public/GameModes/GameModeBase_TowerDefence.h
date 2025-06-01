// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBase_TowerDefence.generated.h"

class UStageAsset;

UCLASS()
class TOWERDEFENCE_API AGameModeBase_TowerDefence : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UStageAsset> StageAsset;
};

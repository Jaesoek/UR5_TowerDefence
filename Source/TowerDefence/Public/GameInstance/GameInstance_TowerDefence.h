// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance_TowerDefence.generated.h"

class UUIAsset;

UCLASS()
class TOWERDEFENCE_API UGameInstance_TowerDefence : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Setting")
	TObjectPtr<UUIAsset> UISettings;

	virtual void Init() override;
};

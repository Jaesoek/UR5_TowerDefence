// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StageAsset.generated.h"

class UMonsterAsset;

USTRUCT(BlueprintType)
struct FStageWaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	TSoftObjectPtr<UMonsterAsset> MonsterAsset;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	int32 Count;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float SpawnInterval;
};

UCLASS(BlueprintType)
class TOWERDEFENCE_API UStageAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FStageWaveInfo> StageWaveInfos;
};

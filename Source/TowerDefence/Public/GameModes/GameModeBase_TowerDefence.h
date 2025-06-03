// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBase_TowerDefence.generated.h"

class UStageAsset;
class AGameState_TowerDefence;

UCLASS()
class TOWERDEFENCE_API AGameModeBase_TowerDefence : public AGameModeBase
{
	GENERATED_BODY()

public:
	// AGameModeBase Interface
	virtual void StartPlay() override;
	// ~AGameModeBase Interface

	virtual void StartRound_Waiting();
	virtual void StartRound_InProgress();
	virtual void StartRound_Finished();

	virtual void StartSpawnMonster();
	virtual void OnSpawnMonster();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UStageAsset> StageAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WatingTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InProgressTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FinishedTime;

	UPROPERTY(Transient)
	TObjectPtr<AGameState_TowerDefence> CachedGameState;

	UPROPERTY(Transient)
	TMap<FName, FTimerHandle> Timers;
};

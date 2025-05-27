// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameState_TowerDefence.generated.h"

UENUM()
enum class ERoundState : uint8
{
	WaitingToStart,
	RoundWaiting,
	RoundInProgress,
	RoundEnded
};

UCLASS()
class TOWERDEFENCE_API AGameState_TowerDefence : public AGameState
{
	GENERATED_BODY()
	
public:
	AGameState_TowerDefence();

protected:
	void HandleMatchHasStarted() override;

public:
	void WaitRound();	// Test 용으로 열어놓음
protected:
	void StartRound();
	void EndGame();

public:
	void WaveFinished(bool isSurvive);

protected:
	UPROPERTY(BlueprintReadOnly)
	ERoundState m_curGameState;
	
	FTimerHandle m_TimerHandle_StartRound;

	TArray<AActor*> m_arrSpawners;


protected:
	UPROPERTY(EditDefaultsOnly, meta = ())
	float m_fRoundWaitTime = 2.f;

	int32 m_iCurLevel = 0;
};

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
	RoundEnded,
	RoundMax
};

UCLASS()
class TOWERDEFENCE_API AGameState_TowerDefence : public AGameState
{
	GENERATED_BODY()
	
public:
	AGameState_TowerDefence();

	virtual void WaitRound();

protected:
	// GameState Interface
	virtual void HandleMatchHasStarted() override;
	// ~GameState Interface

	virtual void StartRound();
	virtual void EndGame();
	virtual void WaveFinished(bool isSurvive);
	virtual void SetGameState(ERoundState InRoundState);

	UPROPERTY(BlueprintReadOnly)
	ERoundState m_curGameState;
	
	UPROPERTY(Transient)
	TArray<AActor*> m_arrSpawners;

	UPROPERTY(EditDefaultsOnly)
	float m_fRoundWaitTime;

	UPROPERTY(Transient)
	int32 m_iCurLevel;

	DECLARE_MULTICAST_DELEGATE(FOnStateChanged)
	FOnStateChanged OnStateChangedEvent[4];

	DECLARE_MULTICAST_DELEGATE(FOnStartRound)
	FOnStartRound OnStartRoundEvent;

public:
	FOnStartRound GetStartRoundEvent() { return OnStartRoundEvent;	}
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameState_TowerDefence.generated.h"

UENUM()
enum class ERoundState : uint8
{
	Round_Waiting,
	Round_InProgress,
	Round_Finished,
	RoundMAX
};

UCLASS()
class TOWERDEFENCE_API AGameState_TowerDefence : public AGameState
{
	GENERATED_BODY()
	
public:
	AGameState_TowerDefence();

protected:
	// GameState Interface
	virtual void HandleMatchHasStarted() override;
	// ~GameState Interface

	virtual void WaitRound();
	virtual void StartRound();
	virtual void EndGame();
	virtual void WaveFinished(bool isSurvive);
	virtual void SetGameState(ERoundState InRoundState);

	UPROPERTY(Transient)
	int32 m_iCurLevel;

	UPROPERTY(BlueprintReadOnly)
	ERoundState m_curRoundState;

	UPROPERTY(EditDefaultsOnly, Category = "Round Rule Setting")
	float m_fRoundWaitTime;


	DECLARE_MULTICAST_DELEGATE(FOnStartRound)
	FOnStartRound OnStartRoundEvent;

	DECLARE_MULTICAST_DELEGATE(FOnStateChanged)
	FOnStateChanged OnStateChangedEvent[(uint8)ERoundState::RoundMAX];

public:
	FOnStartRound GetStartRoundEvent() { return OnStartRoundEvent; }
	FOnStateChanged GetStateChanged(ERoundState roundState) { return OnStateChangedEvent[(uint8)roundState]; }
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameState_TowerDefence.generated.h"

UENUM()
enum class ERoundState : uint8
{
	Default,
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

	virtual void SetGameState(ERoundState InRoundState);
	
	UPROPERTY(Transient)
	int32 m_iCurLevel;

	UPROPERTY(Transient)
	ERoundState m_curRoundState;

	UPROPERTY(Transient)
	int32 m_iRemainNum_Monsters;

	UPROPERTY(EditDefaultsOnly, Category = "Round Rule Setting")
	float m_fRoundWaitTime;

public:
	void SetMonsterNum(int32 iNumMonsters);
	void DecreaseMonster();


protected:
	DECLARE_MULTICAST_DELEGATE(FOnStateChanged)
	FOnStateChanged OnStateChangedEvent[(uint8)ERoundState::RoundMAX];

public:
	FOnStateChanged& GetStateChanged(ERoundState roundState) { return OnStateChangedEvent[(uint8)roundState]; }

	FOnStateChanged& GetWaitRoundEvent() { return OnStateChangedEvent[(uint8)ERoundState::Round_Waiting]; }
	FOnStateChanged& GetStartRoundEvent() { return OnStateChangedEvent[(uint8)ERoundState::Round_InProgress]; }
	FOnStateChanged& GetFinishRoundEvent() { return OnStateChangedEvent[(uint8)ERoundState::Round_Finished]; }
};

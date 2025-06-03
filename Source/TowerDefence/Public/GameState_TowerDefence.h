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
class TOWERDEFENCE_API AGameState_TowerDefence : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AGameState_TowerDefence();

	virtual void SetGameState(ERoundState InRoundState);
	FORCEINLINE virtual int32 GetCurrentLevel() { return m_iCurLevel; }

protected:
	// GameState Interface
	// ~GameState Interface

	virtual void WaitRound();
	virtual void StartRound();
	virtual void EndGame();

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
	template <typename UserClass>
	void RegistEvent_StartRound(UserClass* InObject, typename TMemFunPtrType<false, UserClass, void()>::Type InFunc)
	{
		OnStateChangedEvent[(uint8)ERoundState::Round_InProgress].AddUObject(InObject, InFunc);
	}
};

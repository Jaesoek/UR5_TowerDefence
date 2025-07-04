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

class UUI_Manager;

UCLASS()
class TOWERDEFENCE_API AGameState_TowerDefence : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AGameState_TowerDefence();

	virtual void SetGameState(ERoundState InRoundState);
	FORCEINLINE virtual int32 GetCurrentLevel() { return m_iCurLevel; }

	int32 GetMonsterNum() const { return m_iRemainNum_Monsters; }
	void AddMonster();
	void DecreaseMonster();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_RoundState();

	UFUNCTION()
	void OnRep_MonsterNum();

	UPROPERTY(Transient, Replicated)
	int32 m_iCurLevel;

	UPROPERTY(Transient, Replicated, ReplicatedUsing = OnRep_RoundState)
	ERoundState m_curRoundState;

	UPROPERTY(Transient, Replicated, ReplicatedUsing = OnRep_MonsterNum)
	int32 m_iRemainNum_Monsters;

	UPROPERTY(EditDefaultsOnly, Category = "Round Rule Setting")
	float m_fRoundWaitTime;


protected:
	DECLARE_MULTICAST_DELEGATE(FOnStateChanged)
	FOnStateChanged OnStateChangedEvent[(uint8)ERoundState::RoundMAX];

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnMonsterNumChanged, int32)
	FOnMonsterNumChanged OnMonsterNumChanged;

public:
	template <typename UserClass>
	void RegistEvent_MonsterNumChanged(UserClass* InObject, typename TMemFunPtrType<false, UserClass, void(int32)>::Type InFunc)
	{
		OnMonsterNumChanged.AddUObject(InObject, InFunc);
	}

	template <typename UserClass>
	void RegistEvent_WaitingRound(UserClass* InObject, typename TMemFunPtrType<false, UserClass, void()>::Type InFunc)
	{
		OnStateChangedEvent[(uint8)ERoundState::Round_Waiting].AddUObject(InObject, InFunc);
	}

	template <typename UserClass>
	void RegistEvent_StartRound(UserClass* InObject, typename TMemFunPtrType<false, UserClass, void()>::Type InFunc)
	{
		OnStateChangedEvent[(uint8)ERoundState::Round_InProgress].AddUObject(InObject, InFunc);
	}

	template <typename UserClass>
	void RegistEvent_FinishRound(UserClass* InObject, typename TMemFunPtrType<false, UserClass, void()>::Type InFunc)
	{
		OnStateChangedEvent[(uint8)ERoundState::Round_Finished].AddUObject(InObject, InFunc);
	}
};

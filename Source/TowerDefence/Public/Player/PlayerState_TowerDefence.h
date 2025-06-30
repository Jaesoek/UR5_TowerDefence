// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerState_TowerDefence.generated.h"

UCLASS()
class TOWERDEFENCE_API APlayerState_TowerDefence : public APlayerState
{
	GENERATED_BODY()

public:
	APlayerState_TowerDefence();

	void AddScore(int32 iScore);

	FORCEINLINE int32 GetCurScore() const { return CurScore; }
	FORCEINLINE int32 GetCurHealth() const { return CurHealth; }

protected:
	virtual void PostLoad() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_ScoreEdit();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Info")
	int32 MaxHealth;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_ScoreEdit)
	int32 CurScore;

	UPROPERTY(Transient)
	int32 CurHealth;


protected:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32)
	FOnScoreChanged OnScoreChanged;

public:
	template <typename UserClass>
	void RegistEvent_ScoreChanged(UserClass* InObject, typename TMemFunPtrType<false, UserClass, void(int32)>::Type InFunc)
	{
		OnScoreChanged.AddUObject(InObject, InFunc);
	}
};

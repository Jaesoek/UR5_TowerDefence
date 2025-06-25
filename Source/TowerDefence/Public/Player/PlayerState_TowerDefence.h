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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Info")
	int32 MaxHealth;

	UPROPERTY(Transient)
	int32 CurScore;

	UPROPERTY(Transient)
	int32 CurHealth;
};

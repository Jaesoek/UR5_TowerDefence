// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase_TowerDefence.generated.h"

class UMonsterAsset;

UCLASS()
class TOWERDEFENCE_API AMonsterBase_TowerDefence : public ACharacter
{
	GENERATED_BODY()

public:
	AMonsterBase_TowerDefence();

	virtual void SetupAsset(const UMonsterAsset* InMonsterAsset);

	FORCEINLINE TObjectPtr<UMonsterAsset> GetMonsterAsset() const { return MonsterAsset; }
protected:
	virtual void Destroyed() override;

	UPROPERTY(Transient)
	TObjectPtr<UMonsterAsset> MonsterAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float Health;
};

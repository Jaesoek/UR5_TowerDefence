// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/CombatType.h"
#include "MonsterAsset.generated.h"

UCLASS()
class TOWERDEFENCE_API UMonsterAsset : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Monster")
	FString MonsterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Monster")
	TSoftObjectPtr<USkeletalMesh> MonsterMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Monster")
	int Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Monster")
	int Armor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Monster")
	EArmorType ArmorType;
};

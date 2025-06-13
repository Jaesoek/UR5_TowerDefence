// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"	// For forward declaration
#include "Engine/DataAsset.h"
#include "Types/CombatType.h"
#include "MonsterAsset.generated.h"

class AMonsterBase_TowerDefence;

UCLASS()
class TOWERDEFENCE_API UMonsterAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visible")
	TSubclassOf<AMonsterBase_TowerDefence> MonsterClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visible")
	FString MonsterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visible")
	TSoftObjectPtr<USkeletalMesh> MonsterMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	int Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	int Armor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	EArmorType ArmorType;
};

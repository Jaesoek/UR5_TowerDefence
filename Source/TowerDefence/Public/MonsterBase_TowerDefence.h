// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase_TowerDefence.generated.h"

UCLASS()
class TOWERDEFENCE_API AMonsterBase_TowerDefence : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase_TowerDefence();

protected:
	virtual void Destroyed() override;
};

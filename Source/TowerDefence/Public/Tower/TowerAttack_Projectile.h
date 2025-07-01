// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower/TowerAttackComponent.h"
#include "TowerAttack_Projectile.generated.h"

UCLASS()
class TOWERDEFENCE_API UTowerAttack_Projectile : public UTowerAttackComponent
{
	GENERATED_BODY()
	
public:
	virtual bool Attack(AActor* pTarget) override;
	
};

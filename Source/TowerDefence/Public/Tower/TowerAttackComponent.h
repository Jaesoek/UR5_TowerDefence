// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tower/TowerInclude.h"
#include "TowerAttackComponent.generated.h"


class ATowerBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENCE_API UTowerAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTowerAttackComponent();

	virtual bool Attack(AActor* pTarget);

protected:
	void SetState(ETowerState newState);
	bool HasAuthority();
	ATowerBase* GetTower();
};

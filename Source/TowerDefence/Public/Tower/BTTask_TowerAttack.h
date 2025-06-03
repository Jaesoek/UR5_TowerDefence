// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_FinishWithResult.h"
#include "BTTask_TowerAttack.generated.h"

UCLASS()
class TOWERDEFENCE_API UBTTask_TowerAttack : public UBTTask_FinishWithResult
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	
	
};

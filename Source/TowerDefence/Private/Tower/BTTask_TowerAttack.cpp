// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/BTTask_TowerAttack.h"
#include "Tower/TowerBase.h"
#include "Tower/AIController_Tower.h"

EBTNodeResult::Type UBTTask_TowerAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController_Tower* aiControl = Cast<AAIController_Tower>(OwnerComp.GetAIOwner());
	if (!IsValid(aiControl))
	{
		return EBTNodeResult::Failed;
	}

	ATowerBase* controlledPawn = aiControl->GetPawn<ATowerBase>();
	if (!IsValid(controlledPawn))
	{
		return EBTNodeResult::Failed;
	}

	AActor* pTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetObject")));
	if (controlledPawn->Attack(pTarget))
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}




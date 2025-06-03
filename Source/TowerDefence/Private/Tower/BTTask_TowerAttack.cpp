// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/BTTask_TowerAttack.h"
#include "Tower/BaseTower.h"
#include "Tower/AIController_Tower.h"

EBTNodeResult::Type UBTTask_TowerAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController_Tower* aiControl = Cast<AAIController_Tower>(OwnerComp.GetAIOwner());
	if (!IsValid(aiControl))
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 1.0f, FColor::Green,
			TEXT("Something wrong")
		);

		return EBTNodeResult::Failed;
	}

	ABaseTower* controlledPawn = aiControl->GetPawn<ABaseTower>();
	if (!IsValid(controlledPawn))
	{
		return EBTNodeResult::Failed;
	}

	if (controlledPawn->Attack())
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}




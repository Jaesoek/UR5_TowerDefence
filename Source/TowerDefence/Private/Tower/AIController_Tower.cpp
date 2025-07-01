// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/AIController_Tower.h"
#include "BehaviorTree/BehaviorTree.h"


void AAIController_Tower::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (m_BehaviorTree)
	{
		RunBehaviorTree(m_BehaviorTree);
	}
}
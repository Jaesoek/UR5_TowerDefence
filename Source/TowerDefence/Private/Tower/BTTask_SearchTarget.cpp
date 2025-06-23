// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/BTTask_SearchTarget.h"
#include "Tower/TowerBase.h"
#include "Engine/OverlapResult.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterBase_TowerDefence.h"

UBTTask_SearchTarget::UBTTask_SearchTarget()
{
	NodeName = "Search Monster Target";
}

EBTNodeResult::Type UBTTask_SearchTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	ATowerBase* AIPawn = AICon ? AICon->GetPawn<ATowerBase>() : nullptr;
	if (!IsValid(AIPawn))
	{
		return EBTNodeResult::Type::Failed;
	}

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(AIPawn);

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

	bool bHasOverlap = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		AIPawn->GetActorLocation(),
		FQuat::Identity,
		ObjectQueryParams,
		FCollisionShape::MakeSphere(AIPawn->GetAttackRange()),
		Params
	);

	DrawDebugSphere(
		GetWorld(),
		AIPawn->GetActorLocation(),
		AIPawn->GetAttackRange(),
		12,
		FColor::Red,
		false,
		1.0f
	);


	if (bHasOverlap)
	{
		for (const FOverlapResult& Result : OverlapResults)
		{
			AMonsterBase_TowerDefence* Target = Cast<AMonsterBase_TowerDefence>(Result.GetActor());
			if (IsValid(Target))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetObject"), Target);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetPos"), Target->GetActorLocation());
				return EBTNodeResult::Type::Succeeded;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetObject"), nullptr);
	return EBTNodeResult::Type::Failed;
}

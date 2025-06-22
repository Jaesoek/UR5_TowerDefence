// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/BTService_SearchTarget.h"
#include "Tower/TowerBase.h"
#include "Engine/OverlapResult.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/MonsterBase_TowerDefence.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("Check Monster In Range");
	bNotifyTick = true;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	ATowerBase* AIPawn = AICon ? AICon->GetPawn<ATowerBase>() : nullptr;
	if (!AIPawn)
	{
		return;
	}

	AActor* pTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetObject")));
	if (pTarget != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetPos"), pTarget->GetActorLocation());

		if (FVector::DistSquaredXY(AIPawn->GetActorLocation(), pTarget->GetActorLocation()) < AIPawn->GetAttackRange() * AIPawn->GetAttackRange())
		{
			return;
		}
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

	if (bHasOverlap)
	{
		bool didSet = false;
		for (const FOverlapResult& Result : OverlapResults)
		{
			AMonsterBase_TowerDefence* Target = Cast<AMonsterBase_TowerDefence>(Result.GetActor());
			if (IsValid(Target))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetObject"), Target);
				didSet = true;
				break;
			}
		}

		if (!didSet)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetObject"), nullptr);
		}
	}
}




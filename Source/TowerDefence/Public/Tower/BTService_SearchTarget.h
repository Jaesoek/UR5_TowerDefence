// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SearchTarget.generated.h"

UCLASS()
class TOWERDEFENCE_API UBTService_SearchTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_SearchTarget();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};

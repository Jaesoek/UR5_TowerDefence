// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Tower.generated.h"

UCLASS()
class TOWERDEFENCE_API AAIController_Tower : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, Category = "AI Setting")
	TObjectPtr<class UBehaviorTree> m_BehaviorTree;

};

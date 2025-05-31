// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "InputTriggerEdgeCheck.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API UInputTriggerEdgeCheck : public UInputTrigger
{
	GENERATED_BODY()
	
public:
	UInputTriggerEdgeCheck();

protected:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Transient)
	float EdgeThreshold;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "InputTriggerEdgeCheck.h"

ETriggerState UInputTriggerEdgeCheck::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
	ETriggerState State = Super::UpdateState_Implementation(PlayerInput, ModifiedValue, DeltaTime);
	
	return IsActuated(ModifiedValue) ? ETriggerState::Triggered : ETriggerState::None;
}

bool UInputTriggerEdgeCheck::GetMousePosition(float& fLocationX, float& fLocationY)
{

	return false;
}

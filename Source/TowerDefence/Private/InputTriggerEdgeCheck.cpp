// Fill out your copyright notice in the Description page of Project Settings.


#include "InputTriggerEdgeCheck.h"

#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Framework/Application/SlateApplication.h"

UInputTriggerEdgeCheck::UInputTriggerEdgeCheck()
	: EdgeThreshold{ 20.f }
{
}

ETriggerState UInputTriggerEdgeCheck::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
	if (!GEngine || !GEngine->GameViewport) return ETriggerState::None;

	FVector2D MousePos{};
	GEngine->GameViewport->GetMousePosition(MousePos);
	FVector2D ViewportSize{};
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	const bool bNearLeft = MousePos.X <= EdgeThreshold;
	const bool bNearRight = MousePos.X >= ViewportSize.X - EdgeThreshold;
	const bool bNearTop = MousePos.Y <= EdgeThreshold;
	const bool bNearBottom = MousePos.Y >= ViewportSize.Y - EdgeThreshold;

	const bool bTriggered = bNearLeft || bNearRight || bNearTop || bNearBottom;

	return bTriggered ? ETriggerState::Triggered : ETriggerState::None;
}

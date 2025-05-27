// Fill out your copyright notice in the Description page of Project Settings.


#include "InputComponent_MouseMoving.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UInputComponent_MouseMoving::UInputComponent_MouseMoving()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInputComponent_MouseMoving::BeginPlay()
{
	Super::BeginPlay();
	
}

bool UInputComponent_MouseMoving::EdgeChecking(FVector2D& v2MouseDir)
{
	float MouseX, MouseY;
	APlayerController* pController = Cast<APlayerController>(GetOwner());

	if (!IsValid(pController))
		return false;
	if (!pController->GetMousePosition(MouseX, MouseY))
		return false;

	int32 iViewportSizeX, iViewportSizeY;
	pController->GetViewportSize(iViewportSizeX, iViewportSizeY);

	const float EdgeThreshold = 20.0f;
	FVector2D CameraDirection = FVector2D::ZeroVector;

	if (MouseX <= EdgeThreshold)
		CameraDirection.X = -1.0f;
	else if (MouseX >= iViewportSizeX - EdgeThreshold)
		CameraDirection.X = 1.0f;

	if (MouseY <= EdgeThreshold)
		CameraDirection.Y = 1.0f;
	else if (MouseY >= iViewportSizeY - EdgeThreshold)
		CameraDirection.Y = -1.0f;

	if (CameraDirection.IsZero())
		return false;
	
	v2MouseDir = CameraDirection;

	return true;
}

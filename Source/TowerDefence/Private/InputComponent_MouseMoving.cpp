#include "InputComponent_MouseMoving.h"
#include "GameFramework/PlayerController.h"

UInputComponent_MouseMoving::UInputComponent_MouseMoving()
{
	PrimaryComponentTick.bCanEverTick = true;

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

#include "Player_TowerDefence.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayer_TowerDefence::APlayer_TowerDefence()
	: m_iPlayer_Hp{ 10 }
	, m_fCamSpeed{ 10 }
{
	SetCanBeDamaged(false);

	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	GetMovementComponent()->bComponentShouldUpdatePhysicsVolume = false;

	static FName CollisionProfileName(TEXT("Spectator"));
	GetCapsuleComponent()->SetCollisionProfileName(CollisionProfileName);
}

void APlayer_TowerDefence::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsLocallyControlled())
	{
		// Check Edge
		FVector2D vDirToMove{};
		if (CheckEdge(vDirToMove))
		{
			AddMovementInput({ vDirToMove.Y, vDirToMove.X, 0.f }, m_fCamSpeed);
		}
	}
}

bool APlayer_TowerDefence::CheckEdge(FVector2D& v2MouseDir)
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
#include "PlayerController_InGame.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Public/ControlUnit.h"

APlayerController_InGame::APlayerController_InGame()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCFinder_Spectator(TEXT("/Game/TowerDefence/Characters/IMC_Spectator"));
	if (IMCFinder_Spectator.Succeeded())
		m_pDefaultMappingContext = IMCFinder_Spectator.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IAFinder_MouseClick(TEXT("/Game/TowerDefence/Characters/IA_MouseClick_L"));
	if (IAFinder_MouseClick.Succeeded())
		m_pMouseClick = IAFinder_MouseClick.Object;
}

void APlayerController_InGame::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void APlayerController_InGame::SetupInputComponent()
{
	Super::SetupInputComponent();

	// IMC
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(m_pDefaultMappingContext, 0);

	// IA
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(m_pMouseClick, ETriggerEvent::Completed, this, &APlayerController_InGame::HandleMouseClick);
	}
}

void APlayerController_InGame::PlayerTick(float fDeltaTime)
{
	Super::PlayerTick(fDeltaTime);

	float MouseX, MouseY;
	if (!GetMousePosition(MouseX, MouseY))
		return;
	
	int32 iViewportSizeX, iViewportSizeY;
	GetViewportSize(iViewportSizeX, iViewportSizeY);

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

	if (!CameraDirection.IsZero())
		MoveCamera(CameraDirection, fDeltaTime);
}

void APlayerController_InGame::HandleMouseClick(const FInputActionValue& Value)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, false, HitResult);

	if (IsValid(m_pControlUnit.GetObject()))
	{
		m_pControlUnit->OnMoveTo(HitResult.Location);
	}
	else
	{
		if (HitResult.bBlockingHit)
		{
			m_pControlUnit = HitResult.GetActor();
			if (m_pControlUnit && m_pControlUnit.GetInterface() != nullptr)
				m_pControlUnit->OnFocused();
			else
				m_pControlUnit = nullptr;
		}
	}
}

void APlayerController_InGame::MoveCamera(FVector2D vMove, float fDeltaTime)
{
	GetPawn()->AddMovementInput({ vMove.Y, vMove.X, 0.f }, fDeltaTime);
}

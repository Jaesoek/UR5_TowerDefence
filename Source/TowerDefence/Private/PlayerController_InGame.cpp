#include "PlayerController_InGame.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


APlayerController_InGame::APlayerController_InGame()
{
}

void APlayerController_InGame::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = true;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APlayerController_InGame::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


}

void APlayerController_InGame::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MouseMoving, ETriggerEvent::Triggered, this, &APlayerController_InGame::HandleMouseMoving);
		EnhancedInputComponent->BindAction(MouseClick, ETriggerEvent::Completed, this, &APlayerController_InGame::HandleMouseClick);
	}
}

void APlayerController_InGame::HandleMouseMoving(const FInputActionValue& Value)
{
	FVector2D Delta = Value.Get<FVector2D>();
	AddYawInput(Delta.X);
	AddPitchInput(Delta.Y);
}

void APlayerController_InGame::HandleMouseClick(const FInputActionValue& Value)
{
}
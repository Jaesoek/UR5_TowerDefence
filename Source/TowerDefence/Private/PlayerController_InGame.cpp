#include "PlayerController_InGame.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


APlayerController_InGame::APlayerController_InGame()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCFinder_Spectator(TEXT("/Game/TowerDefence/Characters/IMC_Spectator"));
	if (IMCFinder_Spectator.Succeeded())
		m_pDefaultMappingContext = IMCFinder_Spectator.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IAFinder_MouseMove(TEXT("/Game/TowerDefence/Characters/IA_MouseMoving"));
	if (IAFinder_MouseMove.Succeeded())
		m_pMouseMoving = IAFinder_MouseMove.Object;

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

void APlayerController_InGame::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	m_pPossesedPawn = InPawn;
}

void APlayerController_InGame::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(m_pDefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(m_pMouseMoving, ETriggerEvent::Ongoing, this, &APlayerController_InGame::HandleMouseMoving);
		EnhancedInputComponent->BindAction(m_pMouseClick, ETriggerEvent::Completed, this, &APlayerController_InGame::HandleMouseClick);
	}
}

void APlayerController_InGame::HandleMouseMoving(const FInputActionValue& Value)
{
	if (!IsValid(m_pPossesedPawn))
	{
		m_pPossesedPawn = nullptr;
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("TEST mouse moving!!"));

	FVector2D vInput = Value.Get<FVector2D>();
	m_pPossesedPawn->AddMovementInput({ vInput.X, vInput.Y, 0.f });
}

void APlayerController_InGame::HandleMouseClick(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("TEST mouse click!!"));
}
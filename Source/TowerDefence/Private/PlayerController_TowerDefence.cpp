#include "PlayerController_TowerDefence.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Public/ControlUnit.h"
#include "../Public/InputComponent_MouseMoving.h"

APlayerController_TowerDefence::APlayerController_TowerDefence()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCFinder_Spectator(TEXT("/Game/TowerDefence/Characters/IMC_Spectator"));
	if (IMCFinder_Spectator.Succeeded())
		m_pDefaultMappingContext = IMCFinder_Spectator.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IAFinder_MouseClick(TEXT("/Game/TowerDefence/Characters/IA_MouseClick_L"));
	if (IAFinder_MouseClick.Succeeded())
		m_pMouseClick = IAFinder_MouseClick.Object;
	
	m_pInputComponent_MouseMoving = NewObject<UInputComponent_MouseMoving>(this, UInputComponent_MouseMoving::StaticClass(), TEXT("InputComp_EdgeCheck"));
	m_pInputComponent_MouseMoving->RegisterComponent();
	AddInstanceComponent(m_pInputComponent_MouseMoving);
}

void APlayerController_TowerDefence::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void APlayerController_TowerDefence::SetupInputComponent()
{
	Super::SetupInputComponent();

	// IMC
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(m_pDefaultMappingContext, 0);

	// IA
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(m_pMouseClick, ETriggerEvent::Completed, this, &APlayerController_TowerDefence::HandleMouseClick);
	}
}

void APlayerController_TowerDefence::PlayerTick(float fDeltaTime)
{
	Super::PlayerTick(fDeltaTime);
	
	FVector2D CameraDirection{};
	bool isEdgeChecked = m_pInputComponent_MouseMoving->EdgeChecking(CameraDirection);
	if (isEdgeChecked)
		MoveCamera(CameraDirection, fDeltaTime);
}

void APlayerController_TowerDefence::HandleMouseClick(const FInputActionValue& Value)
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

void APlayerController_TowerDefence::MoveCamera(FVector2D vMove, float fDeltaTime)
{
	GetPawn()->AddMovementInput({ vMove.Y, vMove.X, 0.f }, fDeltaTime * m_fCamspeed);
}

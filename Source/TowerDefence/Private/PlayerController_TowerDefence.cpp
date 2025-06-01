#include "PlayerController_TowerDefence.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Public/ControlUnit.h"
#include "../Public/Player_TowerDefence.h"

APlayerController_TowerDefence::APlayerController_TowerDefence()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCFinder_Spectator(TEXT("/Game/TowerDefence/Player/Input/IMC_Move"));
	if (IMCFinder_Spectator.Succeeded())
		m_pDefaultMappingContext = IMCFinder_Spectator.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IAFinder_MouseMove(TEXT("/Game/TowerDefence/Player/Input/IA_MouseMoving"));
	if (IAFinder_MouseMove.Succeeded())
		m_pIA_MouseMove = IAFinder_MouseMove.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IAFinder_MouseClick_L(TEXT("/Game/TowerDefence/Player/Input/IA_MouseClick_L"));
	if (IAFinder_MouseClick_L.Succeeded())
		m_pIA_MouseClick_L = IAFinder_MouseClick_L.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IAFinder_MouseClick_R(TEXT("/Game/TowerDefence/Player/Input/IA_MouseClick_R"));
	if (IAFinder_MouseClick_R.Succeeded())
		m_pIA_MouseClick_R = IAFinder_MouseClick_R.Object;
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
		EnhancedInputComponent->BindAction(m_pIA_MouseClick_L, ETriggerEvent::Completed, this, &APlayerController_TowerDefence::HandleMouseClick_L);
		EnhancedInputComponent->BindAction(m_pIA_MouseClick_R, ETriggerEvent::Completed, this, &APlayerController_TowerDefence::HandleMouseClick_R);
	}
}

void APlayerController_TowerDefence::HandleMouseClick_L(const FInputActionValue& Value)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, false, HitResult);
	if (!HitResult.bBlockingHit)
	{
		return;
	}

	if (IsValid(m_pControlUnit.GetObject()))
	{
		m_pControlUnit->OnMoveTo(HitResult.Location);
	}
}

void APlayerController_TowerDefence::HandleMouseClick_R(const FInputActionValue& Value)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, false, HitResult);
	if (!HitResult.bBlockingHit)
	{
		return;
	}

	IControlUnit* pControlUnit = Cast<IControlUnit>(HitResult.GetActor());
	if (nullptr != pControlUnit)
	{
		m_pControlUnit = HitResult.GetActor();
		if (m_pControlUnit && m_pControlUnit.GetInterface() != nullptr)
		{
			m_pControlUnit->OnFocused();
		}
		else
		{
			m_pControlUnit = nullptr;
		}
	}

}

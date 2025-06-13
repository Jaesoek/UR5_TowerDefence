#include "PlayerController_TowerDefence.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Public/ControlUnit.h"
#include "../Public/Player_TowerDefence.h"
#include "Kismet/GameplayStatics.h"
#include "LevelDesign/Grid.h"

APlayerController_TowerDefence::APlayerController_TowerDefence()
{
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
	{
		Subsystem->AddMappingContext(m_pDefaultMappingContext, 0);
	}

	// IA
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(m_pIA_SelectActor, ETriggerEvent::Completed, this, &APlayerController_TowerDefence::HandleSelectActor);
		EnhancedInputComponent->BindAction(m_pIA_MoveTo, ETriggerEvent::Completed, this, &APlayerController_TowerDefence::HandelMoveTo);
		EnhancedInputComponent->BindAction(m_pIA_Build, ETriggerEvent::Completed, this, &APlayerController_TowerDefence::HandelBuild);
	}
}

void APlayerController_TowerDefence::HandelMoveTo(const FInputActionValue& Value)
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

void APlayerController_TowerDefence::HandleSelectActor(const FInputActionValue& Value)
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

void APlayerController_TowerDefence::HandelBuild(const FInputActionValue& Value)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, false, HitResult);
	if (!HitResult.bBlockingHit)
	{
		return;
	}

	if (auto pGrid = Cast<AGrid>(HitResult.GetActor()))
	{
		FVector vResultPos;
		if (pGrid->AbleToBuild(HitResult.Location, vResultPos))
		{
			FTransform targetTrans = FTransform{ FRotator::ZeroRotator, vResultPos, FVector::One() };
			ATowerBase* pTower = GetWorld()->SpawnActorDeferred<ATowerBase>(
				ATowerBase::StaticClass(), targetTrans, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
			);
			pTower->SetTowerAsset(ArrayTowerAssets[0]);
			UGameplayStatics::FinishSpawningActor(pTower, targetTrans);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
				TEXT("Can't build in here"));
		}
	}
}

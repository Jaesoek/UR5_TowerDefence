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
	if (false == IsLocalController())	// Key input works only in client
	{
		return;
	}

	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, false, HitResult);
	if (!HitResult.bBlockingHit)
	{
		return;
	}

	if (IsValid(m_pControlUnit.GetObject()))
	{
		// No owner object can be controlled by server - 중요!
		Server_MoveControlUnit(Cast<AActor>(m_pControlUnit.GetObject()), HitResult.Location);
	}
}

void APlayerController_TowerDefence::HandleSelectActor(const FInputActionValue& Value)
{
	if (false == IsLocalController())	// Key input works only in client
	{
		return;
	}

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
	if (false == IsLocalController())	// Key input works only in client
	{
		return;
	}

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
			Server_SpawnTower(vResultPos);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
				TEXT("Can't build in here"));
		}
	}
}

void APlayerController_TowerDefence::Server_SpawnTower_Implementation(FVector vSpawnPos)
{
	if (false == HasAuthority())
	{
		return;
	}

	FTransform targetTrans = FTransform{ FRotator::ZeroRotator, vSpawnPos, FVector::One() };
	ATowerBase* pTower = GetWorld()->SpawnActorDeferred<ATowerBase>(
		ATowerBase::StaticClass(), targetTrans, this, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
	);
	pTower->SetupAsset(ArrayTowerAssets[0]);
	pTower->SetReplicates(true);
	UGameplayStatics::FinishSpawningActor(pTower, targetTrans);
}

void APlayerController_TowerDefence::Server_MoveControlUnit_Implementation(AActor* pControlUnit, FVector vTargetPos)
{
	if (IControlUnit* ControlUnit = Cast<IControlUnit>(pControlUnit))
	{
		ControlUnit->OnMoveTo(vTargetPos);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 1.f, FColor::Green, FString::Printf(TEXT("No nono"))
		);
	}
}
#include "CameraCharacter_TowerDefence.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACameraCharacter_TowerDefence::ACameraCharacter_TowerDefence()
{
	SetCanBeDamaged(false);

	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Collision
	GetMovementComponent()->bComponentShouldUpdatePhysicsVolume = false;

	static FName CollisionProfileName(TEXT("Spectator"));
	GetCapsuleComponent()->SetCollisionProfileName(CollisionProfileName);
}

void ACameraCharacter_TowerDefence::BeginPlay()
{
	Super::BeginPlay();

}

void ACameraCharacter_TowerDefence::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void ACameraCharacter_TowerDefence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

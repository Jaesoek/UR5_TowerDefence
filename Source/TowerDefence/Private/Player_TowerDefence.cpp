#include "Player_TowerDefence.h"
#include "../Public/AIControl_Player.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


APlayer_TowerDefence::APlayer_TowerDefence()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAIControl_Player::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void APlayer_TowerDefence::BeginPlay()
{
	Super::BeginPlay();

}

void APlayer_TowerDefence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayer_TowerDefence::OnFocused()
{
	// TODO: Render selected ring
}

void APlayer_TowerDefence::OnMoveTo(const FVector& vTargetPos)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), vTargetPos);
}
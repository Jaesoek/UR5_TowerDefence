#include "CommandUnit_TowerDefence.h"
#include "../Public/AIControl_Player.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


ACommandUnit_TowerDefence::ACommandUnit_TowerDefence()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAIControl_Player::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ACommandUnit_TowerDefence::OnFocused()
{
	// TODO: Render selected ring
}

void ACommandUnit_TowerDefence::OnMoveTo(const FVector& vTargetPos)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), vTargetPos);
}
#include "CommandUnit_TowerDefence.h"
#include "../Public/AIControl_Player.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Net/UnrealNetwork.h"


ACommandUnit_TowerDefence::ACommandUnit_TowerDefence()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	AIControllerClass = AAIControl_Player::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ACommandUnit_TowerDefence::OnFocused()
{
	// TODO: Render selected ring or UI
}

void ACommandUnit_TowerDefence::OnMoveTo(const FVector& vTargetPos)
{
	if (HasAuthority())
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), vTargetPos);
	}
}
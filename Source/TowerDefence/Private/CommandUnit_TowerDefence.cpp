#include "CommandUnit_TowerDefence.h"
#include "Utils/TDLogChannel.h"
#include "AIControl_Player.h"
#include "UI/UI_Manager.h"

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
	// TODO: Render selected ring
	if (UUI_Manager* pUIManager = GetGameInstance()->GetSubsystem<UUI_Manager>())
	{
		KeyUI = pUIManager->OpenBuildList();
	}
}

void ACommandUnit_TowerDefence::OnUnFocused()
{
	if (UUI_Manager* pUIManager = GetGameInstance()->GetSubsystem<UUI_Manager>())
	{
		pUIManager->DisableUI(KeyUI);
	}
}

void ACommandUnit_TowerDefence::OnMoveTo(const FVector& vTargetPos)
{
	if (HasAuthority())
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), vTargetPos);
	}
}
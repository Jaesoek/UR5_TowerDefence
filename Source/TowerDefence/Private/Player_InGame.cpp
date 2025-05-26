#include "Player_InGame.h"
#include "../Public/AIControl_Player.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


APlayer_InGame::APlayer_InGame()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAIControl_Player::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void APlayer_InGame::BeginPlay()
{
	Super::BeginPlay();

}

void APlayer_InGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayer_InGame::OnFocused()
{
	// TODO: Render selected ring
}

void APlayer_InGame::OnMoveTo(const FVector& vTargetPos)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), vTargetPos);
}
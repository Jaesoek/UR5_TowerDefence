#include "Player_InGame.h"


APlayer_InGame::APlayer_InGame()
{
	PrimaryActorTick.bCanEverTick = true;

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
	// 여기서 처리
	UE_LOG(LogTemp, Display, TEXT("TTT"));
}
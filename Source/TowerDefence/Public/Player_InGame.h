#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IControlUnit.h"
#include "Player_InGame.generated.h"

UCLASS()
class TOWERDEFENCE_API APlayer_InGame : public APawn, public IControlUnit
{
	GENERATED_BODY()

public:
	APlayer_InGame();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnFocused() override;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ControlUnit.h"
#include "Player_TowerDefence.generated.h"

UCLASS()
class TOWERDEFENCE_API APlayer_TowerDefence : public ACharacter, public IControlUnit
{
	GENERATED_BODY()

public:
	APlayer_TowerDefence();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnFocused() override;
	virtual void OnMoveTo(const FVector& vTargetPos) override;
};

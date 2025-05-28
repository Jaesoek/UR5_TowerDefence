#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ControlUnit.h"
#include "CommandUnit_TowerDefence.generated.h"

UCLASS()
class TOWERDEFENCE_API ACommandUnit_TowerDefence : public ACharacter, public IControlUnit
{
	GENERATED_BODY()

public:
	ACommandUnit_TowerDefence();

public:
	virtual void OnFocused() override;
	virtual void OnMoveTo(const FVector& vTargetPos) override;
};

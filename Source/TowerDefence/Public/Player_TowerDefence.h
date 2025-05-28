#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_TowerDefence.generated.h"

UCLASS()
class TOWERDEFENCE_API APlayer_TowerDefence : public ACharacter
{
	GENERATED_BODY()

public:
	APlayer_TowerDefence();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (DisableEditOnInstance))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (DisableEditOnInstance))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MovementInfo)
	float m_fCamSpeed;
};
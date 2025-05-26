#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CameraCharacter_TowerDefence.generated.h"

UCLASS()
class TOWERDEFENCE_API ACameraCharacter_TowerDefence : public ACharacter
{
	GENERATED_BODY()

public:
	ACameraCharacter_TowerDefence();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (DisableEditOnInstance))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (DisableEditOnInstance))
	class USpringArmComponent* CameraBoom;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MovementInfo)
	float m_fCamSpeed;
};
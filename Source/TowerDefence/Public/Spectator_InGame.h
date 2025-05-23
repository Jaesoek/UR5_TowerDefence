#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Spectator_InGame.generated.h"

UCLASS()
class TOWERDEFENCE_API ASpectator_InGame : public ACharacter
{
	GENERATED_BODY()

public:
	ASpectator_InGame();

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
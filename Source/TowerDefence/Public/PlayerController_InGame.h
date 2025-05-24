#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PlayerController_InGame.generated.h"

UCLASS()
class TOWERDEFENCE_API APlayerController_InGame : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerController_InGame();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float fDeltaTime) override;

protected:
	void HandleMouseClick(const FInputActionValue& Value);
	void MoveCamera(FVector2D vMove, float fDeltaTime);


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* m_pDefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* m_pMouseClick;


private:
	APawn* m_pPossesedPawn = nullptr;
};

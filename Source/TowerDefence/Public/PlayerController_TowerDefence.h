#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PlayerController_TowerDefence.generated.h"

UCLASS()
class TOWERDEFENCE_API APlayerController_TowerDefence : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerController_TowerDefence();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void HandleMouseClick_L(const FInputActionValue& Value);
	void HandleMouseClick_R(const FInputActionValue& Value);
	void HandleMouseMove(const FInputActionValue& Value);

protected:
	UPROPERTY(EditDefaultsOnly, Transient, Category = "Input")
	float m_fCamspeed;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* m_pDefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* m_pIA_MouseClick_L;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* m_pIA_MouseClick_R;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* m_pIA_MouseMove;

private:
	TScriptInterface<class IControlUnit> m_pControlUnit;
};

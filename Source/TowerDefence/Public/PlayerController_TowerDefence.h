#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Tower/BaseTower.h"
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

	void HandleSelectActor(const FInputActionValue& Value);
	void HandelMoveTo(const FInputActionValue& Value);
	void HandelBuild(const FInputActionValue& Value);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input Mode")
	TObjectPtr<UInputMappingContext> m_pDefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input Mode")
	TObjectPtr<UInputMappingContext> m_pBuildMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input Action")
	TObjectPtr<UInputAction> m_pIA_SelectActor;

	UPROPERTY(EditDefaultsOnly, Category = "Input Action")
	TObjectPtr<UInputAction> m_pIA_MoveTo;

	UPROPERTY(EditDefaultsOnly, Category = "Input Action")
	TObjectPtr<UInputAction> m_pIA_Build;


	UPROPERTY(EditDefaultsOnly, Category = "Tower")
	TSubclassOf<ABaseTower> DefaultTower;


private:
	TScriptInterface<class IControlUnit>	m_pControlUnit;
};

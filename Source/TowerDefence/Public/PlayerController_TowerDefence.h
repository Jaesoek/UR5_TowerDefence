#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Tower/TowerBase.h"
#include "PlayerController_TowerDefence.generated.h"

class IControlUnit;

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

	UFUNCTION(Server, Reliable)
	void Server_SpawnTower(FVector vSpawnPos);

	UFUNCTION(Server, Reliable)
	void Server_MoveControlUnit(AActor* pControlUnit, FVector vTargetPos);

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
	TArray<TObjectPtr<UTowerAsset>> ArrayTowerAssets;


private:
	TScriptInterface<IControlUnit>	m_pControlUnit;
};

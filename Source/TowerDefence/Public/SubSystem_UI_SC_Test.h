#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SubSystem_UI_SC_Test.generated.h"

class UUIAsset;

UCLASS()
class TOWERDEFENCE_API USubSystem_UI_SC_Test : public UGameInstanceSubsystem
{
	GENERATED_BODY()

friend class UGameInstance_TowerDefence;

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	void OpenSCTest();

protected:
	void OpenUI(TSubclassOf<UUserWidget> userWidget);
	void OpenUIWith(TSubclassOf<UUserWidget> userWidget);
};

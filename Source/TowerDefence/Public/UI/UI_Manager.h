#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI_Manager.generated.h"

class UUIAsset;

UCLASS()
class TOWERDEFENCE_API UUI_Manager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

friend class UGameInstance_TowerDefence;

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	void OpenWait();
	void OpenInProgress();

protected:
	void OpenUI(TSubclassOf<UUserWidget> userWidget);

	UPROPERTY(Transient)
	TObjectPtr<UUIAsset> UI_Asset;

	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> CurrentWidget;

	//UPROPERTY(Transient)
	//TMap<FName, TObjectPtr<UUserWidget>> UI_List;
};

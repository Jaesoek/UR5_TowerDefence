#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/CombatType.h"
#include "TowerAsset.generated.h"

UCLASS()
class TOWERDEFENCE_API UTowerAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	FString TowerName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	TSoftObjectPtr<USkeletalMesh> TowerMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	int DamageAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	EDamageType DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	float AttackRange;
};

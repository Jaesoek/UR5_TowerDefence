#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/CombatType.h"
#include "TowerAsset.generated.h"

UCLASS()
class TOWERDEFENCE_API UTowerAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	FString TowerName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	int DamageAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	EDamageType DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower Mesh")
	TSoftObjectPtr<USkeletalMesh> TowerMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower Mesh")
	TSubclassOf<UAnimInstance> AnimInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower Mesh")
	TObjectPtr<UAnimMontage> AttackMontage;
};

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/CombatType.h"
#include "Tower/AIController_Tower.h"
#include "Tower/TowerAttackComponent.h"
#include "TowerAsset.generated.h"

UCLASS()
class TOWERDEFENCE_API UTowerAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Controller")
	TSubclassOf<AAIController_Tower> AI_Controller;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	FString TowerName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	int DamageAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	EDamageType DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	float AttackCoolTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack Module")
	TSubclassOf<UTowerAttackComponent>	AttackCompClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower Mesh")
	TSoftObjectPtr<USkeletalMesh> TowerMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower Mesh")
	TSubclassOf<UAnimInstance> AnimInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower Mesh")
	TSoftObjectPtr<UAnimMontage> MontageAttack;
};

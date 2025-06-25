// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SplineComponent.h"
#include "MonsterBase_TowerDefence.generated.h"

class UMonsterAsset;

UCLASS()
class TOWERDEFENCE_API AMonsterBase_TowerDefence : public ACharacter
{
	GENERATED_BODY()

public:
	AMonsterBase_TowerDefence();

	virtual void SetupAsset(const UMonsterAsset* InMonsterAsset);
	virtual void SetupSplinePath(TWeakObjectPtr<const USplineComponent> pSplinePath);

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;
	virtual void Attack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 Score;

	UPROPERTY(Transient)
	TWeakObjectPtr<const USplineComponent> SplinePath;

	UPROPERTY(Transient)
	float m_fTargetDistance;

	UPROPERTY(Transient)
	float m_fCurDistance;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ControlUnit.h"
#include "Tower/TowerAsset.h"
#include "TowerBase.generated.h"

UCLASS()
class TOWERDEFENCE_API ATowerBase : public APawn, public IControlUnit
{
	GENERATED_BODY()

public:
	ATowerBase();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_TowerAsset();

	UPROPERTY(Transient, ReplicatedUsing = OnRep_TowerAsset)
	TObjectPtr<UTowerAsset> TowerAsset;

	UPROPERTY(Transient, Replicated)
	bool IsAttackable;

	UPROPERTY(Transient)
	float AttackRange;

	UPROPERTY(Transient)
	TObjectPtr<class UAnimMontage> MontageAttack;

	UPROPERTY(Transient)
	TObjectPtr<class USkeletalMeshComponent> SKMesh;


public:
	void SetupAsset(TObjectPtr<UTowerAsset> towerAsset);

	FORCEINLINE float GetAttackRange() const
	{
		return AttackRange;
	}
	FORCEINLINE float GetAttackRangeSqud() const
	{
		return AttackRange * AttackRange;
	}

	// TODO: Need discussion
	//  About sync between montage and takedamage
	virtual bool Attack(AActor* pTarget) final;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayAttackAnim(AActor* pTarget);
	// ~Need discussion

private:
	virtual void OnFocused() override;
	virtual void OnMoveTo(const FVector& vTargetPos) override;
};

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
	TObjectPtr<class UAnimMontage> MontageAttack;

	UPROPERTY(Transient)
	TObjectPtr<class USkeletalMeshComponent> SKMesh;

	UPROPERTY(Transient)
	float m_fAttackRange;

public:
	void SetupAsset(TObjectPtr<UTowerAsset> towerAsset);

	FORCEINLINE float GetAttackRange() const
	{
		return m_fAttackRange;
	}
	FORCEINLINE float GetAttackRangeSqud() const
	{
		return m_fAttackRange * m_fAttackRange;
	}

	virtual bool Attack(AActor* pTarget) final;

	virtual void FollowTo(FVector& vTargetPos) final;	// 임시: 로직정리되면 지울게요

private:
	virtual void OnFocused() override;
	virtual void OnMoveTo(const FVector& vTargetPos) override;
};

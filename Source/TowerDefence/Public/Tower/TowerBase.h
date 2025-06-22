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
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class USkeletalMeshComponent> m_SKMesh;

	UPROPERTY(Transient)
	TObjectPtr<UTowerAsset> m_TowerAsset;

	UPROPERTY(Transient)
	float m_fAttackRange;

public:
	FORCEINLINE void SetTowerAsset(TObjectPtr<UTowerAsset> towerAsset)
	{
		m_TowerAsset = towerAsset;
	}
	FORCEINLINE float GetAttackRange() const
	{
		return m_fAttackRange;
	}
	FORCEINLINE float GetAttackRangeSqud() const
	{
		return m_fAttackRange * m_fAttackRange;
	}

	virtual bool Attack() final;

	virtual void FollowTo(FVector& vTargetPos) final;	// 임시: 로직정리되면 지울게요

private:
	virtual void OnFocused() override;
	virtual void OnMoveTo(const FVector& vTargetPos) override;
};

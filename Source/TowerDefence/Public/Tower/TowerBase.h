// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower/TowerInclude.h"
#include "GameFramework/Pawn.h"
#include "ControlUnit.h"
#include "Tower/TowerAsset.h"
#include "TowerBase.generated.h"


UCLASS()
class TOWERDEFENCE_API ATowerBase : public APawn, public IControlUnit
{
	GENERATED_BODY()

friend class UTowerAttackComponent;

public:
	ATowerBase();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void OnAttackFinish();
	void SetState(ETowerState newState);

	UFUNCTION()
	void OnRep_TowerAsset();

	UFUNCTION()
	void OnRep_StateChanged();

	UPROPERTY(Transient, ReplicatedUsing = OnRep_TowerAsset)
	TObjectPtr<UTowerAsset> TowerAsset;

	UPROPERTY(Transient, Replicated, ReplicatedUsing = OnRep_StateChanged)
	ETowerState CurState;

	UPROPERTY(Transient)
	float AttackRange;

	UPROPERTY(Transient)
	float AttackCoolTime;

	UPROPERTY(Transient)
	FTimerHandle TimerCoolDown;

	UPROPERTY(Transient)
	TObjectPtr<class UAnimMontage> MontageAttack;

	UPROPERTY(Transient)
	TObjectPtr<class USkeletalMeshComponent> SKMesh;

	UPROPERTY(Transient)
	TObjectPtr<UTowerAttackComponent> AttackComp;


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
	FORCEINLINE ETowerState GetCurrentState() const
	{
		return CurState;
	}
	FORCEINLINE float GetAttackCoolTime() const
	{
		return AttackCoolTime;
	}

	virtual bool Attack(AActor* pTarget) final;
	virtual void Attack_CoolDown() final;
	virtual void TakeDamage(AActor* pTarget) final;

private:
	virtual void OnFocused() override;
};

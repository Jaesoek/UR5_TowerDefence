// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../ControlUnit.h"
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

	virtual void OnMonsterEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnMonsterExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	TObjectPtr<class USphereComponent> m_pAttackRange;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class USkeletalMeshComponent> m_SKMesh;

	UPROPERTY(Transient)
	TWeakObjectPtr<AActor>	m_pCurTarget;

	UPROPERTY(Transient)
	TObjectPtr<UTowerAsset> m_TowerAsset;

public:
	FORCEINLINE void SetTowerAsset(TObjectPtr<UTowerAsset> towerAsset)
	{
		m_TowerAsset = towerAsset;
	}

	virtual bool Attack() final;

	virtual void FollowTo(FVector& vTargetPos) final;	// 임시: 로직정리되면 지울게요

private:
	void SetCurTarget(AActor* pActor = nullptr);

	virtual void OnFocused() override;
	virtual void OnMoveTo(const FVector& vTargetPos) override;
};

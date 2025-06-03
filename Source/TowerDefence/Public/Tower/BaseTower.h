// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tower/TowerAsset.h"
#include "BaseTower.generated.h"

UENUM(BlueprintType)
enum class ETowerState : uint8
{
	STATE_READY, STATE_SET, STATE_MAX
};

UCLASS()
class TOWERDEFENCE_API ABaseTower : public APawn
{
	GENERATED_BODY()

protected:
	ETowerState m_eStatus;

public:
	ABaseTower();

protected:
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaTime) override;

	virtual void OnMonsterEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnMonsterExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(Transient)
	TObjectPtr<AActor>		m_pCurTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	TObjectPtr<class USphereComponent> m_pAttackRange;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<class USkeletalMeshComponent> m_Mesh;

private:
	void SetCurTarget(AActor* pActor = nullptr);

public:
	virtual bool Attack() final;
	virtual void FollowTo(FVector& vTargetPos) final;
};

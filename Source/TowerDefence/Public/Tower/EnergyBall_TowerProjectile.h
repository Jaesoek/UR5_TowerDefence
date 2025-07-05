// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower/TowerInclude.h"
#include "EnergyBall_TowerProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class TOWERDEFENCE_API AEnergyBall_TowerProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnergyBall_TowerProjectile();

	void InitInfo(FProjectileInfo projInfo);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Body")
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Body")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(Transient)
	FProjectileInfo ProjectInfo;
};

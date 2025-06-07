// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelDesign/GridAsset.h"
#include "Grid.generated.h"


UCLASS()
class TOWERDEFENCE_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AGrid();

protected:
	virtual void OnConstruction(const FTransform& trans) override;
	virtual void GenerateGrid();

	UPROPERTY(EditDefaultsOnly, Category = "Grid Setting")
	TObjectPtr<UGridAsset> m_GridAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Grid Setting")
	TMap<EGridType, TObjectPtr<UInstancedStaticMeshComponent>>	m_MapMesh;

public:
	UFUNCTION()
	virtual bool AbleToBuild(const FVector& vInputPos, FVector& vBuildPos) const;

	UFUNCTION()
	virtual EGridType GetTileType(const FVector& vInputPos) const;


#if WITH_EDITOR
	UFUNCTION(CallInEditor, Category = "Grid Setting")
	void SetGridBtn();
#endif


};

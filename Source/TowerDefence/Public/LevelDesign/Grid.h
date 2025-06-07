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


	UPROPERTY(EditAnywhere, Category = "Grid Setting", meta = (ClampMin = "10.0", UIMin = "10.0"))
	float m_fWidth;
	UPROPERTY(EditAnywhere, Category = "Grid Setting", meta = (ClampMin = "10.0", UIMin = "10.0"))
	float m_fHeight;
	UPROPERTY(EditAnywhere, Category = "Grid Setting", meta = (ClampMin = "2", UIMin = "2"))
	int32 m_iNumRow;
	UPROPERTY(EditAnywhere, Category = "Grid Setting", meta = (ClampMin = "2", UIMin = "2"))
	int32 m_iNumCol;
	UPROPERTY(EditAnywhere, Category = "Grid Setting")
	TArray<EGridType> m_typeSetter;

#if WITH_EDITOR
	UFUNCTION(CallInEditor, Category = "Grid Setting")
	void SetGridBtn();
#endif

	UPROPERTY(EditDefaultsOnly, Category = "Grid Setting")
	TMap<EGridType, TObjectPtr<UInstancedStaticMeshComponent>>	m_MapMesh;

	UPROPERTY(Transient)
	TArray<EGridType> m_Cells;

public:
	UFUNCTION()
	virtual bool AbleToBuild(const FVector& vInputPos, FVector& vBuildPos) const;

	UFUNCTION()
	virtual EGridType GetTileType(const FVector& vInputPos) const;



};

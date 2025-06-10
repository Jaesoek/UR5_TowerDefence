// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"


UENUM(BlueprintType)
enum class EGridType : uint8
{
	GRID_NULL, GRID_SPAWN, GRID_PATH, GRID_BUILDABLE, GRID_GOAL
};

UCLASS()
class TOWERDEFENCE_API AGrid : public AActor
{
	GENERATED_BODY()

friend class FDetailGrid;

public:	
	AGrid();

protected:
	virtual void OnConstruction(const FTransform& trans) override;
	virtual void InitGrid();

	UPROPERTY(EditAnywhere, Category = "Grid Setting", meta = (ClampMin = "10.0", UIMin = "10.0"))
	float m_fWidth;
	UPROPERTY(EditAnywhere, Category = "Grid Setting", meta = (ClampMin = "10.0", UIMin = "10.0"))
	float m_fHeight;
	UPROPERTY(EditAnywhere, Category = "Grid Setting", meta = (ClampMin = "2", UIMin = "2"))
	int32 m_iNumRow;
	UPROPERTY(EditAnywhere, Category = "Grid Setting", meta = (ClampMin = "2", UIMin = "2"))
	int32 m_iNumCol;

	UPROPERTY(VisibleDefaultsOnly)
	TMap<EGridType, TObjectPtr<UInstancedStaticMeshComponent>>	m_mapInsMeshComp;

	// Editor에서 직접 수정 불가능
	UPROPERTY(VisibleAnywhere)
	TArray<EGridType> m_cellTypes;
	//~ Editor에서 직접 수정 불가능

	UPROPERTY(Transient)
	TMap<int32, EGridType> m_Indices;	// For follow up datas


public:
	UFUNCTION()
	virtual bool AbleToBuild(const FVector& vInputPos, FVector& vBuildPos) const;

	UFUNCTION()
	virtual EGridType GetTileType(const FVector& vInputPos) const;


#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


};

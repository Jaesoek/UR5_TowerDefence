// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GridAsset.generated.h"

UENUM(BlueprintType)
enum class EGridType : uint8
{
	GRID_NULL, GRID_SPAWN, GRID_PATH, GRID_BUILDABLE, GRID_GOAL
};

UCLASS(BlueprintType)
class TOWERDEFENCE_API UGridAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	bool InitCells();

	UPROPERTY(EditDefaultsOnly, Category = "Grid Setting", meta = (ClampMin = "10.0", UIMin = "10.0"))
	float m_fWidth;
	UPROPERTY(EditDefaultsOnly, Category = "Grid Setting", meta = (ClampMin = "10.0", UIMin = "10.0"))
	float m_fHeight;
	UPROPERTY(EditDefaultsOnly, Category = "Grid Setting", meta = (ClampMin = "2", UIMin = "2"))
	int32 m_iNumRow;
	UPROPERTY(EditDefaultsOnly, Category = "Grid Setting", meta = (ClampMin = "2", UIMin = "2"))
	int32 m_iNumCol;

	UPROPERTY(EditAnywhere, Category = "Grid Setting")
	TArray<EGridType> m_cellTypes;

	UPROPERTY(EditDefaultsOnly, Category = "Grid Setting")
	TMap<EGridType, TSoftObjectPtr<UStaticMesh>>	m_MapMesh;

	
};

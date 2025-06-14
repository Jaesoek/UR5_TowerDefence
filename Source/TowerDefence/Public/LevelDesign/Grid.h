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

struct FGridCoord
{
	int32 iRow, iCol;
	bool operator==(const FGridCoord& Other) const { return iCol == Other.iCol && iRow == Other.iRow; }
};

public:	
	AGrid();

protected:
	virtual void OnConstruction(const FTransform& trans) override;
	virtual void BeginPlay() override;

	virtual void InitGrid();
	virtual void InitPath(std::vector<bool>& vecDidVisited, int32 curRow, int32 curCol);

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
	UPROPERTY()
	TObjectPtr<class UBoxComponent>		m_GridBody;

	UPROPERTY()
	TArray<EGridType> m_cellTypes;
	// TODO: Cell 정보 Transform이랑 같이 넣을 것

	UPROPERTY(Transient)
	TObjectPtr<class USplineComponent>	PathSpline;	// Path for monsters

	UPROPERTY(Transient)
	FVector m_vSpawnPos;	// For saving spawn pos data

	UPROPERTY(Transient)
	int32 m_iSpawnIndex;

	UPROPERTY(Transient)
	FVector m_vGoalPos;	// For saving spawn pos data

	UPROPERTY(Transient)
	int32 m_iGoalIndex;
	//~ Editor에서 직접 수정 불가능


public:
	UFUNCTION()
	virtual bool AbleToBuild(const FVector& vInputPos, FVector& vBuildPos) const;

	UFUNCTION()
	virtual bool GetSpawnTransform(FTransform& outTrans) const;

	UFUNCTION()
	virtual bool GetGoalTransform(FTransform& outTrans) const;

	UFUNCTION()
	virtual EGridType GetTileType(const FVector& vInputPos) const;


#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


private:
	int32 GetIndex(int32 iRow, int32 iCol) const {
		return iRow * m_iNumCol + iCol;
	};
	FGridCoord GetCoord(int32 iIndex) const {
		return { iIndex / m_iNumCol, iIndex % m_iNumCol};
	};
	bool IsValidCoord(int32 iRow, int32 iCol) const
	{
		return iRow >= 0 && iCol >= 0 && iRow < m_iNumRow && iCol < m_iNumCol;
	}
};

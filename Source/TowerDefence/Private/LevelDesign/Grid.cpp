// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDesign/Grid.h"
#include "Components/InstancedStaticMeshComponent.h"

#if WITH_EDITOR
#include "Editor.h"
#endif


AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	m_MapMesh.Add(EGridType::GRID_NULL, CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("DefaultMesh")));
	m_MapMesh.Add(EGridType::GRID_SPAWN, CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("SpawnMesh")));
	m_MapMesh.Add(EGridType::GRID_BUILDABLE, CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("BuildableMesh")));
	m_MapMesh.Add(EGridType::GRID_PATH, CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("PathMesh")));
	m_MapMesh.Add(EGridType::GRID_GOAL, CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GoalMesh")));
}

void AGrid::OnConstruction(const FTransform& trans)
{
	Super::OnConstruction(trans);

	GenerateGrid();
}

void AGrid::GenerateGrid()
{
	if (!IsValid(m_GridAsset))
	{
		return;
	}

	for (auto& instancMesh : m_MapMesh)
	{
		instancMesh.Value->ClearInstances();
	}

	float CellWidth = m_GridAsset->m_fWidth / m_GridAsset->m_iNumCol;
	float CellHeight = m_GridAsset->m_fHeight / m_GridAsset->m_iNumRow;

	for (int32 Row = 0; Row < m_GridAsset->m_iNumRow; ++Row)
	{
		for (int32 Col = 0; Col < m_GridAsset->m_iNumCol; ++Col)
		{			
			if (IsValid(m_MapMesh[m_GridAsset->m_cellTypes[Row * m_GridAsset->m_iNumCol + Col]]))
			{
				FVector Location = FVector(CellWidth * Col, CellHeight * Row, 0.f);
				FTransform Transform(FRotator::ZeroRotator, Location, { CellHeight, CellWidth, 1.f });

				m_MapMesh[m_GridAsset->m_cellTypes[Row * m_GridAsset->m_iNumCol + Col]]->AddInstance(Transform);
			}
		}
	}
}

bool AGrid::AbleToBuild(const FVector& vInputPos, FVector& vBuildPos) const
{


	return false;
}

EGridType AGrid::GetTileType(const FVector& vPos) const
{
	FVector vLocal = vPos - GetActorLocation();

	float fCellWidth = m_GridAsset->m_fWidth / m_GridAsset->m_iNumCol;
	float fCellHeight = m_GridAsset->m_fHeight / m_GridAsset->m_iNumRow;

	int32 col = FMath::FloorToInt(vLocal.X / fCellWidth);
	int32 row = FMath::FloorToInt(vLocal.Y / fCellHeight);

	if (row >= 0 && row < m_GridAsset->m_iNumRow && col >= 0 && col < m_GridAsset->m_iNumCol)
	{
		return m_GridAsset->m_cellTypes[row * m_GridAsset->m_iNumCol + col];
	}
	return EGridType::GRID_NULL;
}

#if WITH_EDITOR

void AGrid::SetGridBtn()
{
	GenerateGrid();
}

#endif

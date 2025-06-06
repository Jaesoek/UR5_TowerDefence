// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDesign/Grid.h"
#include "Components/InstancedStaticMeshComponent.h"


AGrid::AGrid()
	: m_fWidth(10.f), m_fHeight(10), m_iNumCol(2), m_iNumRow(2)
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
	for (auto& instancMesh : m_MapMesh)
	{
		instancMesh.Value->ClearInstances();
	}

	m_Cells.Empty();
	m_Cells.SetNum(m_iNumRow * m_iNumCol);

	float CellWidth = m_fWidth / m_iNumCol;
	float CellHeight = m_fHeight / m_iNumRow;

	for (int32 Row = 0; Row < m_iNumRow; ++Row)
	{
		for (int32 Col = 0; Col < m_iNumCol; ++Col)
		{
			if (m_typeSetter.Num() > Row * m_iNumCol + Col)
			{
				m_Cells[Row * m_iNumCol + Col] = m_typeSetter[Row * m_iNumCol + Col];
			}
			else
			{
				m_Cells[Row * m_iNumCol + Col] = EGridType::GRID_NULL;
			}
			
			if (IsValid(m_MapMesh[m_Cells[Row * m_iNumCol + Col]]))
			{
				FVector Location = FVector(CellWidth * Col, CellHeight * Row, 0.f);
				FTransform Transform(FRotator::ZeroRotator, Location, { CellHeight, CellWidth, 1.f });

				m_MapMesh[m_Cells[Row * m_iNumCol + Col]]->AddInstance(Transform);
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

	float fCellWidth = m_fWidth / m_iNumCol;
	float fCellHeight = m_fHeight / m_iNumRow;

	int32 col = FMath::FloorToInt(vLocal.X / fCellWidth);
	int32 row = FMath::FloorToInt(vLocal.Y / fCellHeight);

	if (row >= 0 && row < m_iNumRow && col >= 0 && col < m_iNumCol)
	{
		return m_Cells[row * m_iNumCol + col];
	}
	return EGridType::GRID_NULL;
}

#if WITH_EDITOR

void AGrid::SetGridBtn()
{
	GenerateGrid();
}

#endif

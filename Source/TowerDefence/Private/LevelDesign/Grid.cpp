// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDesign/Grid.h"
#include "Components/InstancedStaticMeshComponent.h"

#if WITH_EDITOR
#include "Editor.h"
#endif


AGrid::AGrid()
	: m_fWidth(10.f), m_fHeight(10), m_iNumCol(2), m_iNumRow(2)
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	m_mapInsMeshComp.Add(EGridType::GRID_NULL, CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("DefaultMesh")));
	m_mapInsMeshComp.Add(EGridType::GRID_SPAWN, CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("SpawnMesh")));
	m_mapInsMeshComp.Add(EGridType::GRID_BUILDABLE, CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("BuildableMesh")));
	m_mapInsMeshComp.Add(EGridType::GRID_PATH, CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("PathMesh")));
	m_mapInsMeshComp.Add(EGridType::GRID_GOAL, CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GoalMesh")));

	for (auto pairMeshComp : m_mapInsMeshComp)
	{
		pairMeshComp.Value->SetupAttachment(RootComponent);
	}
}

void AGrid::OnConstruction(const FTransform& trans)
{
	Super::OnConstruction(trans);

	InitGrid();
}

void AGrid::InitGrid()
{
	for (auto& instancMesh : m_mapInsMeshComp)
	{
		instancMesh.Value->ClearInstances();
	}

	float CellWidth = m_fWidth / m_iNumCol;
	float CellHeight = m_fHeight / m_iNumRow;

	for (int32 Row = 0; Row < m_iNumRow; ++Row)
	{
		for (int32 Col = 0; Col < m_iNumCol; ++Col)
		{
			if (m_cellTypes.Num() <= Row * m_iNumCol + Col)
			{
				m_cellTypes.Add(EGridType::GRID_NULL);
			}

			const EGridType& curGridType = m_cellTypes[Row * m_iNumCol + Col];
			if (IsValid(m_mapInsMeshComp[curGridType]))
			{
				FVector Location = FVector(CellWidth * Col, CellHeight * Row, 0.f);
				FTransform Transform(FRotator::ZeroRotator, Location, { CellHeight / 100.f, CellWidth / 100.f, 1.f });

				int32&& newIndex = m_mapInsMeshComp[curGridType]->AddInstance(Transform);
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
		return m_cellTypes[row * m_iNumCol + col];
	}
	return EGridType::GRID_NULL;
}

#if WITH_EDITOR

void AGrid::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UE_LOG(LogTemp, Display, TEXT("Grid OnPostEditChange"));
	/*
	FName PropertyName = PropertyChangedEvent.GetPropertyName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AGrid, Transform))
	{
		OtherValue = MyCustomValue * 2.0f;
	}
	*/
}

#endif

// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDesign/Grid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameModes/GameModeBase_TowerDefence.h"

#if WITH_EDITOR
#include "Editor.h"
#endif


AGrid::AGrid()
	: m_fWidth(10.f), m_fHeight(10), m_iNumRow(2), m_iNumCol(2)
{
	PrimaryActorTick.bCanEverTick = true;

	m_GridBody = CreateDefaultSubobject<UBoxComponent>(TEXT("GridBody"));
	if (m_GridBody)
	{
		RootComponent = m_GridBody;
	}

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
	FVector NewExtent(m_fWidth / 2, m_fHeight / 2, 100.f);
	m_GridBody->SetBoxExtent(NewExtent, true);

	for (auto& instancMesh : m_mapInsMeshComp)
	{
		instancMesh.Value->ClearInstances();
	}

	float CellWidth = m_fWidth / m_iNumCol;
	float CellHeight = m_fHeight / m_iNumRow;
	FVector OriginOffset = FVector(m_fWidth * 0.5f, m_fHeight * 0.5f, 0.f);
	FVector CellOffset = FVector(CellWidth * 0.5f, CellHeight * 0.5f, 0.f);

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
				Location -= OriginOffset;
				Location += CellOffset;

				if (curGridType == EGridType::GRID_SPAWN)
				{
					m_vSpawnPos = Location;
				}

				FTransform Transform(FRotator::ZeroRotator, Location, { CellHeight / 100.f, CellWidth / 100.f, 1.f });
				int32&& newIndex = m_mapInsMeshComp[curGridType]->AddInstance(Transform);
			}
		}
	}
}

void AGrid::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase_TowerDefence* GameMode = GetWorld()->GetAuthGameMode<AGameModeBase_TowerDefence>();
	if (IsValid(GameMode))
	{
		GameMode->SetGrid(this);
	}
}

bool AGrid::AbleToBuild(const FVector& vInputPos, FVector& vBuildPos) const
{
	FVector OriginOffset = FVector(m_fWidth * 0.5f, m_fHeight * 0.5f, 0.f);

	FVector vPos = vInputPos - GetActorLocation();
	vPos += OriginOffset;
	
	if (vPos.X < 0 || vPos.Y < 0 || vPos.X >= m_fWidth || vPos.Y >= m_fHeight)
	{
		return false;
	}

	float CellWidth = m_fWidth / m_iNumCol;
	float CellHeight = m_fHeight / m_iNumRow;
	FVector CellOffset = FVector(CellWidth * 0.5f, CellHeight * 0.5f, 0.f);

	int iCol = static_cast<int>(vPos.X / CellWidth);
	int iRow = static_cast<int>(vPos.Y / CellHeight);
	if (EGridType::GRID_BUILDABLE == m_cellTypes[iRow * m_iNumCol + iCol])
	{
		vBuildPos = GetActorLocation() - OriginOffset + CellOffset;
		vBuildPos += FVector{ CellWidth * iCol, CellHeight * iRow, 0.f };
		return true;
	}

	return false;
}

void AGrid::GetSpawnTransform(FTransform& outTrans) const
{
	outTrans = FTransform{
		FRotator::ZeroRotator,
		m_vSpawnPos,
		FVector::OneVector
	};
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

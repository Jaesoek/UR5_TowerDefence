// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDesign/Grid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineComponent.h"
#include "GameModes/GameModeBase_TowerDefence.h"

#if WITH_EDITOR
#include "Editor.h"
#endif


AGrid::AGrid()
	: m_fWidth(10.f), m_fHeight(10), m_iNumRow(2), m_iNumCol(2)
	, m_iSpawnIndex(-1), m_iGoalIndex(-1)
{
	PrimaryActorTick.bCanEverTick = true;

	m_GridBody = CreateDefaultSubobject<UBoxComponent>(TEXT("GridBody"));
	if (m_GridBody)
	{
		RootComponent = m_GridBody;
	}

	SplinePath = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplinePath->SetupAttachment(RootComponent);

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
	InitPath();
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
	FVector OriginOffset = FVector(m_fHeight * 0.5f, m_fWidth * 0.5f, 0.f);
	FVector CellOffset = FVector(CellHeight * 0.5f, CellWidth * 0.5f, 0.f);

	bool isSpawnSet = false, isGoalSet = false;
	for (int32 iIndex = 0; iIndex < m_iNumCol * m_iNumRow; ++iIndex)
	{
		if (m_arrCell.Num() <= iIndex)
		{
			m_arrCell.Add(FGridCellInfo{});
		}

		FGridCoord gridCoord = GetCoord(iIndex);

		FVector Location = FVector(CellHeight * gridCoord.iRow, CellWidth * gridCoord.iCol, 0.f);
		Location -= OriginOffset;
		Location += CellOffset;

		const EGridType& curGridType = m_arrCell[iIndex].typeCell;
		if (curGridType == EGridType::GRID_SPAWN)
		{
			isSpawnSet = true;

			m_vSpawnPos = Location + GetActorLocation();
			m_vSpawnPos[2] = 100.0;

			m_iSpawnIndex = iIndex;
		}
		else if (curGridType == EGridType::GRID_GOAL)
		{
			isGoalSet = true;

			m_vGoalPos = Location + GetActorLocation();
			m_vGoalPos[2] = 100.0;

			m_iGoalIndex = iIndex;
		}

		if (IsValid(m_mapInsMeshComp[curGridType]))
		{
			FTransform Transform(FRotator::ZeroRotator, Location, { CellHeight / 100.f, CellWidth / 100.f, 1.f });
			int32&& newIndex = m_mapInsMeshComp[curGridType]->AddInstance(Transform);
		}
	}

	if (false == isSpawnSet)
	{
		m_iSpawnIndex = -1;
	}
	if (false == isGoalSet)
	{
		m_iGoalIndex = -1;
	}
}

void AGrid::InitPath()
{
	/*
	SplinePath->ClearSplinePoints();

	if (m_iSpawnIndex == -1 || m_iGoalIndex == -1)
	{
		return;
	}

	TSet<FGridCoord> Visited;
	TArray<int32> OrderedIndices;

	FGridCoord Start = GetCoord(m_iSpawnIndex);
	FGridCoord Goal = GetCoord(m_iGoalIndex);

	SplinePath->AddSplinePoint(m_arrCell[m_iSpawnIndex].vPosRelative,
		ESplineCoordinateSpace::Type::Local);
	Visited.Add(Start);

	const TArray<FGridCoord> Directions = {
		{ 1, 0 },
		{ 0, 1 },
		{ 0, -1 },
		{ -1, 0 }
	};

	TArray<FGridCoord> Stack;
	Stack.Add(Start);

	while (Stack.Num() > 0)
	{
		FGridCoord Current = Stack.Pop();

		for (const FGridCoord& Dir : Directions)
		{
			FGridCoord Next = { Current.iRow + Dir.iRow, Current.iCol + Dir.iCol };

			if (!IsValidCoord(Next.iRow, Next.iCol) || Visited.Contains(Next))
				continue;

			int32 NextIdx = GetIndex(Next.iRow, Next.iCol);
			if (m_arrCell[NextIdx].typeCell == EGridType::GRID_PATH)
			{
				Visited.Add(Next);
				OrderedIndices.Add(NextIdx);
				Stack.Add(Next);

				SplinePath->AddSplinePoint(m_arrCell[NextIdx].vPosRelative, ESplineCoordinateSpace::Type::Local);
				break;
			}
		}
	}

	OrderedIndices.Add(m_iGoalIndex);

	SplinePath->AddSplinePoint(m_arrCell[m_iGoalIndex].vPosRelative, ESplineCoordinateSpace::Type::Local);

	SplinePath->SetClosedLoop(false);
	SplinePath->UpdateSpline();
	*/
}

bool AGrid::AbleToBuild(const FVector& vInputPos, FVector& vBuildPos) const
{
	FVector OriginOffset = FVector(m_fHeight * 0.5f, m_fWidth * 0.5f, 0.f);

	FVector vPos = vInputPos - GetActorLocation();
	vPos += OriginOffset;
	
	if (vPos.X < 0 || vPos.Y < 0 || vPos.X >= m_fHeight || vPos.Y >= m_fWidth)
	{
		return false;
	}

	float CellWidth = m_fWidth / m_iNumCol;
	float CellHeight = m_fHeight / m_iNumRow;
	FVector CellOffset = FVector(CellHeight * 0.5f, CellWidth * 0.5f, 0.f);

	int iCol = static_cast<int>(vPos.Y / CellWidth);
	int iRow = static_cast<int>(vPos.X / CellHeight);
	if (EGridType::GRID_BUILDABLE == m_arrCell[GetIndex(iRow, iCol)].typeCell)
	{
		vBuildPos = GetActorLocation() - OriginOffset + CellOffset;
		vBuildPos += FVector{ CellHeight * iRow, CellWidth * iCol, 0.0 };
		vBuildPos[2] = 100.0;
		return true;
	}

	return false;
}

EGridType AGrid::GetTileType(const FVector& vPos) const
{
	FVector vLocal = vPos - GetActorLocation();

	float fCellWidth = m_fWidth / m_iNumCol;
	float fCellHeight = m_fHeight / m_iNumRow;

	int32 col = FMath::FloorToInt(vLocal.Y / fCellWidth);
	int32 row = FMath::FloorToInt(vLocal.X / fCellHeight);

	if (row >= 0 && row < m_iNumRow && col >= 0 && col < m_iNumCol)
	{
		return m_arrCell[GetIndex(row, col)].typeCell;
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

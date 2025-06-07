// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDesign/GridAsset.h"

bool UGridAsset::InitCells()
{
	m_cellTypes.Init(EGridType::GRID_NULL, m_iNumRow * m_iNumCol);

	return false;
}




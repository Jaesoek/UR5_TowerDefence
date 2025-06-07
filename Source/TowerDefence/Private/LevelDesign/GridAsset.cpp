// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDesign/GridAsset.h"

UGridAsset::UGridAsset()
	: m_fWidth(10.f), m_fHeight(10), m_iNumCol(2), m_iNumRow(2)
{
}

bool UGridAsset::InitCells()
{
	m_cellTypes.Init(EGridType::GRID_NULL, m_iNumRow * m_iNumCol);

	return false;
}




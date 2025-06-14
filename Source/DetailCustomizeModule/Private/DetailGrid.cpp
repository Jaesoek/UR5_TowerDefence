// Fill out your copyright notice in the Description page of Project Settings.


#include "DetailGrid.h"
#include "LevelDesign/Grid.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Text/STextBlock.h"
#include "PropertyHandle.h"
#include "Templates/SharedPointer.h"

TSharedRef<IDetailCustomization> FDetailGrid::MakeInstance()
{
	return MakeShareable(new FDetailGrid);
}

void FDetailGrid::CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder)
{
	DetailBuilderPtr = DetailBuilder.ToWeakPtr();

	CustomizeDetails(*DetailBuilder);
}

void FDetailGrid::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() > 0)
	{
		GridInfo = Cast<AGrid>(Objects[0].Get());
	}
	if (!GridInfo.IsValid())
	{
		return;
	}

	IDetailCategoryBuilder& GridCategory = DetailBuilder.EditCategory("Grid", FText::FromString(TEXT("Grid")));

	auto pGrid = GridInfo.Get();
	for (int32 Row = pGrid->m_iNumRow - 1; Row >= 0; --Row)
	{
		TSharedRef<SHorizontalBox> RowBox = SNew(SHorizontalBox);
		for (int32 Col = 0; Col < pGrid->m_iNumCol; ++Col)
		{
			int32 Index = Row * pGrid->m_iNumCol + Col;

			RowBox->AddSlot()
				.AutoWidth()
				.Padding(2)
				[
					SNew(SButton)
						.OnClicked(this, &FDetailGrid::OnCellClicked, Index)
						.ContentPadding(0)
						[
							SNew(SBorder)
								.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
								.BorderBackgroundColor(this, &FDetailGrid::GetCellColor, Index)
								.Padding(FMargin(10.0f))
						]
				];
		}

		GridCategory.AddCustomRow(FText::FromString(FString::Printf(TEXT("Row %d"), Row)))
			.WholeRowContent()
			[
				RowBox
			];
	}
}

FSlateColor FDetailGrid::GetCellColor(int32 Index) const
{
	if (!GridInfo->m_cellTypes.IsValidIndex(Index))
		return FSlateColor(FLinearColor::Black);

	switch (GridInfo->m_cellTypes[Index])
	{
	case EGridType::GRID_SPAWN:
		return FSlateColor(FLinearColor::Green);
	case EGridType::GRID_PATH:
		return FSlateColor(FLinearColor::Blue);
	case EGridType::GRID_BUILDABLE:
		return FSlateColor(FLinearColor::White);
	case EGridType::GRID_GOAL:
		return FSlateColor(FLinearColor::Yellow);
	default:
		return FSlateColor(FLinearColor::Black);
	}
}

FText FDetailGrid::GetButtonText(int32 Index) const
{
	if (!GridInfo->m_cellTypes.IsValidIndex(Index))
		return FText::FromString(TEXT("Err"));

	const EGridType Type = GridInfo->m_cellTypes[Index];
	return FText::FromString(UEnum::GetValueAsString(Type));
}

FReply FDetailGrid::OnCellClicked(int32 Index)
{
	if (!GridInfo->m_cellTypes.IsValidIndex(Index))
		return FReply::Handled();

	EGridType tempType = static_cast<EGridType>(
		(static_cast<uint8>(GridInfo->m_cellTypes[Index]) + 1) % 5);
	if (tempType == EGridType::GRID_SPAWN)
	{
		if (GridInfo->m_iSpawnIndex != -1)
		{
			tempType = EGridType::GRID_PATH;
		}
	}
	else if (tempType == EGridType::GRID_GOAL)
	{
		if (GridInfo->m_iGoalIndex != -1)
		{
			tempType = EGridType::GRID_NULL;
		}
	}
	GridInfo->m_cellTypes[Index] = tempType;

	// 적용
	if (GridInfo.IsValid())
	{
		GridInfo->Modify();
		GridInfo->RerunConstructionScripts();
	}

	// Refresh UI
	if (DetailBuilderPtr.IsValid())
	{
		DetailBuilderPtr.Pin()->ForceRefreshDetails();
	}

	return FReply::Handled();
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "DetailGrid.h"
#include "../../TowerDefence/Public/LevelDesign/GridAsset.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Text/STextBlock.h"
#include "PropertyHandle.h"

TSharedRef<IDetailCustomization> FDetailGrid::MakeInstance()
{
	return MakeShareable(new FDetailGrid);
}

void FDetailGrid::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() > 0)
	{
		GridAsset = Cast<UGridAsset>(Objects[0].Get());
	}
	if (!GridAsset.IsValid())
	{
		return;
	}

	if (GridAsset->m_cellTypes.Num() != GridAsset->m_iNumRow * GridAsset->m_iNumCol)
	{
		GridAsset->InitCells();
	}

	IDetailCategoryBuilder& GridCategory =
		DetailBuilder.EditCategory("Grid", FText::FromString(TEXT("Grid")));
	for (int32 Row = 0; Row < GridAsset->m_iNumRow; ++Row)
	{
		TSharedRef<SHorizontalBox> RowBox = SNew(SHorizontalBox);
		for (int32 Col = 0; Col < GridAsset->m_iNumCol; ++Col)
		{
			int32 Index = Row * GridAsset->m_iNumCol + Col;

			RowBox->AddSlot()
				.AutoWidth()
				.Padding(2)
				[
					SNew(SButton)
						.Text(this, &FDetailGrid::GetButtonText, Index)
						.OnClicked(this, &FDetailGrid::OnCellClicked, Index)
				];
		}

		GridCategory.AddCustomRow(FText::FromString(FString::Printf(TEXT("Row %d"), Row)))
			.WholeRowContent()
			[
				RowBox
			];
	}
}

FText FDetailGrid::GetButtonText(int32 Index) const
{
	if (!GridAsset->m_cellTypes.IsValidIndex(Index))
		return FText::FromString(TEXT("Err"));

	const EGridType Type = GridAsset->m_cellTypes[Index];
	return FText::FromString(UEnum::GetValueAsString(Type));
}

FReply FDetailGrid::OnCellClicked(int32 Index)
{
	if (!GridAsset->m_cellTypes.IsValidIndex(Index))
		return FReply::Handled();

	EGridType& Type = GridAsset->m_cellTypes[Index];
	Type = static_cast<EGridType>((static_cast<uint8>(Type) + 1) % 4);

	return FReply::Handled();
}
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
	for (int32 Row = 0; Row < pGrid->m_iNumRow; ++Row)
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
	if (!GridInfo->m_cellTypes.IsValidIndex(Index))
		return FText::FromString(TEXT("Err"));

	const EGridType Type = GridInfo->m_cellTypes[Index];
	return FText::FromString(UEnum::GetValueAsString(Type));
}

FReply FDetailGrid::OnCellClicked(int32 Index)
{
	if (!GridInfo->m_cellTypes.IsValidIndex(Index))
		return FReply::Handled();

	EGridType& Type = GridInfo->m_cellTypes[Index];
	Type = static_cast<EGridType>((static_cast<uint8>(Type) + 1) % 4);

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
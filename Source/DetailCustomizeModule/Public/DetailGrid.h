// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailLayoutBuilder;
class AGrid;

class DETAILCUSTOMIZEMODULE_API FDetailGrid : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

protected:
	FSlateColor GetCellColor(int32 Index) const;
	FText GetButtonText(int32 Index) const;
	FReply OnCellClicked(int32 Index);

private:
	TWeakPtr<IDetailLayoutBuilder> DetailBuilderPtr;

	TWeakObjectPtr<AGrid> GridInfo;
};
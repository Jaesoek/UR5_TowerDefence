// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IDetailLayoutBuilder;
class UGridAsset;

class DETAILCUSTOMIZEMODULE_API FDetailGrid : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

protected:
	FText GetButtonText(int32 Index) const;
	FReply OnCellClicked(int32 Index);

private:
	TWeakObjectPtr<UGridAsset> GridAsset;
};
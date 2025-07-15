// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomImageBtn.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class TOWERDEFENCE_API UCustomImageBtn : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeButton(const FString& InLabel, const FLinearColor& InColor);

	const UButton* GetButton() const { return Button.Get(); }

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock;
};

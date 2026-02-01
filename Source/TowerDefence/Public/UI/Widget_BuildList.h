// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/UMGSequencePlayer.h"
#include "Widget_BuildList.generated.h"

class UButton;
class UCustomImageBtn;

UCLASS()
class TOWERDEFENCE_API UWidget_BuildList : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativePreConstruct() override;
	virtual void NativeConstruct() override;

protected:
	void PlayContentAppear(UUMGSequencePlayer& Player);

	UFUNCTION()
	void OnBtnClicked();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> TowerTable;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> Button_0;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> Button_1;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> Button_2;
	
	UPROPERTY(Transient)
	TArray<TObjectPtr<UButton>> BtnArray;


	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> BoxAppear;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> ContentAppear;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> BoxHovered;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCustomImageBtn> ClassCustomBtn;
};

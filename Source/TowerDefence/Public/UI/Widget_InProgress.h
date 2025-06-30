// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_InProgress.generated.h"


UCLASS()
class TOWERDEFENCE_API UWidget_InProgress : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom Info")
	int32 m_iRemainNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom Info")
	int32 m_iCurScore;

protected:
	virtual void MonsterNumChanged(int32 iRemainNum) final;
	virtual void ScoreChanged(int32 iCurScore) final;
};

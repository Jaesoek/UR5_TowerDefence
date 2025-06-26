// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTD, Log, All);

#define TD_LOG(OBJECT,FMT) UE_LOG(LogTD, Log, TEXT("%s%s%s"),*GetNetModeString(OBJECT), *GetRoleString(OBJECT), FMT);

TOWERDEFENCE_API FString GetNetModeString(UObject* InObject);
TOWERDEFENCE_API FString GetRoleString(UObject* InObject);
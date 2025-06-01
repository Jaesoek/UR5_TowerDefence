// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatType.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	DAMAGETYPE_NORMAL	UMETA(DisplayName = "Normal")
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	ARMORTYPE_NORMAL		UMETA(DisplayName = "Normal")
};

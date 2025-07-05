#pragma once

#include "CoreMinimal.h"
#include "TowerInclude.generated.h"


UENUM()
enum class ETowerState : uint8
{
	IDLE, ATTACK, MAX
};

USTRUCT()
struct FProjectileInfo
{
	GENERATED_BODY()

	float fInitSpeed;
	float fMaxSpeed;
	float fGravitySpeed;
	float fDamageAmount;
	FVector vTargetPos;
	
	TSoftObjectPtr<UStaticMesh> pMesh;
};
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerMonster_TowerDefence.generated.h"

UCLASS()
class TOWERDEFENCE_API ASpawnerMonster_TowerDefence : public AActor
{
	GENERATED_BODY()

public:	
	ASpawnerMonster_TowerDefence();

protected:
	virtual void BeginPlay() override;
	
	virtual void SpawnMonsters();
};

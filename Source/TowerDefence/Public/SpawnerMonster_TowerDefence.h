#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Public/MonsterBase_TowerDefence.h"
#include "SpawnerMonster_TowerDefence.generated.h"

UCLASS()
class TOWERDEFENCE_API ASpawnerMonster_TowerDefence : public AActor
{
	GENERATED_BODY()

public:	
	ASpawnerMonster_TowerDefence();

protected:
	virtual void BeginPlay() override;
	
	virtual void StartSpawning();
	virtual void SpawnMonster();

	UPROPERTY(Transient)
	FTimerHandle TimerHandle_StartRound;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float m_fTimeInterval_Spawning;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TMap<FName, TSubclassOf<AMonsterBase_TowerDefence>> m_MonsterMap;

	UPROPERTY(EditAnywhere, Category = "Spawning")		// 임시: Round를 파일화해서 저장할 것
	int32 m_iMonsterNum_Test;

	UPROPERTY(Transient)
	int32 m_iCurNum_SpawnedMonster;

};

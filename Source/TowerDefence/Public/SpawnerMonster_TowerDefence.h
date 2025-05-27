#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerMonster_TowerDefence.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFinishWave, bool);

UCLASS()
class TOWERDEFENCE_API ASpawnerMonster_TowerDefence : public AActor
{
	GENERATED_BODY()

private:
	enum class ESpawnerState
	{
		Default, Spawning, End
	};

public:	
	ASpawnerMonster_TowerDefence();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void StartSpawning(int iLevel);

	ESpawnerState m_eCurState = ESpawnerState::Default;

	FOnFinishWave OnWaveFinished;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GameModeBase_TowerDefence.h"
#include "GameState_TowerDefence.h"
#include "Monster/MonsterAsset.h"
#include "Monster/MonsterBase_TowerDefence.h"
#include "Stage/StageAsset.h"
#include "Player/PlayerState_TowerDefence.h"
#include "LevelDesign/Grid.h"			// For getting spawn position
#include "Kismet/GameplayStatics.h"		// For deferred spawning

void AGameModeBase_TowerDefence::StartPlay()
{
	Super::StartPlay();

	CachedGameState = Cast<AGameState_TowerDefence>(GetWorld()->GetGameState());

	// Regist spawning monster logic in "GameState"
	CachedGameState->RegistEvent_StartRound(this, &ThisClass::StartSpawnMonster);

	StartRound_Waiting();	// Start waiting
}

void AGameModeBase_TowerDefence::StartRound_Waiting()
{
    if (IsValid(CachedGameState))
    {
        CachedGameState->SetGameState(ERoundState::Round_Waiting);
    }

    GetWorldTimerManager().SetTimer(
        Timers.FindOrAdd("Waiting"),
        this,
        &ThisClass::StartRound_InProgress,
        WatingTime,
        false
    );
}

void AGameModeBase_TowerDefence::StartRound_InProgress()
{
	if (IsValid(CachedGameState))
    {
        CachedGameState->SetGameState(ERoundState::Round_InProgress);


	}

    GetWorldTimerManager().SetTimer(
        Timers.FindOrAdd("InProgress"),
        this,
        &ThisClass::StartRound_Finished,
        InProgressTime,
        false
    );
}

void AGameModeBase_TowerDefence::StartRound_Finished()
{
	if (IsValid(CachedGameState))
    {
        CachedGameState->SetGameState(ERoundState::Round_Finished);
    }

	/*
	* Temporary hiding
	GetWorldTimerManager().SetTimer(
        Timers.FindOrAdd("Finished"),
        this,
        &ThisClass::StartRound_Waiting,
        FinishedTime,
        false
    );
	*/
}

void AGameModeBase_TowerDefence::StartSpawnMonster()
{
	if (!IsValid(CachedGameState))
    {
		return;
    }

    if (!StageAsset.IsValid())
    {
        StageAsset.LoadSynchronous();
    }

    if (!StageAsset.IsValid() || !StageAsset.Get()->StageWaveInfos.IsValidIndex(CachedGameState->GetCurrentLevel()))
	{
		return;
	}
 
    FStageWaveInfo StageWaveInfo = StageAsset.Get()->StageWaveInfos[CachedGameState->GetCurrentLevel()];
	if (StageWaveInfo.SpawnInterval > 0.f)
    {
		m_iTarget_NumMonster = StageWaveInfo.Count;

		GetWorldTimerManager().SetTimer(
            Timers.FindOrAdd("SpawnMonster"),
            this,
            &ThisClass::OnSpawnMonster,
            StageWaveInfo.SpawnInterval,
            true
        );
    }
}

void AGameModeBase_TowerDefence::OnSpawnMonster()
{
	if (!IsValid(CachedGameState))
    {
        return;
    }

    FStageWaveInfo StageWaveInfo = StageAsset.Get()->StageWaveInfos[CachedGameState->GetCurrentLevel()];
    if (!StageWaveInfo.MonsterAsset.IsValid())
    {
        StageWaveInfo.MonsterAsset.LoadSynchronous();
    }

	if (StageWaveInfo.MonsterAsset.IsValid() && IsValid(StageWaveInfo.MonsterAsset.Get()->MonsterClass))
    {
		if (Grid.IsValid() && Grid->IsSpawnSet())
		{
			--m_iTarget_NumMonster;
			CachedGameState->AddMonster();

			FTransform spawnTrans = Grid->GetSpawnTransform();

			auto&& pMonster = GetWorld()->SpawnActorDeferred<AMonsterBase_TowerDefence>(
				StageWaveInfo.MonsterAsset.Get()->MonsterClass, spawnTrans, nullptr, nullptr,
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
			);
			pMonster->SetupAsset(StageWaveInfo.MonsterAsset.Get());
			pMonster->SetupSplinePath(Grid->GetSpline());
			UGameplayStatics::FinishSpawningActor(pMonster, spawnTrans);
		}
	}

	// Stop spawn timer when finished
	if (m_iTarget_NumMonster == 0)
	{
		SpawnFinish();
	}
}

void AGameModeBase_TowerDefence::SpawnFinish()
{
	GetWorld()->GetTimerManager().ClearTimer(Timers.FindOrAdd("SpawnMonster"));
	
	if (!IsValid(CachedGameState))
	{
		return;
	}

	// TODO: 시간 기다렸다가 Finish 호출하기
}

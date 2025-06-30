// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerState_TowerDefence.h"
#include "UI/UI_Manager.h"
#include "Net/UnrealNetwork.h"

APlayerState_TowerDefence::APlayerState_TowerDefence()
	: MaxHealth(20), CurScore(0), CurHealth(0.f)
{
}

void APlayerState_TowerDefence::PostLoad()
{
	Super::PostLoad();

	CurHealth = MaxHealth;
}

void APlayerState_TowerDefence::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerState_TowerDefence, CurScore);
}

void APlayerState_TowerDefence::OnRep_ScoreEdit()
{
	OnScoreChanged.Broadcast(CurScore);
}

void APlayerState_TowerDefence::AddScore(int32 iScore)
{
	if (HasAuthority())
	{
		CurScore += iScore;
	}
}


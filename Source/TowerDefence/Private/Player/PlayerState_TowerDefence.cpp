// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerState_TowerDefence.h"

APlayerState_TowerDefence::APlayerState_TowerDefence()
	: MaxHealth(20), CurScore(0), CurHealth(0.f)
{
}

void APlayerState_TowerDefence::PostLoad()
{
	Super::PostLoad();

	CurHealth = MaxHealth;
}

void APlayerState_TowerDefence::AddScore(int32 iScore)
{
	CurScore = iScore;
}


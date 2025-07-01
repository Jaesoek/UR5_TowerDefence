// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/TowerAttackComponent.h"
#include "Tower/TowerBase.h"

UTowerAttackComponent::UTowerAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

bool UTowerAttackComponent::Attack(AActor* pTarget)
{
	if (false == IsValid(pTarget))
	{
		return false;
	}

	ATowerBase* pTower = GetTower();
	if (false == IsValid(pTower))
	{
		return false;
	}

	return true;
}

void UTowerAttackComponent::SetState(ETowerState newState)
{
	GetTower()->SetState(newState);
}

bool UTowerAttackComponent::HasAuthority()
{
	return GetOwner()->HasAuthority();
}

ATowerBase* UTowerAttackComponent::GetTower()
{
	return Cast<ATowerBase>(GetOwner());
}


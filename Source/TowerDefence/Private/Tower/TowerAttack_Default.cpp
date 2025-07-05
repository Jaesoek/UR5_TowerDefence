// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/TowerAttack_Default.h"
#include "Tower/TowerBase.h"

bool UTowerAttack_Default::Attack(AActor* pTarget)
{
	if (false == Super::Attack(pTarget))
	{
		return false;
	}

	if (HasAuthority())
	{
		ATowerBase* pTower = GetTower();
		if (ETowerState::ATTACK != pTower->GetCurrentState())
		{
			SetState(ETowerState::ATTACK);

			pTower->TakeDamage(pTarget);
			pTower->Attack_CoolDown();

			return true;
		}
	}

	return false;
}

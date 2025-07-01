// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/TowerAttack_Projectile.h"
#include "Tower/TowerBase.h"

bool UTowerAttack_Projectile::Attack(AActor* pTarget)
{
	if (false == Super::Attack(pTarget))
	{
		return false;
	}

	return false;
}



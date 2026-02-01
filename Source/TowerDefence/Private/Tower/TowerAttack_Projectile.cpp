// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/TowerAttack_Projectile.h"
#include "Tower/TowerBase.h"
#include "Tower/EnergyBall_TowerProjectile.h"
#include "Kismet/GameplayStatics.h"		// For deferred spawning

bool UTowerAttack_Projectile::Attack(AActor* pTarget)
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

			//auto pProj = GetWorld()->SpawnActorDeferred<AEnergyBall_TowerProjectile>(
			//	AEnergyBall_TowerProjectile::StaticClass(), pTower->GetTransform(), nullptr, pTower,
			//	ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			//);
			//pProj->InitInfo(
			//	FProjectileInfo
			//	{
			//		100.f,
			//		200.f,
			//		9.8,
			//		10.f,
			//		pTarget->GetActorLocation(),
			//		vTargetPos
			//	}
			//);
			//UGameplayStatics::FinishSpawningActor(pProj, pTower->GetTransform());

			pTower->Attack_CoolDown();

			return true;
		}
	}

	return false;
}



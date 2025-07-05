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

			// TODO: Spawn projectile
			//  Projectile 정보는 어디서 가져오지?
			//  1안 : TowerAsset Detail에서 저장가능하도록 설정한다(Need to talk)
			//  2안 : 여기서 경로 하드 코딩한다 <- 일단 이걸로 하자
			
			auto pProj = GetWorld()->SpawnActorDeferred<AEnergyBall_TowerProjectile>(
				AEnergyBall_TowerProjectile::StaticClass(), pTower->GetTransform(), nullptr, pTower,
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);
			pProj->InitInfo(
				FProjectileInfo {

				}
			);

			UGameplayStatics::FinishSpawningActor(pProj, pTower->GetTransform());

			pTower->Attack_CoolDown();

			return true;
		}
	}

	return false;
}



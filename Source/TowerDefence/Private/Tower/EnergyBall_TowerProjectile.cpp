// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/EnergyBall_TowerProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Monster/MonsterBase_TowerDefence.h"


AEnergyBall_TowerProjectile::AEnergyBall_TowerProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	// Sphere - Collision
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	if (SphereComp)
	{
		SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
		SphereComp->SetCollisionResponseToAllChannels(ECR_Block);
		SphereComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
		SphereComp->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
		SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		SphereComp->SetMobility(EComponentMobility::Movable);
		SphereComp->SetSimulatePhysics(false);

		RootComponent = SphereComp;
	}

	// Mesh - Rendering
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	if (MeshComp)
	{
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MeshComp->SetMobility(EComponentMobility::Movable);
		MeshComp->SetSimulatePhysics(false);
	
		MeshComp->SetupAttachment(RootComponent);
	}

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
}

void AEnergyBall_TowerProjectile::InitInfo(FProjectileInfo projInfo)
{
	ProjectInfo = projInfo;

	ProjectileMovement->ProjectileGravityScale = ProjectInfo.fGravitySpeed;
	ProjectileMovement->InitialSpeed = ProjectInfo.fInitSpeed;
	ProjectileMovement->MaxSpeed = ProjectInfo.fMaxSpeed;

	if (ProjectInfo.pMesh.ToSoftObjectPath().IsValid())
	{
		ProjectInfo.pMesh.LoadSynchronous();
		MeshComp->SetStaticMesh(ProjectInfo.pMesh.Get());
	}
}

void AEnergyBall_TowerProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Add collision event
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	FVector LaunchVelocity;
	UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		GetActorLocation(),
		ProjectInfo.vTargetPos,
		ProjectInfo.fInitSpeed,
		false, 0.f, 0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	ProjectileMovement->Velocity = LaunchVelocity;
}

void AEnergyBall_TowerProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (false == HasAuthority())
	{
		return;
	}

	auto pMonster = Cast<AMonsterBase_TowerDefence>(OtherActor);
	if (IsValid(pMonster))
	{
		OtherActor->TakeDamage(ProjectInfo.fDamageAmount, FPointDamageEvent{}, GetInstigatorController(), this);

		// TODO: Spawn Effect

		Destroy();
	}
}
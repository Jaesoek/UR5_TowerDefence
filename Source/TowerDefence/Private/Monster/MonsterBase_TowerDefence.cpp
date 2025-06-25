#include "Monster/MonsterBase_TowerDefence.h"
#include "../Public/GameState_TowerDefence.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterAsset.h"
#include "GameModes/GameModeBase_TowerDefence.h"
#include "Components/CapsuleComponent.h"

AMonsterBase_TowerDefence::AMonsterBase_TowerDefence()
	: Health(0.f), Speed(0.f), m_fTargetDistance(0.f), m_fCurDistance(0.f)
{
	PrimaryActorTick.bCanEverTick = true; // ���� �Ⱦ��� ��Ȱ��ȭ

	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	const float fHalfHeight = 50.f;	// Only for init

	UCapsuleComponent* pCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComp"));
	if (IsValid(pCapsule))
	{
		pCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		pCapsule->SetCollisionObjectType(ECC_Pawn);
		pCapsule->SetCollisionResponseToAllChannels(ECR_Block);
		pCapsule->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
		pCapsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

		pCapsule->InitCapsuleSize(30.f, fHalfHeight);
		pCapsule->SetRelativeLocation(FVector(0.f, 0.f, fHalfHeight));
		pCapsule->SetMobility(EComponentMobility::Movable);
		pCapsule->SetSimulatePhysics(false);

		RootComponent = pCapsule;
	}

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	if (IsValid(SkeletalMeshComponent))
	{
		SkeletalMeshComponent->SetupAttachment(RootComponent);
		SkeletalMeshComponent->SetRelativeLocation(FVector{ 0.f, 0.f, -fHalfHeight });
		SkeletalMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
}

void AMonsterBase_TowerDefence::SetupAsset(const UMonsterAsset* InMonsterAsset)
{
	if (!IsValid(InMonsterAsset))
	{
		return;
	}
	
	if (InMonsterAsset->MonsterMesh.ToSoftObjectPath().IsValid())
	{
		USkeletalMesh* SkelMesh = InMonsterAsset->MonsterMesh.LoadSynchronous();
		if (IsValid(SkelMesh))
		{
			SkeletalMeshComponent->SetSkeletalMesh(SkelMesh);
		}
	}

	Health = InMonsterAsset->Health;
	Speed = InMonsterAsset->Speed;
	Score = 10;
}

void AMonsterBase_TowerDefence::SetupSplinePath(TWeakObjectPtr<const USplineComponent> pSplinePath)
{
	if (pSplinePath.IsValid())
	{
		SplinePath = pSplinePath;
		m_fTargetDistance = SplinePath->GetSplineLength();
		m_fCurDistance = 0.f;
	}
	else
	{
		SplinePath = nullptr;
	}
}

float AMonsterBase_TowerDefence::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float finalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= finalDamage;
	if (Health <= 0.f)
	{
		if (HasAuthority())
		{
			GetWorld()->GetAuthGameMode<AGameModeBase_TowerDefence>()->AddScore(EventInstigator, Score);
		}

		Destroy();
	}

	return finalDamage;
}

void AMonsterBase_TowerDefence::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (SplinePath.IsValid())
	{
		m_fCurDistance += Speed * DeltaSeconds;
		if (m_fCurDistance >= m_fTargetDistance)
		{
			Attack();
		}
		else
		{
			const FVector&& vCurLocation = SplinePath->GetLocationAtDistanceAlongSpline(m_fCurDistance, ESplineCoordinateSpace::Type::World);
			const FRotator&& vCurRotator = SplinePath->GetRotationAtDistanceAlongSpline(m_fCurDistance, ESplineCoordinateSpace::Type::World);
			SetActorLocation(vCurLocation);
			SetActorRotation(vCurRotator);
		}
	}
}

void AMonsterBase_TowerDefence::Destroyed()
{
	Super::Destroyed();

	AGameState_TowerDefence* pGameState = GetWorld()->GetGameState<AGameState_TowerDefence>();
	if (IsValid(pGameState))
	{
		pGameState->DecreaseMonster();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("GameState doesnt' exist"));
	}
}

void AMonsterBase_TowerDefence::Attack()
{
	// TODO: Attack to player health
	Destroy();
}


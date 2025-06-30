#include "Monster/MonsterBase_TowerDefence.h"
#include "../Public/GameState_TowerDefence.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterAsset.h"
#include "GameModes/GameModeBase_TowerDefence.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Net/UnrealNetwork.h"

AMonsterBase_TowerDefence::AMonsterBase_TowerDefence()
	: Health(0.f), Speed(0.f), m_fTargetDistance(0.f), m_fCurDistance(0.f)
{
	PrimaryActorTick.bCanEverTick = true; // ���� �Ⱦ��� ��Ȱ��ȭ

	bReplicates = true;

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
		pCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

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

	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComp->SetIsReplicated(true);
}

void AMonsterBase_TowerDefence::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMonsterBase_TowerDefence, MonsterAsset);
	DOREPLIFETIME(AMonsterBase_TowerDefence, Health);
}

void AMonsterBase_TowerDefence::OnRep_MonsterAsset()
{
	if (MonsterAsset->MonsterMesh.ToSoftObjectPath().IsValid())
	{
		USkeletalMesh* SkelMesh = MonsterAsset->MonsterMesh.LoadSynchronous();
		if (IsValid(SkelMesh))
		{
			SkeletalMeshComponent->SetSkeletalMesh(SkelMesh);
			SkeletalMeshComponent->SetAnimInstanceClass(MonsterAsset->AnimInstance);
		}

		if (MonsterAsset->MontageHit.IsValid())
		{
			MonsterAsset->MontageHit.LoadSynchronous();
			MontageHit = MonsterAsset->MontageHit.Get();
		}
	}
}

void AMonsterBase_TowerDefence::OnRep_Damaged()
{
	if (IsValid(MontageHit) && !SkeletalMeshComponent->GetAnimInstance()->Montage_IsPlaying(MontageHit))
	{
		SkeletalMeshComponent->GetAnimInstance()->Montage_Play(MontageHit);
	}
}

void AMonsterBase_TowerDefence::SetupAsset(TObjectPtr<UMonsterAsset> InMonsterAsset)
{
	if (!IsValid(InMonsterAsset))
	{
		return;
	}

	if (HasAuthority())
	{
		MonsterAsset = InMonsterAsset;

		Health = MonsterAsset->Health;
		Speed = MonsterAsset->Speed;
		Score = 10;
	}
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
	if (false == HasAuthority())
	{
		return 0.f;
	}

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

	if (HasAuthority())
	{
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
				FVector Direction = (vCurLocation - GetActorLocation()).GetSafeNormal();
				MovementComp->AddInputVector(Direction * Speed);

				FVector Velocity = GetVelocity();
				Velocity.Z = 0.f;
				if (!Velocity.IsNearlyZero())
				{
					FRotator CurrentRotation = GetActorRotation();
					FRotator TargetRotation = Velocity.ToOrientationRotator();

					FRotator NewRotation;
					const float RotationTolerance = 1.0f;
					if (CurrentRotation.Equals(TargetRotation, RotationTolerance))
					{
						NewRotation = TargetRotation;
					}
					else
					{
						NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, 10.f);
					}
					SetActorRotation(NewRotation);
				}
			}
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


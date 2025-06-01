#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_TowerDefence.generated.h"

UCLASS()
class TOWERDEFENCE_API APlayer_TowerDefence : public ACharacter
{
	GENERATED_BODY()

public:
	APlayer_TowerDefence();

protected:
	virtual void Tick(float DeltaSeconds) override;

	bool CheckEdge(FVector2D& v2MouseDir);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (DisableEditOnInstance))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (DisableEditOnInstance))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MovementInfo)
	float m_fCamSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Info")
	int32 m_iPlayer_Hp;

public:
	int32 GetPlayerHp() const { return m_iPlayer_Hp; }
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputComponent_MouseMoving.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENCE_API UInputComponent_MouseMoving : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputComponent_MouseMoving();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	bool EdgeChecking(FVector2D& v2MouseDir);
		
	
};

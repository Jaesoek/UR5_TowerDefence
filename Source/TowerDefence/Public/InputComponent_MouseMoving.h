#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputComponent_MouseMoving.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENCE_API UInputComponent_MouseMoving : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInputComponent_MouseMoving();

public:
	bool EdgeChecking(FVector2D& v2MouseDir);
		
	
};

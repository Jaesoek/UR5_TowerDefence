#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ControlUnit.generated.h"

UINTERFACE(MinimalAPI)
class UControlUnit : public UInterface
{
	GENERATED_BODY()
};

// 실제 Interface 선언 및 함수 정의
class IControlUnit
{
	GENERATED_BODY()

public:
	virtual void OnFocused() = 0;
};
#pragma once

#include "CoreMinimal.h"

class TOWERDEFENCE_API IControlUnit
{
public:
	IControlUnit();
	virtual ~IControlUnit();

public:
	virtual void OnFocused() {};
};

#pragma once

#include "Modules/ModuleManager.h"

class FDetailCustomizeModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
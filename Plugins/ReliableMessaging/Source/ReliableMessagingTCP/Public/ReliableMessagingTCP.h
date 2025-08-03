#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FReliableMessagingTCPModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
	FDelegateHandle FactoryDelegateHandle;
};

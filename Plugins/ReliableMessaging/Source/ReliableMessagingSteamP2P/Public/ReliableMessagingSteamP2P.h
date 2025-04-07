#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FReliableMessagingSteamP2PModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
	FDelegateHandle FactoryDelegateHandle;
};

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FOnlineIntegrationEditorModule : public IModuleInterface
{
protected:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

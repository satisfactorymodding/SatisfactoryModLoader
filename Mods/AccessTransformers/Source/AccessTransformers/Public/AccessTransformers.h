#pragma once
#include "CoreMinimal.h"
#include "ContentBrowserDelegates.h"
#include "Interfaces/IPluginManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAccessTransformers, Verbose, All);

class FAccessTransformersModule : public IModuleInterface {
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

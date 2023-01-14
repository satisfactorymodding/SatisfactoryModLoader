#pragma once
#include "CoreMinimal.h"
#include "ContentBrowserDelegates.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAlpakit, Verbose, All);

class FAlpakitModule : public IModuleInterface {
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    
    /** ID name for the mod creator tab */
    static const FName ModCreatorTabName;
private:
    TSharedPtr<class FUICommandList> PluginCommands;

    TSharedRef<SDockTab> HandleSpawnModCreatorTab(const FSpawnTabArgs& SpawnTabArgs);
    
    void RegisterSettings() const;
    void UnregisterSettings() const;
};

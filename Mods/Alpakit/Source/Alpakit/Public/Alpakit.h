#pragma once
#include "CoreMinimal.h"
#include "ContentBrowserDelegates.h"
#include "Interfaces/IPluginManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAlpakit, Verbose, All);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQueueChanged, TArray<FString>)
DECLARE_MULTICAST_DELEGATE(FOnQueueStarted)
DECLARE_MULTICAST_DELEGATE(FOnQueueComplete)

class FAlpakitModule : public IModuleInterface {
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    void PackageMods(TArray<FString> PluginNames, bool ReleaseBuild);

    FOnQueueStarted& GetOnQueueStarted() { return OnQueueStarted; }
    FOnQueueChanged& GetOnQueueChanged() { return OnQueueChanged; }
    FOnQueueComplete& GetOnQueueComplete() { return OnQueueComplete; }
    
    TArray<TSharedRef<struct FModTemplateDescription>> GetModTemplates() const { return ModTemplates; }
    
    /** ID name for the mod creator tab */
    static const FName ModCreatorTabName;
private:
    TSharedPtr<class FUICommandList> PluginCommands;

    TSharedRef<SDockTab> HandleSpawnModCreatorTab(const FSpawnTabArgs& SpawnTabArgs);
    
    void RegisterSettings() const;
    void UnregisterSettings() const;

    void ProcessQueue();
    void ProcessQueueItem(FString PluginName, bool bIsLastItem);
    FCriticalSection QueueLock;
	TArray<FString> ModQueue;
    bool bReleaseBuild = false;
    bool QueueRunning = false;

    FOnQueueStarted OnQueueStarted;
    FOnQueueChanged OnQueueChanged;
    FOnQueueComplete OnQueueComplete;

    void RegisterModTemplates();
    void AddModTemplatesFromPlugin(IPlugin& Plugin);
    TArray<TSharedRef<struct FModTemplateDescription>> ModTemplates;
};

#pragma once
#include "CoreMinimal.h"
#include "AlpakitProfile.h"
#include "Interfaces/IPluginManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAlpakit, Verbose, All);

class FAlpakitModule : public IModuleInterface {
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    static FAlpakitModule& Get() { return FModuleManager::GetModuleChecked<FAlpakitModule>("Alpakit"); }

    TArray<TSharedRef<struct FModTemplateDescription>> GetModTemplates() const { return ModTemplates; }

	void PackageModsDevelopment(TArray<TSharedRef<IPlugin>> Mods);
	void PackageModsRelease(TArray<TSharedRef<IPlugin>> Mods);
	void PackageMods(TArray<TSharedRef<FAlpakitProfile>> ProfilesToPackage);
	bool IsPackaging() const { return bIsPackaging; }

	static FString GetCurrentSMLVersion();
	static FString GetCurrentGameVersion();

	static const FName AlpakitDevTabName;
	static const FName AlpakitReleaseTabName;
    static const FName ModCreatorTabName;
	static const FName AlpakitLogTabName;
private:
    TSharedPtr<class FUICommandList> PluginCommands;

    TSharedRef<SDockTab> HandleSpawnModCreatorTab(const FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<SDockTab> HandleSpawnAlpakitLogTab(const FSpawnTabArgs& SpawnTabArgs);
    
    void RegisterSettings() const;
    void UnregisterSettings() const;

    void RegisterModTemplates();
    void AddModTemplatesFromPlugin(IPlugin& Plugin);
    TArray<TSharedRef<struct FModTemplateDescription>> ModTemplates;

	bool bIsPackaging = false;
	TArray<TSharedRef<FAlpakitProfile>> ProfilePackageQueue; 
	void ProcessQueueItem();
};

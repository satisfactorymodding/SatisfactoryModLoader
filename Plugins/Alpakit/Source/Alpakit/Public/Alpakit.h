#pragma once
#include "CoreMinimal.h"
#include "ContentBrowserDelegates.h"
#include "AlpakitSettings.h"
#include "AssetData.h"
#include "Dom/JsonObject.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAlpakit, Verbose, Verbose);

struct FPakListEntry {
	FString AssetFilePathOnDisk;
	FString AssetPathInPakFile;
	FString ToString() const;
};

struct FModPackingProgress {
	TArray<FAlpakitMod> ModsToPack;
	int32 CurrentModIndex;
	TArray<FPakListEntry> PakListEntries;
	TFunction<void(bool bSuccess, const FString& ErrorMessage)> OriginalFinishCallback;
};

class FAlpakitModule : public IModuleInterface {
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Packs mod assets according to UAlpakitSettings configuration */
	virtual void PackModAssets(TFunction<void(bool bSuccess, const FString& ErrorMessage)> PackingFinished);
private:
	TSharedPtr<class FUICommandList> PluginCommands;

	void FinishModAssetPacking(const FString& AutomationToolLogDir, const FString& AutomationToolReturnCode, TFunction<void(bool bSuccess, const FString& ErrorMessage)> PackingFinishedCallback);
	static void RunUnrealPak(const FString& PakListFilePath, const FString& OutputPakFilePath, TFunction<void(bool bSuccess, const FString& ErrorMessage)> PackingFinishedCallback);
	static void ProcessSingleModPackage(const TSharedPtr<FModPackingProgress>& PackingProgress);
	static void PerformPostProcessTasks(const TSharedPtr<FModPackingProgress>& PackingProgress);
	static void SerializeModInfoToDataJson(const TSharedRef<FJsonObject>& DataJson, const FAlpakitMod& ModInfo);

	/** Returns automation tool log directory path used by UAT used with current engine */
	static FString GetAutomationToolLogDir();
	/** Returns project directory path, falling back to engine root with project name if necessary */
	static FString GetProjectPathWithFallback();

	void RegisterConsoleCommands();
	void HandleAlpakitConsoleCommand();
	
	void OnExtendContentBrowserCommands(TSharedRef<FUICommandList> CommandList, FOnContentBrowserGetSelection GetSelectionDelegate);
	void OpenAlpakitOverwriteUI(TArray<FName> SelectedPackages) const;
	void OpenAlpakitOverwriteUI(TArray<FAssetIdentifier> SelectedIdentifiers) const;
	TArray<FName> GetContentBrowserSelectedAssetPackages(FOnContentBrowserGetSelection GetSelectionDelegate) const;
	void GetAssetDataInPaths(const TArray<FString>& Paths, TArray<FAssetData>& OutAssetData) const;

	static void CreateAssetContextMenu(FMenuBuilder& MenuBuilder);
	static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets);
	static TSharedRef<FExtender> OnExtendContentBrowserPathSelectionMenu(const TArray<FString>& SelectedPaths);
	TSharedRef<FExtender> OnExtendAssetEditor(const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects);

	void RegisterSettings() const;
	void UnregisterSettings() const;
};

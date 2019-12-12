// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ContentBrowserDelegates.h"
#include "Modules/ModuleManager.h"
#include "AlpakitSettings.h"
#include "AssetData.h"
#include "AssetRegistryModule.h"
#include "ContentBrowserDelegates.h"

class FToolBarBuilder;
class FMenuBuilder;

class FAlpakitModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> SpawnAlpakitOverwriteTab(const class FSpawnTabArgs& SpawnTabArgs);
	void OnExtendContentBrowserCommands(TSharedRef<FUICommandList> CommandList, FOnContentBrowserGetSelection GetSelectionDelegate);
	void OpenAlpakitOverwriteUI(TArray<FName> SelectedPackages);
	void OpenAlpakitOverwriteUI(TArray<FAssetIdentifier> SelectedIdentifiers);
	TArray<FName> GetContentBrowserSelectedAssetPackages(FOnContentBrowserGetSelection GetSelectionDelegate);
	void GetAssetDataInPaths(const TArray<FString>& Paths, TArray<FAssetData>& OutAssetData);
	IAssetRegistry* AssetRegistry;
	FDelegateHandle ContentBrowserCommandExtenderDelegateHandle;
	FDelegateHandle ContentBrowserAssetExtenderDelegateHandle;
	FDelegateHandle ContentBrowserPathExtenderDelegateHandle;
	FDelegateHandle AssetEditorExtenderDelegateHandle;
	void CreateAssetContextMenu(FMenuBuilder& MenuBuilder);
	TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets);
	TSharedRef<FExtender> OnExtendContentBrowserPathSelectionMenu(const TArray<FString>& SelectedPaths);
	TSharedRef<FExtender> OnExtendAssetEditor(const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
	bool HandleSettingsSaved();
	void RegisterSettings();
	void UnregisterSettings();
};

// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Alpakit.h"
#include "AlpakitStyle.h"
#include "AlpakitCommands.h"
#include "AlpakitWidget.h"
#include "AlpakitOverwriteWidget.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "AlpakitSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "ARFilter.h"
#include "ContentBrowserDelegates.h"
#include "ContentBrowserModule.h"
#include "PropertyEditorModule.h"
#include "GenericPlatform/GenericPlatformProcess.h"

static const FName AlpakitTabName("Alpakit");
static const FName AlpakitOverwriteTabName("AlpakitOverwrite");
static const FName AlpakitModInfoTabName("AlpakitModInfo");

#define LOCTEXT_NAMESPACE "FAlpakitModule"

// A lot of the stuff here is literally copy paste from https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/AssetManagerEditorModule.cpp

void FAlpakitModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	AssetRegistry = &AssetRegistryModule.Get();
	
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	TArray<FContentBrowserMenuExtender_SelectedAssets>& CBAssetMenuExtenderDelegates = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();
	CBAssetMenuExtenderDelegates.Add(FContentBrowserMenuExtender_SelectedAssets::CreateRaw(this, &FAlpakitModule::OnExtendContentBrowserAssetSelectionMenu));
	ContentBrowserAssetExtenderDelegateHandle = CBAssetMenuExtenderDelegates.Last().GetHandle();

	TArray<FContentBrowserMenuExtender_SelectedPaths>& CBPathExtenderDelegates = ContentBrowserModule.GetAllPathViewContextMenuExtenders();
	CBPathExtenderDelegates.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this, &FAlpakitModule::OnExtendContentBrowserPathSelectionMenu));
	ContentBrowserPathExtenderDelegateHandle = CBPathExtenderDelegates.Last().GetHandle();

	TArray<FContentBrowserCommandExtender>& CBCommandExtenderDelegates = ContentBrowserModule.GetAllContentBrowserCommandExtenders();
	CBCommandExtenderDelegates.Add(FContentBrowserCommandExtender::CreateRaw(this, &FAlpakitModule::OnExtendContentBrowserCommands));
	ContentBrowserCommandExtenderDelegateHandle = CBCommandExtenderDelegates.Last().GetHandle();

	// Register asset editor hooks
	TArray<FAssetEditorExtender>& AssetEditorMenuExtenderDelegates = FAssetEditorToolkit::GetSharedMenuExtensibilityManager()->GetExtenderDelegates();
	AssetEditorMenuExtenderDelegates.Add(FAssetEditorExtender::CreateRaw(this, &FAlpakitModule::OnExtendAssetEditor));
	AssetEditorExtenderDelegateHandle = AssetEditorMenuExtenderDelegates.Last().GetHandle();

	RegisterSettings();
	
	FAlpakitStyle::Initialize();
	FAlpakitStyle::ReloadTextures();

	FAlpakitCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAlpakitCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAlpakitModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("FileProject", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FAlpakitModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FAlpakitModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AlpakitTabName, FOnSpawnTab::CreateRaw(this, &FAlpakitModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAlpakitTabTitle", "Alpakit"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AlpakitOverwriteTabName, FOnSpawnTab::CreateRaw(this, &FAlpakitModule::SpawnAlpakitOverwriteTab))
		.SetDisplayName(LOCTEXT("AlpakitOverwriteTitle", "Overwrite in mod"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("Alpakit"), TEXT("Executes Alpakit!"), FConsoleCommandDelegate::CreateStatic(([]() {
		UE_LOG(LogTemp, Warning, TEXT("Start Alpakit"));
		TPromise<void> promise;
		TFuture<void> future = promise.GetFuture();
        SAlpakaWidget::Alpakit([&promise]() {
        	UE_LOG(LogTemp, Warning, TEXT("Alpakit Finishing..."));
			promise.EmplaceValue();
        });
		future.Wait();
		UE_LOG(LogTemp, Warning, TEXT("Alpakit Done"));
    })));
}

void FAlpakitModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (UObjectInitialized())
	{
		UnregisterSettings();
	}

	FAlpakitStyle::Shutdown();

	FAlpakitCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AlpakitTabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AlpakitOverwriteTabName);
}

TSharedRef<SDockTab> FAlpakitModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SAlpakaWidget)
		];
}

TSharedRef<SDockTab> FAlpakitModule::SpawnAlpakitOverwriteTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SAlpakitOverwriteWidget)
		];
}

void FAlpakitModule::CreateAssetContextMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FAlpakitCommands::Get().AlpakitOverwrite);
}

TSharedRef<FExtender> FAlpakitModule::OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets)
{
	TSharedRef<FExtender> Extender(new FExtender());

	Extender->AddMenuExtension(
		"AssetContextReferences",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateRaw(this, &FAlpakitModule::CreateAssetContextMenu));

	return Extender;
}

TSharedRef<FExtender> FAlpakitModule::OnExtendContentBrowserPathSelectionMenu(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> Extender(new FExtender());

	Extender->AddMenuExtension(
		"PathContextBulkOperations",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateRaw(this, &FAlpakitModule::CreateAssetContextMenu));

	return Extender;
}

TSharedRef<FExtender> FAlpakitModule::OnExtendAssetEditor(const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects)
{
	TArray<FName> PackageNames;
	for (UObject* EditedAsset : ContextSensitiveObjects)
	{
		if (EditedAsset && EditedAsset->IsAsset() && !EditedAsset->IsPendingKill())
		{
			PackageNames.AddUnique(EditedAsset->GetOutermost()->GetFName());
		}
	}

	TSharedRef<FExtender> Extender(new FExtender());

	if (PackageNames.Num() > 0)
	{
		// It's safe to modify the CommandList here because this is run as the editor UI is created and the payloads are safe
		CommandList->MapAction(
			FAlpakitCommands::Get().AlpakitOverwrite,
			FExecuteAction::CreateRaw(this, &FAlpakitModule::OpenAlpakitOverwriteUI, PackageNames));

		Extender->AddMenuExtension(
			"FindInContentBrowser",
			EExtensionHook::After,
			CommandList,
			FMenuExtensionDelegate::CreateRaw(this, &FAlpakitModule::CreateAssetContextMenu));
	}

	return Extender;
}

void FAlpakitModule::GetAssetDataInPaths(const TArray<FString>& Paths, TArray<FAssetData>& OutAssetData)
{
	// Form a filter from the paths
	FARFilter Filter;
	Filter.bRecursivePaths = true;
	for (const FString& Path : Paths)
	{
		new (Filter.PackagePaths) FName(*Path);
	}

	// Query for a list of assets in the selected paths
	AssetRegistry->GetAssets(Filter, OutAssetData);
}

TArray<FName> FAlpakitModule::GetContentBrowserSelectedAssetPackages(FOnContentBrowserGetSelection GetSelectionDelegate)
{
	TArray<FName> OutAssetPackages;
	TArray<FAssetData> SelectedAssets;
	TArray<FString> SelectedPaths;

	if (GetSelectionDelegate.IsBound())
	{
		GetSelectionDelegate.Execute(SelectedAssets, SelectedPaths);
	}

	GetAssetDataInPaths(SelectedPaths, SelectedAssets);

	TArray<FName> PackageNames;
	for (const FAssetData& AssetData : SelectedAssets)
	{
		OutAssetPackages.AddUnique(AssetData.PackageName);
	}

	return OutAssetPackages;
}

void FAlpakitModule::OnExtendContentBrowserCommands(TSharedRef<FUICommandList> CommandList, FOnContentBrowserGetSelection GetSelectionDelegate)
{
	CommandList->MapAction(FAlpakitCommands::Get().AlpakitOverwrite,
		FExecuteAction::CreateLambda([this, GetSelectionDelegate]
		{
			OpenAlpakitOverwriteUI(GetContentBrowserSelectedAssetPackages(GetSelectionDelegate));
		})
	);
}

void FAlpakitModule::OpenAlpakitOverwriteUI(TArray<FName> SelectedPackages)
{
	TArray<FAssetIdentifier> Identifiers;
	for (FName Name : SelectedPackages)
	{
		Identifiers.Add(FAssetIdentifier(Name));
	}

	OpenAlpakitOverwriteUI(Identifiers);
}

void FAlpakitModule::OpenAlpakitOverwriteUI(TArray<FAssetIdentifier> SelectedIdentifiers)
{
	if (SelectedIdentifiers.Num() > 0)
	{
		TSharedRef<SDockTab> NewTab = FGlobalTabmanager::Get()->InvokeTab(AlpakitOverwriteTabName);
		TSharedRef<SAlpakitOverwriteWidget> ReferenceViewer = StaticCastSharedRef<SAlpakitOverwriteWidget>(NewTab->GetContent());
		ReferenceViewer->SetPathsToOverwrite(SelectedIdentifiers);
	}
}

void FAlpakitModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(AlpakitTabName);
}

void FAlpakitModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FAlpakitCommands::Get().OpenPluginWindow);
}

void FAlpakitModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FAlpakitCommands::Get().OpenPluginWindow);
}


// Callback for when the settings were saved.
bool FAlpakitModule::HandleSettingsSaved()
{
	UAlpakitSettings* Settings = GetMutableDefault<UAlpakitSettings>();
	bool ResaveSettings = false;

	// You can put any validation code in here and resave the settings in case an invalid
	// value has been entered

	if (ResaveSettings)
	{
		Settings->SaveConfig();
	}

	return true;
}

void FAlpakitModule::RegisterSettings()
{
	// Registering some settings is just a matter of exposing the default UObject of
	// your desired class, feel free to add here all those settings you want to expose
	// to your LDs or artists.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");
		SettingsContainer->DescribeCategory("Alpakit Settings",
			LOCTEXT("RuntimeWDCategoryName", "Alpakit Settings"),
			LOCTEXT("RuntimeWDCategoryDescription", "Alpakit Settings. Can also be edited in the Alpakit menu"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Alpakit", "General",
			LOCTEXT("RuntimeGeneralSettingsName", "General"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Alpakit Settings. Can also be edited in the Alpakit menu"),
			GetMutableDefault<UAlpakitSettings>()
		);

		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FAlpakitModule::HandleSettingsSaved);
		}
	}
}

void FAlpakitModule::UnregisterSettings()
{
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Alpakit", "General");
	}
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAlpakitModule, Alpakit)
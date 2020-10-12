#include "Alpakit.h"

#include "AlpakitStyle.h"
#include "AlpakitCommands.h"
#include "AlpakitWidget.h"
#include "AlpakitOverwriteWidget.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "AlpakitSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "ARFilter.h"
#include "AssetRegistryModule.h"
#include "ContentBrowserDelegates.h"
#include "ContentBrowserModule.h"
#include "IAssetRegistry.h"
#include "SatisfactoryModLoader.h"
#include "UATHelper/Public/IUATHelperModule.h"

static const FName AlpakitTabName("Alpakit");
static const FName AlpakitOverwriteTabName("AlpakitOverwrite");

#define LOCTEXT_NAMESPACE "FAlpakitModule"

DEFINE_LOG_CATEGORY(LogAlpakit)

void FAlpakitModule::StartupModule() {
	//Register editor settings
	RegisterSettings();

	//Register console commands
	RegisterConsoleCommands();

	//Initialize Slate stuff, including commands
	FAlpakitStyle::Initialize();
	FAlpakitStyle::ReloadTextures();
	FAlpakitCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FAlpakitCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateLambda([](){
			FGlobalTabmanager::Get()->InvokeTab(AlpakitTabName);
		}),
		FCanExecuteAction());
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	//Register Alpakit Settings in Editor's Project Menu
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuExtension("FileProject", EExtensionHook::After, PluginCommands,
		FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& Builder){
			Builder.AddMenuEntry(FAlpakitCommands::Get().OpenPluginWindow);
		}));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	
	//Register Alpakit Settings in Editor's Toolbar
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands,
		FToolBarExtensionDelegate::CreateLambda([](FToolBarBuilder& Builder) {
			Builder.AddToolBarButton(FAlpakitCommands::Get().OpenPluginWindow);
		}));
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);

	//Register normal alpakit settings tab spawner
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AlpakitTabName,
		FOnSpawnTab::CreateLambda([](const FSpawnTabArgs&){
			TSharedRef<SAlpakitWidget> AlpakitWidget = SNew(SAlpakitWidget);
			return SNew(SDockTab)
				.TabRole(NomadTab)
				//Save settings when tab is closed automatically
				.OnTabClosed_Lambda([AlpakitWidget](TSharedRef<SDockTab>) { AlpakitWidget->SaveSettings(); })
				[ AlpakitWidget ];
		}))
		.SetDisplayName(LOCTEXT("FAlpakitTabTitle", "Alpakit"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	//Register alpakit overwrites tab spawner
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AlpakitOverwriteTabName,
		FOnSpawnTab::CreateLambda([](const FSpawnTabArgs&){
			TSharedRef<SAlpakitOverwriteWidget> OverwriteWidget = SNew(SAlpakitOverwriteWidget);
		    return SNew(SDockTab)
				.TabRole(NomadTab)
				//Save settings when tab is closed automatically
				.OnTabClosed_Lambda([OverwriteWidget](TSharedRef<SDockTab>) { OverwriteWidget->SaveSettings(); })
				[ OverwriteWidget ];
		}))
		.SetDisplayName(LOCTEXT("AlpakitOverwriteTitle", "Overwrite in mod"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	//Register content browsers extensions
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	const auto SelectedAssetsDelegate = FContentBrowserMenuExtender_SelectedAssets::CreateStatic(&FAlpakitModule::OnExtendContentBrowserAssetSelectionMenu);
	auto& CBAssetMenuExtenderDelegates = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();
	CBAssetMenuExtenderDelegates.Add(SelectedAssetsDelegate);

	const auto SelectedPathsDelegate = FContentBrowserMenuExtender_SelectedPaths::CreateStatic(&FAlpakitModule::OnExtendContentBrowserPathSelectionMenu);
	auto& CBPathExtenderDelegates = ContentBrowserModule.GetAllPathViewContextMenuExtenders();
	CBPathExtenderDelegates.Add(SelectedPathsDelegate);

	const auto ContentBrowserCommandExtender = FContentBrowserCommandExtender::CreateRaw(this, &FAlpakitModule::OnExtendContentBrowserCommands);
	auto& CBCommandExtenderDelegates = ContentBrowserModule.GetAllContentBrowserCommandExtenders();
	CBCommandExtenderDelegates.Add(ContentBrowserCommandExtender);

	const auto AssetEditorExtenderDelegate = FAssetEditorExtender::CreateRaw(this, &FAlpakitModule::OnExtendAssetEditor);
	TArray<FAssetEditorExtender>& AssetEditorMenuExtenderDelegates = FAssetEditorToolkit::GetSharedMenuExtensibilityManager()->GetExtenderDelegates();
	AssetEditorMenuExtenderDelegates.Add(AssetEditorExtenderDelegate);
}

void FAlpakitModule::ShutdownModule() {
	if (UObjectInitialized()) {
		UnregisterSettings();
	}
	FAlpakitStyle::Shutdown();
	FAlpakitCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AlpakitTabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AlpakitOverwriteTabName);
}

struct FNotificationItemHolder {
	TWeakPtr<SNotificationItem> NotificationItem;
};

TFunction<void(bool bSuccess, const FString& FailureReason)> SpawnModContentPackingNotification() {
	const TStatId StatIdEmpty;
	TSharedPtr<FNotificationItemHolder> NotificationItemHolder = MakeShareable(new FNotificationItemHolder());

	const FGraphEventRef TaskRef = FFunctionGraphTask::CreateAndDispatchWhenReady([NotificationItemHolder](){
		FNotificationInfo Info(LOCTEXT("ModPackingInProcessNotification", "Alpakit: Packing Mod Assets"));
        Info.bFireAndForget = false;
        Info.FadeOutDuration = 0.0f;
        Info.ExpireDuration = 0.0f;
	
        TSharedPtr<SNotificationItem> NotificationInfo = FSlateNotificationManager::Get().AddNotification(Info);
        NotificationInfo->SetCompletionState(SNotificationItem::CS_Pending);
        const TWeakPtr<SNotificationItem> NotificationItemPtr = NotificationInfo;
        GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileStart_Cue.CompileStart_Cue"));
		NotificationItemHolder->NotificationItem = NotificationInfo;
		
	}, StatIdEmpty, NULL, ENamedThreads::GameThread);

	//Wait for notification spawning
	FTaskGraphInterface::Get().WaitUntilTaskCompletes(TaskRef);
	check(NotificationItemHolder->NotificationItem.IsValid());
	
	return [NotificationItemHolder, StatIdEmpty](bool bSuccess, const FString& FailureReason){
		FFunctionGraphTask::CreateAndDispatchWhenReady([NotificationItemHolder, bSuccess, FailureReason](){
			if (NotificationItemHolder->NotificationItem.IsValid()) {
				TSharedPtr<SNotificationItem> NotificationItem = NotificationItemHolder->NotificationItem.Pin();
                if (bSuccess) {
                    GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileSuccess_Cue.CompileSuccess_Cue"));
                    NotificationItem->SetCompletionState(SNotificationItem::CS_Success);
                    NotificationItem->SetText(LOCTEXT("PackingFailure", "Finished packing successfully"));
                } else {
                    GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileFailed_Cue.CompileFailed_Cue"));
                    NotificationItem->SetCompletionState(SNotificationItem::CS_Fail);
                    FFormatNamedArguments Arguments;
                    Arguments.Add(TEXT("Reason"), FText::FromString(FailureReason));
                    NotificationItem->SetText(FText::Format(LOCTEXT("PackingFailure", "Failed to pack mod assets: {Reason}"), Arguments));
                }
                NotificationItem->SetExpireDuration(3.0f);
                NotificationItem->SetFadeOutDuration(0.5f);
                NotificationItem->ExpireAndFadeout();
			}
		}, StatIdEmpty, NULL, ENamedThreads::GameThread);
	};
}

void FAlpakitModule::PackModAssets(TFunction<void(bool bSuccess, const FString& FailureReason)> PackingFinished) {
	//Make sure Settings are saved at this point
	UAlpakitSettings::Get()->SaveSettings();
	
	//Ensure we have WWiseAudio content directory before build (WWise requires it)
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const FString WwiseAudioDirectory = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("WwiseAudio"));
	PlatformFile.CreateDirectory(*WwiseAudioDirectory);

	//Clear AutomationTool log directory prior to running the tool again
	const FString AutomationToolLogDir = GetAutomationToolLogDir();
	PlatformFile.DeleteDirectoryRecursively(*AutomationToolLogDir);

	//Run the BuildCookRun Automation task and display progress in editor
	const FString ProjectPath = GetProjectPathWithFallback();
	const FString CommandLine = FString::Printf(TEXT("BuildCookRun -nop4 -project=\"%s\" -cook -package -pak -skipstage -iterate"), *ProjectPath);

	IUATHelperModule::Get().CreateUatTask(CommandLine,
		FText::FromString("Windows"),
		FText::FromString("Cooking content"),
		FText::FromString("Cooking"), nullptr,
		[this, PackingFinished, AutomationToolLogDir](const FString& CookingResult, double /*RunTimeSeconds*/) {
			FinishModAssetPacking(AutomationToolLogDir, CookingResult, PackingFinished);
    });
}

FString MakePackageListFilePath(const FString& LogDirPath, const FString& ProjectName) {
	const FString PakListName = FString::Printf(TEXT("PakList_%s-WindowsNoEditor.txt"), *ProjectName);
	return FPaths::Combine(LogDirPath, PakListName);
}

FString FPakListEntry::ToString() const {
	return FString::Printf(TEXT("\"%s\" \"%s\""), *AssetFilePathOnDisk, *AssetPathInPakFile);
}

void FAlpakitModule::FinishModAssetPacking(const FString& AutomationToolLogDir, const FString& AutomationToolReturnCode, TFunction<void(bool bSuccess, const FString& FailureReason)> PackingFinishedCallback) {
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	auto NotificationFuture = SpawnModContentPackingNotification();
	
	const TFunction<void(bool, const FString&)> CombinedFuture = [NotificationFuture, PackingFinishedCallback](bool bSuccess, const FString& FailureReason){
		NotificationFuture(bSuccess, FailureReason);
		PackingFinishedCallback(bSuccess, FailureReason);
	};
	
	if (!AutomationToolReturnCode.Equals(TEXT("Completed"), ESearchCase::IgnoreCase)) {
		UE_LOG(LogAlpakit, Error, TEXT("Packing Mod Content failed: AutomationTool returned %s"), *AutomationToolReturnCode);
		CombinedFuture(false, TEXT("AutomationTool failed to complete"));
		return;
	}
	const FString PackageListFilePath = MakePackageListFilePath(AutomationToolLogDir, FApp::GetProjectName());
	if (!PlatformFile.FileExists(*PackageListFilePath)) {
		UE_LOG(LogAlpakit, Error, TEXT("Packing Mod Content failed: PakList file not found at %s"), *PackageListFilePath);
		CombinedFuture(false, TEXT("PakList file not found"));
		return;
	}
	TArray<FString> FilesToPak;
	const bool bReadSuccess = FFileHelper::LoadFileToStringArray(FilesToPak, *PackageListFilePath);
	if (!bReadSuccess) {
		UE_LOG(LogAlpakit, Error, TEXT("Packing Mod Content failed: Failed to open pak list file at %s"), *PackageListFilePath);
		CombinedFuture(false, TEXT("PakList file failed to open"));
		return;
	}
	UAlpakitSettings* Settings = UAlpakitSettings::Get();
	//Initialize primary settings and call common function for each mod
	TSharedPtr<FModPackingProgress> ModPackingProgress = MakeShareable(new FModPackingProgress());
	ModPackingProgress->ModsToPack = Settings->Mods;
	ModPackingProgress->OriginalFinishCallback = CombinedFuture;
	TArray<FPakListEntry>& PakListEntries = ModPackingProgress->PakListEntries;
	
	for (const FString& PakListLine : FilesToPak) {
		const TCHAR* LinePtr = *PakListLine;
		FPakListEntry& PakListEntry = PakListEntries.AddDefaulted_GetRef();
		FParse::Token(LinePtr, PakListEntry.AssetFilePathOnDisk, false);
		FParse::Token(LinePtr, PakListEntry.AssetPathInPakFile, false);
	}
	
	ProcessSingleModPackage(ModPackingProgress);
}

//Converts raw .PAK file path to asset path used in unreal engine asset system
//Since not all files in pack represent unreal engine assets, some of them will fail conversion,
//in that case empty string will be returned
FString FormatPakListAssetPath(const FString& AssetPath) {
	if (!AssetPath.StartsWith(TEXT("../../../"))) {
		//We should never encounter assets that don't follow that convention, might as well hard crash at this point
		return TEXT("");
	}
	//Remove beginning parts and extension to get normal asset path
	int32 ExtensionIndex;
	AssetPath.FindLastChar(TEXT('.'), ExtensionIndex);
	//If there is no extension, we cut to the end of the string
	if (ExtensionIndex == INDEX_NONE) {
		ExtensionIndex = AssetPath.Len();
	}
	//Now we have asset path in form of (/FactoryGame/Content|/Engine/Content)/SML/ModDescriptionTextStyle
	//We need to get rid of content and prefix it all with either engine or game
	const FString IntermediateAssetPath = AssetPath.Mid(8, ExtensionIndex - 8);
	const FString GameProjectPath = FString::Printf(TEXT("/%s/Content/"), FApp::GetProjectName());
	const FString EnginePath = TEXT("/Engine/Content/");
	
	if (IntermediateAssetPath.StartsWith(GameProjectPath)) {
		//Strip game project path, prefix it with /Game/
		const FString RawAssetPath = IntermediateAssetPath.Mid(GameProjectPath.Len());
		return FString::Printf(TEXT("/Game/%s"), *RawAssetPath);
	}

	if (IntermediateAssetPath.StartsWith(EnginePath)) {
		//Strip engine path, prefix it with /Engine/
		const FString RawAssetPath = IntermediateAssetPath.Mid(EnginePath.Len());
		return FString::Printf(TEXT("/Engine/%s"), *RawAssetPath);
	}
	//Otherwise it should be configurations? Something like /Engine/Config/BaseInput.ini
	//Mods can add their own configurations, but i honestly have no idea how we would differentiate between
	//game and custom mod configuration files. so don't package them at all for now
	//If you feel like you need that feature, contact @Archengius in discord
	return TEXT("");
}

FString GetModDirectory(const FString& ModReference) {
	return FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectDir(), TEXT("mods"), ModReference));
}

void EnsureGameDevelopmentModeIsEnabled(const FString& ConfigDirectory) {
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	//Ensure config directory exists
	PlatformFile.CreateDirectory(*ConfigDirectory);
	const FString ModLoaderConfigPath = FPaths::Combine(ConfigDirectory, TEXT("SML.cfg"));
	TSharedPtr<FJsonObject> ModLoaderConfig = MakeShareable(new FJsonObject());
	//SML.cfg exists already, read settings from it
	if (PlatformFile.FileExists(*ModLoaderConfigPath)) {
		FString FileJsonString;
		if (FFileHelper::LoadFileToString(FileJsonString, *ModLoaderConfigPath)) {
			const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(FileJsonString);
			FJsonSerializer JsonSerializer;
			if (!JsonSerializer.Deserialize(JsonReader, ModLoaderConfig)) {
				const FString MoveLocation = FString::Printf(TEXT("%s.bkp"), *ModLoaderConfigPath);
				UE_LOG(LogAlpakit, Error, TEXT("Failed to parse SML.cfg at %s, moving it to %s"), *ModLoaderConfigPath, *MoveLocation);
				PlatformFile.MoveFile(*ModLoaderConfigPath, *MoveLocation);
			}
		} else {
			UE_LOG(LogAlpakit, Error, TEXT("Failed to read SML.cfg from %s"), *ModLoaderConfigPath);
		}
	}
	//Add developmentMode = true to it and overwrite if it wasn't there
	bool bEnabledDevelopmentMode = false;
	if (!ModLoaderConfig->HasTypedField<EJson::Boolean>(TEXT("developmentMode")) ||
		!ModLoaderConfig->GetBoolField(TEXT("developmentMode"))) {
		ModLoaderConfig->SetBoolField(TEXT("developmentMode"), true);
		bEnabledDevelopmentMode = true;
	}
	//Overwrite config file if we enabled development mode
	if (bEnabledDevelopmentMode) {
		FString OutputJsonString;
		const TSharedRef<TJsonWriter<>> JsonWriter = TJsonStringWriter<>::Create(&OutputJsonString);
		FJsonSerializer JsonSerializer;
		JsonSerializer.Serialize(ModLoaderConfig.ToSharedRef(), JsonWriter);
		if (!FFileHelper::SaveStringToFile(OutputJsonString, *ModLoaderConfigPath)) {
			UE_LOG(LogAlpakit, Error, TEXT("Failed to save SML.cfg to %s"), *ModLoaderConfigPath);
		} else {
			UE_LOG(LogAlpakit, Display, TEXT("Successfully enabled developmentMod in SML.cfg at %s"), *ModLoaderConfigPath);
		}
	}
}

void CopyModsIntoGameModDirectory(const FString& ModDirectory, const FString& LoadersDirectory, const TSharedPtr<FModPackingProgress>& PackingProgress) {
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	//Ensure that mod directory exists
	PlatformFile.CreateDirectory(*ModDirectory);
	PlatformFile.CreateDirectory(*LoadersDirectory);
	//Iterate mod list and copy each mod pak file
	int32 ModsCopied = 0;
	for (const FAlpakitMod& AlpakitMod : PackingProgress->ModsToPack) {
		if (AlpakitMod.Enabled) {
			const FString AlpakitModDirectory = GetModDirectory(AlpakitMod.Name);
			const FString ModPakFileName = FString::Printf(TEXT("%s.pak"), *AlpakitMod.Name);
			const FString SourceFilePath = FPaths::Combine(AlpakitModDirectory, ModPakFileName);
			const bool bCopyToLoaders = AlpakitMod.Name == TEXT("SML");
			const FString DestFolder = bCopyToLoaders ? LoadersDirectory : ModDirectory;
			const FString DestFilePath = FPaths::Combine(DestFolder, ModPakFileName);
			if (!PlatformFile.CopyFile(*DestFilePath, *SourceFilePath)) {
				UE_LOG(LogAlpakit, Error, TEXT("Failed to copy mod file from %s to %s"), *SourceFilePath, *DestFilePath);
			} else {
				ModsCopied++;
			}
		}
	}
	UE_LOG(LogAlpakit, Display, TEXT("Successfully copied %d mod(s) to mod directory at %s"), ModsCopied, *ModDirectory);
}

void LaunchMonitoredGameProcess(const FString& GameURLPath) {
	FString OutErrorString;
	FPlatformProcess::LaunchURL(*GameURLPath, NULL, &OutErrorString);
	if (!OutErrorString.IsEmpty()) {
		UE_LOG(LogAlpakit, Error, TEXT("Failed to open Satisfactory URL: %s"), *OutErrorString);
	}
}

FString CreateLaunchURLForStartType(EStartGameType StartType) {
	switch (StartType) {
		case EStartGameType::STEAM: return TEXT("steam://rungameid/526870");
		case EStartGameType::EPIC_EARLY_ACCESS: return TEXT("com.epicgames.launcher://apps/CrabEA?action=launch&silent=true");
		case EStartGameType::EPIC_EXPERIMENTAL: return TEXT("com.epicgames.launcher://apps/CrabTest?action=launch&silent=true");
		default: return TEXT("");
	}
}

/** Performs post-processing tasks such as copying mods to game mods folder */
void FAlpakitModule::PerformPostProcessTasks(const TSharedPtr<FModPackingProgress>& PackingProgress) {
	UAlpakitSettings* Settings = UAlpakitSettings::Get();
	const FString SatisfactoryDirectory = Settings->SatisfactoryGamePath.Path;
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.DirectoryExists(*SatisfactoryDirectory)) {
		//Copy mods to game folder as specified in alpakit
		if (Settings->CopyModsToGame) {
			const FString ModDirectory = FPaths::Combine(SatisfactoryDirectory, TEXT("mods"));
			const FString LoadersDirectory = FPaths::Combine(SatisfactoryDirectory, TEXT("loaders"));
			const FString ConfigDirectory = FPaths::Combine(SatisfactoryDirectory, TEXT("configs"));
			EnsureGameDevelopmentModeIsEnabled(ConfigDirectory);
			CopyModsIntoGameModDirectory(ModDirectory, LoadersDirectory, PackingProgress);
		}
		//Launch game by URL, it's the fastest way possible
		if (Settings->LaunchGameAfterPacking != EStartGameType::NONE) {
			const FString GameURL = CreateLaunchURLForStartType(Settings->LaunchGameAfterPacking);
			LaunchMonitoredGameProcess(GameURL);
		}
	}
	//Finish original task now
	PackingProgress->OriginalFinishCallback(true, TEXT(""));
}

void EnsureModHasSMLDependency(TArray<FAlpakitModDependency>& ModDependencies) {
	bool bFoundSMLDependency = false;
	for (const FAlpakitModDependency& Dependency : ModDependencies) {
		if (Dependency.Mod == TEXT("SML"))
			bFoundSMLDependency = true;
	}
	if (!bFoundSMLDependency) {
		//Add SML dependency ourselves if user hasn't specified one
		FAlpakitModDependency SMLDependency;
		const FString ModLoaderVersion = SML::GetRawModLoaderVersionString();
		SMLDependency.Mod = TEXT("SML");
		SMLDependency.Constraint = FString::Printf(TEXT("^%s"), *ModLoaderVersion);
		ModDependencies.Add(SMLDependency);
	}
}

void FAlpakitModule::SerializeModInfoToDataJson(const TSharedRef<FJsonObject>& DataJson, const FAlpakitMod& ModInfo) {
	DataJson->SetStringField(TEXT("mod_reference"), ModInfo.Name);
	DataJson->SetStringField(TEXT("name"), ModInfo.DisplayName);
	DataJson->SetStringField(TEXT("version"), ModInfo.Version);

	if (!ModInfo.Description.IsEmpty()) {
		DataJson->SetStringField(TEXT("description"), ModInfo.Description);
	}
	if (!ModInfo.Credits.IsEmpty()) {
		DataJson->SetStringField(TEXT("credits"), ModInfo.Credits);
	}
	if (ModInfo.Authors.Num() > 0) {
		TArray<TSharedPtr<FJsonValue>> AuthorsArray;
		for (const FString& ModAuthor : ModInfo.Authors)
			AuthorsArray.Add(MakeShareable(new FJsonValueString(ModAuthor)));
		DataJson->SetArrayField(TEXT("authors"), AuthorsArray);
	}
	
	TArray<FAlpakitModDependency> ModDependencies = ModInfo.Dependencies;
	if (ModInfo.Name != TEXT("SML")) {
		EnsureModHasSMLDependency(ModDependencies);
	}
	if (ModDependencies.Num() > 0) {
		TSharedPtr<FJsonObject> Dependencies = MakeShareable(new FJsonObject());
		for (const FAlpakitModDependency& Dependency : ModDependencies)
			Dependencies->SetStringField(Dependency.Mod, Dependency.Constraint);
		DataJson->SetObjectField(TEXT("dependencies"), Dependencies);
	}
	
	if (ModInfo.OptionalDependencies.Num() > 0) {
		TSharedPtr<FJsonObject> OptionalDependencies = MakeShareable(new FJsonObject());
		for (const FAlpakitModDependency& Dependency : ModInfo.OptionalDependencies)
			OptionalDependencies->SetStringField(Dependency.Mod, Dependency.Constraint);
		DataJson->SetObjectField(TEXT("optional_dependencies"), OptionalDependencies);
	}

	//Add "accept any remote version" attribute only if it is specified as true
	//It also overrides remote_version attribute in Alpakit
	if (ModInfo.RemoteVersion.bModIsNotRequiredOnRemote) {
		DataJson->SetBoolField(TEXT("accept_any_remote_version"), true);
	} else if (!ModInfo.RemoteVersion.AcceptedRemoteVersions.IsEmpty()) {
		DataJson->SetStringField(TEXT("remote_version"), ModInfo.RemoteVersion.AcceptedRemoteVersions);
	}
	
	//TODO verify icon path is correct?
	if (!ModInfo.ModResources.ModIconPath.IsEmpty()) {
		TSharedPtr<FJsonObject> ModResources = MakeShareable(new FJsonObject());
		ModResources->SetStringField(TEXT("icon"), ModInfo.ModResources.ModIconPath);
		DataJson->SetObjectField(TEXT("resources"), ModResources);
	}
}


void FAlpakitModule::ProcessSingleModPackage(const TSharedPtr<FModPackingProgress>& PackingProgress) {
	const int32 CurrentModIndex = PackingProgress->CurrentModIndex++;
	//Call post processing tasks if we don't have any mods remaining
	if (CurrentModIndex >= PackingProgress->ModsToPack.Num()) {
		PerformPostProcessTasks(PackingProgress);
		return;
	}
	const FAlpakitMod& AlpakitMod = PackingProgress->ModsToPack[CurrentModIndex];
	//Mod is disabled, call ProcessSingleModPackage again
	if (!AlpakitMod.Enabled) {
		ProcessSingleModPackage(PackingProgress);
		return;
	}
	const FString ModDirectory = GetModDirectory(AlpakitMod.Name);
	const FString ModPakFileName = FString::Printf(TEXT("%s.pak"), *AlpakitMod.Name);
	const FString OutputPakFilePath = FPaths::Combine(ModDirectory, *ModPakFileName);
	const FString OutputDataJsonFilePath = FPaths::Combine(ModDirectory, TEXT("data.json"));
	
	const FString TemporaryDirectoryPath = FPlatformProcess::UserTempDir();
	const FString ModPakListPrefix = FString::Printf(TEXT("Alpakit_ModPakList_%s"), *AlpakitMod.Name);
	const FString ModOverwriteListPrefix = FString::Printf(TEXT("Alpakit_ModOverwriteList_%s"), *AlpakitMod.Name);
	
	//Create file paths for two temporary files used for packing - overwrite list (queried by SML in runtime) and pak list (used by UnrealPak)
	const FString ModListFilePath = FPaths::CreateTempFilename(*TemporaryDirectoryPath, *ModPakListPrefix, TEXT(".txt"));
	const FString ModOverwriteListFilePath = FPaths::CreateTempFilename(*TemporaryDirectoryPath, *ModOverwriteListPrefix, TEXT(".txt"));

	FPakListEntry OverwriteListEntry;
	OverwriteListEntry.AssetFilePathOnDisk = ModOverwriteListFilePath;
	OverwriteListEntry.AssetPathInPakFile = FString::Printf(TEXT("../../../%s/Content/%s/ModOverwriteList.txt"), FApp::GetProjectName(), *AlpakitMod.Name);
	
	TArray<FString> PakListOutputLines;
	PakListOutputLines.Add(OverwriteListEntry.ToString());
	//First line is always a comment with mod reference, starting with # (just so result file won't be empty)
	TArray<FString> OverwritesToSave;
	OverwritesToSave.Add(FString::Printf(TEXT("# Overwrite List for mod %s. Generated by Alpakit at %s"),
		*AlpakitMod.Name, *FDateTime::Now().ToString()));

	//PakList AssetPaths always start with ../../../, because package files are mounted under FactoryGame/Content/Paks,
	//and normal asset paths always start from game project directory. So we just strip them to get
	//correct path relative to game root directory. Example asset path:
	//../../../FactoryGame/Content/SML/ModDescriptionTextStyle.uasset
	const FString ModAssetPrefix = FString::Printf(TEXT("/Game/%s/"), *AlpakitMod.Name);
	
	for (const FPakListEntry& PakListEntry : PackingProgress->PakListEntries) {
		const FString AssetPath = FormatPakListAssetPath(PakListEntry.AssetPathInPakFile);
		if (AssetPath.IsEmpty())
			continue; //FormatPakListAssetPath returns empty string if path is invalid
		//Now we have correct path to UPackage and we can work with it directly
		if (AssetPath.StartsWith(ModAssetPrefix)) {
			PakListOutputLines.Add(PakListEntry.ToString());
			
		} else if (AlpakitMod.OverwritePaths.Contains(AssetPath)) {
			const FString PakListLine = PakListEntry.ToString();
			PakListOutputLines.Add(PakListLine);
			OverwritesToSave.AddUnique(AssetPath);
		}
	}
	const bool bPakListSaveSuccess = FFileHelper::SaveStringArrayToFile(PakListOutputLines, *ModListFilePath);
	const bool bOverwriteListSaveSuccess = FFileHelper::SaveStringArrayToFile(OverwritesToSave, *ModOverwriteListFilePath);
	if (!bPakListSaveSuccess) {
		UE_LOG(LogAlpakit, Error, TEXT("Failed to save package list file for mod %s at %s"), *ModPakFileName, *ModListFilePath);
		PackingProgress->OriginalFinishCallback(false, TEXT("Failed to save package list file"));
		return;
	}
	if (!bOverwriteListSaveSuccess) {
		UE_LOG(LogAlpakit, Error, TEXT("Failed to save overwrite list file for mod %s at %s"), *ModPakFileName, *ModListFilePath);
		PackingProgress->OriginalFinishCallback(false, TEXT("Failed to save overwrite list"));
		return;
	}
	
	//Write data.json now
	TSharedRef<FJsonObject> DataJson = MakeShareable(new FJsonObject());
	SerializeModInfoToDataJson(DataJson, AlpakitMod);
	FString ResultDataJsonString;
	TSharedRef<TJsonWriter<>> StringWriter = TJsonStringWriter<>::Create(&ResultDataJsonString);
	FJsonSerializer JsonSerializer;
	JsonSerializer.Serialize(DataJson, StringWriter);
	
	bool bModInfoSaveSuccess = FFileHelper::SaveStringToFile(ResultDataJsonString, *OutputDataJsonFilePath);
	if (!bModInfoSaveSuccess) {
		UE_LOG(LogAlpakit, Error, TEXT("Failed to save data.json file for mod %s at %s"), *ModPakFileName, *OutputDataJsonFilePath);
		PackingProgress->OriginalFinishCallback(false, TEXT("Failed to save data.json file for mod"));
		return;
	}
	
	RunUnrealPak(ModListFilePath, OutputPakFilePath, [PackingProgress, ModPakFileName](bool bSuccess, const FString& FailureReason){
		if (bSuccess) {
			UE_LOG(LogAlpakit, Display, TEXT("Succesfully packaged mod %s"), *ModPakFileName);
			ProcessSingleModPackage(PackingProgress);
		} else {
			UE_LOG(LogAlpakit, Error, TEXT("Failed to package mod %s: %s"), *ModPakFileName, *FailureReason);
			PackingProgress->OriginalFinishCallback(false, FailureReason);
		}
	});
}

struct FProcessPointerHolder {
	TSharedPtr<FMonitoredProcess> ProcessPtr;
};

void FAlpakitModule::RunUnrealPak(const FString& PakListFilePath, const FString& OutputPakFilePath, TFunction<void(bool bSuccess, const FString& FailureReason)> PackingFinishedCallback) {
	const FString CommandLineExecutable = TEXT("cmd.exe");
	const FString UnrealPakPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::EngineDir(), TEXT("Binaries"), TEXT("Win64"), TEXT("UnrealPak.exe")));

	const FString FullCommandLine = FString::Printf(TEXT("/c \"\"%s\" %s\""), *UnrealPakPath,
		*FString::Printf(TEXT("\"%s\" -Create=\"%s\""), *OutputPakFilePath, *PakListFilePath));
	TSharedPtr<FMonitoredProcess> PackProcess = MakeShareable(new FMonitoredProcess(CommandLineExecutable, FullCommandLine, true));
	TSharedPtr<FProcessPointerHolder> PointerHolder = MakeShareable(new FProcessPointerHolder{PackProcess});

	//Use short pak file name in log file to avoid printing full path on every UnrealPak output line
	const FString PakFileName = FPaths::GetCleanFilename(OutputPakFilePath);
	PackProcess->OnOutput().BindLambda([PakFileName](const FString& OutputLine){
		UE_LOG(LogAlpakit, Display, TEXT("UnrealPak (%s): %s"), *PakFileName, *OutputLine);
	});
	//Keep reference to process so it won't be freed until process execution ends
	PackProcess->OnCompleted().BindLambda([PackingFinishedCallback, OutputPakFilePath, PointerHolder](int32 ExitCode){
		AsyncTask(ENamedThreads::AnyThread, [=](){
			if (ExitCode == 0) {
				UE_LOG(LogAlpakit, Display, TEXT("UnrealPak finished successfully for file %s"), *OutputPakFilePath);
				PackingFinishedCallback(true, TEXT(""));
			} else {
				UE_LOG(LogAlpakit, Error, TEXT("UnrealPak for file %s failed. Exit Code: %d"), *OutputPakFilePath, ExitCode);
				const FString FailureReason = FString::Printf(TEXT("UnrealPak exited with code %d"), ExitCode);
				PackingFinishedCallback(false, FailureReason);
			}
			//Reset shared pointer to the process so it can be destroyed
			//Note that our outer scope will be destroyed too, as this object actually owns thread instance
			//That's why we need to wrap this code into AsyncTask block
			PointerHolder->ProcessPtr.Reset();
		});
	});
	
	UE_LOG(LogAlpakit, Display, TEXT("Starting UnrealPak for file %s"), *OutputPakFilePath);
	if (!PackProcess->Launch()) {
		UE_LOG(LogAlpakit, Error, TEXT("Couldn't launch UnrealPak process for file %s"), *OutputPakFilePath);
		PackingFinishedCallback(false, TEXT("Failed to launch UnrealPak process"));
	}
}

void FAlpakitModule::RegisterConsoleCommands() {
	IConsoleManager::Get().RegisterConsoleCommand(TEXT("Alpakit"),
		TEXT("Performs mod asset packaging according to configuration in Game.ini"),
		FConsoleCommandDelegate::CreateLambda([this]() { this->HandleAlpakitConsoleCommand(); }));
}

void FAlpakitModule::HandleAlpakitConsoleCommand() {
	TPromise<FString> PackingResultPromise;
	const TFuture<FString> PackingResultFuture = PackingResultPromise.GetFuture();
	UE_LOG(LogAlpakit, Display, TEXT("Starting packing mod assets"));
	PackModAssets([&](const bool bSuccess, const FString& FailureReason){
		if (bSuccess) {
			PackingResultPromise.SetValue(TEXT(""));
		} else {
			PackingResultPromise.SetValue(FailureReason);
		}
	});
	PackingResultFuture.Wait();
	const FString FailureMessage = PackingResultFuture.Get();
	if (FailureMessage.IsEmpty()) {
		UE_LOG(LogAlpakit, Display, TEXT("Packing mod assets finished successfully."));
	} else {
		UE_LOG(LogAlpakit, Error, TEXT("Packing mod assets failed: %s"), *FailureMessage);
	}
}

void FAlpakitModule::CreateAssetContextMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(FAlpakitCommands::Get().AlpakitOverwrite);
}

TSharedRef<FExtender> FAlpakitModule::OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets) {
	TSharedRef<FExtender> Extender(new FExtender());

	Extender->AddMenuExtension(
		"AssetContextReferences",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateStatic(&FAlpakitModule::CreateAssetContextMenu));

	return Extender;
}

TSharedRef<FExtender> FAlpakitModule::OnExtendContentBrowserPathSelectionMenu(const TArray<FString>& SelectedPaths) {
	TSharedRef<FExtender> Extender(new FExtender());

	Extender->AddMenuExtension(
		"PathContextBulkOperations",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateStatic(&FAlpakitModule::CreateAssetContextMenu));

	return Extender;
}

TSharedRef<FExtender> FAlpakitModule::OnExtendAssetEditor(const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects) {
	TArray<FName> PackageNames;

	for (UObject* EditedAsset : ContextSensitiveObjects) {
		if (EditedAsset && EditedAsset->IsAsset() && !EditedAsset->IsPendingKill()) {
			PackageNames.AddUnique(EditedAsset->GetOutermost()->GetFName());
		}
	}

	TSharedRef<FExtender> Extender(new FExtender());

	if (PackageNames.Num() > 0) {
		// It's safe to modify the CommandList here because this is run as the editor UI is created and the payloads are safe
		CommandList->MapAction(
			FAlpakitCommands::Get().AlpakitOverwrite,
			FExecuteAction::CreateRaw(this, &FAlpakitModule::OpenAlpakitOverwriteUI, PackageNames));

		Extender->AddMenuExtension(
			"FindInContentBrowser",
			EExtensionHook::After,
			CommandList,
			FMenuExtensionDelegate::CreateStatic(&FAlpakitModule::CreateAssetContextMenu));
	}

	return Extender;
}

void FAlpakitModule::GetAssetDataInPaths(const TArray<FString>& Paths, TArray<FAssetData>& OutAssetData) const {
	// Form a filter from the paths
	FARFilter Filter;
	Filter.bRecursivePaths = true;
	for (const FString& Path : Paths) {
		new (Filter.PackagePaths) FName(*Path);
	}

	// Query for a list of assets in the selected paths
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	AssetRegistry.GetAssets(Filter, OutAssetData);
}

TArray<FName> FAlpakitModule::GetContentBrowserSelectedAssetPackages(FOnContentBrowserGetSelection GetSelectionDelegate) const {
	TArray<FName> OutAssetPackages;
	TArray<FAssetData> SelectedAssets;
	TArray<FString> SelectedPaths;

	if (GetSelectionDelegate.IsBound()) {
		GetSelectionDelegate.Execute(SelectedAssets, SelectedPaths);
	}
	GetAssetDataInPaths(SelectedPaths, SelectedAssets);

	TArray<FName> PackageNames;
	for (const FAssetData& AssetData : SelectedAssets) {
		OutAssetPackages.AddUnique(AssetData.PackageName);
	}
	return OutAssetPackages;
}

void FAlpakitModule::OnExtendContentBrowserCommands(TSharedRef<FUICommandList> CommandList, FOnContentBrowserGetSelection GetSelectionDelegate) {
	CommandList->MapAction(FAlpakitCommands::Get().AlpakitOverwrite,
		FExecuteAction::CreateLambda([this, GetSelectionDelegate](){
			OpenAlpakitOverwriteUI(GetContentBrowserSelectedAssetPackages(GetSelectionDelegate));
		})
	);
}

void FAlpakitModule::OpenAlpakitOverwriteUI(TArray<FName> SelectedPackages) const {
	TArray<FAssetIdentifier> Identifiers;
	for (const FName& Name : SelectedPackages) {
		Identifiers.Add(FAssetIdentifier(Name));
	}
	OpenAlpakitOverwriteUI(Identifiers);
}

void FAlpakitModule::OpenAlpakitOverwriteUI(TArray<FAssetIdentifier> SelectedIdentifiers) const {
	if (SelectedIdentifiers.Num() > 0) {
		TSharedRef<SDockTab> NewTab = FGlobalTabmanager::Get()->InvokeTab(AlpakitOverwriteTabName);
		TSharedRef<SAlpakitOverwriteWidget> ReferenceViewer = StaticCastSharedRef<SAlpakitOverwriteWidget>(NewTab->GetContent());
		ReferenceViewer->SetPathsToOverwrite(SelectedIdentifiers);
	}
}

void FAlpakitModule::RegisterSettings() const {
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings")) {
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");
		SettingsContainer->DescribeCategory("Alpakit Settings",
			LOCTEXT("RuntimeWDCategoryName", "Alpakit Settings"),
			LOCTEXT("RuntimeWDCategoryDescription", "Alpakit Settings. Can also be edited in the Alpakit menu"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Alpakit", "General",
			LOCTEXT("RuntimeGeneralSettingsName", "General"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Alpakit Settings. Can also be edited in the Alpakit menu"),
			UAlpakitSettings::Get()
		);
		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		if (SettingsSection.IsValid()) {
			SettingsSection->OnModified().BindLambda([](){
				UAlpakitSettings::Get()->SaveSettings();
				return true;
			});
		}
	}
}

void FAlpakitModule::UnregisterSettings() const {
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings")) {
		SettingsModule->UnregisterSettings("Project", "Alpakit", "General");
	}
}

FString EscapePath(const FString& InPath) {
	return InPath.Replace(TEXT(":"), TEXT(""))
			.Replace(TEXT("/"), TEXT("+"))
			.Replace(TEXT("\\"), TEXT("+"))
			.Replace(TEXT(" "), TEXT("+"));
}

FString GetLocalBuildsLogFolderForCurrentPlatform() {
#ifdef PLATFORM_WINDOWS
	//On Windows, UserSettingsDir returns %LocalAppData% path, so normal %RoamingAppData% is Roaming directory nearby
	const FString SettingsDir = FPlatformProcess::UserSettingsDir();
	const FString ResultAppDataPath = FPaths::Combine(SettingsDir, TEXT(".."), TEXT("Roaming"));
	return FPaths::Combine(ResultAppDataPath, TEXT("Unreal Engine"), TEXT("AutomationTool"), TEXT("Logs"));
#else
	static_assert(0, "GetLocalBuildsLogFolderForCurrentPlatform not implemented for current platform");
	return TEXT("Not Implemented");
#endif
}

/** Returns automation tool log directory path for installed engine distribution (InstalledBuilt.txt marker file in engine) */
FString GetAutomationToolLogDirForInstalledEngine() {
	FString RootPath = FPaths::RootDir();
	FPaths::NormalizeDirectoryName(RootPath);
	const FString RootPathEscaped = EscapePath(RootPath);
	//No need to handle trailing / now because NormalizeDirectoryName already does that
	const FString LocalBuildsLogFolder = GetLocalBuildsLogFolderForCurrentPlatform();
	return FPaths::Combine(LocalBuildsLogFolder, RootPathEscaped);
}

/** Returns automation tool log directory path for engine built from source (no InstalledBuild.txt file in engine) */
FString GetAutomationToolLogDirForSourceBuiltEngine() {
	return FPaths::Combine(FPaths::RootDir(), TEXT("Engine"), TEXT("Programs"), TEXT("AutomationTool"), TEXT("Saved"), TEXT("Logs"));
}

/** Returns automation tool log directory path used by UAT used with current engine */
FString FAlpakitModule::GetAutomationToolLogDir() {
	const FString InstalledBuildFilePath = FPaths::Combine(FPaths::EngineDir(), TEXT("Build"), TEXT("InstalledBuild.txt"));
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const bool bIsEngineInstalled = PlatformFile.FileExists(*InstalledBuildFilePath);
	return FPaths::ConvertRelativePathToFull(bIsEngineInstalled ? GetAutomationToolLogDirForInstalledEngine() : GetAutomationToolLogDirForSourceBuiltEngine());
}

FString FAlpakitModule::GetProjectPathWithFallback() {
	if (FPaths::IsProjectFilePathSet()) {
		//ProjectFilePath is set, so we can return it directly
		return FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath());
	}
	//Otherwise we fall back to engine directory with known project name
	const FString ProjectFileName = FString::Printf(TEXT("%s.uproject"), FApp::GetProjectName());
	return FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::RootDir(), FApp::GetProjectName(), ProjectFileName));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAlpakitModule, Alpakit)
#include "Alpakit.h"
#include "AlpakitStyle.h"
#include "AlpakitCommands.h"
#include "AlpakitWidget.h"
#include "AssetRegistryModule.h"
#include "ContentBrowserModule.h"
#include "ISettingsContainer.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "LevelEditor.h"

static const FName AlpakitTabName("Alpakit");
static const FName AlpakitOverwriteTabName("AlpakitOverwrite");

#define LOCTEXT_NAMESPACE "FAlpakitModule"

DEFINE_LOG_CATEGORY(LogAlpakit)

void FAlpakitModule::StartupModule() {
	//Register editor settings
	RegisterSettings();

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
				// TODO: Save settings when tab is closed automatically
				//.OnTabClosed_Lambda([AlpakitWidget](TSharedRef<SDockTab>) { AlpakitWidget->SaveSettings(); })
				[ AlpakitWidget ];
		}))
		.SetDisplayName(LOCTEXT("FAlpakitTabTitle", "Alpakit"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	//Register content browsers extensions
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
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

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAlpakitModule, Alpakit)
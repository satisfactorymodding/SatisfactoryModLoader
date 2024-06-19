#include "Alpakit.h"
#include "AlpakitStyle.h"
#include "AlpakitCommands.h"
#include "AlpakitSettings.h"
#include "AlpakitDevWidget.h"
#include "AlpakitReleaseWidget.h"
#include "ContentBrowserModule.h"
#include "ISettingsContainer.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "LevelEditor.h"
#include "IPluginBrowser.h"
#include "UATHelper/Public/IUATHelperModule.h"
#include "ModWizardDefinition.h"
#include "ModTargetsConfig.h"
#include "SAlpakitLogTabContent.h"


#define LOCTEXT_NAMESPACE "FAlpakitModule"

DEFINE_LOG_CATEGORY(LogAlpakit)

const FName FAlpakitModule::AlpakitDevTabName("AlpakitDev");
const FName FAlpakitModule::AlpakitReleaseTabName("AlpakitRelease");
const FName FAlpakitModule::ModCreatorTabName(TEXT("ModCreator"));
const FName FAlpakitModule::AlpakitLogTabName(TEXT("AlpakitLog"));

void FAlpakitModule::StartupModule() {
    //Register editor settings
    RegisterSettings();

    //Register mod templates
    RegisterModTemplates();

    //Initialize Slate stuff, including commands
    FAlpakitStyle::Initialize();
    FAlpakitStyle::ReloadTextures();
    FAlpakitCommands::Register();
    
    PluginCommands = MakeShareable(new FUICommandList);
    PluginCommands->MapAction(
        FAlpakitCommands::Get().AlpakitDevWindow,
        FExecuteAction::CreateLambda([](){
            FGlobalTabmanager::Get()->TryInvokeTab(AlpakitDevTabName);
        }),
        FCanExecuteAction());
    PluginCommands->MapAction(
        FAlpakitCommands::Get().AlpakitReleaseWindow,
        FExecuteAction::CreateLambda([](){
            FGlobalTabmanager::Get()->TryInvokeTab(AlpakitReleaseTabName);
        }),
        FCanExecuteAction());
    PluginCommands->MapAction(
        FAlpakitCommands::Get().AlpakitLogWindow,
        FExecuteAction::CreateLambda([](){
            FGlobalTabmanager::Get()->TryInvokeTab(AlpakitLogTabName);
        }),
        FCanExecuteAction());
    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
    
    //Register Alpakit Settings in Editor's Project Menu
    TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
    MenuExtender->AddMenuExtension(TEXT("FileProject"), EExtensionHook::After, PluginCommands,
        FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& Builder){
            Builder.AddMenuEntry(FAlpakitCommands::Get().AlpakitDevWindow);
            Builder.AddMenuEntry(FAlpakitCommands::Get().AlpakitReleaseWindow);
            Builder.AddMenuEntry(FAlpakitCommands::Get().AlpakitLogWindow);
        }));
    LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
    
    //Register Alpakit Settings in Editor's Toolbar
    TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
    ToolbarExtender->AddToolBarExtension(TEXT("Play"), EExtensionHook::After, PluginCommands,
        FToolBarExtensionDelegate::CreateLambda([this](FToolBarBuilder& Builder) {
            {
                Builder.BeginStyleOverride(FName("Toolbar.BackplateLeft"));
                Builder.AddToolBarButton(FAlpakitCommands::Get().AlpakitDevWindow);

                Builder.BeginStyleOverride(FName("Toolbar.BackplateCenter"));
                Builder.AddToolBarButton(FAlpakitCommands::Get().AlpakitReleaseWindow);

                Builder.EndStyleOverride();
            }
            {
                Builder.BeginStyleOverride(FName("Toolbar.BackplateRightCombo"));

                Builder.AddComboButton(FUIAction(), FOnGetContent::CreateLambda([this]() {                
                    FMenuBuilder MenuBuilder(true, PluginCommands);

                    MenuBuilder.AddMenuEntry(FAlpakitCommands::Get().AlpakitLogWindow);
        
                    return MenuBuilder.MakeWidget();
                }));

                Builder.EndStyleOverride();
            }
        }));
    LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);

    //Register normal alpakit settings tab spawner
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AlpakitDevTabName,
        FOnSpawnTab::CreateLambda([](const FSpawnTabArgs&){
            const TSharedRef<SAlpakitDevWidget> AlpakitWidget = SNew(SAlpakitDevWidget);
            return SNew(SDockTab)
                .TabRole(NomadTab)
                [ AlpakitWidget ];
        }))
        .SetDisplayName(LOCTEXT("FAlpakitDevTabTitle", "Alpakit Dev"))
        .SetIcon(FSlateIcon(FAlpakitStyle::GetStyleSetName(), "Alpakit.AlpakitDevWindow"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);
    
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AlpakitReleaseTabName,
        FOnSpawnTab::CreateLambda([](const FSpawnTabArgs&){
            const TSharedRef<SAlpakitReleaseWidget> AlpakitWidget = SNew(SAlpakitReleaseWidget);
            return SNew(SDockTab)
                .TabRole(NomadTab)
                [ AlpakitWidget ];
        }))
        .SetDisplayName(LOCTEXT("FAlpakitReleaseTabTitle", "Alpakit Release"))
        .SetIcon(FSlateIcon(FAlpakitStyle::GetStyleSetName(), "Alpakit.AlpakitReleaseWindow"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);
    
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
        ModCreatorTabName,
        FOnSpawnTab::CreateRaw(this, &FAlpakitModule::HandleSpawnModCreatorTab))
        .SetDisplayName(LOCTEXT("NewPluginTabHeader", "New Mod"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		AlpakitLogTabName,
		FOnSpawnTab::CreateRaw(this, &FAlpakitModule::HandleSpawnAlpakitLogTab))
		.SetDisplayName(LOCTEXT("AlpakitLogHeader", "Alpakit Log"))
		.SetIcon( FSlateIcon( FAlpakitStyle::Get().GetStyleSetName(), TEXT("Alpakit.AlpakitLogWindow") ) )
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FAlpakitModule::ShutdownModule() {
    if (UObjectInitialized()) {
        UnregisterSettings();
    }
    
    FAlpakitStyle::Shutdown();
    FAlpakitCommands::Unregister();

    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AlpakitDevTabName);
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AlpakitReleaseTabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ModCreatorTabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AlpakitLogTabName);
}

FString FAlpakitModule::GetCurrentSMLVersion()
{
    TSharedPtr<IPlugin> SMLPlugin = IPluginManager::Get().FindPlugin(TEXT("SML"));
    if (SMLPlugin.IsValid())
    {
        FPluginDescriptor SMLDescriptor = SMLPlugin->GetDescriptor();
        return SMLDescriptor.CachedJson->GetStringField(TEXT("SemVersion"));
    }
    return TEXT("");
}

FString FAlpakitModule::GetCurrentGameVersion()
{
    FString CurrentVersionFile = FPaths::ProjectDir() / TEXT("Source") / TEXT("FactoryGame") / TEXT("currentVersion.txt");
    FString GameVersion;
    FFileHelper::LoadFileToString(GameVersion, *CurrentVersionFile);
    return GameVersion.TrimStartAndEnd();
}

TSharedRef<FAlpakitProfile> MakeDevelopmentProfileForMod(TSharedRef<IPlugin> Mod) {
    TSharedRef<FAlpakitProfile> Profile = MakeShared<FAlpakitProfile>(Mod->GetName());

    Profile->bBuild = Mod->GetDescriptor().Modules.Num() > 0;
    
    UAlpakitSettings* Settings = UAlpakitSettings::Get();

    Profile->BuildConfiguration = Settings->GetBuildConfiguration();

    for (auto& [CookedPlatform, TargetSetting] : Settings->GetPlatformTargetSettings()) {
        if (TargetSetting.bEnabled) {
            Profile->CookedPlatforms.Add(CookedPlatform);
            if (TargetSetting.bCopyModsToGame) {
                FAlpakitProfileGameInfo& GameInfo = Profile->PlatformGameInfo.FindOrAdd(CookedPlatform);
                GameInfo.bCopyToGame = true;
                GameInfo.GamePath = TargetSetting.SatisfactoryGamePath;
            }
        }
    }

    return Profile;
}

void FAlpakitModule::PackageModsDevelopment(TArray<TSharedRef<IPlugin>> Mods) {
    if (Mods.Num() == 0) {
        return;
    }
    
    TArray<TSharedRef<FAlpakitProfile>> ProfilesToPackage;
    
    UAlpakitSettings* Settings = UAlpakitSettings::Get();
	    
    for (TSharedRef<IPlugin> Mod : Mods) {
        ProfilesToPackage.Add(MakeDevelopmentProfileForMod(Mod));
    }

    TSharedRef<FAlpakitProfile> LastProfile = ProfilesToPackage.Last();

    for (auto& [CookedPlatform, TargetSetting] : Settings->GetPlatformTargetSettings()) {
        if (TargetSetting.bEnabled) {
            if (TargetSetting.bLaunchGame) {
                FAlpakitProfileGameInfo& GameInfo = LastProfile->PlatformGameInfo.FindOrAdd(CookedPlatform);
                GameInfo.bStartGame = true;
                GameInfo.StartGameType = TargetSetting.LaunchGameType;
                GameInfo.CustomLaunchPath = TargetSetting.CustomLaunchPath;
                GameInfo.CustomLaunchArgs = TargetSetting.CustomLaunchArgs;
            }
        }
    }

    PackageMods(ProfilesToPackage);
}

TSharedRef<FAlpakitProfile> MakeReleaseProfileForMod(TSharedRef<IPlugin> Mod) {
    TSharedRef<FAlpakitProfile> Profile = MakeShared<FAlpakitProfile>(Mod->GetName());

    Profile->bBuild = Mod->GetDescriptor().Modules.Num() > 0;
    Profile->BuildConfiguration = EBuildConfiguration::Shipping;

    Profile->bMergeArchive = true;
    
    FModTargetsConfig TargetsConfig(Mod);
    Profile->CookedPlatforms.Append(TargetsConfig.GetCookedPlatforms());

    return Profile;
}

void FAlpakitModule::PackageModsRelease(TArray<TSharedRef<IPlugin>> Mods) {
    if (Mods.Num() == 0) {
        return;
    }
    
    TArray<TSharedRef<FAlpakitProfile>> ProfilesToPackage;
	    
    for (TSharedRef<IPlugin> Mod : Mods) {
        ProfilesToPackage.Add(MakeReleaseProfileForMod(Mod));
    }

    PackageMods(ProfilesToPackage);
}

void FAlpakitModule::PackageMods(TArray<TSharedRef<FAlpakitProfile>> ProfilesToPackage) {
    if(!ensure(!bIsPackaging)) {
        return;
    }
    bIsPackaging = true;

    ProfilePackageQueue = ProfilesToPackage;

    ProcessQueueItem();
}

void FAlpakitModule::ProcessQueueItem() {
    if (ProfilePackageQueue.IsEmpty()) {
        bIsPackaging = false;
        return;
    }
    TSharedRef<FAlpakitProfile> Profile = ProfilePackageQueue[0];
    ProfilePackageQueue.RemoveAt(0);

    const TSharedRef<FAlpakitInstance> AlpakitInstance = MakeShared<FAlpakitInstance>( Profile->PluginName, Profile );
    AlpakitInstance->OnProcessCompleted().AddLambda([&](EAlpakitInstanceResult Result) {
        if (Result == EAlpakitInstanceResult::Success) {
            ProcessQueueItem();
        } else {
            bIsPackaging = false;
            ProfilePackageQueue.Empty();
        }
    });
    AlpakitInstance->Start();
}

TSharedRef<SDockTab> FAlpakitModule::HandleSpawnModCreatorTab(const FSpawnTabArgs& SpawnTabArgs)
{
    IPluginBrowser& PluginBrowser = FModuleManager::Get().GetModuleChecked<IPluginBrowser>(TEXT("PluginBrowser"));
    return PluginBrowser.SpawnPluginCreatorTab(SpawnTabArgs, MakeShared<FModWizardDefinition>());
}

TSharedRef<SDockTab> FAlpakitModule::HandleSpawnAlpakitLogTab( const FSpawnTabArgs& SpawnTabArgs )
{
	return SNew( SDockTab )
		.Label( LOCTEXT("AlpakitLogLabel", "Alpakit Log") )
		.TabRole( NomadTab )
		[
			SNew( SAlpakitLogTabContent )
		];
}

void FAlpakitModule::RegisterSettings() const {
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>(TEXT("Settings"))) {
        // Create the new category
        ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer(TEXT("Project"));
        SettingsContainer->DescribeCategory(TEXT("Alpakit Settings"),
            LOCTEXT("RuntimeWDCategoryName", "Alpakit Settings"),
            LOCTEXT("RuntimeWDCategoryDescription", "Alpakit Settings. Can also be edited in the Alpakit menu"));

        // Register the settings
        ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings(TEXT("Project"), TEXT("Alpakit"), TEXT("General"),
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
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>(TEXT("Settings"))) {
        SettingsModule->UnregisterSettings(TEXT("Project"), TEXT("Alpakit"), TEXT("General"));
    }
}

bool IsPluginAMod(IPlugin& Plugin) {
    //Mod plugins are always considered mods
    if (Plugin.GetType() == EPluginType::Mod) {
        return true;
    }
    //Project plugins are considered mods too, for now
    if (Plugin.GetType() == EPluginType::Project) {
        return true;
    }
    return false;
}

void FAlpakitModule::RegisterModTemplates() {
    TArray<TSharedRef<IPlugin>> EnabledPlugins = IPluginManager::Get().GetEnabledPlugins();
    for (TSharedRef<IPlugin> Plugin : EnabledPlugins) {
        if (IsPluginAMod(Plugin.Get())) {
            AddModTemplatesFromPlugin(Plugin.Get());
        }
    }
    IPluginManager::Get().OnNewPluginMounted().AddLambda([this](IPlugin& Plugin){
        if (IsPluginAMod(Plugin)) {
            AddModTemplatesFromPlugin(Plugin);
        }
    });
}

void FAlpakitModule::AddModTemplatesFromPlugin(IPlugin& Plugin) {
    FString TemplatesPath = Plugin.GetBaseDir() / TEXT("Templates");
    if (!FPaths::DirectoryExists(TemplatesPath)) {
        return;
    }
    FString TemplatesJSONPath = TemplatesPath / TEXT("templates.json");
    if (!FPaths::FileExists(TemplatesJSONPath)) {
        return;
    }
    FString TemplatesJSON;
    if (!FFileHelper::LoadFileToString(TemplatesJSON, *TemplatesJSONPath)) {
        return;
    }
    const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(TemplatesJSON);
    TSharedPtr<FJsonObject> TemplatesJSONObj;
    if (!FJsonSerializer::Deserialize(JsonReader, TemplatesJSONObj)) {
        UE_LOG(LogAlpakit, Error, TEXT("Invalid templates for mod %s: invalid json"), *Plugin.GetName());
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* TemplatesArrayPtr;
    if(!TemplatesJSONObj->TryGetArrayField(TEXT("templates"), TemplatesArrayPtr)) {
        UE_LOG(LogAlpakit, Error, TEXT("Invalid templates for mod %s: \"templates\" not in json"), *Plugin.GetName());
        return;
    }
    int i = 0;
    for(TSharedPtr<FJsonValue> Item : *TemplatesArrayPtr)
    {
        i++;
        const TSharedPtr<FJsonObject>* ItemObjPtr;
        if(!Item->TryGetObject(ItemObjPtr)) {
            UE_LOG(LogAlpakit, Error, TEXT("Invalid template for mod %s: template %d: not an object"), *Plugin.GetName(), i);
            continue;
        }

        FString Error;
        TSharedPtr<FModTemplateDescription> ModTemplate = FModTemplateDescription::Load(*ItemObjPtr, TemplatesPath, Error);
        if(!ModTemplate.IsValid())
        {
            UE_LOG(LogAlpakit, Error, TEXT("Invalid templates for mod %s: template %d: %s"), *Plugin.GetName(), i, *Error);
            continue;
        }
        ModTemplates.Add(ModTemplate.ToSharedRef());
    }    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FAlpakitModule, Alpakit)

#include "Alpakit.h"
#include "AlpakitStyle.h"
#include "AlpakitCommands.h"
#include "AlpakitSettings.h"
#include "AlpakitWidget.h"
#include "ContentBrowserModule.h"
#include "ISettingsContainer.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "LevelEditor.h"
#include "IPluginBrowser.h"
#include "UATHelper/Public/IUATHelperModule.h"
#include "ModWizardDefinition.h"
#include "ModTargetsConfig.h"

static const FName AlpakitTabName("Alpakit");

#define LOCTEXT_NAMESPACE "FAlpakitModule"

DEFINE_LOG_CATEGORY(LogAlpakit)

const FName FAlpakitModule::ModCreatorTabName(TEXT("ModCreator"));

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
        FAlpakitCommands::Get().OpenPluginWindow,
        FExecuteAction::CreateLambda([](){
            FGlobalTabmanager::Get()->TryInvokeTab(AlpakitTabName);
        }),
        FCanExecuteAction());
    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
    
    //Register Alpakit Settings in Editor's Project Menu
    TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
    MenuExtender->AddMenuExtension(TEXT("FileProject"), EExtensionHook::After, PluginCommands,
        FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& Builder){
            Builder.AddMenuEntry(FAlpakitCommands::Get().OpenPluginWindow);
        }));
    LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
    
    //Register Alpakit Settings in Editor's Toolbar
    TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
    ToolbarExtender->AddToolBarExtension(TEXT("Play"), EExtensionHook::After, PluginCommands,
        FToolBarExtensionDelegate::CreateLambda([](FToolBarBuilder& Builder) {
            Builder.AddToolBarButton(FAlpakitCommands::Get().OpenPluginWindow);
        }));
    LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);

    //Register normal alpakit settings tab spawner
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AlpakitTabName,
        FOnSpawnTab::CreateLambda([](const FSpawnTabArgs&){
            const TSharedRef<SAlpakitWidget> AlpakitWidget = SNew(SAlpakitWidget);
            return SNew(SDockTab)
                .TabRole(NomadTab)
                // TODO: Save settings when tab is closed automatically
                //.OnTabClosed_Lambda([AlpakitWidget](TSharedRef<SDockTab>) { AlpakitWidget->SaveSettings(); })
                [ AlpakitWidget ];
        }))
        .SetDisplayName(LOCTEXT("FAlpakitTabTitle", "Alpakit"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);
    
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
        ModCreatorTabName,
        FOnSpawnTab::CreateRaw(this, &FAlpakitModule::HandleSpawnModCreatorTab))
        .SetDisplayName(LOCTEXT("NewPluginTabHeader", "New Mod"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FAlpakitModule::ShutdownModule() {
    if (UObjectInitialized()) {
        UnregisterSettings();
    }
    
    FAlpakitStyle::Shutdown();
    FAlpakitCommands::Unregister();

    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AlpakitTabName);
}
TSharedRef<SDockTab> FAlpakitModule::HandleSpawnModCreatorTab(const FSpawnTabArgs& SpawnTabArgs)
{
    IPluginBrowser& PluginBrowser = FModuleManager::Get().GetModuleChecked<IPluginBrowser>(TEXT("PluginBrowser"));
    return PluginBrowser.SpawnPluginCreatorTab(SpawnTabArgs, MakeShared<FModWizardDefinition>());
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

FString GetArgumentForLaunchType(EAlpakitStartGameType LaunchMode) {
    switch (LaunchMode) {
    case EAlpakitStartGameType::STEAM:
        return TEXT("Steam");
    case EAlpakitStartGameType::STEAM_SERVER:
        return TEXT("SteamDS");
    case EAlpakitStartGameType::EPIC_EARLY_ACCESS:
        return TEXT("EpicEA");
    case EAlpakitStartGameType::EPIC_EXPERIMENTAL:
        return TEXT("EpicExp");
    case EAlpakitStartGameType::EPIC_SERVER:
        return TEXT("EpicDS");
    case EAlpakitStartGameType::EPIC_SERVER_EXPERIMENTAL:
        return TEXT("EpicDSExp");
    case EAlpakitStartGameType::CUSTOM:
        return TEXT("Custom");
    default:
        return TEXT("");
    }
}

FString MakeUATArguments(FAlpakitTargetSettings TargetSettings, FString TargetName, bool AllowGameLaunch = false)
{
    FString UATArguments;
    
    if(TargetSettings.bCopyModsToGame) {
        UATArguments.Append(FString::Printf(TEXT("-%s_CopyToGameDir "), *TargetName));
        UATArguments.Append(FString::Printf(TEXT("-%s_GameDir=\"%s\" "), *TargetName, *TargetSettings.SatisfactoryGamePath.Path));

        if(TargetSettings.bLaunchGame && AllowGameLaunch) {
            UATArguments.Append(FString::Printf(TEXT("-%s_LaunchGame "), *TargetName));
            UATArguments.Append(FString::Printf(TEXT("-%s_LaunchType=%s "), *TargetName, *GetArgumentForLaunchType(TargetSettings.LaunchGameAfterPacking)));
            if(TargetSettings.LaunchGameAfterPacking == EAlpakitStartGameType::CUSTOM) {
                UATArguments.Append(FString::Printf(TEXT("-%s_CustomLaunchPath=\"%s\" "), *TargetName, *TargetSettings.CustomLaunchPath));
            }
        }
    }

    return UATArguments;
}

void FAlpakitModule::PackageMods(TArray<TSharedRef<IPlugin>> Plugins, bool ReleaseBuild) {
    if(QueueRunning) {
        UE_LOG(LogAlpakit, Warning, TEXT("PackageMods called while another queue is in progress"));
        return;
    }
    {
        FScopeLock Lock = FScopeLock(&QueueLock);
        ModQueue = Plugins;
        bReleaseBuild = ReleaseBuild;
    }
    OnQueueChanged.Broadcast(ModQueue);
    OnQueueStarted.Broadcast();
    QueueRunning = true;
    AsyncThread([this] {
        ProcessQueue();
        QueueRunning = false;
        AsyncTask(ENamedThreads::GameThread, [this] {
            OnQueueComplete.Broadcast();
        });
    });
}

void FAlpakitModule::ProcessQueue() {
    int NumQueued;
    {
        FScopeLock Lock = FScopeLock(&QueueLock);
        NumQueued = ModQueue.Num();
    }
    for (int i = NumQueued - 1; i >= 0; i--) {
        TSharedPtr<IPlugin> Plugin;
        {
            FScopeLock Lock = FScopeLock(&QueueLock);
            Plugin = ModQueue[0];
        }
        ProcessQueueItem(Plugin.ToSharedRef(), i == 0);
        {
            FScopeLock Lock = FScopeLock(&QueueLock);
            ModQueue.RemoveAt(0);
            AsyncTask(ENamedThreads::GameThread, [this] {
                OnQueueChanged.Broadcast(ModQueue);
            });
        }
    }
}

void FAlpakitModule::ProcessQueueItem(TSharedRef<IPlugin> Plugin, bool bIsLastItem) {
    UAlpakitSettings* Settings = UAlpakitSettings::Get();

    const FString ProjectPath = FPaths::IsProjectFilePathSet()
        ? FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath())
        : FPaths::RootDir() / FApp::GetProjectName() / FApp::GetProjectName() + TEXT(".uproject");

    FString AdditionalUATArguments;

    TArray<FString> PlatformNames;
    if (bReleaseBuild) {        
        FModTargetsConfig TargetsConfig(Plugin);
        if(TargetsConfig.bWindows) {
            AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Win64\" "));
            PlatformNames.Add(TEXT("Windows"));
        }
        if(TargetsConfig.bWindowsServer) {
            AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Win64_Server\" "));
            PlatformNames.Add(TEXT("Windows Server"));
        }
        if(TargetsConfig.bLinuxServer) {
            AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Linux_Server\" "));
            PlatformNames.Add(TEXT("Linux Server"));
        }
    } else {
        if(Settings->WindowsGameTargetSettings.bEnabled)
        {
            AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Win64\" "));
            AdditionalUATArguments.Append(MakeUATArguments(Settings->WindowsGameTargetSettings, TEXT("Windows"), bIsLastItem));
            PlatformNames.Add(TEXT("Windows"));
        }

        if(Settings->WindowsServerTargetSettings.bEnabled)
        {
            AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Win64_Server\" "));
            AdditionalUATArguments.Append(MakeUATArguments(Settings->WindowsServerTargetSettings, TEXT("WindowsServer"), bIsLastItem));
            PlatformNames.Add(TEXT("Windows Server"));
        }

        if(Settings->LinuxServerTargetSettings.bEnabled)
        {
            AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Linux_Server\" "));
            AdditionalUATArguments.Append(MakeUATArguments(Settings->LinuxServerTargetSettings, TEXT("LinuxServer"), bIsLastItem));
            PlatformNames.Add(TEXT("Linux Server"));
        }
    }

	if(bReleaseBuild)
		AdditionalUATArguments.Append(TEXT("-MergeArchive"));

    UE_LOG(LogAlpakit, Display, TEXT("Packaging plugin \"%s\""), *Plugin->GetName());

    const FString CommandLine = FString::Printf(TEXT("-ScriptsForProject=\"%s\" PackagePlugin -Project=\"%s\" -PluginName=\"%s\" %s"),
                                                *ProjectPath, *ProjectPath, *Plugin->GetName(), *AdditionalUATArguments);
    
    {
        // Destructor of FScopedEvent will wait for the event to be triggered
        FScopedEvent Done;
        AsyncTask(ENamedThreads::GameThread, [&]() {
            IUATHelperModule::Get().CreateUatTask(
                CommandLine,
                FText::FromString(FString::Join(PlatformNames, TEXT(", "))),
                FText::Format(LOCTEXT("PackageModTaskName", "Packaging {0}"), FText::FromString(Plugin->GetName())),
                FText::Format(LOCTEXT("PackageModTaskShortName", "Package {0}"), FText::FromString(Plugin->GetName())),
                FAlpakitStyle::Get().GetBrush("Alpakit.OpenPluginWindow"),
                nullptr,
                [&Done](FString resultType, double runTime) {
                    Done.Trigger();
                }
            );
        });
    }
    UE_LOG(LogAlpakit, Display, TEXT("Finished packaging mod %s"), *Plugin->GetName());
 }


#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FAlpakitModule, Alpakit)

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
#include "IUATHelperModule.h"
#include "ModWizardDefinition.h"

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
    ToolbarExtender->AddToolBarExtension(TEXT("Settings"), EExtensionHook::After, PluginCommands,
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
    default:
        return TEXT("");
    }
}

FText GetCurrentPlatformName() {
#if PLATFORM_WINDOWS
    return LOCTEXT("PlatformName_Windows", "Windows");
#elif PLATFORM_MAC
    return LOCTEXT("PlatformName_Mac", "Mac");
#elif PLATFORM_LINUX
    return LOCTEXT("PlatformName_Linux", "Linux");
#else
    return LOCTEXT("PlatformName_Other", "Other OS");
#endif
}

FString MakeUATArguments(FAlpakitTargetSettings TargetSettings, FString TargetName, bool LaunchGame = false)
{
    FString UATArguments;
    
    if(TargetSettings.bCopyModsToGame) {
        UATArguments.Append(FString::Printf(TEXT("-%s_CopyToGameDir "), *TargetName));
        UATArguments.Append(FString::Printf(TEXT("-%s_GameDir=%s "), *TargetName, *TargetSettings.SatisfactoryGamePath.Path));

        if(TargetSettings.LaunchGameAfterPacking != EAlpakitStartGameType::NONE && LaunchGame) {
            UATArguments.Append(FString::Printf(TEXT("-%s_LaunchGame "), *TargetName));
            UATArguments.Append(FString::Printf(TEXT("-%s_LaunchType=%s "), *TargetName, *GetArgumentForLaunchType(TargetSettings.LaunchGameAfterPacking)));
        }
    }

    return UATArguments;
}

void FAlpakitModule::PackageMods(TArray<FString> PluginNames, bool ReleaseBuild) {
    if(QueueRunning) {
        UE_LOG(LogAlpakit, Warning, TEXT("PackageMods called while another queue is in progress"));
        return;
    }
    {
        FScopeLock Lock = FScopeLock(&QueueLock);
        ModQueue = PluginNames;
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
        FString PluginName;
        {
            FScopeLock Lock = FScopeLock(&QueueLock);
            PluginName = ModQueue[0];
        }
        ProcessQueueItem(PluginName, i == 0);
        {
            FScopeLock Lock = FScopeLock(&QueueLock);
            ModQueue.RemoveAt(0);
            AsyncTask(ENamedThreads::GameThread, [this] {
                OnQueueChanged.Broadcast(ModQueue);
            });
        }
    }
}

void FAlpakitModule::ProcessQueueItem(FString PluginName, bool bIsLastItem) {
    UAlpakitSettings* Settings = UAlpakitSettings::Get();

    const FString ProjectPath = FPaths::IsProjectFilePathSet()
        ? FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath())
        : FPaths::RootDir() / FApp::GetProjectName() / FApp::GetProjectName() + TEXT(".uproject");

    FString AdditionalUATArguments;

    if(Settings->WindowsGameTargetSettings.bEnabled)
    {
        AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Win64\" "));
        if(!bReleaseBuild)
            AdditionalUATArguments.Append(MakeUATArguments(Settings->WindowsGameTargetSettings, TEXT("WindowsNoEditor"), bIsLastItem));
    }

    if(Settings->WindowsServerTargetSettings.bEnabled)
    {
        AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Win64_Server\" "));
        if(!bReleaseBuild)
            AdditionalUATArguments.Append(MakeUATArguments(Settings->WindowsServerTargetSettings, TEXT("WindowsServer"), bIsLastItem));
    }

    if(Settings->LinuxServerTargetSettings.bEnabled)
    {
        AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Linux_Server\" "));
        if(!bReleaseBuild)
            AdditionalUATArguments.Append(MakeUATArguments(Settings->LinuxServerTargetSettings, TEXT("LinuxServer"), bIsLastItem));
    }

	if(bReleaseBuild)
		AdditionalUATArguments.Append(TEXT("-MergeArchive"));

    UE_LOG(LogAlpakit, Display, TEXT("Packaging plugin \"%s\""), *PluginName);

    const FString CommandLine = FString::Printf(TEXT("-Compile -ScriptsForProject=\"%s\" PackagePlugin -Project=\"%s\" -PluginName=\"%s\" %s"),
                                                *ProjectPath, *ProjectPath, *PluginName, *AdditionalUATArguments);

    const FText PlatformName = GetCurrentPlatformName();
    {
        // Destructor of FScopedEvent will wait for the event to be triggered
        FScopedEvent Done;
        AsyncTask(ENamedThreads::GameThread, [&]() {
            IUATHelperModule::Get().CreateUatTask(
                CommandLine,
                PlatformName,
                FText::Format(LOCTEXT("PackageModTaskName", "Packaging {0}"), FText::FromString(PluginName)),
                FText::Format(LOCTEXT("PackageModTaskShortName", "Package {0}"), FText::FromString(PluginName)),
                FAlpakitStyle::Get().GetBrush("Alpakit.OpenPluginWindow"),
                [&Done](FString resultType, double runTime) {
                    Done.Trigger();
                }
            );
        });
    }
    UE_LOG(LogAlpakit, Display, TEXT("Finished packaging mod %s"), *PluginName);
 }


#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FAlpakitModule, Alpakit)
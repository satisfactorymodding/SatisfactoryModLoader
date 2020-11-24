#include "SatisfactoryModLoader.h"
#include "bootstrapper_exports.h"
#include "ConfigManager.h"
#include "FGAssetDumper.h"
#include "FGPlayerController.h"
#include "ItemTooltipHandler.h"
#include "LegacyConfigurationHelper.h"
#include "Logging.h"
#include "ModContentRegistry.h"
#include "ModHandler.h"
#include "NativeHookManager.h"
#include "NetworkHandler.h"
#include "RemoteCallObjectRegistry.h"
#include "SMLNetworkManager.h"
#include "SMLRemoteCallObject.h"
#include "SMLSubsystemHolder.h"
#include "SubsystemHolderRegistry.h"
#include "Patch/CrashContextPatch.h"
#include "Patch/MainMenuPatch.h"
#include "Patch/OfflinePlayerHandler.h"
#include "Patch/OptionsKeybindPatch.h"

extern "C" DLLEXPORT const TCHAR* modLoaderVersionString = TEXT("2.3.0");
extern "C" DLLEXPORT const TCHAR* targetBootstrapperVersionString = TEXT("2.0.11");
extern "C" DLLEXPORT const long targetGameVersion = 124066;

DEFINE_LOG_CATEGORY(LogSatisfactoryModLoader);

const FName FModLoaderExtraAttributes::EA_BootstrapperVersion = TEXT("BootstrapperVersion");

TSharedPtr<FModHandler> FSatisfactoryModLoader::ModHandlerPrivate = NULL;
TSharedPtr<BootstrapAccessors> FSatisfactoryModLoader::BootstrapperAccessors = NULL;
FSMLConfiguration FSatisfactoryModLoader::SMLConfigurationPrivate;

FVersion FSatisfactoryModLoader::GetModLoaderVersion() {
    static FVersion* ModLoaderVersion = NULL;
    if (ModLoaderVersion == NULL) {
        FString OutErrorMessage;
        ModLoaderVersion = new FVersion();
        ModLoaderVersion->ParseVersion(modLoaderVersionString, OutErrorMessage);
    }
    return *ModLoaderVersion;
}

TMap<FName, FString> FSatisfactoryModLoader::GetExtraAttributes() {
    TMap<FName, FString> OutExtraAttributes;
    if (BootstrapperAccessors.IsValid()) {
        OutExtraAttributes.Add(FModLoaderExtraAttributes::EA_BootstrapperVersion, BootstrapperAccessors->version);
    }
    return OutExtraAttributes;
}

void FSatisfactoryModLoader::SetupBootstrapperAccessors(const BootstrapAccessors& Accessors) {
    BootstrapperAccessors = MakeShareable(new BootstrapAccessors(Accessors));
}

void FSatisfactoryModLoader::LoadSMLConfiguration(bool bAllowSave) {
    const FString ConfigLocation = FLegacyConfigurationHelper::GetModConfigFilePath(TEXT("SML"));
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    bool bShouldWriteConfiguration = false;
    
    if (PlatformFile.FileExists(*ConfigLocation)) {
        FString RawSMLConfiguration;
        if (FFileHelper::LoadFileToString(RawSMLConfiguration, *ConfigLocation)) {
            
            TSharedPtr<FJsonObject> OutJsonObject;
            const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(RawSMLConfiguration);
            
            if (FJsonSerializer::Deserialize(JsonReader, OutJsonObject)) {
                FSMLConfiguration::ReadFromJson(OutJsonObject, SMLConfigurationPrivate, &bShouldWriteConfiguration);
                SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Successfully loaded SML configuration from disk"));
                
            } else {
                SML_LOG(LogSatisfactoryModLoader, Warning, TEXT("Failed to load SML configuration, JSON is malformed"));
                bShouldWriteConfiguration = true;
            }
        } else {
            SML_LOG(LogSatisfactoryModLoader, Error, TEXT("Failed to load SML configuration from %s"), *ConfigLocation);   
        }
    } else {
        SML_LOG(LogSatisfactoryModLoader, Log, TEXT("SML configuration file is missing, saving new one"));
        bShouldWriteConfiguration = true;
    }

    if (bShouldWriteConfiguration) {
        const TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        FSMLConfiguration::WriteToJson(JsonObject, SMLConfigurationPrivate);

        FString OutSerializedConfiguration;
        const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutSerializedConfiguration);
        FJsonSerializer::Serialize(JsonObject, JsonWriter);

        //Make sure configuration directory exists
        FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*FPaths::GetPath(ConfigLocation));

        //Write file onto the disk now
        if (FFileHelper::SaveStringToFile(OutSerializedConfiguration, *ConfigLocation)) {
            SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Successfully saved SML configuration"));
        } else {
            SML_LOG(LogSatisfactoryModLoader, Error, TEXT("Failed to save SML configuration to %s"), *ConfigLocation);
        }
    }
}

void FSatisfactoryModLoader::CheckGameAndBootstrapperVersion() {
    const uint32 CurrentChangelist = FEngineVersion::Current().GetChangelist();
    const uint32 MinChangelistSupported = (uint32) targetGameVersion;
    
    if (!(CurrentChangelist >= MinChangelistSupported)) {
        SML_LOG(LogSatisfactoryModLoader, Fatal, TEXT("Game version check failed: Game version is %d, but this SML version is built for %d"), CurrentChangelist, MinChangelistSupported);
    }

    FString OutErrorMessage;
    FVersion MinSupportedBootstrapperVersion;
    MinSupportedBootstrapperVersion.ParseVersion(targetBootstrapperVersionString, OutErrorMessage);

    if (BootstrapperAccessors.IsValid()) {
        FVersion BootstrapperVersion;
        BootstrapperVersion.ParseVersion(BootstrapperAccessors->version, OutErrorMessage);
        if (BootstrapperVersion.Compare(MinSupportedBootstrapperVersion) < 0) {
            SML_LOG(LogSatisfactoryModLoader, Fatal, TEXT("Bootstrapp version check failed: Bootstrapper version is %s, but this SML version only supports %s"), *BootstrapperVersion.ToString(), *MinSupportedBootstrapperVersion.ToString());
        }
    }
    SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Version check passed successfully! Game Changelist: %d"), CurrentChangelist);
}

void FSatisfactoryModLoader::InitializeSubsystems() {
    //First initialize Configuration Manager
    UConfigManager::RegisterConfigurationManager();
    
    //Then subsystem holder registry, as other subsystems depend on it
    USubsystemHolderRegistry::InitializeRegistry();

    //Register SML subsystem holder, holding content registry and chat command subsystem
    USMLSubsystemHolder::RegisterSubsystemHolder();
    
    //Override vanilla managers content resolution and make them follow mod content registry
    AModContentRegistry::InjectIntoVanillaManagers();
    
    //Initialize remote call object registry
    URemoteCallObjectRegistry::InitializeRegistry();
    
    //Register SML Remote Call Object
    USMLRemoteCallObject::RegisterRemoteCallObject();

    //Initialize network manager handling mod packets
    UModNetworkHandler::Initialize();
    
    //Register version checker for remote connections
    FSMLNetworkManager::RegisterMessageTypeAndHandlers();

    //Initialize tooltip handler
    UItemTooltipHandler::Initialize();

    //Register offline player handler, providing ability to fallback to offline username and net id
    FOfflinePlayerHandler::RegisterHandler();

    //Register asset dumping related console commands
    FGameAssetDumper::RegisterConsoleCommands();

    //Register main menu additions, like mod list and labels
    FMainMenuPatch::RegisterPatch();

    //Register options menu key bindings patch, providing better keybind categorization
    FOptionsKeybindPatch::RegisterPatch();
}

void FSatisfactoryModLoader::PreInitializeModLoading() {
    //Initialize logging first
    FSMLLoggingInternal::InitializeLogging();
    SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Satisfactory Mod Loader v.%s pre-initializing..."), modLoaderVersionString);

    //Don't try to save configuration in the editor, because it will make new folders with no real reason
    const bool bAllowSavingConfiguration = !WITH_EDITOR;
    LoadSMLConfiguration(bAllowSavingConfiguration);

    if (BootstrapperAccessors.IsValid()) {
        SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Using bootstrapper v.%s for mod loading"), BootstrapperAccessors->version);
    }

    //Check versions before actually trying to load mods
    CheckGameAndBootstrapperVersion();

    //Setup hooking with bootstrapper accessors if we have them
    //TODO hooking should be perfectly capable of working without accessors or PDB loading
    if (BootstrapperAccessors.IsValid()) {
        FNativeHookManagerInternal::SetupWithAccessors(*BootstrapperAccessors);
    }

    //Initialize ModHandler and perform mods discovery and pre initialization
    ModHandlerPrivate = MakeShareable(new FModHandler());
    if (BootstrapperAccessors.IsValid()) {
        ModHandlerPrivate->SetupWithAccessors(*BootstrapperAccessors);
    }
    
    //Perform mod discovery and check for stage errors
    SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Performing mod discovery"));
    ModHandlerPrivate->DiscoverMods();

    //Perform mods pre initialization (load native module DLLs into process)
    SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Pre-initializing mods"));
    ModHandlerPrivate->PreInitializeMods();

    //Register crash context patch very early, but after mod loading
    //So debug symbols can be flushed now from loaded native modules
    FCrashContextPatch::RegisterPatch();

    //Delay initialization to post engine init and finish pre-initialization
    FCoreDelegates::OnPostEngineInit.AddStatic(InitializeModLoading);
    
    SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Pre-initialization finished!"));
}

void FSatisfactoryModLoader::InitializeModLoading() {
    SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Performing mod loader initialization"));
    
    //Finish logging initialization and open console if requested by user
    FSMLLoggingInternal::HandlePostEngineInit();

    //Setup SML subsystems and custom content registries
    SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Setting up SML subsystems"));
    InitializeSubsystems();

    //Subscribe to world lifecycle event for mod initializers
    ModHandlerPrivate->SubscribeToLifecycleEvents();

    //Perform actual mod loading
    SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Initializing mods"));
    ModHandlerPrivate->InitializeMods();

    //Initialize game instance subsystems and give mods opportunity to register global content
    ModHandlerPrivate->InitializeGameInstance();

    //Reload configuration manager to handle mod configs
    UConfigManager::ReloadModConfigurations(true);

    SML_LOG(LogSatisfactoryModLoader, Log, TEXT("Initialization finished!"));
}

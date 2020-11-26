#include "Configuration/ConfigManager.h"
#include "BlueprintReflectionLibrary.h"
#include "ModHandler.h"
#include "Paths.h"
#include "SatisfactoryModLoader.h"
#include "SemVersion.h"
#include "TimerManager.h"
#include "Configuration/RootConfigValueHolder.h"
#include "Configuration/Values/ConfigValueSection.h"
#include "Engine/Engine.h"
#include "Json/JsonRawFormatConverter.h"
#include "Util/EngineUtil.h"

DEFINE_LOG_CATEGORY(LogConfigManager);

const TCHAR* SMLConfigModVersionField = TEXT("SML_ModVersion_DoNotChange");

#pragma optimize("", off)

void UConfigManager::ReloadModConfigurations(bool bSaveOnSchemaChange) {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();

    UE_LOG(LogConfigManager, Display, TEXT("Reloading mod configurations..."));
    for (const TPair<FConfigId, FRegisteredConfigurationData>& Pair : ConfigManager->Configurations) {
        LoadConfigurationInternal(Pair.Key, Pair.Value.RootValue, bSaveOnSchemaChange);
    }
}

void UConfigManager::SaveConfigurationInternal(const FConfigId& ConfigId) {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    const FRegisteredConfigurationData& ConfigurationData = ConfigManager->Configurations.FindChecked(ConfigId);
    
    const URootConfigValueHolder* RootValue = ConfigurationData.RootValue;
    URawFormatValue* RawFormatValue = RootValue->GetWrappedValue()->Serialize(ConfigManager);
    checkf(RawFormatValue, TEXT("Root RawFormatValue returned NULL for config %s"), *ConfigId.ModReference);
    
    //Root value should always be JsonObject, since root property is section property
    const TSharedPtr<FJsonValue> JsonValue = FJsonRawFormatConverter::ConvertToJson(RawFormatValue);
    check(JsonValue->Type == EJson::Object);
    TSharedRef<FJsonObject> UnderlyingObject = JsonValue->AsObject().ToSharedRef();
    
    //Serialize resulting JSON to string
    FString JsonOutputString;
    const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonOutputString);
    FJsonSerializer::Serialize(UnderlyingObject, JsonWriter);
            
    //Record mod version so we can keep file system file schema up to date
    FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
    if (ModHandler != NULL && ModHandler->IsModLoaded(ConfigId.ModReference)) {
        const FVersion ModVersion = ModHandler->GetLoadedMod(ConfigId.ModReference)->ModInfo.Version;
        UnderlyingObject->SetStringField(SMLConfigModVersionField, ModVersion.ToString());
    }

    //Write configuration into the file system now at the generated path
    const FString ConfigurationFilePath = GetConfigurationFilePath(ConfigId);
    //Make sure configuration directory exists
    FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*FPaths::GetPath(ConfigurationFilePath));
    
    if (!FFileHelper::SaveStringToFile(JsonOutputString, *ConfigurationFilePath)) {
        UE_LOG(LogConfigManager, Error, TEXT("Failed to save configuration file to %s"), *ConfigurationFilePath);
        return;
    }
    UE_LOG(LogConfigManager, Display, TEXT("Saved configuration to %s"), *ConfigurationFilePath);
}

void UConfigManager::LoadConfigurationInternal(const FConfigId& ConfigId, URootConfigValueHolder* RootConfigValueHolder, bool bSaveOnSchemaChange) {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
    
    //Determine configuration path and try to read it to string if it exists
    const FString ConfigurationFilePath = GetConfigurationFilePath(ConfigId);

    //Check if configuration file exists, and if it doesn't, return early, optionally writing defaults
    if (!IFileManager::Get().FileExists(*ConfigurationFilePath)) {
        if (bSaveOnSchemaChange) {
            SaveConfigurationInternal(ConfigId);
        }
        return;
    }

    //Load file contents into the string for parsing
    FString JsonTextString;
    if (!FFileHelper::LoadFileToString(JsonTextString, *ConfigurationFilePath)) {
        UE_LOG(LogConfigManager, Error, TEXT("Failed to load configuration file from %s"), *ConfigurationFilePath);
        return;
    }

    //Try to parse it as valid JSON now
    const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonTextString);
    TSharedPtr<FJsonObject> JsonObject;
    if (!FJsonSerializer::Deserialize(JsonReader, JsonObject)) {
        UE_LOG(LogConfigManager, Error, TEXT("Failed to parse configuration file %s"), *ConfigurationFilePath);
        //TODO maybe rename it and write default values instead?
        return;
    }

    //Convert JSON tree into the raw value tree and feed it to root section value
    const TSharedRef<FJsonValue> RootValue = MakeShareable(new FJsonValueObject(JsonObject));
    URawFormatValue* RawFormatValue = FJsonRawFormatConverter::ConvertToRawFormat(ConfigManager, RootValue);
    RootConfigValueHolder->GetWrappedValue()->Deserialize(RawFormatValue);

    UE_LOG(LogConfigManager, Display, TEXT("Successfully loaded configuration from %s"), *ConfigurationFilePath);

    //Check that mod version matches if we are allowed to overwrite files
    if (ModHandler != NULL && ModHandler->IsModLoaded(ConfigId.ModReference)) {
        const FString ModVersion = ModHandler->GetLoadedMod(ConfigId.ModReference)->ModInfo.Version.ToString();
        FString FileVersion;
        if (JsonObject->HasTypedField<EJson::String>(SMLConfigModVersionField)) {
            FileVersion = JsonObject->GetStringField(SMLConfigModVersionField);
        }
        //Overwrite file if schema version doesn't match loaded mod version
        if (bSaveOnSchemaChange && FileVersion != ModVersion) {
            UE_LOG(LogConfigManager, Display, TEXT("Refreshing configuration file %s"), *ConfigurationFilePath);
            SaveConfigurationInternal(ConfigId);
        }
    }
}

void UConfigManager::FlushPendingSaves() {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    for (const FConfigId& ConfigId : ConfigManager->PendingSaveConfigurations) {
        SaveConfigurationInternal(ConfigId);
    }
    ConfigManager->PendingSaveConfigurations.Empty();
}

void UConfigManager::MarkConfigurationDirty(const FConfigId& ConfigId) {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    ConfigManager->PendingSaveConfigurations.AddUnique(ConfigId);
    //Make sure cached structs are synchronized with real configuration state
    ReinitializeCachedStructs(ConfigId);
}

void UConfigManager::ReinitializeCachedStructs(const FConfigId& ConfigId) {
#if OPTIMIZE_FILL_CONFIGURATION_STRUCT
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    const FRegisteredConfigurationData& ConfigurationData = ConfigManager->Configurations.FindChecked(ConfigId);
    URootConfigValueHolder* RootConfigValue = ConfigurationData.RootValue;
    
    for (const TPair<UScriptStruct*, FReflectedObject>& Pair : ConfigurationData.CachedValues) {
        RootConfigValue->GetWrappedValue()->FillConfigStructSelf(Pair.Value);
    }
#endif
}

void UConfigManager::FillConfigurationStruct(const FConfigId& ConfigId, const FDynamicStructInfo& StructInfo) {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    FRegisteredConfigurationData& ConfigurationData = ConfigManager->Configurations.FindChecked(ConfigId);

#if OPTIMIZE_FILL_CONFIGURATION_STRUCT
    //If this struct type is cached, just copy it from the cache directly
    //Cached value should be up to date with configuration state as long as MarkConfigurationDirty is called properly
    const FReflectedObject* ExistingObject = ConfigurationData.CachedValues.Find(StructInfo.Struct);
    if (ExistingObject != NULL) {
        ExistingObject->CopyWrappedStruct(StructInfo.Struct, StructInfo.StructValue);
        return;
    }
#endif

    //We don't have this type of script struct in the cache, reflect it and populate
    URootConfigValueHolder* RootConfigValue = ConfigurationData.RootValue;
    const FReflectedObject StructReflection = UBlueprintReflectionLibrary::ReflectStruct(StructInfo);
    RootConfigValue->GetWrappedValue()->FillConfigStructSelf(StructReflection);

    //Copy populated reflected struct state back into original state
    StructReflection.CopyWrappedStruct(StructInfo.Struct, StructInfo.StructValue);

#if OPTIMIZE_FILL_CONFIGURATION_STRUCT
    //Store cached struct reflection in the cache
    ConfigurationData.CachedValues.Add(StructInfo.Struct, StructReflection);

    //Because for some retarded reason UPROPERTY on Configurations doesn't prevent garbage collection hello????
    StructInfo.Struct->AddToRoot();
#endif
}

UUserWidget* UConfigManager::CreateConfigurationWidget(const FConfigId& ConfigId, UUserWidget* Outer) {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    FRegisteredConfigurationData& ConfigurationData = ConfigManager->Configurations.FindChecked(ConfigId);
    const TSubclassOf<UModConfiguration> ConfigurationType = ConfigurationData.ConfigurationClass;
    UConfigPropertySection* RootProperty = ConfigurationType.GetDefaultObject()->RootSection;
    UConfigValueSection* RootValue = ConfigurationData.RootValue->GetWrappedValue();

    return RootProperty->CreateEditorWidget(Outer, RootValue);
}

void UConfigManager::RegisterModConfiguration(const FConfigId& ConfigId, TSubclassOf<UModConfiguration> Configuration) {
    checkf(Configuration.Get(), TEXT("Attempt to register NULL configuration"));

    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    checkf(ConfigManager->Configurations.Find(ConfigId) == NULL, TEXT("Configuration already registered: %s:%s"), *ConfigId.ModReference, *ConfigId.ConfigCategory);
    
    //Create root value and wrap it into config root handling marking config dirty
    URootConfigValueHolder* RootConfigValueHolder = NewObject<URootConfigValueHolder>(ConfigManager);

    //Because for some retarded reason UPROPERTY on Configurations doesn't prevent garbage collection hello????
    RootConfigValueHolder->AddToRoot();
    Configuration->AddToRoot();
    
    UConfigValueSection* RootSectionValue = CastChecked<UConfigValueSection>(Configuration.GetDefaultObject()->RootSection->CreateNewValue(RootConfigValueHolder));
    RootConfigValueHolder->SetupRootValue(ConfigId, RootSectionValue);
    
    //Register configuration inside all of the internal properties
    ConfigManager->Configurations.Add(ConfigId, FRegisteredConfigurationData{ConfigId, Configuration, RootConfigValueHolder});
}

FString UConfigManager::GetConfigurationFolderPath() {
    return FPaths::RootDir() + TEXT("configs/");
}

FString UConfigManager::GetConfigurationFilePath(const FConfigId& ConfigId) {
    const FString ConfigDirectory = GetConfigurationFolderPath();
    if (ConfigId.ConfigCategory == TEXT("")) {
        //Category is empty, that means mod has only one configuration file
        return ConfigDirectory + FString::Printf(TEXT("%s.cfg"), *ConfigId.ModReference);
    }
    //We have a category, so mod reference is a folder and category is a file name
    return ConfigDirectory + FString::Printf(TEXT("%s/%s.cfg"), *ConfigId.ModReference, *ConfigId.ConfigCategory);
}

void UConfigManager::RegisterConfigurationManager() {
    //Subscribe to exit event so we make sure that pending saves are written to filesystem
    FCoreDelegates::OnPreExit.AddLambda([](){
        UE_LOG(LogConfigManager, Display, TEXT("Flushing configuration caches into file system"));
        FlushPendingSaves();
    });

    //Setup a timer which will force all changes into filesystem every 10 seconds
    FTimerManager* TimerManager = FEngineUtil::GetGlobalTimerManager();
    check(TimerManager);
    FTimerHandle OutTimerHandle;
    TimerManager->SetTimer(OutTimerHandle, [](){ UConfigManager::FlushPendingSaves(); }, 10.0f, true);
}

#pragma optimize("", on)
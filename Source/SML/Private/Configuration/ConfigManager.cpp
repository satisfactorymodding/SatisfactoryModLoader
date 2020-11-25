#include "Configuration/ConfigManager.h"
#include "BlueprintReflectionLibrary.h"
#include "Logging.h"
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

void UConfigManager::ReloadModConfigurations(bool bSaveOnSchemaChange) {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();

    SML_LOG(LogConfigManager, Display, TEXT("Reloading mod configurations..."));
    for (const TPair<FConfigId, URootConfigValueHolder*>& Pair : ConfigManager->ActiveConfigValues) {
        LoadConfigurationInternal(Pair.Key, Pair.Value, bSaveOnSchemaChange);
    }
}

void UConfigManager::SaveConfigurationInternal(const FConfigId& ConfigId) {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    
    if (ConfigManager->ActiveConfigValues.Contains(ConfigId)) {
        URootConfigValueHolder* ConfigValueHolder = ConfigManager->ActiveConfigValues.FindChecked(ConfigId);
        URawFormatValue* RawFormatValue = ConfigValueHolder->GetWrappedValue()->Serialize(ConfigManager);
        checkf(RawFormatValue, TEXT("Root RawFormatValue returned NULL for config %s"), *ConfigId.ModReference);
        
        //Root value should always be JsonObject, since root property is section property
        const TSharedPtr<FJsonValue> JsonValue = FJsonRawFormatConverter::ConvertToJson(RawFormatValue);
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
            SML_LOG(LogConfigManager, Error, TEXT("Failed to save configuration file to %s"), *ConfigurationFilePath);
            return;
        }
        SML_LOG(LogConfigManager, Display, TEXT("Saved configuration to %s"), *ConfigurationFilePath);
    }
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
        SML_LOG(LogConfigManager, Error, TEXT("Failed to load configuration file from %s"), *ConfigurationFilePath);
        return;
    }

    //Try to parse it as valid JSON now
    const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonTextString);
    TSharedPtr<FJsonObject> JsonObject;
    if (!FJsonSerializer::Deserialize(JsonReader, JsonObject)) {
        SML_LOG(LogConfigManager, Error, TEXT("Failed to parse configuration file %s"), *ConfigurationFilePath);
        //TODO maybe rename it and write default values instead?
        return;
    }

    //Convert JSON tree into the raw value tree and feed it to root section value
    const TSharedRef<FJsonValue> RootValue = MakeShareable(new FJsonValueObject(JsonObject));
    URawFormatValue* RawFormatValue = FJsonRawFormatConverter::ConvertToRawFormat(ConfigManager, RootValue);
    RootConfigValueHolder->GetWrappedValue()->Deserialize(RawFormatValue);

    SML_LOG(LogConfigManager, Display, TEXT("Successfully loaded configuration from %s"), *ConfigurationFilePath);

    //Check that mod version matches if we are allowed to overwrite files
    if (ModHandler != NULL && ModHandler->IsModLoaded(ConfigId.ModReference)) {
        const FString ModVersion = ModHandler->GetLoadedMod(ConfigId.ModReference)->ModInfo.Version.ToString();
        FString FileVersion;
        if (JsonObject->HasTypedField<EJson::String>(SMLConfigModVersionField)) {
            FileVersion = JsonObject->GetStringField(SMLConfigModVersionField);
        }
        //Overwrite file if schema version doesn't match loaded mod version
        if (bSaveOnSchemaChange && FileVersion != ModVersion) {
            SML_LOG(LogConfigManager, Display, TEXT("Refreshing configuration file %s"), *ConfigurationFilePath);
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
    URootConfigValueHolder* RootConfigValue = ConfigManager->ActiveConfigValues.FindChecked(ConfigId);
    TMap<UScriptStruct*, FReflectedObject>& CachedValues = ConfigManager->CachedStructValues.FindChecked(ConfigId);
    for (const TPair<UScriptStruct*, FReflectedObject>& Pair : CachedValues) {
        RootConfigValue->GetWrappedValue()->FillConfigStructSelf(Pair.Value);
    }
#endif
}

void UConfigManager::FillConfigurationStruct(const FConfigId& ConfigId, const FDynamicStructInfo& StructInfo) {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    
    if (ConfigManager->ActiveConfigValues.Contains(ConfigId)) {
#if OPTIMIZE_FILL_CONFIGURATION_STRUCT
        
        UScriptStruct* ScriptStructType = StructInfo.Struct;
        TMap<UScriptStruct*, FReflectedObject>& CachedValues = ConfigManager->CachedStructValues.FindChecked(ConfigId);
        if (CachedValues.Contains(ScriptStructType)) {
            //This struct type is cached, just copy it from cache directly
            const FReflectedObject& ExistingObject = CachedValues.FindChecked(ScriptStructType);
            ExistingObject.CopyWrappedStruct(ScriptStructType, StructInfo.StructValue);
            return;
        }

        //We don't have this type of script struct in the cache, let's make a new one and populate it
        URootConfigValueHolder* RootConfigValue = ConfigManager->ActiveConfigValues.FindChecked(ConfigId);
        FReflectedObject ReflectedObject;
        ReflectedObject.SetupFromStruct(ScriptStructType);
        RootConfigValue->GetWrappedValue()->FillConfigStructSelf(ReflectedObject);
        //Copy struct value into the resulting struct
        ReflectedObject.CopyWrappedStruct(ScriptStructType, StructInfo.StructValue);
        //Cache this struct for faster access next time
        CachedValues.Add(ScriptStructType, ReflectedObject);
        
#else
        
        URootConfigValueHolder* RootConfigValue = ConfigManager->ActiveConfigValues.FindChecked(ConfigId);
        FReflectedObject ReflectedResultStruct;
        ReflectedResultStruct.SetupFromStruct(StructInfo.Struct, StructInfo.StructValue);
        RootConfigValue->GetWrappedValue()->FillConfigStructSelf(ReflectedResultStruct);
#endif
    }
}

UUserWidget* UConfigManager::CreateConfigurationWidget(const FConfigId& ConfigId, UUserWidget* Outer) {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    TSubclassOf<UModConfiguration> const* Configuration = ConfigManager->RegisteredConfigs.Find(ConfigId);
    if (Configuration != NULL) {
        UConfigPropertySection* RootProperty = Configuration->GetDefaultObject()->RootSection;
        UConfigValueSection* RootValue = ConfigManager->ActiveConfigValues.FindChecked(ConfigId)->GetWrappedValue();
        return RootProperty->CreateEditorWidget(Outer, RootValue);
    }
    return NULL;
}

void UConfigManager::RegisterModConfiguration(const FConfigId& ConfigId, TSubclassOf<UModConfiguration> Configuration) {
    UConfigManager* ConfigManager = GetMutableDefault<UConfigManager>();
    checkf(!ConfigManager->RegisteredConfigs.Contains(ConfigId), TEXT("Configuration already registered: %s:%s"), *ConfigId.ModReference, *ConfigId.ConfigCategory);

    //Create root value and wrap it into config root handling marking config dirty
    URootConfigValueHolder* RootConfigValueHolder = NewObject<URootConfigValueHolder>(ConfigManager);
    UConfigValueSection* RootSectionValue = CastChecked<UConfigValueSection>(Configuration.GetDefaultObject()->RootSection->CreateNewValue(RootConfigValueHolder));
    RootConfigValueHolder->SetupRootValue(ConfigId, RootSectionValue);
    
    //Register configuration inside all of the internal properties
    ConfigManager->RegisteredConfigs.Add(ConfigId, Configuration);
    ConfigManager->ActiveConfigValues.Add(ConfigId, RootConfigValueHolder);
    ConfigManager->CachedStructValues.Add(ConfigId, TMap<UScriptStruct*, FReflectedObject>());
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
        SML_LOG(LogConfigManager, Display, TEXT("Flushing configuration caches into file system"));
        FlushPendingSaves();
    });

    //Setup a timer which will force all changes into filesystem every 10 seconds
    FTimerManager* TimerManager = FEngineUtil::GetGlobalTimerManager();
    check(TimerManager);
    FTimerHandle OutTimerHandle;
    TimerManager->SetTimer(OutTimerHandle, [](){ UConfigManager::FlushPendingSaves(); }, 10.0f, true);
}
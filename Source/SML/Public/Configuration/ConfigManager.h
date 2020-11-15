#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConfigValue.h"
#include "ModConfiguration.h"
#include "ReflectionHelper.h"
#include "ConfigManager.generated.h"

//Whenever to use FillConfigStruct optimization caching results in a single struct and then copying it
//When disabled, each FillConfigStruct call will cause full population of passed struct through UConfigValue chain
#define OPTIMIZE_FILL_CONFIGURATION_STRUCT 1

class UUserWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogConfigManager, Log, Log)

/** Describes an identifier for a single configuration tree */
USTRUCT(BlueprintType)
struct SML_API FConfigId {
    GENERATED_BODY();
public:    
    /** Mod reference of the requested configuration owner */
    UPROPERTY(BlueprintReadWrite)
    FString ModReference;

    /** Category if this configuration. Leave empty if mod has only one configuration */
    UPROPERTY(BlueprintReadWrite)
    FString ConfigCategory;

    bool operator==(const FConfigId& ConfigId) const;
};

FORCEINLINE uint32 GetTypeHash(const FConfigId& ConfigId) {
    return HashCombine(GetTypeHash(ConfigId.ModReference), GetTypeHash(ConfigId.ConfigCategory));
}

FORCEINLINE bool FConfigId::operator==(const FConfigId& ConfigId) const {
    return ConfigId.ModReference == ModReference && ConfigId.ConfigCategory == ConfigCategory;
}

/** Manages mod configuration states */
UCLASS()
class SML_API UConfigManager : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    /** Reloads mod configurations from disk, optionally saving them back if schema changes */
    UFUNCTION(BlueprintCallable)
    static void ReloadModConfigurations(bool bSaveOnSchemaChange);

    /** Flushes all pending saves and forces manager to write them into filesystem */
    UFUNCTION(BlueprintCallable)
    static void FlushPendingSaves();

    /** Marks configuration as dirty and pending save */
    UFUNCTION(BlueprintCallable)
    static void MarkConfigurationDirty(const FConfigId& ConfigId);
    
    /** Fills passed struct with a data obtained from active configuration identified by passed config id */
    UFUNCTION(BlueprintPure)
    static void FillConfigurationStruct(const FConfigId& ConfigId, UPARAM(Ref) const FDynamicStructInfo& StructInfo);

    /** Creates a configuration widget hierarchy for active configuration specified by passed id */
    UFUNCTION(BlueprintCallable)
    static UUserWidget* CreateConfigurationWidget(const FConfigId& ConfigId, UUserWidget* Outer);

    /** Registers a configuration under specified ID. Should be only called on startup for it to load from disk */
    UFUNCTION(BlueprintCallable)
    static void RegisterModConfiguration(const FConfigId& ConfigId, TSubclassOf<UModConfiguration> Configuration);

    /** Returns configuration folder path used by config manager */
    static FString GetConfigurationFolderPath();
private:
    friend class FSatisfactoryModLoader;

    /** Returns path to the provided configuration */
    static FString GetConfigurationFilePath(const FConfigId& ConfigId);

    /** Saves configuration with specified id into the file system */
    static void SaveConfigurationInternal(const FConfigId& ConfigId);

    /** Loads configuration and optionally overwrites it on the disk */
    static void LoadConfigurationInternal(const FConfigId& ConfigId, class URootConfigValueHolder* RootConfigValueHolder, bool bSaveOnSchemaChange);

    /** Registers exit callbacks and internal save timer */
    static void RegisterConfigurationManager();

    /** Updates cached struct values with actual values from configuration */
    static void ReinitializeCachedStructs(const FConfigId& ConfigId);

    /** Array of all configurations pending save */
    TArray<FConfigId> PendingSaveConfigurations;
    
    /** Registered configuration schemas */
    TMap<FConfigId, TSubclassOf<UModConfiguration>> RegisteredConfigs;
    
    /** Active configuration values, either default populated or loaded from disk */
    TMap<FConfigId, class URootConfigValueHolder*> ActiveConfigValues;
    
    /** Cached values of struct types passed to FillConfigurationStruct, used for quickly copying them for better performance */
    TMap<FConfigId, TMap<UScriptStruct*, FReflectedObject>> CachedStructValues;
};
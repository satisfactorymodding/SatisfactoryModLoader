#pragma once
#include "CoreMinimal.h"
#include "Configuration/ConfigValue.h"
#include "Subsystems/EngineSubsystem.h"
#include "Configuration/ModConfiguration.h"
#include "Reflection/ReflectionHelper.h"
#include "ConfigManager.generated.h"

//Whenever to use FillConfigStruct optimization caching results in a single struct and then copying it
//When disabled, each FillConfigStruct call will cause full population of passed struct through UConfigValue chain
#define OPTIMIZE_FILL_CONFIGURATION_STRUCT 1

class UUserWidget;
class URootConfigValueHolder;

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

/** Describes active configuration data */
USTRUCT()
struct SML_API FRegisteredConfigurationData {
    GENERATED_BODY()
public:
    /** Identifier of configuration being handled */
    UPROPERTY()
    FConfigId ConfigId;

    /** Descriptor of this configuration */
    UPROPERTY()
    TSubclassOf<UModConfiguration> ConfigurationClass;

    /** Root value in this configuration value hierarchy */
    UPROPERTY()
    URootConfigValueHolder* RootValue;

    /** Cached structs populated with this configuration values. Used for faster FillConfigStruct implementation */
    UPROPERTY()
    TMap<UScriptStruct*, FReflectedObject> CachedValues;
};

/** Manages mod configuration states */
UCLASS()
class SML_API UConfigManager : public UEngineSubsystem {
    GENERATED_BODY()
public:
    /** Reloads mod configurations from disk, optionally saving them back if schema changes */
    UFUNCTION(BlueprintCallable)
    void ReloadModConfigurations();

    /** Flushes all pending saves and forces manager to write them into filesystem */
    UFUNCTION(BlueprintCallable)
    void FlushPendingSaves();

    /** Marks configuration as dirty and pending save */
    UFUNCTION(BlueprintCallable)
    void MarkConfigurationDirty(const FConfigId& ConfigId);
    
    /** Fills passed struct with a data obtained from active configuration identified by passed config id */
    UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "StructInfo"))
    void FillConfigurationStruct(const FConfigId& ConfigId, UPARAM(Ref) const FDynamicStructInfo& StructInfo);

    /** Creates a configuration widget hierarchy for active configuration specified by passed id */
    UFUNCTION(BlueprintCallable)
    UUserWidget* CreateConfigurationWidget(const FConfigId& ConfigId, UUserWidget* Outer);

    /** Registers a configuration under specified ID. Should be only called on startup for it to load from disk */
    UFUNCTION(BlueprintCallable)
    void RegisterModConfiguration(const FConfigId& ConfigId, TSubclassOf<UModConfiguration> Configuration);

    void Initialize(FSubsystemCollectionBase& Collection) override;
    
    /** Returns configuration folder path used by config manager */
    static FString GetConfigurationFolderPath();
private:
    friend class FSatisfactoryModLoader;
    
    /** Returns path to the provided configuration */
    static FString GetConfigurationFilePath(const FConfigId& ConfigId);

    void ReplaceConfigurationClass(FRegisteredConfigurationData* ExistingData, TSubclassOf<UModConfiguration> NewConfiguration);
    
    void OnTimerManagerAvailable(class FTimerManager* TimerManager);

    /** Saves configuration with specified id into the file system */
    void SaveConfigurationInternal(const FConfigId& ConfigId);

    /** Loads configuration and optionally overwrites it on the disk */
    void LoadConfigurationInternal(const FConfigId& ConfigId, class URootConfigValueHolder* RootConfigValueHolder, bool bSaveOnSchemaChange);

    /** Updates cached struct values with actual values from configuration */
    void ReinitializeCachedStructs(const FConfigId& ConfigId);

    /** Array of all configurations pending save */
    TArray<FConfigId> PendingSaveConfigurations;
    
    /** Registered configurations */
    UPROPERTY()
    TMap<FConfigId, FRegisteredConfigurationData> Configurations;

    DECLARE_FUNCTION(execFillConfigurationStruct) {
        P_GET_STRUCT(FConfigId, ConfigId);
        const FDynamicStructInfo StructInfo = FReflectionHelper::CheckStructParameter(Context, Stack);
        P_FINISH;
        P_THIS->FillConfigurationStruct(ConfigId, StructInfo);
    }
};

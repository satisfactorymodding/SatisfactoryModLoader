#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "AlpakitSettings.generated.h"

UENUM()
enum class EAlpakitStartGameType : uint8 {
    STEAM UMETA(DisplayName = "Steam"),
    STEAM_SERVER UMETA(DisplayName = "Steam: Dedicated Server"),
    EPIC_EARLY_ACCESS UMETA(DisplayName = "Epic: Early Access"),
    EPIC_EXPERIMENTAL UMETA(DisplayName = "Epic: Experimental"),
    EPIC_SERVER UMETA(DisplayName = "Epic: Dedicated Server"),
    CUSTOM UMETA(DisplayName = "Custom")
};

USTRUCT()
struct ALPAKIT_API FAlpakitTargetSettings
{
    GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, config, Category = Config)
    bool bEnabled = true;

    UPROPERTY(config)
    bool bCopyModsToGame = false;
    
    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName = "Copy to Game Path", meta = ( EditCondition = bCopyModsToGame ))
    FDirectoryPath SatisfactoryGamePath;

    UPROPERTY(config)
    bool bLaunchGame = false;

    UPROPERTY(EditAnywhere, config, Category = Config, meta = ( EditCondition = bLaunchGame ))
    EAlpakitStartGameType LaunchGameAfterPacking;

    UPROPERTY(EditAnywhere, config, Category = Config, meta = ( EditCondition = "LaunchGameAfterPacking == EAlpakitStartGameType::CUSTOM", EditConditionHides ))
    FString CustomLaunchPath;
};

UCLASS(config=Game)
class ALPAKIT_API UAlpakitSettings : public UObject {
    GENERATED_BODY()
public:
    /** Retrieves global instance of alpakit settings */
    static UAlpakitSettings* Get();

    /** Saves alpakit settings to configuration file */
    void SaveSettings();

    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName="Windows")
    FAlpakitTargetSettings WindowsGameTargetSettings;

    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName="Windows Server")
    FAlpakitTargetSettings WindowsServerTargetSettings;

    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName="Linux Server")
    FAlpakitTargetSettings LinuxServerTargetSettings;
    
    UPROPERTY(BlueprintReadOnly, config, Category = Config)
    TMap<FString, bool> ModSelection;
};

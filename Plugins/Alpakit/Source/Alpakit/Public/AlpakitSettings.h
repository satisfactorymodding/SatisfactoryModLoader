#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "AlpakitSettings.generated.h"

UENUM()
enum class EAlpakitStartGameType : uint8 {
    NONE UMETA(DisplayName = "Do not launch"),
    STEAM UMETA(DisplayName = "Steam"),
    STEAM_SERVER UMETA(DisplayName = "Steam Dedicated Server"),
    EPIC_EARLY_ACCESS UMETA(DisplayName = "Epic: Early Access"),
    EPIC_EXPERIMENTAL UMETA(DisplayName = "Epic: Experimental"),
    EPIC_SERVER UMETA(DisplayName = "Epic: Dedicated Server")
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

    UPROPERTY(EditAnywhere, config, Category = Config, meta = ( EditCondition = bCopyModsToGame ))
    EAlpakitStartGameType LaunchGameAfterPacking;

};

UCLASS(config=Game)
class ALPAKIT_API UAlpakitSettings : public UObject {
    GENERATED_BODY()
public:
    /** Retrieves global instance of alpakit settings */
    static UAlpakitSettings* Get();

    /** Saves alpakit settings to configuration file */
    void SaveSettings();

    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName="Windows Client")
    FAlpakitTargetSettings WindowsNoEditorTargetSettings;

    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName="Windows Server")
    FAlpakitTargetSettings WindowsServerTargetSettings;

    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName="Linux Server")
    FAlpakitTargetSettings LinuxServerTargetSettings;

    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName="Create merged mod for release")
    bool bMerge;
    
    UPROPERTY(BlueprintReadOnly, config, Category = Config)
    TMap<FString, bool> ModSelection;
};

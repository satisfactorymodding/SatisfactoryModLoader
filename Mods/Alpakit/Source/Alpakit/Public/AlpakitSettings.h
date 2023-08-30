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
    EPIC_SERVER_EXPERIMENTAL UMETA(DisplayName = "Epic: Dedicated Server Experimental"),
    CUSTOM UMETA(DisplayName = "Custom")
};

USTRUCT()
struct ALPAKIT_API FAlpakitTargetSettings
{
    GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, config, Category = Config, meta = (ToolTip = "Controls if this target will be built when pressing the 'Alpakit Dev' button, and what action will be taken for this target after a successful pack"))
    bool bEnabled = true;

    UPROPERTY(config)
    bool bCopyModsToGame = false;
    
    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName = "Copy to Game Path", meta = (EditCondition = bCopyModsToGame, ToolTip = "If enabled, mods will be copied to this installation location after a successful pack"))
    FDirectoryPath SatisfactoryGamePath;

    UPROPERTY(config)
    bool bLaunchGame = false;

    UPROPERTY(EditAnywhere, config, Category = Config, meta = ( EditCondition = bLaunchGame, ToolTip = "If enabled, this approach will be used to launch this platform after a successful pack"))
    EAlpakitStartGameType LaunchGameAfterPacking;

    UPROPERTY(EditAnywhere, config, Category = Config, meta = ( EditCondition = "LaunchGameAfterPacking == EAlpakitStartGameType::CUSTOM", EditConditionHides, ToolTip = "The Unreal Automation tool will execute this after a successful pack.\nCheck the 'Testing' page on the modding docs for example scripts to call with this feature.\n\nExample value:\nC:\\Git\\SF_ModProject\\RobWorkingDir\\Auto_Exp_LoadLatest.bat"))
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

    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName="Windows", meta = (ToolTip = "Packaging settings for 'Alpakit Dev' for the Windows target"))
    FAlpakitTargetSettings WindowsGameTargetSettings;

    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName="Windows Server", meta = (ToolTip = "Packaging settings for 'Alpakit Dev' for the Windows Server target"))
    FAlpakitTargetSettings WindowsServerTargetSettings;

    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName="Linux Server", meta = (ToolTip = "Packaging settings for 'Alpakit Dev' for the Linux Server target"))
    FAlpakitTargetSettings LinuxServerTargetSettings;
    
    UPROPERTY(BlueprintReadOnly, config, Category = Config)
    TMap<FString, bool> ModSelection;
};

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "AlpakitSettings.generated.h"

UENUM()
enum class EAlpakitStartGameType : uint8 {
    STEAM UMETA(DisplayName = "Steam"),
    STEAM_SERVER UMETA(DisplayName = "Steam: Dedicated Server"),
    EPIC_STABLE UMETA(DisplayName = "Epic: Stable"),
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
	
    UPROPERTY(EditAnywhere, config, Category = Config, meta = (ToolTip = "Controls if this target will be built when pressing the 'Alpakit Dev' button (or Alpakit! for one mod) and what action will be taken for this target after all tasks complete."))
    bool bEnabled = true;

    UPROPERTY(EditAnywhere, config, Category = Config, meta = (InlineEditConditionToggle))
    bool bCopyModsToGame = false;
	
    UPROPERTY(EditAnywhere, config, Category = Config, DisplayName = "Copy to Game Path", meta = (EditCondition = bCopyModsToGame, ToolTip = "If enabled, mods will be copied to this installation location after a successful pack.\n\nExample value:\nC:\\EpicGamesGames\\SatisfactoryExperimental"))
    FDirectoryPath SatisfactoryGamePath;

    UPROPERTY(EditAnywhere, config, Category = Config, meta = (InlineEditConditionToggle))
    bool bLaunchGame = false;

    UPROPERTY(EditAnywhere, config, Category = Config, meta = ( EditCondition = bLaunchGame, ToolTip = "If enabled, this approach will be used to launch this target after a successful pack"))
    EAlpakitStartGameType LaunchGameType;

    UPROPERTY(EditAnywhere, config, Category = Config, meta = ( EditCondition = "LaunchGameType == EAlpakitStartGameType::CUSTOM", EditConditionHides, ToolTip = "When 'Custom' is selected, the Unreal Automation tool will execute this after a successful pack.\nCheck the 'Testing' page on the modding docs for example scripts to call with this feature.\n\nExample value:\npowershell"))
    FString CustomLaunchPath;

    UPROPERTY(EditAnywhere, config, Category = Config, meta = ( EditCondition = "LaunchGameType == EAlpakitStartGameType::CUSTOM", EditConditionHides, ToolTip = "When 'Custom' is selected, these arguments will be used when executing the above after a successful pack.\nCheck the 'Testing' page on the modding docs for example scripts to call with this feature.\n\nExample value:\nC:\\Git\\SatisfactoryModLoader\\Automation\\SFLaunch.ps1 -branch EA -loadLatestSave"))
    FString CustomLaunchArgs;
};

ALPAKIT_API const TCHAR* LexToString(EAlpakitStartGameType StartGameType);

UCLASS(config=Game)
class ALPAKIT_API UAlpakitSettings : public UObject {
    GENERATED_BODY()
public:
    /** Retrieves global instance of alpakit settings */
    static UAlpakitSettings* Get();

    /** Saves alpakit settings to configuration file */
    void SaveSettings();
	
	// Hide this field for now, as the game is only built for Shipping
	/*
	// Name of the build configuration in which the mod should be built
	UPROPERTY(EditAnywhere, config, Category = "Dev Packaging Settings", meta = ( GetOptions = GetAllowedBuildConfigurations ))
	FString BuildConfiguration;
	*/

    UPROPERTY(EditAnywhere, config, Category = "Dev Packaging Settings", DisplayName = "Windows", meta = (ToolTip = "Development-time packaging settings for the Windows target"))
    FAlpakitTargetSettings WindowsGameTargetSettings;

    UPROPERTY(EditAnywhere, config, Category = "Dev Packaging Settings", DisplayName="Windows Server", meta = (ToolTip = "Development-time packaging settings for the Windows Server target"))
    FAlpakitTargetSettings WindowsServerTargetSettings;

    UPROPERTY(EditAnywhere, config, Category = "Dev Packaging Settings", DisplayName="Linux Server", meta = (ToolTip = "Development-time packaging settings for the Linux Server target"))
    FAlpakitTargetSettings LinuxServerTargetSettings;
    
    UPROPERTY(BlueprintReadOnly, config, Category = Config)
    TMap<FString, bool> ModSelection;

	UFUNCTION()
	TArray<FString> GetAllowedBuildConfigurations() const;

	EBuildConfiguration GetBuildConfiguration() const;

    const TMap<FString, FAlpakitTargetSettings> GetPlatformTargetSettings() const;
};

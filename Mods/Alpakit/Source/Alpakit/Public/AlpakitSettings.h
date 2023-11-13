#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "AlpakitSettings.generated.h"

UENUM()
enum class EAlpakitStartGameType : uint8 {
    NONE UMETA(DisplayName = "Do not launch"),
    STEAM UMETA(DisplayName = "Steam"),
    EPIC_EARLY_ACCESS UMETA(DisplayName = "Epic: Early Access"),
    EPIC_EXPERIMENTAL UMETA(DisplayName = "Epic: Experimental")
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

	// Hide these fields for now, as only Windows Shipping is allowed
	/*
	// Name of the build configuration in which the mod should be built
	UPROPERTY(EditAnywhere, config, Category = Config, meta = ( GetOptions = GetAllowedBuildConfigurations ))
	FString BuildConfiguration;

	// The configurations to cook the mods in (Windows, WindowsServer, and so on)
	UPROPERTY(EditAnywhere, config, Category = Config)
	TArray<FString> CookPlatforms;
	*/

    UPROPERTY(EditAnywhere, config, Category = Config)
    FDirectoryPath SatisfactoryGamePath;

    UPROPERTY(EditAnywhere, config, Category = Config)
    EAlpakitStartGameType LaunchGameAfterPacking;

    UPROPERTY(EditAnywhere, config, Category = Config)
    bool bCopyModsToGame = false;

    UPROPERTY(BlueprintReadOnly, config, Category = Config)
    TMap<FString, bool> ModSelection;

	UFUNCTION()
	TArray<FString> GetAllowedBuildConfigurations() const;

	EBuildConfiguration GetBuildConfiguration() const;
};

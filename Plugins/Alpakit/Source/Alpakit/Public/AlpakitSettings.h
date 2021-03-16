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

UCLASS(config=Game)
class ALPAKIT_API UAlpakitSettings : public UObject {
	GENERATED_BODY()
public:
	/** Retrieves global instance of alpakit settings */
	static UAlpakitSettings* Get();

	/** Saves alpakit settings to configuration file */
	void SaveSettings();

	UPROPERTY(EditAnywhere, config, Category = Config)
	FDirectoryPath SatisfactoryGamePath;

	UPROPERTY(EditAnywhere, config, Category = Config)
	EAlpakitStartGameType LaunchGameAfterPacking;

	UPROPERTY(EditAnywhere, config, Category = Config)
	bool bCopyModsToGame = false;
};
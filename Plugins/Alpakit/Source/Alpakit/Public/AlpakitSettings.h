#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "AlpakitSettings.generated.h"

USTRUCT()
struct FAlpakitModDependency {
	GENERATED_BODY()
	
	/** mod_reference of your dependency */
    UPROPERTY(EditAnywhere, config)
    FString Mod;

    /** A version constraint (ex. ^2.1.0) */
	UPROPERTY(EditAnywhere, config)
    FString Constraint;
};

USTRUCT()
struct FAlpakitModResources {
	GENERATED_BODY()

	/** Path to mod icon inside zip file, e.g icon.png */
	UPROPERTY(EditAnywhere, Config)
	FString ModIconPath;
};

USTRUCT()
struct FAlpakitModRemoteVersion {
	GENERATED_BODY()
	FAlpakitModRemoteVersion();

	UPROPERTY(EditAnywhere, Config, Category = "Remote Version")
    /** Check if this mod is client-only/server-only mod (does not need to be installed on remote clients joining in multiplayer) */
    bool bModIsNotRequiredOnRemote;

	/** Accepted range of remote versions, format is the same as in dependencies */
	UPROPERTY(EditAnywhere, Config, Category = "Remote Version")
    FString AcceptedRemoteVersions;
};

USTRUCT()
struct FAlpakitMod {
	GENERATED_BODY()
	FAlpakitMod();
	
	/** Should this mod be paked? */
	UPROPERTY(EditAnywhere, Config)
	bool Enabled;

	/** mod_reference in data.json, your mod folder name */
	UPROPERTY(EditAnywhere, Config)
	FString Name;

	/** The mod name that players see */
	UPROPERTY(EditAnywhere, Config)
	FString DisplayName;

	/** Description of the mod shown in mod list */
	UPROPERTY(EditAnywhere, Config)
	FString Description;

	/** Your mod version, format: X.Y.Z */
	UPROPERTY(EditAnywhere, Config)
	FString Version;

	/** List of authors to show in the mod list */
	UPROPERTY(EditAnywhere, Config)
	TArray<FString> Authors;

	/** Mods that are required for running your mod */
	UPROPERTY(EditAnywhere, Config)
	TArray<FAlpakitModDependency> Dependencies;
	
	/** Mods that that your mod can integrate with, but are not required */
	UPROPERTY(EditAnywhere, Config)
    TArray<FAlpakitModDependency> OptionalDependencies;
	
	/** Can include paths to vanilla assets, or other mod assets that you wish to replace with your version. You don't need to add your mod here */
	UPROPERTY(EditAnywhere, Config)
	TArray<FString> OverwritePaths;

	/** Credits for displaying in mod list. Can be left empty. */
	UPROPERTY(EditAnywhere, Config)
	FString Credits;

	/** Information about how mod should act in multiplayer */
	UPROPERTY(EditAnywhere, Config, Category = "Remote Version")
	FAlpakitModRemoteVersion RemoteVersion;

	/** Mod resources such as icon */
	UPROPERTY(EditAnywhere, Config, Category = "Mod Resources")
	FAlpakitModResources ModResources;
};

UENUM()
enum class EStartGameType : uint8 {
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

	/** Tries to find mod entry index by mod reference, or returns INDEX_NONE on failure */
	int32 FindModIndexByModReference(const FString& ModReference);

	UPROPERTY(EditAnywhere, config, Category = Config)
	FDirectoryPath SatisfactoryGamePath;
	
	UPROPERTY(EditAnywhere, config, Category = Mods)
	TArray<FAlpakitMod> Mods;

	UPROPERTY(EditAnywhere, config, Category = Config)
	EStartGameType LaunchGameAfterPacking;

	UPROPERTY(EditAnywhere, config, Category = Config)
	bool CopyModsToGame;
};
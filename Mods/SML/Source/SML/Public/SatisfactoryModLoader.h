#pragma once
#include "SMLConfiguration.h"
#include "Util/SemVersion.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSatisfactoryModLoader, Log, All);

/** Describes a set of known attributes returned by GetExtraAttributes() */
struct SML_API FModLoaderExtraAttributes {
public:
};

class SML_API FSatisfactoryModLoader {
private:
	//Delete all the constructors, all members of this class are static
	FSatisfactoryModLoader() = delete;
	FSatisfactoryModLoader(const FSatisfactoryModLoader&) = delete;
	FSatisfactoryModLoader(FSatisfactoryModLoader&&) = delete;
public:
	/** Returns version of the mod loader */
	static FVersion GetModLoaderVersion();

	/** Returns map of implementation dependent extra attributes describing current mod loader configuration */
	static TMap<FName, FString> GetExtraAttributes();
	
	/** Returns active SML configuration. If not loaded, it will return empty struct */
	FORCEINLINE static FSMLConfiguration GetSMLConfiguration() { return SMLConfigurationPrivate; }
private:
	friend class FSMLModule;
	
	static FSMLConfiguration SMLConfigurationPrivate;

	/** Loads SML configuration from file and optionally saves it back */
	static void LoadSMLConfiguration(bool bAllowSave);

	/** Checks game and bootstrapper version before launching */
	static void CheckGameVersion();

	/** Registers SML subsystems */
	static void RegisterSubsystems();

	static void SetupShippingDebuggerSupport();
	
	/** Does early mod loading initialization like allocating mod handler, discovering mods and loading DLLs */
	static void PreInitializeModLoading();

	/** Finishes mod loading and mounts packages, initializes subsystems, loads mod configurations, etc */
	static void InitializeModLoading();

	/** Runs console commands using the ExecCmds argument (reimplementation; existing UE ExecCmds doesn't work in shipping) */
	static void ParseExecCmds();
};

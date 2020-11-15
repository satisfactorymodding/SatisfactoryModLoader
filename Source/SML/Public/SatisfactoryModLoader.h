#pragma once
#include "SMLConfiguration.h"
#include "SemVersion.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSatisfactoryModLoader, Log, Log);

/** Describes a set of known attributes returned by GetExtraAttributes() */
struct SML_API FModLoaderExtraAttributes {
public:
	/** Version of bootstrapper we are running on. Can be absent. Represents a valid SemVersion */
	static const FName EA_BootstrapperVersion;
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

	/** Returns currently active mod handler instance, or NULL if mod loading is not initialized */
	FORCEINLINE static class FModHandler* GetModHandler() { return ModHandlerPrivate.Get(); }

	/** Returns active SML configuration. If not loaded, it will return empty struct */
	FORCEINLINE static FSMLConfiguration GetSMLConfiguration() { return SMLConfigurationPrivate; }
private:
	static TSharedPtr<struct BootstrapAccessors> BootstrapperAccessors;
	static TSharedPtr<FModHandler> ModHandlerPrivate;
	static FSMLConfiguration SMLConfigurationPrivate;

	/** Setups bootstrapper accessors used by mod loader */
	static void SetupBootstrapperAccessors(const BootstrapAccessors& Accessors);

	/** Loads SML configuration from file and optionally saves it back */
	static void LoadSMLConfiguration(bool bAllowSave);

	/** Checks game and bootstrapper version before launching */
	static void CheckGameAndBootstrapperVersion();

	/** Registers SML subsystems */
	static void InitializeSubsystems();

	/** Does early mod loading initialization like allocating mod handler, discovering mods and loading DLLs */
	static void PreInitializeModLoading();

	/** Finishes mod loading and mounts packages, initializes subsystems, loads mod configurations, etc */
	static void InitializeModLoading();
};
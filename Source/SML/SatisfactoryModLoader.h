#pragma once
#include <iosfwd>

#include "mod/SemVersion.h"
#include "mod/ModHandler.h"
#include "util/bootstrapper_exports.h"

namespace SML {
	struct FSMLConfiguration {
		/**
		 * Whenever satisfactory crash reporter should be enabled
		 * Can only be active in clean environment without development mode enabled
		 * and target version of CL matching game's actual version
		 */
		bool bEnableCrashReporter;

		/**
		 * Development mode is the mode in which SML will load
		 * mods which are considered unsafe in normal environment
		 * Most notable, it will be able to load raw .dll or .pak mods, which
		 * is handy for development process because you avoid packing stuff every time you want to test it
		 * Note that such mods CANNOT have dependencies or dependents, and are always loaded in the last order
		 * Environment with enabled development mode is invalid for submitting bug reports
		 */
		bool bDevelopmentMode;

		//toggles debug output in the log
		bool bDebugLogOutput;

		/**
		* Opens a console window wich outputs all standard output streams
		* for allowing you to better debug the runtime
		*/
		bool bConsoleWindow;

		/**
		 * Dumps all satisfactory assets into the configs folder as json file
		 * for further import by the editor tools
		 * Takes some time to complete, and usually you want it for 1 launch only
		 */
		bool bDumpGameAssets;

		/**
		 * List of fully qualified command names that won't be usable by players in the game
		 * Full command name is mod_reference:command_name
		 * Note that this setting will only affect players, other command senders will still be able to use it
		 */
		TArray<FString> DisabledCommands;

		/**
		 * Whenever to enable console commands which are considered cheat and disabled by default
		 * See UFGCheatManager for command list
		 */
		bool bEnableCheatConsoleCommands;
	};
};

namespace SML {
	/**
	 * Version of the SML mod loader
	 * Can be also investigated via getting ModInfo of the mod with ModID "SML"
	 * You can depend on the specific SML version in your data.json to be able
	 * to use features which appeared in some later version
	 */
	SML_API extern const FVersion& GetModLoaderVersion();

	/**
	 * Version of the bootstrapper running mod linkage and symbol resolution.
	 * Here just for informational purposes
	 */
	SML_API extern const FVersion& GetBootstrapperVersion();

	/**
	 * Returns output stream used for global SML log
	 * throws std::invalid_argument if called too early in the initialization process
	 */
	SML_API extern std::wofstream& GetLogFile();

	/**
	 * Retrieves mod handler global object
	 * It manages mod loading and can be used to retrieve information
	 * about loading progress and active mods
	 * Use it to enable optional features depending on the mods installed
	 */
	SML_API extern FModHandler& GetModHandler();

	/**
	 * Retrieves active SML configuration object
	 * throws std::invalid_argument if called too early in the initialization process
	 * thread-safe to call as it is immutable
	 */
	SML_API extern const SML::FSMLConfiguration& GetSmlConfig();

	/**
	 * Retrieves path to the mods directory used by the mod handler to locate mods
	 */
	SML_API extern FString GetModDirectory();

	/**
	 * Retrieves path used for storing configuration information related to SML
	 * and active mods. You don't have to use it directly, instead, you can use
	 * ready configuration module which will locate proper config automatically
	 */
	SML_API extern FString GetConfigDirectory();

	/**
	 * Retrieves path to the directory used for caching resources unpacked from mod zips
	 * to avoid polluting actual game folders
	 * It can be invalidated in any time, so it's not safe to use it for persistent storage
	 * for configuration, use getConfigDirectory()
	 */
	SML_API extern FString GetCacheDirectory();

	/** @deprectated Internal usage only */
	BootstrapAccessors& GetBootstrapperAccessors();
};

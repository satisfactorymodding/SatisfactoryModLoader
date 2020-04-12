#pragma once
#include "mod/version.h"
#include "mod/ModHandler.h"

namespace SML {
	struct FSMLConfiguration {
		/**
		 * Whenever SML should register it's chat commands
		 * They are mostly used for obtaining information about the environment,
		 * you can disable them if you don't want to have them
		 * Note that this setting **does not** affect commands registered by other mods
		 */
		bool enableSMLChatCommands;

		/**
		 * Whenever satisfactory crash reporter should be enabled
		 * Can only be active in clean environment without development mode enabled
		 * and target version of CL matching game's actual version
		 */
		bool enableCrashReporter;

		/**
		 * Development mode is the mode in which SML will load
		 * mods which are considered unsafe in normal environment
		 * Most notable, it will be able to load raw .dll or .pak mods, which
		 * is handy for development process because you avoid packing stuff every time you want to test it
		 * Note that such mods CANNOT have dependencies or dependents, and are always loaded in the last order
		 * Environment with enabled development mode is invalid for submitting bug reports
		 */
		bool developmentMode;

		//toggles debug output in the log
		bool debugLogOutput;

		/**
		* Opens a console window wich outputs all standard output streams
		* for allowing you to better debug the runtime
		*/
		bool consoleWindow;

		/**
		 * Dumps all satisfactory assets into the configs folder as json file
		 * for further import by the editor tools
		 * Takes some time to complete, and usually you want it for 1 launch only
		 */
		bool dumpGameAssets;
	};
};

namespace SML {
	/**
	 * Version of the SML mod loader
	 * Can be also investigated via getting ModInfo of the mod with ModID "SML"
	 * You can depend on the specific SML version in your data.json to be able
	 * to use features which appeared in some later version
	 */
	SML_API extern const SML::Versioning::FVersion& getModLoaderVersion();

	/**
	 * Version of the bootstrapper running mod linkage and symbol resolution.
	 * Here just for informational purposes
	 */
	SML_API extern const SML::Versioning::FVersion& getBootstrapperVersion();

	/**
	 * Returns output stream used for global SML log
	 * throws std::invalid_argument if called too early in the initialization process
	 */
	SML_API extern std::wofstream& getLogFile();

	/**
	 * Retrieves mod handler global object
	 * It manages mod loading and can be used to retrieve information
	 * about loading progress and active mods
	 * Use it to enable optional features depending on the mods installed
	 */
	SML_API extern Mod::FModHandler& getModHandler();

	/**
	 * Retrieves active SML configuration object
	 * throws std::invalid_argument if called too early in the initialization process
	 * thread-safe to call as it is immutable
	 */
	SML_API extern const SML::FSMLConfiguration& getSMLConfig();

	/**
	 * Retrieves path to the mods directory used by the mod handler to locate mods
	 */
	SML_API extern FString getModDirectory();

	/**
	 * Retrieves path used for storing configuration information related to SML
	 * and active mods. You don't have to use it directly, instead, you can use
	 * ready configuration module which will locate proper config automatically
	 */
	SML_API extern FString getConfigDirectory();

	/**
	 * Retrieves path to the directory used for caching resources unpacked from mod zips
	 * to avoid polluting actual game folders
	 * It can be invalidated in any time, so it's not safe to use it for persistent storage
	 * for configuration, use getConfigDirectory()
	 */
	SML_API extern FString getCacheDirectory();

	void* ResolveGameSymbol(const char* symbolName);
};

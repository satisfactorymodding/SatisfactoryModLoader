/*
  ____  __  __ _
 / ___||  \/  | |
 \___ \| |\/| | |
  ___) | |  | | |___
 |____/|_|  |_|_____|

 SatisfactoryModLoader is a tool to load dll mods into satisfactory.
 To get started with modding, take a look at BaseMod/ExampleMod.cpp.
 If you have any questions, please contact SuperCoder79 on the modding discord.

 Known issues:
 * Everything crashes 10000% more than it should
 * SML 1.0.0 has been delayed by 2000 years
 * People still can't install this properly (even though there's instructions everywhere ffs)
*/
#include "SatisfactoryModLoader.h"
#include "util/bootstrapper_exports.h"
#include <string>
#include <fstream>
#include <functional>
#include "util/Logging.h"
#include "Misc/App.h"
#include "util/Internal.h"
#include "CoreDelegates.h"
#include "FGGameMode.h"

std::string convertStr(const TCHAR* string) {
	size_t arraySize;
	wcstombs_s(&arraySize, nullptr, 0, string, 0);
	std::vector<char> result;
	result.reserve(arraySize);
	wcstombs_s(nullptr, result.data(), arraySize, string, arraySize);
	return std::string(result.data());
}

std::wstring convertStr(const char* string) {
	size_t arraySize;
	mbstowcs_s(&arraySize, nullptr, 0, string, 0);
	std::vector<TCHAR> result;
	result.reserve(arraySize);
	mbstowcs_s(nullptr, result.data(), arraySize, string, arraySize);
	return std::wstring(result.data());
}

bool checkGameVersion(const long targetVersion) {
	std::string str = convertStr(FApp::GetBuildVersion());
	const long version = std::atoi(str.substr(str.find_last_of('-') + 1).c_str());
	if (targetVersion > version) {
		SML::Logging::fatal("Version check failed: Satisfactory version CL-", version, " is outdated, loader requires at least CL-", targetVersion, ". Things are not going to work.");
		return false;
	}
	if (targetVersion < version) {
		SML::Logging::warning("Detected game version newer than one SML was built for. Things can break or work in unexpected way. Proceed with caution.");
		return true;
	}
	return true;
}

void parseConfig(nlohmann::json& json, SML::FSMLConfiguration& config) {
	try {
		json.at("enableSMLCommands").get_to(config.enableSMLChatCommands);
		json.at("enableCrashReporter").get_to(config.enableCrashReporter);
		json.at("developmentMode").get_to(config.developmentMode);
		json.at("debug").get_to(config.debugLogOutput);
	} catch (std::exception& ex) {
		SML::Logging::error("Failed to parse SML configuration SML.cfg: ", convertStr(ex.what()));
	}
}

namespace SML {
	//version of the SML mod loader, as specified in the SML.h
	static SML::Versioning::FVersion* modLoaderVersion;

	//name of the file which will be used for logging purposes
	static const TCHAR* logFileName = TEXT("SatisfactoryModLoader.log");
	
	//CL of Satisfactory we want to target
	//SML will be unable to load in production mode if it doesn't match actual game version
	const int targetGameVersion = 106027; //106504;
	
	//Pointer to the active mod handler object
	//Initialized early during the process attach
	static Mod::FModHandler* modHandlerPtr;

	//Pointer to the active configuration object
	//Initialized early during process attach
	static FSMLConfiguration* activeConfiguration;

	//Pointer to the SML log file
	static std::wofstream* logOutputStream;

	//Holds pointers to the bootstrapper functions used for loading modules
	static BootstrapAccessors* bootstrapAccessors;

	//path to the root of the game
	static path* rootGamePath;

	void postInitializeSML();

	//called by a bootstrapper off the engine thread during process initialization
	//you should not access engine at that point since for now no engine code was executed
	void bootstrapSML(BootstrapAccessors& accessors) {
		bootstrapAccessors = new BootstrapAccessors(accessors);
		logOutputStream = new std::wofstream();
		logOutputStream->open(path(accessors.gameRootDirectory) / logFileName, std::ios_base::out | std::ios_base::trunc);

		SML::Logging::info(TEXT("Log System Initialized!"));

		modLoaderVersion = new SML::Versioning::FVersion(TEXT("2.0.0"));
		SML::Logging::info(TEXT("Constructing SatisfactoryModLoader v"), modLoaderVersion->string());

		rootGamePath = new path(accessors.gameRootDirectory);
		SML::Logging::info(TEXT("Game root directory: "), rootGamePath->generic_wstring());

		try {
	
			create_directories(getModDirectory());
			create_directories(getConfigDirectory());
			create_directories(getCacheDirectory());

			if (!checkGameVersion(targetGameVersion)) {
				SML::shutdownEngine(TEXT("Game version check failed."));
			}

			nlohmann::json configJson = readModConfig(TEXT("SML"));
			activeConfiguration = new FSMLConfiguration{ true, true, false, false };
			if (!configJson.is_null()) {
				parseConfig(configJson, *activeConfiguration);
			}

			modHandlerPtr = new Mod::FModHandler();
			SML::Logging::info(TEXT("Performing mod discovery"));
			modHandlerPtr->discoverMods();
			SML::Logging::info(TEXT("Resolving mod dependencies"));
			modHandlerPtr->checkDependencies();
		} catch (std::exception& ex) {
			*logOutputStream << convertStr(ex.what()) << std::endl;
			SML::Logging::fatal("Failed to initialize SML: ", convertStr(ex.what()));
			exit(1);
		}
		
		SML::Logging::info(TEXT("Construction phase finished!"));
		
		FCoreDelegates::OnPostEngineInit.AddStatic(postInitializeSML);
	}

	//called after primary engine initialization, it is safe
	//to load modules, mount paks and access most of the engine systems here
	//however note that level could still be not loaded at that moment
	void postInitializeSML() {
		SML::Logging::info(TEXT("Loading Mods..."));
		modHandlerPtr->loadMods(*bootstrapAccessors);
		SML::Logging::info(TEXT("Post Initialization finished!"));
	}

	SML_API path getModDirectory() {
		return *rootGamePath / TEXT("mods");
	}

	SML_API path getConfigDirectory() {
		return *rootGamePath / TEXT("configs");
	}

	SML_API path getCacheDirectory() {
		return *rootGamePath / TEXT(".cache");
	}

	SML_API const SML::FSMLConfiguration& getSMLConfig() {
		return *activeConfiguration;
	}

	SML_API Mod::FModHandler& getModHandler() {
		return *modHandlerPtr;
	}

	SML_API std::wofstream& getLogFile() {
		return *logOutputStream;
	}

	SML_API const SML::Versioning::FVersion& getModLoaderVersion() {
		return *modLoaderVersion;
	}
}

extern "C" SML_API void BootstrapModule(BootstrapAccessors& accessors) {
	return SML::bootstrapSML(accessors);
}

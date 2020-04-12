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
 * SML 2.0.0 has been delayed by 2000 years
 * People still can't install this properly (even though there's instructions everywhere ffs)
*/
#include "SatisfactoryModLoader.h"
#include "util/bootstrapper_exports.h"
#include <fstream>
#include <functional>
#include "util/Logging.h"
#include "Misc/App.h"
#include "util/Internal.h"
#include "CoreDelegates.h"
#include "FGGameMode.h"
#include "mod/ModHandler.h"
#include "util/Console.h"
#include "player/PlayerUtility.h"
#include "command/ChatCommandAPI.h"
#include "command/SMLChatCommands.h"
#include "player/VersionCheck.h"
#include "player/MainMenuMixin.h"
#include "command/SMLDebugCommands.h"
#include "mod/toolkit/FGAssetDumper.h"

bool checkGameVersion(const long targetVersion) {
	const FString& buildVersion = FString(FApp::GetBuildVersion());
	int32 charIndex = -1;
	buildVersion.FindLastChar('-', charIndex);
	const long version = FCString::Atoi(*buildVersion.Mid(charIndex + 1));
	if (targetVersion > version) {
		SML::Logging::fatal(*FString::Printf(TEXT("Version check failed: Satisfactory version CL-%ld is outdated. SML requires at least CL-%ld. Things are not going to work."), version, targetVersion));
		return false;
	}
	if (targetVersion < version) {
		SML::Logging::warning(TEXT("Detected game version newer than one SML was built for. Things can break or work in unexpected way. Proceed with caution."));
		return true;
	}
	return true;
}

bool checkBootstrapperVersion(SML::Versioning::FVersion target, SML::Versioning::FVersion actual) {
	if (actual.compare(target) < 0) {
		SML::Logging::fatal(*FString::Printf(TEXT("Bootstrapper version check failed: Bootstrapper version %s is outdated. SML requires at least %s"), *actual.string(), *target.string()));
		return false;
	}
	return true;
}

void parseConfig(const TSharedRef<FJsonObject>& json, SML::FSMLConfiguration& config) {
	config.enableSMLChatCommands = json->GetBoolField(TEXT("enableSMLCommands"));
	config.enableCrashReporter = json->GetBoolField(TEXT("enableCrashReporter"));
	config.developmentMode = json->GetBoolField(TEXT("developmentMode"));
	config.debugLogOutput = json->GetBoolField(TEXT("debug"));
	config.consoleWindow = json->GetBoolField(TEXT("consoleWindow"));
	config.dumpGameAssets = json->GetBoolField(TEXT("dumpGameAssets"));
}

TSharedRef<FJsonObject> createConfigDefaults() {
	TSharedRef<FJsonObject> ref = MakeShareable(new FJsonObject());
	ref->SetBoolField(TEXT("enableSMLCommands"), true);
	ref->SetBoolField(TEXT("enableCrashReporter"), true);
	ref->SetBoolField(TEXT("developmentMode"), false);
	ref->SetBoolField(TEXT("debug"), false);
	ref->SetBoolField(TEXT("consoleWindow"), false);
	ref->SetBoolField(TEXT("dumpGameAssets"), false);
	return ref;
}

namespace SML {
	extern "C" DLLEXPORT const TCHAR* modLoaderVersionString = TEXT("2.0.0");
	
	//version of the SML mod loader, as specified in the SML.h
	static SML::Versioning::FVersion* modLoaderVersion = new SML::Versioning::FVersion(modLoaderVersionString);

	extern "C" DLLEXPORT const TCHAR* targetBootstrapperVersionString = TEXT("2.0.4");

	//target (minimum) version of the bootstrapper we are capable running on
	static SML::Versioning::FVersion* targetBootstrapperVersion = new SML::Versioning::FVersion(targetBootstrapperVersionString);

	//version of the bootstrapper we are running on
	static SML::Versioning::FVersion* bootstrapperVersion;
	
	//name of the file which will be used for logging purposes
	static const TCHAR* logFileName = TEXT("SatisfactoryModLoader.log");
	
	//CL of Satisfactory we want to target
	//SML will be unable to load in production mode if it doesn't match actual game version
	extern "C" DLLEXPORT const long targetGameVersion = 118201;
	
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

	//FString to the root of the game
	static FString* rootGamePath;

	void* ResolveGameSymbol(const char* symbolName) {
		return bootstrapAccessors->ResolveGameSymbol(symbolName);
	}

	void postInitializeSML();

	//called by a bootstrapper off the engine thread during process initialization
	//you should not access engine at that point since for now no engine code was executed
	void bootstrapSML(BootstrapAccessors& accessors) {
		bootstrapAccessors = new BootstrapAccessors(accessors);
		logOutputStream = new std::wofstream();
		logOutputStream->open(*(FString(accessors.gameRootDirectory) / logFileName), std::ios_base::out | std::ios_base::trunc);

		SML::Logging::info(TEXT("Log System Initialized!"));
		SML::Logging::info(TEXT("Constructing SatisfactoryModLoader v"), *modLoaderVersion->string());
		bootstrapperVersion = new SML::Versioning::FVersion(accessors.version);
		
		rootGamePath = new FString(accessors.gameRootDirectory);
		SML::Logging::info(TEXT("Game root directory: "), **rootGamePath);

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		PlatformFile.CreateDirectoryTree(*getModDirectory());
		PlatformFile.CreateDirectoryTree(*getConfigDirectory());
		PlatformFile.CreateDirectoryTree(*getCacheDirectory());

		if (!checkBootstrapperVersion(*targetBootstrapperVersion, *bootstrapperVersion)) {
			SML::shutdownEngine(TEXT("Incompatible bootstrapper version."));
		}
		if (!checkGameVersion(targetGameVersion)) {
			SML::shutdownEngine(TEXT("Game version check failed."));
		}
		
		const TSharedRef<FJsonObject>& configJson = readModConfig(TEXT("SML"), createConfigDefaults());
		activeConfiguration = new FSMLConfiguration;
		parseConfig(configJson, *activeConfiguration);

		initConsole();

		modHandlerPtr = new Mod::FModHandler();
		SML::Logging::info(TEXT("Performing mod discovery"));
		modHandlerPtr->discoverMods();
		SML::Logging::info(TEXT("Resolving mod dependencies"));
		modHandlerPtr->checkDependencies();

		modHandlerPtr->attachLoadingHooks();
		initializePlayerComponent();
		registerVersionCheckHooks();
		registerMainMenuHooks();
		if (getSMLConfig().enableSMLChatCommands) {
			SML::Logging::info(TEXT("Registering SML chat commands"));
			SML::ChatCommand::registerSMLChatCommands();
			if (getSMLConfig().developmentMode) {
				SML::Logging::info(TEXT("Register SML development commands"));
				SML::ChatCommand::registerSMLDebugCommands();
			}
		}

		modHandlerPtr->loadDllMods(*bootstrapAccessors);

		SML::Logging::info(TEXT("Construction phase finished!"));
		
		FCoreDelegates::OnPostEngineInit.AddStatic(postInitializeSML);
	}

	void flushDebugSymbols() {
		//ensure StackWalker is initialized before flushing symbols
		ANSICHAR tmpBuffer[100];
		FGenericPlatformStackWalk::StackWalkAndDump(tmpBuffer, 100, 0);		
		//flush bootstrapper cached symbols
		SML::Logging::info(TEXT("Flushing debug symbols"));
		bootstrapAccessors->FlushDebugSymbols();
	}
	
	//called after primary engine initialization, it is safe
	//to load modules, mount paks and access most of the engine systems here
	//however note that level could still be not loaded at that moment
	void postInitializeSML() {
		SML::Logging::info(TEXT("Loading Mods..."));
		modHandlerPtr->loadMods(*bootstrapAccessors);
		SML::Logging::info(TEXT("Post Initialization finished!"));
		flushDebugSymbols();
		if (getSMLConfig().dumpGameAssets) {
			SML::Logging::info(TEXT("Game Asset Dump requested in configuration, performing..."));
			SML::dumpSatisfactoryAssets(TEXT("/Game/FactoryGame/"), TEXT("FGBlueprints.json"));
		}
	}

	SML_API FString getModDirectory() {
		return *rootGamePath / TEXT("mods");
	}

	SML_API FString getConfigDirectory() {
		return *rootGamePath / TEXT("configs");
	}

	SML_API FString getCacheDirectory() {
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

	SML_API const SML::Versioning::FVersion& getBootstrapperVersion() {
		return *bootstrapperVersion;
	}
}

extern "C" SML_API void BootstrapModule(BootstrapAccessors& accessors) {
	return SML::bootstrapSML(accessors);
}
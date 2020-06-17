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
#include "util/Logging.h"
#include "Misc/App.h"
#include "util/Internal.h"
#include "CoreDelegates.h"
#include "FGGameMode.h"
#include "WindowsPlatformCrashContext.h"
#include "mod/ModHandler.h"
#include "util/Console.h"
#include "player/PlayerUtility.h"
#include "mod/hooking.h"
#include "network/RemoteVersionChecker.h"
#include "player/MainMenuMixin.h"
#include "mod/toolkit/FGAssetDumper.h"
#include "mod/ModSubsystems.h"
#include "player/BuildMenuTweaks.h"
#include "tooltip/ItemTooltipHandler.h"
#include "util/FuncNames.h"
#include "network/NetworkHandler.h"

bool CheckGameVersion(const long TargetVersion) {
	const FString& BuildVersion = FString(FApp::GetBuildVersion());
	int32 CharIndex = -1;
	BuildVersion.FindLastChar('-', CharIndex);
	const long Version = FCString::Atoi(*BuildVersion.Mid(CharIndex + 1));
	if (TargetVersion > Version) {
		SML::Logging::fatal(*FString::Printf(TEXT("Version check failed: Satisfactory version CL-%ld is outdated. SML requires at least CL-%ld. Things are not going to work."), Version, TargetVersion));
		return false;
	}
	if (TargetVersion < Version) {
		SML::Logging::warning(TEXT("Detected game version newer than one SML was built for. Things can break or work in unexpected way. Proceed with caution."));
		return true;
	}
	return true;
}

bool CheckBootstrapperVersion(const FVersion& Target, const FVersion& Actual) {
	if (Actual.Compare(Target) < 0) {
		SML::Logging::fatal(*FString::Printf(TEXT("Bootstrapper version check failed: Bootstrapper version %s is outdated. SML requires at least %s"), *Actual.String(), *Target.String()));
		return false;
	}
	return true;
}

void ParseConfig(const TSharedRef<FJsonObject>& JSON, SML::FSMLConfiguration& Config) {
	Config.bEnableCrashReporter = JSON->GetBoolField(TEXT("enableCrashReporter"));
	Config.bDevelopmentMode = JSON->GetBoolField(TEXT("developmentMode"));
	Config.bDebugLogOutput = JSON->GetBoolField(TEXT("debug"));
	Config.bConsoleWindow = JSON->GetBoolField(TEXT("consoleWindow"));
	Config.bDumpGameAssets = JSON->GetBoolField(TEXT("dumpGameAssets"));
	Config.DisabledCommands = SML::Map(JSON->GetArrayField(TEXT("disabledCommands")), [](auto It) { return It->AsString(); });
	Config.bEnableCheatConsoleCommands = JSON->GetBoolField(TEXT("enableCheatConsoleCommands"));
}

TSharedRef<FJsonObject> CreateConfigDefaults() {
	TSharedRef<FJsonObject> Ref = MakeShareable(new FJsonObject());
	Ref->SetBoolField(TEXT("enableSMLCommands"), true);
	Ref->SetBoolField(TEXT("enableCrashReporter"), true);
	Ref->SetBoolField(TEXT("developmentMode"), false);
	Ref->SetBoolField(TEXT("debug"), false);
	Ref->SetBoolField(TEXT("consoleWindow"), false);
	Ref->SetBoolField(TEXT("dumpGameAssets"), false);
	Ref->SetBoolField(TEXT("enableCheatConsoleCommands"), false);
	return Ref;
}

namespace SML {
	extern "C" DLLEXPORT const TCHAR* modLoaderVersionString = TEXT("2.1.3");
	
	//version of the SML mod loader, as specified in the SML.h
	static FVersion* modLoaderVersion = new FVersion(modLoaderVersionString);

	extern "C" DLLEXPORT const TCHAR* targetBootstrapperVersionString = TEXT("2.0.10");

	//target (minimum) version of the bootstrapper we are capable running on
	static FVersion* targetBootstrapperVersion = new FVersion(targetBootstrapperVersionString);

	//version of the bootstrapper we are running on
	static FVersion* bootstrapperVersion;
	
	//name of the file which will be used for logging purposes
	static const TCHAR* logFileName = TEXT("SatisfactoryModLoader.log");
	
	//CL of Satisfactory we want to target
	//SML will be unable to load in production mode if it doesn't match actual game version
	extern "C" DLLEXPORT const long targetGameVersion = 124066;
	
	//Pointer to the active mod handler object
	//Initialized early during the process attach
	static FModHandler* modHandlerPtr;

	//Pointer to the active configuration object
	//Initialized early during process attach
	static FSMLConfiguration* activeConfiguration;

	//Pointer to the SML log file
	static std::wofstream* logOutputStream;

	//Holds pointers to the bootstrapper functions used for loading modules
	static BootstrapAccessors* bootstrapAccessors;

	//FString to the root of the game
	static FString* rootGamePath;

	void* ResolveGameSymbol(const char* SymbolName) {
		return bootstrapAccessors->ResolveGameSymbol(SymbolName);
	}

	void PostInitializeSML();

	void AppendSymbolSearchPaths(FString& OutSearchPaths);
	void RegisterCrashContextHooks();
	
	//called by a bootstrapper off the engine thread during process initialization
	//you should not access engine at that point since for now no engine code was executed
	void BootstrapSML(BootstrapAccessors& accessors) {
		bootstrapAccessors = new BootstrapAccessors(accessors);
		logOutputStream = new std::wofstream();
		logOutputStream->open(*(FString(accessors.gameRootDirectory) / logFileName), std::ios_base::out | std::ios_base::trunc);

		SML::Logging::info(TEXT("Log System Initialized!"));
		SML::Logging::info(TEXT("Constructing SatisfactoryModLoader v"), *modLoaderVersion->String());
		bootstrapperVersion = new FVersion(accessors.version);
		
		rootGamePath = new FString(accessors.gameRootDirectory);
		SML::Logging::info(TEXT("Game root directory: "), **rootGamePath);

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		PlatformFile.CreateDirectoryTree(*GetModDirectory());
		PlatformFile.CreateDirectoryTree(*GetConfigDirectory());
		PlatformFile.CreateDirectoryTree(*GetCacheDirectory());

		if (!CheckBootstrapperVersion(*targetBootstrapperVersion, *bootstrapperVersion)) {
			SML::ShutdownEngine(TEXT("Incompatible bootstrapper version."));
		}
		if (!CheckGameVersion(targetGameVersion)) {
			SML::ShutdownEngine(TEXT("Game version check failed."));
		}
		
		const TSharedRef<FJsonObject>& configJson = ReadModConfig(TEXT("SML"), CreateConfigDefaults());
		activeConfiguration = new FSMLConfiguration;
		ParseConfig(configJson, *activeConfiguration);

		InitConsole();

		modHandlerPtr = new FModHandler();
		SML::Logging::info(TEXT("Performing mod discovery"));
		modHandlerPtr->DiscoverMods();
		SML::Logging::info(TEXT("Resolving mod dependencies"));
		modHandlerPtr->CheckDependencies();

		//C++ hooks can be registered very early in the engine initialization
		modHandlerPtr->AttachLoadingHooks();
		InitializePlayerComponent();
		UModNetworkHandler::Register();
		FRemoteVersionChecker::Register();
		FSubsystemInfoHolder::SetupHooks();
		RegisterCrashContextHooks();
		modHandlerPtr->LoadDllMods(*bootstrapAccessors);
		SML::Logging::info(TEXT("Construction phase finished!"));
		
		FCoreDelegates::OnPostEngineInit.AddStatic(PostInitializeSML);
	}

	void BeginCrashReportSection(FGenericCrashContext* Context, const TCHAR* SectionName);
	void EndCrashReportSection(FGenericCrashContext* Context, const TCHAR* SectionName);
	
	//Register hooks for symbol resolution and enhanced crash info
	void RegisterCrashContextHooks() {
		SUBSCRIBE_METHOD(FWindowsPlatformStackWalk::GetDownstreamStorage, [](auto& Call) {
            FString OriginalResult = Call();
            AppendSymbolSearchPaths(OriginalResult);
            Call.Override(OriginalResult);
        });
		SUBSCRIBE_METHOD_AFTER_MANUAL("FGenericCrashContext::AddPortableCallStack", FGenericCrashContextProto::AddPortableCallStack, [](void* ProtoContext) {
            FGenericCrashContext* Context = static_cast<FGenericCrashContext*>(ProtoContext);
            BeginCrashReportSection(Context, TEXT("ModdingProperties"));
            Context->AddCrashProperty(TEXT("BootstrapperVersion"), *GetBootstrapperVersion().String());
            Context->AddCrashProperty(TEXT("ModLoaderVersion"), *GetModLoaderVersion().String());
            BeginCrashReportSection(Context, TEXT("LoadedMods"));
            const FModHandler& ModHandler = GetModHandler();
            for (const FString& ModId : ModHandler.GetLoadedMods()) {
                FString VersionString = ModHandler.GetLoadedMod(ModId).ModInfo.Version.String();
                BeginCrashReportSection(Context, TEXT("Mod"));
                Context->AddCrashProperty(TEXT("ModReference"), *ModId);
                Context->AddCrashProperty(TEXT("Version"), *VersionString);
                EndCrashReportSection(Context, TEXT("Mod"));
            }
            EndCrashReportSection(Context, TEXT("LoadedMods"));
            EndCrashReportSection(Context, TEXT("ModdingProperties"));
        });
	}
	
	//Wrapper for bootstrapper functions allocating memory with prototype void*(*)(unsigned long long)
	void* BootstrapperFMemoryMallocWrapper(uint64 Size) {
		return FMemory::Malloc(Size);
	}
	
	void AppendSymbolSearchPaths(FString& OutSearchPaths) {
		wchar_t* SymbolFileRoots = bootstrapAccessors->GetSymbolFileRoots(&BootstrapperFMemoryMallocWrapper);
		SML::Logging::info(TEXT("Appending SML symbol search paths: "), SymbolFileRoots);
		OutSearchPaths.AppendChar(';');
		OutSearchPaths.Append(SymbolFileRoots);
		FMemory::Free(SymbolFileRoots);
	}

	void FlushDebugSymbols() {
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
	void PostInitializeSML() {
		SML::Logging::info(TEXT("Loading Mods..."));
		modHandlerPtr->LoadMods(*bootstrapAccessors);
		SML::Logging::info(TEXT("Post Initialization finished!"));
		FlushDebugSymbols();

		//Blueprint hooks are registered here, after engine initialization
		GRegisterBuildMenuHooks();
		GRegisterMainMenuHooks();
		UItemTooltipHandler::RegisterHooking();
		UModNetworkHandler::Register();
		
		
		if (GetSmlConfig().bDumpGameAssets) {
			SML::Logging::info(TEXT("Game Asset Dump requested in configuration, performing..."));
			SML::dumpSatisfactoryAssets(TEXT("/Game/FactoryGame/"), TEXT("FGBlueprints.json"));
		}
	}

	SML_API FString GetModDirectory() {
		return *rootGamePath / TEXT("mods");
	}

	SML_API FString GetConfigDirectory() {
		return *rootGamePath / TEXT("configs");
	}

	SML_API FString GetCacheDirectory() {
		return *rootGamePath / TEXT(".cache");
	}

	BootstrapAccessors& GetBootstrapperAccessors() {
		return *bootstrapAccessors;
	}

	SML_API const SML::FSMLConfiguration& GetSmlConfig() {
		return *activeConfiguration;
	}

	SML_API FModHandler& GetModHandler() {
		return *modHandlerPtr;
	}

	SML_API std::wofstream& GetLogFile() {
		return *logOutputStream;
	}

	SML_API const FVersion& GetModLoaderVersion() {
		return *modLoaderVersion;
	}

	SML_API const FVersion& GetBootstrapperVersion() {
		return *bootstrapperVersion;
	}

	void BeginCrashReportSection(FGenericCrashContext* Context, const TCHAR* SectionName) {
		FString& CommonBuffer = Context->GetBuffer();
		CommonBuffer += TEXT( "<" );
		CommonBuffer += SectionName;
		CommonBuffer += TEXT( ">" );
		CommonBuffer += LINE_TERMINATOR;
	}

	void EndCrashReportSection(FGenericCrashContext* Context, const TCHAR* SectionName) {
		FString& CommonBuffer = Context->GetBuffer();
		CommonBuffer += TEXT( "</" );
		CommonBuffer += SectionName;
		CommonBuffer += TEXT( ">" );
		CommonBuffer += LINE_TERMINATOR;
	}
}

extern "C" SML_API void BootstrapModule(BootstrapAccessors& accessors) {
	return SML::BootstrapSML(accessors);
}
#include "CrashReporting/SMLCrashReporter.h"

#include "SatisfactoryModLoader.h"
#include "SMLConfiguration.h"

void FSmlCrashReporter::ApplyCrashReporterPatch() {
	FSMLConfiguration Config = FSatisfactoryModLoader::GetSMLConfiguration();
	if (Config.bDisableModdingCrashReporter) return;

	FCoreDelegates::OnShutdownAfterError.AddStatic([]() {
		static bool bAlreadyLaunched = false;
		if (bAlreadyLaunched) return;
		bAlreadyLaunched = true;
		
		UE_LOG(LogSatisfactoryModLoader, Warning, TEXT("Launch Satisfactory Modding Crash Reporter"));
		
		FString Path = FPlatformMisc::RootDir();
		FString ModsFolderPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectModsDir());
		FString CrashReporterPath = FPaths::Combine(ModsFolderPath, TEXT("SML/Resources/ModdingCrashReporter.exe"));
		FString SMLConfigPath = FPaths::Combine(ModsFolderPath, TEXT("../Configs/SML.cfg"));
		
		FPlatformProcess::CreateProc(*CrashReporterPath, *("\"" + ModsFolderPath + "\" \"" + SMLConfigPath + "\""), true, false, false, NULL, 0, NULL, NULL);
	});
}

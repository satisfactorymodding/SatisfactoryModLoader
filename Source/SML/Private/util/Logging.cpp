#include "Util/Logging.h"
#include "OutputDeviceConsole.h"
#include "OutputDeviceFile.h"
#include "Paths.h"
#include "SatisfactoryModLoader.h"
#include "Engine/Engine.h"
#include "Private/Misc/VarargsHelper.h"

bool FSMLLoggingInternal::IsEngineInitialized() {
    return GEngine && GEngine->IsInitialized();
}

void FSMLLoggingInternal::Logf(const FLogCategoryBase& LogCategory, ELogVerbosity::Type Verbosity, const TCHAR* Fmt, ...) {
    GROWABLE_LOGF(FileOutputDevice->Log(LogCategory.GetCategoryName(), Verbosity, Buffer));
}

void FSMLLoggingInternal::AssertFailed(const ANSICHAR* Filename, int32 LineNumber, const TCHAR* Fmt, ...) {
    GROWABLE_LOGF(FPlatformMisc::MessageBoxExt(EAppMsgType::Ok, Buffer, TEXT("~~SML Has Crashed~~")));
    FPlatformMisc::RequestExit(true);
}

void FSMLLoggingInternal::InitializeLogging() {
    const FString LoggingFileLocation = FPaths::RootDir() + TEXT("SatisfactoryModLoader.log");
    FileOutputDevice = MakeShareable(new FOutputDeviceFile(*LoggingFileLocation));
}

void FSMLLoggingInternal::HandlePostEngineInit() {
    //Show console window if it is requested by configuration
    //Interesting fact: console window can be also opened by using SHOWLOG console command,
    //but unfortunately it is not included in shipping
    if (FSatisfactoryModLoader::GetSMLConfiguration().bConsoleWindow) {
        if (GLogConsole) {
            GLogConsole->Show(true);
        }
    }
}

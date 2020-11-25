#include "Util/Logging.h"
#include "OutputDeviceConsole.h"
#include "OutputDeviceFile.h"
#include "Paths.h"
#include "Engine/Engine.h"
#include "Private/Misc/VarargsHelper.h"

TSharedPtr<FOutputDevice> FSMLLoggingInternal::FileOutputDevice = NULL;

void FSMLLoggingInternal::Logf(const FLogCategoryBase& LogCategory, ELogVerbosity::Type Verbosity, const TCHAR* Fmt, ...) {
    GROWABLE_LOGF(FileOutputDevice->Log(LogCategory.GetCategoryName(), Verbosity, Buffer));
}

void FSMLLoggingInternal::InitializeLogging() {
    const FString LoggingFileLocation = FPaths::RootDir() + TEXT("SatisfactoryModLoader.log");
    FileOutputDevice = MakeShareable(new FOutputDeviceFile(*LoggingFileLocation, true));
}
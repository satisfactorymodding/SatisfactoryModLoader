#include "BlueprintLoggingLibrary.h"
#include "Package.h"

DEFINE_LOG_CATEGORY(LogBlueprintLogging);

void UBlueprintLoggingLibrary::LogImpl(ELogVerbosity::Type Verbosity, UPackage* SourcePackage, const FString& Message) {
   SML_LOG_RUNTIME(LogBlueprintLogging, Verbosity, TEXT("[%s]: %s"), *SourcePackage->GetPathName(), *Message);
}

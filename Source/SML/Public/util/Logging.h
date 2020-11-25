#pragma once
#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSML, Verbose, Verbose);

#define SML_LOG(Category, Verbosity, Message, ...) \
	SML_LOG_RUNTIME(Category, ELogVerbosity::Verbosity, Message, ##__VA_ARGS__);

//Same as SML_LOG, but can accept Verbosity as variable name
#define SML_LOG_RUNTIME(Category, Verbosity, Message, ...) \
	if (!Category.IsSuppressed(Verbosity) || Verbosity == ELogVerbosity::Fatal) { \
		FSMLLoggingInternal::Logf(Category, Verbosity, Message, ##__VA_ARGS__); \
		FMsg::Logf(UE_LOG_SOURCE_FILE(__FILE__), __LINE__, Category.GetCategoryName(), Verbosity, Message, ##__VA_ARGS__); \
	}

class SML_API FSMLLoggingInternal {
public:
	static void Logf(const FLogCategoryBase& LogCategory, ELogVerbosity::Type Verbosity, const TCHAR* Fmt, ...);
private:
	friend class FSatisfactoryModLoader;
	static TSharedPtr<FOutputDevice> FileOutputDevice;
	
	/** Initializes logging system */
	static void InitializeLogging();
};
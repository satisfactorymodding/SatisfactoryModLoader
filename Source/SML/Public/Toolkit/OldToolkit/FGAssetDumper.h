#pragma once
#include "Logging/LogMacros.h"
#include "Containers/UnrealString.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAssetDumper, Log, Log);

class SML_API FGameAssetDumper {
private:
	friend class FSatisfactoryModLoader;
	
	/** Registers Unreal console commands */
	static void RegisterConsoleCommands();
};

#include "Util/DebuggerHelper.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
THIRD_PARTY_INCLUDES_START
	#include <debugapi.h>
THIRD_PARTY_INCLUDES_END
#include "Windows/HideWindowsPlatformTypes.h"
#endif

bool FDebuggerHelper::IsDebuggerPresent() {
#if PLATFORM_WINDOWS
	return ::IsDebuggerPresent();
#else
	return FPlatformMisc::IsDebuggerPresent();
#endif
}

void FDebuggerHelper::DebugBreak() {
#if PLATFORM_WINDOWS
	return ::DebugBreak();
#else
	UE_DEBUG_BREAK();
#endif
}

bool FDebuggerHelper::IsDebuggerHelperSupported() {
#if PLATFORM_WINDOWS
	return true;
#else
	return false;
#endif
}

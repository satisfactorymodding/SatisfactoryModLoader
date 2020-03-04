#pragma once
#include "util/Logging.h"
#include "PlatformStackWalk.h"

namespace SML {
	inline void shutdownEngine(const std::wstring& reason) {
		FPlatformStackWalk::InitStackWalking();
		ANSICHAR StackTrace[4096];
		FPlatformStackWalk::StackWalkAndDump(StackTrace, ARRAY_COUNT(StackTrace), 0);
		SML::Logging::fatal(TEXT("Stack Back Trace: "));
		SML::Logging::fatal(StackTrace);
		SML::Logging::fatal(TEXT("@@@@ SML HAS CRASHED: "), reason.c_str(), TEXT(" @@@@"));
		exit(1);
	}
}

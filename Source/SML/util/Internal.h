#pragma once
#include "util/Logging.h"
#include "PlatformStackWalk.h"

namespace SML {
	inline void shutdownEngine(const FString& reason) {
		FPlatformStackWalk::InitStackWalking();
		ANSICHAR StackTrace[4096];
		FPlatformStackWalk::StackWalkAndDump(StackTrace, ARRAY_COUNT(StackTrace), 0);
		SML::Logging::error(TEXT("Stack Back Trace: "));
		SML::Logging::error(StackTrace);
		SML::Logging::fatal(*FString::Printf(TEXT("@@@@ SML HAS CRASHED: %s @@@@"), *reason));
		exit(1);
	}
}

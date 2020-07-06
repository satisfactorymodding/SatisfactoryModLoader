#pragma once
#include "util/Logging.h"

namespace SML {
	inline void ShutdownEngine(const FString& reason) {
		SML::Logging::fatal(*FString::Printf(TEXT("@@@@ SML HAS CRASHED: %s @@@@"), *reason));
	}
}

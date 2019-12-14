#pragma once
#include "util/Logging.h"
#include "Text.h"

namespace SML {
	inline void shutdownEngine(const std::wstring& reason) {
		SML::Logging::fatal(TEXT("@@@@ SML HAS CRASHED: "), reason.c_str(), TEXT(" @@@@"));
		exit(1);
	}
}

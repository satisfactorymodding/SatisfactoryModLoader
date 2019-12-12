#pragma once
#include "util/Logging.h"
#include "CoreDelegates.h"
#include "Text.h"

namespace SML {
	inline void shutdownEngine(const std::wstring& reason) {
		SML::Logging::info(TEXT("Shutting down the engine: "), reason);
		const FText title = FText::AsCultureInvariant(TEXT("SML has crashed!"));
		const FText message = FText::AsCultureInvariant(reason.c_str());
		int result = FCoreDelegates::ModalErrorMessage.Execute(EAppMsgType::Ok, title, message);
		exit(1);
	}
}

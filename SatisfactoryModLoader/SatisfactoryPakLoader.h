#pragma once

#include "../SatisfactorySDK/SDK.hpp"

#include <game/Global.h>

namespace SPL {

	static std::vector<SML::Objects::UObject*> mods; // Contains all mod actors
	static std::wstring modNames; // Contains all mod names (seperated by a comma)
	/** Initializes SPL */
	void Init();

	void CallPreInit();
	void CallPostInit();
}

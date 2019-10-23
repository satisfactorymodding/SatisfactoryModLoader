/*
  ____  ____  _
 / ___||  _ \| |
 \___ \| |_) | |
  ___) |  __/| |___
 |____/|_|   |_____|

  SatisfactoryPakLoader is a tool to initialize pak mods at runtime.
  For more information, check out https://github.com/PXA-Renegade/Satisfactory-Pak-Modding

*/

#pragma once

#include <game/Global.h>
#include <util/Objects/TArray.h>
#include <util/Objects/UFunction.h>

namespace SML {
	namespace SPL {
		namespace {
			std::vector<SML::Objects::UObject*> mods; // Contains all mod actors
			std::wstring modNames; // Contains all mod names (seperated by a comma)
			Objects::TArray<Objects::FString> modNamesArray;
		}

		/** Invokes given init func */
		void invokeInitFunc(Objects::UObject* mod, Objects::UFunction* func);

		/** Initializes SPL */
		void Init();
	}
}
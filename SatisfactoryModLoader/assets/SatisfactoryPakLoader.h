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
namespace SML {
	namespace Paks {
		namespace {
			std::vector<SML::Objects::UObject*> mods; // Contains all mod actors
		}

		/** Initializes SPL */
		void initPakLoader();
	}
}
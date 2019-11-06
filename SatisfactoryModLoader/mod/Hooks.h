#pragma once
#include <Windows.h>
#include <Lib.h>
#include <util/Objects/FString.h>
#include <HookLoader.h>
#include <HookLoaderInternal.h>
#include "ModFunctions.h"
#include <assets/AssetFunctions.h>
#include <game/Global.h>

namespace SML {
	namespace Mod {
		class Hooks {
		public:
			static void hookFunctions();

			static void engineInit(Functions::ModReturns* ret, Objects::FEngineLoop* fEngine);

			static void playerSentMessage(Functions::ModReturns* ret, Objects::AFGPlayerController* player, Objects::FString* message);

			static bool smlCommands(Functions::CommandData data);
		};
	}
}
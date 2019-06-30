#pragma once
#include <Windows.h>
#include <Lib.h>
#include <util/FString.h>
#include <HookLoader.h>
#include <HookLoaderInternal.h>
#include "ModFunctions.h"
#include <assets/AssetFunctions.h>

namespace SML {
	namespace Mod {
		class Hooks {
		public:
			static PVOID chatFunc;
			static PVOID worldFunc;
			static PVOID playerAddedFunc;
			static PVOID playerControllerAddedFunc;
			static PVOID engineInitFunc;
			static PVOID levelDestroyFunc;
			static PVOID sigCheckFunc;

			static void hookFunctions();

			static void engineInit(void* fEngine);

			static void getWorld(void* self);

			static void sigCheck(void* self, bool b, void* v);

			static void playerAdded(SDK::AFGGameState* gameState, SDK::AFGCharacterPlayer* player);

			static void playerControllerAdded(SDK::AFGPlayerController* self);

			static void levelDestructor(SDK::ULevel* level);

			static void playerSentMessage(void* player, SDK::FString* message);

			static bool smlCommands(Functions::CommandData data);
		};
	}
}
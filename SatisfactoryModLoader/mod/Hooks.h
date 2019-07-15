#pragma once
#include <Windows.h>
#include <Lib.h>
#include <util/FString.h>
#include <HookLoader.h>
#include <HookLoaderInternal.h>
#include "ModFunctions.h"
#include <assets/AssetFunctions.h>
#include <game/Global.h>

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

			static void engineInit(Functions::ModReturns* ret, Objects::FEngineLoop* fEngine);

			//static void getWorld(void* self);

			//static void playerAdded(SDK::AFGGameState* gameState, SDK::AFGCharacterPlayer* player);

			//static void playerControllerAdded(SDK::AFGPlayerController* self);

			static void levelDestructor(SDK::ULevel* level);

			static void playerSentMessage(Functions::ModReturns* ret, Objects::AFGPlayerController* player, Objects::FString* message);

			
			static bool smlCommands(Functions::CommandData data);
		};
	}
}
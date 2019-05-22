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

			static void hookFunctions();

			static void get_world(void* self);

			static void player_sent_message(void* player, SML::Objects::FString* message);

			static bool smlCommands(Functions::CommandData data);
		};
	}
}
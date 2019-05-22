#include <stdafx.h>

#include <Windows.h>
#include <detours.h>
#include "AssetLoader.h"
#include <Lib.h>

namespace SML {
	namespace Assets {
		SML_API void* CurrentWorld = NULL;
	}
	namespace Mod {
		namespace Functions {
			SML_API SDK::UObject* loadObjectFromPak(SDK::UClass *ObjectClass, const wchar_t *InName) {
				return Assets::AssetLoader::LoadObjectSimple(ObjectClass, InName);
			}

			SML_API void* spawnActor(void* UWorld, void* *UClass, void* *FVector, void* *FRotator, void* *FActorSpawnParameters) {
				PVOID spawnActorFn = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UWorld::SpawnActor");
				auto spawnActorFunc = (SDK::UClass * (WINAPI*)(void*, void*, void*, void*, void*))spawnActorFn;
				return spawnActorFunc(UWorld, UClass, &FVector, &FRotator, &FActorSpawnParameters);
			}

			SML_API void* getWorld() {
				return Assets::CurrentWorld;
			}
		}
	}
}
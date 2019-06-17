#include <stdafx.h>

#include <string>
#include <Windows.h>
#include <detours.h>
#include "AssetLoader.h"
#include <Lib.h>
#include "FObjectSpawnParameters.h"
#include <SatisfactoryModLoader.h>
#include <util/Utility.h>

namespace SML {
	namespace Assets {
		SML_API void* CurrentWorld = NULL;
		SML_API SDK::AFGCharacterPlayer* SinglePlayerPawn = nullptr;
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

			SML_API SDK::AFGCharacterPlayer* getPlayerPawn() {
				return Assets::SinglePlayerPawn;
			}

			SML_API void spawnActorAtPlayer(const wchar_t* name, float x, float y, float z) {
				FActorSpawnParameters params = FActorSpawnParameters();
				void* obj = SML::Assets::AssetLoader::LoadObjectSimple(SDK::UClass::StaticClass(), name);
				auto myPlayer = Functions::getPlayerPawn();
				auto buildingLocation = myPlayer->K2_GetActorLocation();
				auto buildingRotation = myPlayer->K2_GetActorRotation();
				buildingLocation.Z += z;
				buildingLocation.X += x;
				buildingLocation.Y += y;
				PVOID spawnActorFn = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UWorld::SpawnActor");
				auto spawnActor = (SDK::UClass * (WINAPI*)(void*, void*, void*, void*, void*))spawnActorFn;
				spawnActor(Functions::getWorld(), obj, &buildingLocation, &buildingRotation, &params);
			}

			SML_API void spawnActorAtPlayer(const wchar_t* name) {
				spawnActorAtPlayer(name, 0, 0, 0);
			}

			SML_API void spawnActor(const wchar_t* name, float x, float y, float z, float pitch, float roll, float yaw) {
				FActorSpawnParameters params = FActorSpawnParameters();
				void* obj = SML::Assets::AssetLoader::LoadObjectSimple(SDK::UClass::StaticClass(), name);
				SDK::FVector vec = SDK::FVector();
				vec.X = x;
				vec.Y = y;
				vec.Z = z;
				SDK::FRotator rot = SDK::FRotator();
				rot.Pitch = pitch;
				rot.Roll = roll;
				rot.Yaw = yaw;
				PVOID spawnActorFn = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UWorld::SpawnActor");
				auto spawnActor = (SDK::UClass * (WINAPI*)(void*, void*, void*, void*, void*))spawnActorFn;
				spawnActor(Functions::getWorld(), obj, &vec, &rot, &params);
			}

			SML_API void registerAssetForCache(const wchar_t* name) {
				if (modHandler.currentStage == GameStage::SETUP || modHandler.currentStage == GameStage::POST_SETUP) {
					if (modHandler.assetCache.count(name) > 0) {
						Utility::warning("Skipping cache registration of existing asset ", name);
					} else {
						modHandler.assetCache.emplace(name, nullptr);
					}
				} else if (modHandler.currentStage == GameStage::RUN) {
					if (modHandler.assetCache.count(name) > 0) {
						Utility::warning("Skipping cache registration of existing asset ", name);
					} else {
						modHandler.assetCache.emplace(name, nullptr);
						modHandler.assetCache[name] = Assets::AssetLoader::LoadObjectSimple(SDK::UClass::StaticClass(), name);
					}
				}
			}

			SML_API SDK::UObject* getAssetFromCache(const wchar_t* name) {
				if (modHandler.currentStage != GameStage::RUN) {
					std::wstring ws(name);
					std::string msg = "Attempted to get cached asset\n" + std::string(ws.begin(), ws.end()) + "\n before it was cached! Press Ok to exit.";
					MessageBoxA(NULL, msg.c_str(), "SatisfactoryModLoader Fatal Error", MB_ICONERROR);
					abort();
				} else {
					if (modHandler.assetCache.count(name) > 0) {
						return modHandler.assetCache[name];
					}
					else {
						modHandler.assetCache.emplace(name, nullptr);
						modHandler.assetCache[name] = Assets::AssetLoader::LoadObjectSimple(SDK::UClass::StaticClass(), name);
						return modHandler.assetCache[name];
					}
				}
			}
		}
	}
}
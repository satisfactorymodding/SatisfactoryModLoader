#include <stdafx.h>

#include <game/Global.h>
#include <HookLoaderInternal.h>
#include <string>
#include <Windows.h>
#include <detours.h>
#include "AssetLoader.h"
#include <Lib.h>
#include "FObjectSpawnParameters.h"
#include <SatisfactoryModLoader.h>
#include <mod/MathFunctions.h>
#include <util/Utility.h>
#include <util/FString.h>

namespace SML {
	namespace Assets {
		SML_API SDK::UWorld** CurrentWorld = nullptr;
		SML_API SDK::AFGCharacterPlayer* SinglePlayerCharacter = nullptr;
		SML_API SDK::AFGPlayerController* SinglePlayerController = nullptr;
	}
	namespace Mod {
		namespace Functions {
			SML_API SDK::UObject* loadObjectFromPak(SDK::UClass* ObjectClass, const wchar_t *InName) {
				return Assets::AssetLoader::loadObjectSimple(ObjectClass, InName);
			}

			SML_API SDK::UObject* loadObjectFromPak(const wchar_t *InName) {
				return Assets::AssetLoader::loadObjectSimple(SDK::UClass::StaticClass(), InName);
			}

			SML_API SDK::UClass* spawnActor(void* UWorld, void* *UClass, void* *FVector, void* *FRotator, void* *FActorSpawnParameters) {
				PVOID spawnActorFn = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UWorld::SpawnActor");
				auto spawnActorFunc = (SDK::UClass* (WINAPI*)(void*, void*, void*, void*, void*))spawnActorFn;
				return spawnActorFunc(UWorld, UClass, &FVector, &FRotator, &FActorSpawnParameters);
			}

			SML_API SDK::UWorld* getWorld() {
				return SDK::UWorld::GetWorld();
			}

			SML_API SDK::AFGCharacterPlayer* getPlayerCharacter() {
				return reinterpret_cast<SDK::AFGCharacterPlayer*>(SDK::UWorld::GetWorld()->OwningGameInstance->LocalPlayers[0]->PlayerController->Character);
			}

			SML_API SDK::AFGPlayerController* getPlayerController() {
				return reinterpret_cast<SDK::AFGPlayerController*>(SDK::UWorld::GetWorld()->OwningGameInstance->LocalPlayers[0]->PlayerController);
			}

			SML_API SDK::UClass* spawnActorAtPlayer(SDK::UObject* obj, float x, float y, float z) {
				FActorSpawnParameters params = FActorSpawnParameters();
				auto myPlayer = getPlayerCharacter();
				auto buildingLocation = myPlayer->K2_GetActorLocation();
				auto buildingRotation = myPlayer->K2_GetActorRotation();
				buildingLocation.Z += z;
				buildingLocation.X += x;
				buildingLocation.Y += y;
				PVOID spawnActorFn = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UWorld::SpawnActor");
				auto spawnActor = (SDK::UClass* (WINAPI*)(void*, void*, void*, void*, void*))spawnActorFn;
				return spawnActor(getWorld(), obj, &buildingLocation, &buildingRotation, &params);
			}

			SML_API SDK::UClass* spawnActorAtPlayer(SDK::UObject* obj) {
				return spawnActorAtPlayer(obj, 0, 0, 0);
			}

			SML_API SDK::UClass* spawnActor(SDK::UObject* obj, float x, float y, float z, float pitch, float roll, float yaw) {
				FActorSpawnParameters params = FActorSpawnParameters();
				SDK::FVector vec = Functions::makeVector(x, y, z);
				SDK::FRotator rot = Functions::makeRotator(pitch, roll, yaw);
				PVOID spawnActorFn = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UWorld::SpawnActor");
				auto spawnActor = (SDK::UClass* (WINAPI*)(void*, void*, void*, void*, void*))spawnActorFn;
				return spawnActor(getWorld(), obj, &vec, &rot, &params);
			}

			SML_API void addRecipe(const wchar_t* recipeName) {
				SDK::UClass* recipe = static_cast<SDK::UClass*>(loadObjectFromPak(recipeName));
				PVOID addAvailableRecipeFn = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "AFGRecipeManager::AddAvailableRecipe");
				auto addAvailableRecipe = static_cast<SDK::AFGRecipeManager* (WINAPI*)(void*, void*)>(addAvailableRecipeFn);
				SDK::TSubclassOf<SDK::UFGRecipe> recipeClass(recipe);
				addAvailableRecipe(static_cast<SDK::AFGGameState*>(getWorld()->GameState)->mRecipeManager, recipe);
			}

			SML_API void addRecipe(SDK::UClass* recipe) {
				PVOID addAvailableRecipeFn = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "AFGRecipeManager::AddAvailableRecipe");
				auto addAvailableRecipe = static_cast<SDK::AFGRecipeManager* (WINAPI*)(void*, void*)>(addAvailableRecipeFn);
				SDK::TSubclassOf<SDK::UFGRecipe> recipeClass(recipe);
				addAvailableRecipe(static_cast<SDK::AFGGameState*>(getWorld()->GameState)->mRecipeManager, recipe);
			}

			SML_API SDK::FInventoryStack makeItemStack(SDK::UClass* clazz, int amount) {
				SDK::FInventoryStack stack = SDK::FInventoryStack();
				SDK::FInventoryItem item = SDK::FInventoryItem();

				item.ItemClass = clazz;

				stack.Item = item;
				stack.NumItems = amount;

				return stack;
			}

			SML_API void addItemStackToPlayer(SDK::FInventoryStack stack) {
				auto player = getPlayerCharacter();
				player->mInventory->AddStack(stack, true);
			}

			SML_API void addItemStackToPlayer(SDK::UObject* item, const int& amount) {
				SDK::FInventoryStack stack = makeItemStack(static_cast<SDK::UClass*>(item), amount);

				auto player = getPlayerCharacter();
				player->mInventory->AddStack(stack, true);
			}

			SML_API void sendMessageToPlayer(std::string msg) {
				std::wstring wstr = std::wstring(msg.begin(), msg.end());
				const wchar_t* wmsg = wstr.c_str();
				SDK::FString* fstring = &SDK::FString(wmsg);
				PVOID hook = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "AFGPlayerController::EnterChatMessage");
				auto pointer = (void(WINAPI*)(void*, void*))hook;
				pointer(getPlayerController(), fstring);
			}

			SML_API int registerAssetForCache(const wchar_t* name) {
				int id = 0;
				if (modHandler.currentStage == GameStage::SETUP || modHandler.currentStage == GameStage::POST_SETUP) {
					if (modHandler.assetCache.count(name) > 0) {
						Utility::warning("Skipping cache registration of existing asset ", name);
						for (std::pair<int, const wchar_t*> pair : modHandler.assetIdRegistry) {
							if (name == pair.second) {
								id = pair.first;
								break;
							}
						}
					} else {
						id = modHandler.assetCache.size();
						modHandler.assetCache.emplace(name, nullptr);
						modHandler.assetIdRegistry.emplace(id, name);
					}
				} else if (modHandler.currentStage == GameStage::RUN) {
					if (modHandler.assetCache.count(name) > 0) {
						Utility::warning("Skipping cache registration of existing asset ", name);
						for (std::pair<int, const wchar_t*> pair : modHandler.assetIdRegistry) {
							if (name == pair.second) {
								id = pair.first;
								break;
							}
						}
					} else {
						id = modHandler.assetCache.size();
						modHandler.assetCache.emplace(name, nullptr);
						modHandler.assetCache[name] = Assets::AssetLoader::loadObjectSimple(SDK::UClass::StaticClass(), name);
						modHandler.assetIdRegistry.emplace(id, name);
					}
				}
				return id;
			}

			SML_API SDK::UObject* getAssetFromCache(const wchar_t* name) {
				if (modHandler.currentStage != GameStage::RUN) {
					std::wstring ws(name);
					Utility::displayCrash("Attempted to get cached asset\n" + std::string(ws.begin(), ws.end()) + "\n before it was cached!");
					abort();
				} else {
					if (modHandler.assetCache.count(name) > 0) {
						return modHandler.assetCache[name];
					}
					else {
						int id = modHandler.assetCache.size();
						modHandler.assetCache.emplace(name, nullptr);
						modHandler.assetCache[name] = Assets::AssetLoader::loadObjectSimple(SDK::UClass::StaticClass(), name);
						modHandler.assetIdRegistry.emplace(id, name);
						return modHandler.assetCache[name];
					}
				}
			}

			//again, if you hardcode these ids, you are setting yourself up for disaster
			SML_API SDK::UObject* getAssetFromCacheWithID(int id) {
				if (modHandler.assetIdRegistry.count(id) > 0) {
					return modHandler.assetCache[modHandler.assetIdRegistry[id]];
				}
				else {
					Utility::displayCrash("Attempted to get cached asset with id (" + std::to_string(id) + ") that doesn't exist!");
				}
			}

			SML_API const wchar_t* getAssetNameFromID(int id) {
				if (modHandler.assetIdRegistry.count(id) > 0) {
					return modHandler.assetIdRegistry[id];
				}
				else {
					Utility::displayCrash("Attempted to get cached asset name with id (" + std::to_string(id) + ") that doesn't exist!");
				}
			}
		}
	}
}
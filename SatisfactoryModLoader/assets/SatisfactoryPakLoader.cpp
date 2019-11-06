#include "stdafx.h"
#include "SatisfactoryPakLoader.h"

#include <filesystem>
#include <vector>

#include <game/Global.h>
#include <game/Player.h>
#include <util/Utility.h>
#include <util/Objects/UFunction.h>
#include <util/Objects/UClass.h>
#include <mod/ModFunctions.h>
#include <mod/MathFunctions.h>
#include <assets/AssetLoader.h>
#include <assets/AssetFunctions.h>
#include <HookLoaderInternal.h>
#include <SatisfactoryModLoader.h>

#include "../SatisfactorySDK/SDK.hpp"

namespace SML {
	namespace Paks {
		void invokeInitFunc(Objects::UObject* mod, Objects::UFunction* func) {
			if (!func) return;
			func->invoke(mod, nullptr);
		}

		void initPakLoader() {
			using namespace SML::Mod;

			::subscribe<&Objects::AFGGameMode::InitGameState>([](Functions::ModReturns* ret, Objects::AFGGameMode* player) {
				bool firstMenuLoad = true;
				bool menu = false;
				//check if we are in the menu
				SDK::FString* mapname = (SDK::FString*)::call<&Objects::UWorld::GetMapName>((Objects::UWorld*)Functions::getWorld(), (Objects::FString*)&SDK::FString());
				if (mapname->ToString() == "MenuScene_01") {
					menu = true;
				} else {
					bool firstMenuLoad = false;
					menu = false;
					Utility::info("Initializing Paks!");
					mods.clear();
				}

				// Get the execution path (\FactoryGame\Binaries\Win64\FactoryGame.exe)
				char path_c[MAX_PATH];
				GetModuleFileNameA(NULL, path_c, MAX_PATH);

				// :)
				std::string path = std::string(path_c);			 // ..\FactoryGame\Binaries\Win64\.exe
				path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries\Win64
				path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries
				path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame
				path = path + "\\Content\\Paks";                 // ..\FactoryGame\Content\Paks

				std::vector<std::filesystem::directory_entry> paksToLoad;

				for (auto& entry : std::filesystem::directory_iterator(path))
					if (entry.path().extension().string() == ".pak")
						paksToLoad.push_back(entry);

				for (auto& entry : std::filesystem::directory_iterator(path + "\\hiddenpaks"))
					if (entry.path().extension().string() == ".pak")
						paksToLoad.push_back(entry);

				// Iterate all paks in the pak folder
				for (auto& entry : paksToLoad) {
					if (entry.path().extension().string() == ".pak") { // check if extension is .pak
						std::wstring filename = entry.path().filename().wstring(); // Get the pak file name

						if (filename != L"FactoryGame-WindowsNoEditor.pak") { // ignore the satisfactory pak file
							std::wstring modNameW = filename.substr(0, filename.length() - 4); // remove the file extension from the file name

							if (modNameW.substr(modNameW.length() - 2, 2) == L"_p") // check if file name ends with _p
								modNameW = modNameW.substr(0, modNameW.length() - 2); // remove _p extension

							if (menu) {
								// Load the blueprint
								const std::wstring bpPath = L"/Game/FactoryGame/" + modNameW + L"/InitMenu.InitMenu_C";
								SDK::UObject* clazz = Functions::loadObjectFromPak(bpPath.c_str());

								// Convert wstring to string D:
								std::string modName(modNameW.begin(), modNameW.end());

								// Check if InitMenu cannot be found
								if (!clazz) {
									if (debugOutput) {
										Utility::debug("No InitMenu was found for ", modName);
									}
									continue;
								} else {
									Utility::debug("Running InitMenu for ", modName, "");
								}

								// Spawn the actor somewhere
								SDK::FVector position = Functions::makeVector(0, 0, 0);
								SDK::FRotator rotation = Functions::makeRotator(0, 0, 0);

								FActorSpawnParameters spawnParams;

								Objects::UObject* modActor = (Objects::UObject*)::call<&Objects::UWorld::SpawnActor>((Objects::UWorld*)*SDK::UWorld::GWorld, (SDK::UClass*)clazz, &position, &rotation, &spawnParams);
								//Propogate data to initmenu
								if (debugOutput) {
									invokeInitFunc(modActor, modActor->findFunction(L"DebugModeEnabled")); // Call the event
								}
								if (firstMenuLoad) {
									invokeInitFunc(modActor, modActor->findFunction(L"FirstMenuLoad")); // Call the event
								}
								invokeInitFunc(modActor, modActor->findFunction(L"Init")); // Call the event
							} else {
								// Load the blueprint
								const std::wstring bpPath = L"/Game/FactoryGame/" + modNameW + L"/InitMod.InitMod_C";
								SDK::UObject* clazz = Functions::loadObjectFromPak(bpPath.c_str());

								// Convert wstring to string D:
								std::string modName(modNameW.begin(), modNameW.end());

								// Check if InitMod cannot be found
								if (!clazz) {
									Utility::warning("No InitMod was found for ", modName, "");
									if (debugOutput) {
										Utility::warning("Your InitMod actor MUST be in this path: /Content/FactoryGame/", modName, " and called InitMod (no spaces) and it must inherit from actor.");
									}
									continue;
								} else {
									Utility::debug("Running InitMod for ", modName, "");
								}

								// Spawn the actor somewhere
								SDK::FVector position = Functions::makeVector(0, 0, 0);

								SDK::FRotator rotation = Functions::makeRotator(0, 0, 0);

								FActorSpawnParameters spawnParams;

								Objects::UObject* modActor = (Objects::UObject*)::call<&Objects::UWorld::SpawnActor>((Objects::UWorld*)*SDK::UWorld::GWorld, (SDK::UClass*)clazz, &position, &rotation, &spawnParams);
								mods.push_back(modActor); // Add the mod actor to the mods list
							}
						}
					}
				}

				Functions::broadcastEvent("beforePakPreInit");
				// Iterate through all mods and call the preinit event
				for (Objects::UObject* mod : mods) {
					//Propogate data to initmod
					invokeInitFunc(mod, mod->findFunction(L"PreInit")); // Call the event
				};
				Functions::broadcastEvent("afterPakPreInit");
				Functions::broadcastEvent("beforePakInit");
				// Iterate through all mods and call the init event
				for (Objects::UObject* mod : mods) {
					invokeInitFunc(mod, mod->findFunction(L"Init")); // Call the event
				}
				Functions::broadcastEvent("afterPakInit");
			});

			//delay post init to later down the loading sequence
			::subscribe<&Objects::AFGPlayerController::BeginPlay>([](Functions::ModReturns* ret, Objects::AFGPlayerController* player) {
				// Iterate through all mods and call the postinit event
				Functions::broadcastEvent("beforePakPostInit");
				for (Objects::UObject* mod : mods) {
					invokeInitFunc(mod, mod->findFunction(L"PostInit")); // Call the event
					::call<&Objects::AActor::Destroy>((Objects::AActor*)mod, false, true);
				}
				Functions::broadcastEvent("afterPakPostInit");
				Utility::info("Finished initializing paks!");
			});
		}
	};
}
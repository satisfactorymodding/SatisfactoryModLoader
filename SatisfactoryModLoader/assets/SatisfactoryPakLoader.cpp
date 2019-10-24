#include "stdafx.h"
#include "SatisfactoryPakLoader.h"

#include <filesystem>
#include <vector>

#include <game/Global.h>
#include <game/Player.h>
#include <util/Utility.h>
#include <mod/ModFunctions.h>
#include <mod/MathFunctions.h>
#include <assets/AssetLoader.h>
#include <assets/AssetFunctions.h>
#include <HookLoaderInternal.h>
#include <SatisfactoryModLoader.h>

#include "../SatisfactorySDK/SDK.hpp"
namespace SML {
	namespace Paks {
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
					modNames = L""; //clear pakmod list when loading a new map
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
				// Iterate all paks in the pak folder
				for (auto &entry : std::filesystem::directory_iterator(path)) {
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
										Utility::warning("No InitMenu was found for ", modName);
									}
									continue;
								} else {
									if (debugOutput) {
										Utility::warning("Running InitMenu for \"", modName, "\"");
									}
								}

								// Spawn the actor somewhere
								SDK::FVector position = Functions::makeVector(0, 0, 0);
								SDK::FRotator rotation = Functions::makeRotator(0, 0, 0);

								FActorSpawnParameters spawnParams;

								Objects::UObject* modActor = (Objects::UObject*)::call<&Objects::UWorld::SpawnActor>((Objects::UWorld*)*SDK::UWorld::GWorld, (SDK::UClass*)clazz, &position, &rotation, &spawnParams);
								//Propogate data to initmenu
								if (debugOutput) {
									::call<&Objects::UObject::CallFunctionByNameWithArguments>(modActor, L"DebugModeEnabled", &output, (SDK::UObject*)NULL, true); // Call the event
								}
								if (firstMenuLoad) {
									::call<&Objects::UObject::CallFunctionByNameWithArguments>(modActor, L"FirstMenuLoad", &output, (SDK::UObject*)NULL, true);
								}
								::call<&Objects::UObject::CallFunctionByNameWithArguments>(modActor, L"Init", &output, (SDK::UObject*)NULL, true);
							} else {
								// Load the blueprint
								const std::wstring bpPath = L"/Game/FactoryGame/" + modNameW + L"/InitMod.InitMod_C";
								SDK::UObject* clazz = Functions::loadObjectFromPak(bpPath.c_str());

								// Convert wstring to string D:
								std::string modName(modNameW.begin(), modNameW.end());

								// Check if InitMod cannot be found
								if (!clazz) {
									Utility::warning("No InitMod was found for \"", modName, "\"");
									if (debugOutput) {
										Utility::warning("Your InitMod actor MUST be in this path: /Content/FactoryGame/", modName, " and called InitMod (no spaces) and it must inherit from actor.");
									}
									continue;
								} else {
									if (debugOutput) {
										Utility::warning("Running InitMod for \"", modName, "\"");
									}
								}

								// Spawn the actor somewhere
								SDK::FVector position = Functions::makeVector(0, 0, 0);

								SDK::FRotator rotation = Functions::makeRotator(0, 0, 0);

								FActorSpawnParameters spawnParams;

								Objects::UObject* modActor = (Objects::UObject*)::call<&Objects::UWorld::SpawnActor>((Objects::UWorld*)*SDK::UWorld::GWorld, (SDK::UClass*)clazz, &position, &rotation, &spawnParams);
								mods.push_back(modActor); // Add the mod actor to the mods list
								modNames += L"," + modNameW; // Append the mod name to the modNames string
							}
						}
					}
				}

				// Check if any mods got loaded
				if (modNames.length() > 0) {
					modNames = modNames.substr(1); // remove the first letter (99.98% a comma)
					Functions::broadcastEvent("beforePakPreInit");
					// Iterate through all mods and call the preinit event
					for (Objects::UObject* mod : mods) {
						//Propogate data to initmod
						if (debugOutput) {
							::call<&Objects::UObject::CallFunctionByNameWithArguments>(mod, L"DebugModeEnabled", &output, (SDK::UObject*)NULL, true); // Call the event
						}
						::call<&Objects::UObject::CallFunctionByNameWithArguments>(mod, L"PreInit", &output, (SDK::UObject*)NULL, true); // Call the event
					};
					Functions::broadcastEvent("afterPakPreInit");
					Functions::broadcastEvent("beforePakInit");
					// Iterate through all mods and call the init event
					for (Objects::UObject* mod : mods) {
						::call<&Objects::UObject::CallFunctionByNameWithArguments>(mod, (L"Init " + modNames).c_str(), &output, (SDK::UObject*)NULL, true); // Call the event
					}
					Functions::broadcastEvent("afterPakInit");
				}
			});

			//delay post init to later down the loading sequence
			::subscribe<&Objects::AFGPlayerController::BeginPlay>([](Functions::ModReturns* ret, Objects::AFGPlayerController* player) {
				// Iterate through all mods and call the postinit event
				Functions::broadcastEvent("beforePakPostInit");
				for (Objects::UObject* mod : mods) {
					::call<&Objects::UObject::CallFunctionByNameWithArguments>(mod, (L"PostInit " + modNames).c_str(), &output, (SDK::UObject*)NULL, true); // Call the event
					::call<&Objects::AActor::Destroy>((Objects::AActor*)mod, false, true);
				}
				Functions::broadcastEvent("afterPakPostInit");
				Utility::info("Finished initializing paks!");
			});
		}
	};
}
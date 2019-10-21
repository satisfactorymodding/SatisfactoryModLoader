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

#include "../SatisfactorySDK/SDK.hpp"
namespace SML {
	namespace Paks {
		void initPakLoader() {
			using namespace SML::Mod;

			::subscribe<&Objects::AFGGameMode::InitGameState>([](Mod::Functions::ModReturns* ret, Objects::AFGGameMode* player) {
				//check if we are in the menu
				SDK::FString* mapname = (SDK::FString*)::call<&Objects::UWorld::GetMapName>((Objects::UWorld*)Functions::getWorld(), (Objects::FString*)&SDK::FString());
				if (mapname->ToString() == "MenuScene_01") {
					return; //skip loading mods in the menu because it leads to all sorts of weird shit
				}
				else {
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
					Utility::info("test");
					if (entry.path().extension().string() == ".pak") { // check if extension is .pak
						std::wstring filename = entry.path().filename().wstring(); // Get the pak file name

						if (filename != L"FactoryGame-WindowsNoEditor.pak") { // ignore the satisfactory pak file
							std::wstring modNameW = filename.substr(0, filename.length() - 4); // remove the file extension from the file name

							if (modNameW.substr(modNameW.length() - 2, 2) == L"_p") // check if file name ends with _p
								modNameW = modNameW.substr(0, modNameW.length() - 2); // remove _p extension

							// Load the blueprint
							const std::wstring bpPath = L"/Game/FactoryGame/" + modNameW + L"/InitMod.InitMod_C";
							SDK::UObject* clazz = Functions::loadObjectFromPak(bpPath.c_str());

							// Convert wstring to string D:
							std::string modName;

							for (char x : modNameW) {
								modName += x;
							}

							// Check if InitMod cannot be found
							if (!clazz) {
								Utility::warning("Failed to initialize \"", modName, "\"");
								continue;
							}

							// Spawn the actor somewhere
							SDK::FVector position = Mod::Functions::makeVector(0, 0, 0);

							SDK::FRotator rotation = Mod::Functions::makeRotator(0, 0, 0);

							FActorSpawnParameters spawnParams;

							Objects::UObject* modActor = (Objects::UObject*)::call<&Objects::UWorld::SpawnActor>((Objects::UWorld*)*SDK::UWorld::GWorld, (SDK::UClass*)clazz, &position, &rotation, &spawnParams);
							mods.push_back(modActor); // Add the mod actor to the mods list
							modNames += L"," + modNameW; // Append the mod name to the modNames string
						}
					}
				}

				// Check if any mods got loaded
				if (modNames.length() > 0) {
					modNames = modNames.substr(1); // remove the first letter (99.98% a comma)

					// Iterate through all mods and call the preinit event
					for (Objects::UObject* mod : mods) {
						Objects::FOutputDevice IDontEvenKnowWhatThisIs; // lol
						::call<&Objects::UObject::CallFunctionByNameWithArguments>(mod, L"PreInit", &IDontEvenKnowWhatThisIs, (SDK::UObject*)NULL, true); // Call the event
					};

					// Iterate through all mods and call the init event
					for (Objects::UObject* mod : mods) {
						Objects::FOutputDevice IDontEvenKnowWhatThisIs; // lul
						::call<&Objects::UObject::CallFunctionByNameWithArguments>(mod, (L"Init " + modNames).c_str(), &IDontEvenKnowWhatThisIs, (SDK::UObject*)NULL, true); // Call the event
					}
				}
			});

			//delay post init to later down the loading sequence
			::subscribe<&Objects::AFGPlayerController::BeginPlay>([](Mod::Functions::ModReturns* ret, Objects::AFGPlayerController* player) {
				// Iterate through all mods and call the postinit event
				for (Objects::UObject* mod : mods) {
					Objects::FOutputDevice IDontEvenKnowWhatThisIs; // lel
					::call<&Objects::UObject::CallFunctionByNameWithArguments>(mod, (L"PostInit " + modNames).c_str(), &IDontEvenKnowWhatThisIs, (SDK::UObject*)NULL, true); // Call the event
					::call<&Objects::AActor::Destroy>((Objects::AActor*)mod, false, true);
				}

			});
		}
	};
}
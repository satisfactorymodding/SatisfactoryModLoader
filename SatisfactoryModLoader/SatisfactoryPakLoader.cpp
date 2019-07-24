/*
  ____  ____  _
 / ___||  _ \| |
 \___ \| |_) | |
  ___) |  __/| |___
 |____/|_|   |_____|

  SatisfactoryPakLoader is a tool to initialize pak mods at runtime.
  For more information, check out https://github.com/PXA-Renegade/Satisfactory-Pak-Modding

*/

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
#include <HookLoaderInternal.h>

void SPL::Init() {
	using namespace SML;

	::subscribe<&Objects::AFGPlayerController::BeginPlay>([](Mod::Functions::ModReturns* ret, Objects::AFGPlayerController* player) {
		// Get the execution path (\FactoryGame\Binaries\Win64\FactoryGame.exe)
		char path_c[MAX_PATH];
		GetModuleFileNameA(NULL, path_c, MAX_PATH);

		// :)
		std::string path = std::string(path_c);			 // ..\FactoryGame\Binaries\Win64\.exe
		path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries\Win64
		path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries
		path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame
		path = path + "\\Content\\Paks";                 // ..\FactoryGame\Content\Paks

		std::vector<Objects::UObject*> mods; // Contains all mod actors
		std::wstring modNames; // Contains all mod names (seperated by a comma)

		// Iterate all paks in the pak folder
		for (auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.path().extension().string() == ".pak") { // check if extension is .pak
				std::wstring filename = entry.path().filename().wstring(); // Get the pak file name

				if (filename != L"FactoryGame-WindowsNoEditor.pak") { // ignore the satisfactory pak file
					std::wstring modNameW = filename.substr(0, filename.length() - 4); // remove the file extension from the file name

					if (modNameW.substr(modNameW.length() - 2, 2) == L"_p") // check if file name ends with _p
						modNameW = modNameW.substr(0, modNameW.length() - 2); // remove _p extension

					// Load the blueprint
					const std::wstring bpPath = L"/Game/FactoryGame/" + modNameW + L"/InitMod.InitMod_C";
					SDK::UObject* clazz = Assets::AssetLoader::loadObjectSimple(SDK::UClass::StaticClass(), bpPath.c_str());

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
			std::for_each(mods.begin(), mods.end(), [modNames](Objects::UObject* mod) {
				Objects::FOutputDevice IDontEvenKnowWhatThisIs; // lol
				::call<&Objects::UObject::CallFunctionByNameWithArguments>(mod, L"PreInit", &IDontEvenKnowWhatThisIs, (SDK::UObject*)NULL, true); // Call the event
			});

			// Iterate through all mods and call the init event
			std::for_each(mods.begin(), mods.end(), [modNames](Objects::UObject* mod) {
				Objects::FOutputDevice IDontEvenKnowWhatThisIs; // lul
				::call<&Objects::UObject::CallFunctionByNameWithArguments>(mod, (L"Init " + modNames).c_str(), &IDontEvenKnowWhatThisIs, (SDK::UObject*)NULL, true); // Call the event
			});

			// Iterate through all mods and call the postinit event
			std::for_each(mods.begin(), mods.end(), [modNames](Objects::UObject* mod) {
				Objects::FOutputDevice IDontEvenKnowWhatThisIs; // lel
				::call<&Objects::UObject::CallFunctionByNameWithArguments>(mod, (L"PostInit " + modNames).c_str(), &IDontEvenKnowWhatThisIs, (SDK::UObject*)NULL, true); // Call the event
				::call<&Objects::AActor::Destroy>((Objects::AActor*)mod, false, true);
			});
		}
	});
}
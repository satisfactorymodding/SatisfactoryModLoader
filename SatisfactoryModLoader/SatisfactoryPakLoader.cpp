/*
  ____  ____  _
 / ___||  _ \| |
 \___ \| |_) | |
  ___) |  __/| |___
 |____/|_|   |_____|

  SatisfactoryPakLoader is a tool to initialize pak-mods
  Check out https://github.com/PXA-Renegade/Satisfactory-Pak-Modding for more information

*/

#include "stdafx.h"
#include "SatisfactoryPakLoader.h"

#include <filesystem>
#include <vector>

#include "game/Global.h"
#include "game/Player.h"
#include "util/Utility.h"
#include "mod/ModFunctions.h"
#include "assets/AssetLoader.h"
#include "HookLoaderInternal.h"

void SPL::Init() {
	using namespace SML;

	::subscribe<&Objects::AFGPlayerController::BeginPlay>([](Mod::Functions::ModReturns* ret, Objects::AFGPlayerController* player) {
		char path_c[MAX_PATH];
		GetModuleFileNameA(NULL, path_c, MAX_PATH);

		std::string path = std::string(path_c);			 // ..\FactoryGame\Binaries\Win64\.exe
		path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries\Win64
		path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries
		path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame
		path = path + "\\Content\\Paks";                 // ..\FactoryGame\Content\Paks

		std::vector<AMod*> mods;
		std::wstring modNames;

		for (auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.path().extension().string() == ".pak") { // check if extension is .pak
				std::wstring filename = entry.path().filename().wstring();

				if (filename != L"FactoryGame-WindowsNoEditor.pak") { // ignore the satisfactory pak file
					std::wstring modNameW = filename.substr(0, filename.length() - 4); // remove the file extension from the file name

					if (modNameW.substr(modNameW.length() - 2, 2) == L"_p") // check if file name ends with _p
						modNameW = modNameW.substr(0, modNameW.length() - 2); // remove _p extension

					const std::wstring bpPath = L"/Game/FactoryGame/" + modNameW + L"/InitMod.InitMod_C";
					SDK::UObject* clazz = Assets::AssetLoader::loadObjectSimple(SDK::UClass::StaticClass(), bpPath.c_str());

					std::string modName;

					for (char x : modNameW)
						modName += x;

					if (!clazz) {
						Utility::warning("Failed to initialize \"", modName, "\"");
						continue;
					}

					SDK::FVector position;
					position.X = 0;
					position.Y = 0;
					position.Z = 0;

					SDK::FRotator rotation;
					rotation.Pitch = 0;
					rotation.Yaw = 0;
					rotation.Roll = 0;

					FActorSpawnParameters spawnParams;
					
					AMod* mod = (AMod*)::call<&Objects::UWorld::SpawnActor>((Objects::UWorld*)*SDK::UWorld::GWorld, (SDK::UClass*)clazz, &position, &rotation, &spawnParams);

					mods.push_back(mod);
					modNames += L"," + modNameW;
				}
			}
		}

		if (modNames.length() > 0)
			modNames = modNames.substr(1);

		static auto ufunction_preinit = SDK::UObject::FindObject<SDK::UFunction>("Function InitMod.InitMod_C.PreInit");
		static auto ufunction_init = SDK::UObject::FindObject<SDK::UFunction>("Function InitMod.InitMod_C.Init");
		static auto ufunction_postinit = SDK::UObject::FindObject<SDK::UFunction>("Function InitMod.InitMod_C.PostInit");

		InitMod_PreInit_Params	preInitParams;
		InitMod_Init_Params		initParams;
		InitMod_PostInit_Params	postInitParams;

		initParams.Mods = SDK::FString(modNames.c_str());
		postInitParams.Mods = SDK::FString(modNames.c_str());

		std::for_each(mods.begin(), mods.end(), [preInitParams](AMod* mod) {
			CallModFunction(mod, ufunction_preinit, preInitParams);
		});

		std::for_each(mods.begin(), mods.end(), [initParams](AMod* mod) {
			CallModFunction(mod, ufunction_init, initParams);
		});

		std::for_each(mods.begin(), mods.end(), [postInitParams](AMod* mod) {
			CallModFunction(mod, ufunction_preinit, postInitParams);

			::call<&Objects::AActor::Destroy>((Objects::AActor*)mod, false, true);
		});
	});
}

template <typename T>
void SPL::CallModFunction(AMod* mod, SDK::UFunction* fn, T params) {
	if (fn) {
		auto flags = fn->FunctionFlags;

		mod->ProcessEvent(fn, &params);

		fn->FunctionFlags = flags;
	}
}
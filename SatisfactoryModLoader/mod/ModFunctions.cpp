#include <stdafx.h>
#include "ModFunctions.h"
#include <SatisfactoryModLoader.h>
#include <assets/FObjectSpawnParameters.h>
#include <detours.h>
#include <assets/AssetLoader.h>
#include <assets/AssetFunctions.h>
#include <memory>

namespace SML {
	namespace Mod {
		namespace Functions {
			
			//registers a command to the mod handler
			SML_API void registerCommand(std::string name, PVOID func) {
				if (modHandler.currentStage != GameStage::SETUP) {
					SML::Utility::warning("REGISTRY WARNING: command " + name + " was registered outside of setup!");
				}
				Registry r = {
					name,
					func
				};
				modHandler.commandRegistry.push_back(r);
			}

			// registers an API function to the mod handler
			SML_API void registerAPIFunction(std::string name, PVOID func) {
				if (modHandler.currentStage != GameStage::SETUP) {
					SML::Utility::warning("REGISTRY WARNING: API function " + name + " was registered outside of setup!");
				}
				for (Registry reg : modHandler.APIRegistry) {
					if (reg.name == name) {
						std::string msg = "Duplicate API function " + name + " registered!\nPress Ok to exit.";
						MessageBoxA(NULL, msg.c_str(), "SatisfactoryModLoader Fatal Error", MB_ICONERROR);
						abort();
					}
				}
				Registry r = {
					name,
					func
				};
				modHandler.APIRegistry.push_back(r);
			}

			// gets an API function from the mod handler
			SML_API PVOID getAPIFunction(std::string name) {
				bool found = false;
				PVOID func = NULL;
				for (Registry reg : modHandler.APIRegistry) {
					if (reg.name == name) {
						func = reg.func;
						found = true;
					}
				}
				if (!found) {
					std::string msg = "Requested API function " + name + " not found!\nMake sure that the mod that provides this function is installed or added as a dependency to your mod.\nPress Ok to exit.";
					MessageBoxA(NULL, msg.c_str(), "SatisfactoryModLoader Fatal Error", MB_ICONERROR);
					abort();
				}
				return func;
			}

			// checks if a mod is loaded through mod name
			SML_API bool isModLoaded(std::string name) {
				bool found = false;
				for (auto&& mod : modHandler.mods) {
					if (mod->info.name == name) {
						found = true;
						break;
					}
				}
				return found;
			}

			//runs all events registered under 'name'
			SML_API void broadcastEvent(std::string name) {
				if (modHandler.eventRegistry.count(name) == 0) {
					// do nothing if event doesn't exist
				}
				else {
					for (int i = 0; i < modHandler.eventRegistry[name].size(); i++) {
						PVOID event = modHandler.eventRegistry[name][i];
						auto func = (void(WINAPI*)()) event;
						func();
					}
				}
			}

			//registers an event under 'name'
			SML_API void registerEvent(std::string name, PVOID func) {
				if (modHandler.currentStage != GameStage::SETUP) {
					SML::Utility::warning("REGISTRY WARNING: event " + name + " was registered outside of setup!");
				}
				if (modHandler.eventRegistry.count(name) == 0) {
					std::vector<PVOID> v = {
						func
					};
					modHandler.eventRegistry.insert(std::pair<std::string, std::vector<PVOID>>(name, v));
				} else {
					modHandler.eventRegistry[name].push_back(func);
				}
			}
		}
	}
}
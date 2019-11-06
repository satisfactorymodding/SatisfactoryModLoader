#include <stdafx.h>
#include "ModFunctions.h"
#include <SatisfactoryModLoader.h>
#include <assets/FObjectSpawnParameters.h>
#include <Windows.h>
#include <detours.h>
#include <assets/AssetLoader.h>
#include <assets/AssetFunctions.h>
#include <memory>
#include <sstream>
#include <mod/Hooks.h>

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

			//runs a command directly
			SML_API void runCommand(std::string name) {
				std::vector<std::string> arguments;
				std::stringstream ss(name);
				std::string temp;
				if (name.find(' ') == std::string::npos) {
					arguments.push_back(name);
				}
				else {
					while (getline(ss, temp, ' ')) {
						arguments.push_back(temp);
					}
				}
				SML::Mod::Functions::CommandData data = {
					arguments.size(),
					arguments,
					nullptr
				};
				Hooks::smlCommands(data); //run SML's commands
				for (Registry r : modHandler.commandRegistry) {
					if (arguments[0] == "/" + r.name) {
						auto commandFunc = (void(WINAPI*)(SML::Mod::Functions::CommandData))r.func;
						commandFunc(data);
					}
				}
			}

			// registers an API function to the mod handler
			SML_API void registerAPIFunction(std::string name, PVOID func) {
				if (modHandler.currentStage != GameStage::SETUP) {
					SML::Utility::warning("REGISTRY WARNING: API function " + name + " was registered outside of setup!");
				}
				for (Registry reg : modHandler.APIRegistry) {
					if (reg.name == name) {
						Utility::displayCrash("Duplicate API function " + name + " registered!\nPress Ok to exit.");
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
					Utility::displayCrash("Requested API function " + name + " not found!\nMake sure that the mod that provides this function is installed or added as a dependency to your mod.\nPress Ok to exit.");
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

			//checks if a pak exists
			SML_API bool doesPakExist(std::string name) {
				char path_c[MAX_PATH];
				GetModuleFileNameA(NULL, path_c, MAX_PATH);
				std::string path = std::string(path_c);			 // ..\FactoryGame\Binaries\Win64\.exe
				path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries\Win64
				path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries
				path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame
				path = path + "\\Content\\Paks";
				if (name.find(".pak") == std::string::npos) {
					name.append(".pak");
				}
				std::string pakLoc = path.append("\\" + name);
				std::filesystem::path pakPath(pakLoc);
				if (!std::filesystem::exists(pakPath)) {
					return false;
				}
				return true;
			}

			//raises an error if a pak doesn't exist
			SML_API void setDependsOnPak(std::string name) {
				if (!doesPakExist(name)) {
					Utility::displayCrash("You are missing " + name + " from your install!\nMake sure you installed your mods properly!\n");
				}
			}
		}
	}
}
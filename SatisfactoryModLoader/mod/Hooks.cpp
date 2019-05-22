#include <stdafx.h>
#include "Hooks.h"
#include <detours.h>
#include <stdio.h> 
#include <sstream>
#include <functional>
#include <SatisfactoryModLoader.h>
#include <game/Global.h>
#include <util/Utility.h>
#include "ModFunctions.h"

using namespace std::placeholders;

namespace SML {
	namespace Mod {
		PVOID Hooks::chatFunc;
		PVOID Hooks::worldFunc;

		void Hooks::hookFunctions() {
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());

			// find the function by name
			chatFunc = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "AFGPlayerController::EnterChatMessage");
			DetourAttach(&(PVOID&)chatFunc, player_sent_message);
			Utility::info("Hooked Command Registry!");

			worldFunc = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "ULevel::PostLoad");
			DetourAttach(&(PVOID&)worldFunc, get_world);

			//info("Hooked Paks!");

			DetourTransactionCommit();
		}

		void Hooks::get_world(void* self) {
			auto pointer = (void(WINAPI*)(void*))worldFunc;
			pointer(self);

			PVOID getWorldRaw = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "ULevel::GetWorld");
			auto getWorld = (void*(WINAPI*)(void*))getWorldRaw;
			Assets::CurrentWorld = getWorld(self);
			Utility::info(Assets::CurrentWorld);
		}

		// parse commands when the player sends a message
		void Hooks::player_sent_message(void* player, SML::Objects::FString* message) {

			auto pointer = (void(WINAPI*)(void*, void*))chatFunc;

			char* chars = new char[message->length];

			for (size_t i = 0; i < message->length; i++) {
				chars[i] = message->data[i];
			}

			std::string str(chars);
			std::vector<std::string> arguments;
			std::stringstream ss(str);
			std::string temp;
			if (str.find(' ') == std::string::npos) {
				arguments.push_back(str);
			}
			else {
				while (getline(ss, temp, ' ')) {
					arguments.push_back(temp);
				}
			}

			bool found = false;
			SML::Mod::Functions::CommandData data = {
						arguments.size(),
						arguments
			};
			found = smlCommands(data); //run SML's commands
			for (Registry r : modHandler.commandRegistry) {
				if (arguments[0] == "/" + r.name) {
					auto commandFunc = (void(WINAPI*)(SML::Mod::Functions::CommandData))r.func;
					commandFunc(data);
					found = true;
				}
			}
			if (!found) {
				pointer(player, message);
			}

		}

		bool Hooks::smlCommands(Functions::CommandData data) {
			if (data.argv[0] == "/sml") {
				if (data.argc == 1) {
					Utility::info("Please enter a subcommand with /sml: help, modlist, die, commands, apis, events");
				}
				else if (data.argc >= 2) {
					if (data.argv[1] == "help") {
						Utility::info("/sml help     -> Displays this help message");
						Utility::info("/sml modlist  -> Lists all the information about the loaded mods");
						Utility::info("/sml die      -> Performs a hard shutdown");
						Utility::info("/sml commands -> Lists all the commands in the registry");
						Utility::info("/sml apis     -> Lists all the API functions in the registry");
						Utility::info("/sml events   -> Lists all the custom events in the registry");
					} else if (data.argv[1] == "modlist") {
						for (auto&& m : modHandler.mods) {
							Utility::info(m->info.name);
							Utility::info(m->info.version);
							Utility::info(m->info.loaderVersion);
							Utility::info(m->info.description);
							Utility::info(m->info.authors);
							Utility::info("Dependencies: ");
							for (std::string s : m->info.dependencies) {
								Utility::info(s);
							}
							Utility::info("=======================");
						}
					}
					else if (data.argv[1] == "die") {
						Utility::info("Hard shutdown requested!");
						SML::cleanup();
						abort();
					}
					else if (data.argv[1] == "commands") {
						for (Registry r : modHandler.commandRegistry) {
							Utility::info(r.name, " -> ", r.func);
						}

					}
					else if (data.argv[1] == "apis") {
						for (Registry r : modHandler.APIRegistry) {
							Utility::info(r.name, " -> ", r.func);
						}
					}
					else if (data.argv[1] == "events") {
						for (auto r : modHandler.eventRegistry) {
							Utility::info(r.first, ": ", r.second.size(), " function(s):");
							for (PVOID p : r.second) {
								Utility::info(p);
							}
							Utility::info("=======================");
						}
					}
					else if (data.argv[1] == "world") {
						Utility::info(Assets::CurrentWorld);
					}
					else {
						Utility::info("Subcommand not recognized!");
					}
				}
				return true;
			}
			return false;
		}

		//void get_signing_keys(ModReturns* modReturns, void* outKey) {
		//	info("Test");
		//	modReturns->use_original_function = false;
		//}
	}
}
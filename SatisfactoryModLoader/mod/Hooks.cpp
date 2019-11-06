#include <stdafx.h>
#include "Hooks.h"
#include <Windows.h>
#include <detours.h>
#include <stdio.h> 
#include <sstream>
#include <vector>
#include <functional>
#include <SatisfactoryModLoader.h>
#include <game/Global.h>
#include <game/Player.h>
#include <util/Utility.h>
#include <mod/ModFunctions.h>
#include "ModFunctions.h"
#include <assets/AssetLoader.h>
#include <mod/Coremods.h>
#include <filesystem>
#include <assets/BPInterface.h>
#include <assets/SatisfactoryPakLoader.h>

using namespace std::placeholders;

/*
Quick warning before you proceed:
This is probably the messiest part of the entire codebase.
Please disregard any shit code in here as it's all a Work In Progress(TM)
*/

namespace SML {
	namespace Mod {
		void Hooks::hookFunctions() {
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());

			//Major major props to Brabb3l for helping me figure this peice of shit code out

			::subscribe<&Objects::AFGPlayerController::EnterChatMessage>([](Functions::ModReturns* modReturns, Objects::AFGPlayerController* player, Objects::FString* message) {
				Hooks::playerSentMessage(modReturns, player, message);
			});

			::subscribe<&Objects::FEngineLoop::Init>([](Functions::ModReturns* ret, Objects::FEngineLoop* engineLoop) {
				Hooks::engineInit(ret, engineLoop);
			});

			// Initialize the Pakloader
			Paks::initPakLoader();
			Paks::initBPInterface();

			Utility::info("Registered hooks!");

			DetourTransactionCommit();
		}

		void Hooks::engineInit(Functions::ModReturns* ret, Objects::FEngineLoop* engine) {
			//caching of assets
			Functions::broadcastEvent("beforeEngineInit");
			modHandler.currentStage = GameStage::RUN;
			for (std::pair<const wchar_t*, SDK::UObject*> asset : modHandler.assetCache) {
				modHandler.assetCache[asset.first] = Assets::AssetLoader::loadObjectSimple(SDK::UClass::StaticClass(), asset.first);
			}

			//load delayed coremods
			for (std::string libPath : delayedCoremods) {
				LoadLibraryA(libPath.c_str());
			}

			ret->useOriginalFunction = true;
		}

		// parse commands when the player sends a message
		void Hooks::playerSentMessage(Functions::ModReturns* ret, Objects::AFGPlayerController* player, Objects::FString* messageIn) {
			SDK::FString* message = reinterpret_cast<SDK::FString*>(messageIn);

			if (!message->IsValid()) {
				return;
			}

			std::string str = message->ToString();
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
				arguments,
				reinterpret_cast<SDK::AFGPlayerController*>(player)
			};
			found = smlCommands(data); //run SML's commands
			for (Registry r : modHandler.commandRegistry) {
				if (arguments[0] == "/" + r.name) {
					auto commandFunc = (void(WINAPI*)(SML::Mod::Functions::CommandData))r.func;
					commandFunc(data);
					found = true;
				}
			}
			ret->useOriginalFunction = !found;
		}

		bool Hooks::smlCommands(Functions::CommandData data) {
			if (chatCommands) {
				if (data.argv[0] == "/sml") {
					if (data.argc == 1) {
						Utility::info("Please enter a subcommand with /sml: help, modlist, die, commands, apis, events");
					}
					else if (data.argc >= 2) {
						if (data.argv[1] == "help") {
							Utility::info("/sml help     -> Displays this help message");
							Utility::info("/sml modlist  -> Lists all the information about the loaded mods");
							Utility::info("/sml die      -> Performs a hard shutdown");
							Utility::info("/sml obj      -> Displays the memory address of various game objects");
							Utility::info("/sml commands -> Lists all the commands in the registry");
							Utility::info("/sml apis     -> Lists all the API functions in the registry");
							Utility::info("/sml events   -> Lists all the custom events in the registry");
						}
						else if (data.argv[1] == "modlist") {
							if (modHandler.mods.size() > 0) {
								Utility::info("Mod list: ");
								for (auto&& m : modHandler.mods) {
									Utility::info("=======================");
									Utility::info(m->info.name);
									Utility::info(m->info.version);
									Utility::info(m->info.loaderVersion);
									Utility::info(m->info.description);
									Utility::info(m->info.authors);
									if (m->info.dependencies.size() > 0) {
										Utility::info("Dependencies: ");
										for (std::string s : m->info.dependencies) {
											Utility::info(s);
										}
									}
								}
								Utility::info("=======================");
							}
							if (coremodList.size() > 0) {
								Utility::info("Coremod list: ");
								for (std::string cm : coremodList) {
									Utility::info(cm);
								}
							}
							if (delayedCoremods.size() > 0) {
								Utility::info("Delayed Coremod list: ");
								for (std::string cm : delayedCoremods) {
									Utility::info(cm);
								}
							}
						}
						else if (data.argv[1] == "die") {
							Utility::info("Hard shutdown requested!");
							Utility::closeGame();
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
						else if (data.argv[1] == "obj") {
							Utility::info("World:", Functions::getWorld());
							Utility::info("Local Character:", Functions::getPlayerCharacter());
							Utility::info("Local Controller: ", Functions::getPlayerController());
							Utility::info("Game Instance: ", Functions::getGameInstance());
							Utility::info("Game State: ", Functions::getGameState());
							Utility::info("Level: ", Functions::getLevel());
							Utility::info("Net Driver: ", Functions::getNetDriver());
						}
						else {
							Utility::info("Subcommand not recognized!");
						}
					}
					return true;
				}
			}
			else {

			}
			return false;
		}
	}
}
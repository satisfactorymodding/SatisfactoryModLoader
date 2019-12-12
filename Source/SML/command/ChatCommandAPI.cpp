#include "ChatCommandAPI.h"
#include "FGChatManager.h"
#include "util/Utility.h"
#include "player/PlayerUtility.h"
#include <algorithm>

namespace SML {
	namespace ChatCommand {
		class CharacterPlayerAccessor : AFGPlayerController {
			typedef void (AFGPlayerController::*EnterChatMessageType)(const FString& inMessage);
			static EnterChatMessageType EnterChatMessagePtr() { return &AFGPlayerController::EnterChatMessage; }
		};
		
		//holds the mapping of the command name/alias to the command registrar entry
		static std::map<std::wstring, FCommandRegistrarEntry> registeredCommands;
		//holds the list of all registered commands
		static std::vector<FCommandRegistrarEntry> registeredCommandsList;

		//returns the list of all registered commands
		const std::vector<FCommandRegistrarEntry>& getRegisteredCommands() {
			return registeredCommandsList;
		}

		void registerCommand(const FCommandRegistrarEntry& commandEntry) {
			std::wstring fqCommandName = formatStr(commandEntry.modid, TEXT(":"), commandEntry.commandName);
			//register short command name
			registeredCommands.insert({ commandEntry.commandName, commandEntry });
			//register fully qualified command name
			registeredCommands.insert({ fqCommandName, commandEntry });
			//register command entry
			registeredCommandsList.push_back(commandEntry);
		}

		void printCommandNotFound(AFGPlayerController* player) {
			//AFGCharacterPlayer* character = getPlayerCharacter(player->Player);
			//AFGChatManager* chatManager = AFGChatManager::Get(player->GetWorld());
			//TODO need to work with replication to send message to only that player
		}

		bool runChatCommand(std::wstring commandLine, AFGPlayerController* player) {
			if (commandLine.empty()) {
				printCommandNotFound(player);
				return false;
			}
			if (commandLine[0] == TEXT('/')) {
				commandLine.erase(0, 1);
			}
			//TODO not really relevant until replication is working
			return false;
		}

		std::wstring parseArgument(const std::wstring& line, size_t& off) {
			wchar_t escapeChar = TEXT('\\');
			bool previousCharIsEscape = line[off] == escapeChar;
			bool isQuoted = line[off++] == TEXT('"');
			wchar_t breakCharacter = isQuoted ? TEXT('"') : TEXT(' ');
			std::wstring result;
			while (line.size() > off) {
				wchar_t character = line[off];
				if (!previousCharIsEscape) {
					//break on the control character
					if (character == breakCharacter) break;
					//set last character as escape
					if (character == escapeChar) {
						previousCharIsEscape = true;
						//continue here to skip resetting prevIsEscape
						//and adding character to the result
						continue; 
					}
				}
				result += character;
				previousCharIsEscape = false;
				off++;
			}
			return result;
		}

		std::vector<AFGPlayerController*> parsePlayerName(AFGPlayerController* caller, const std::wstring& name) {
			UWorld* world = caller != nullptr ? caller->GetWorld() : GWorld;
			if (name == TEXT("@s")) {
				//check if caller is null, then return empty vector
				if (caller == nullptr) return {};
				return { caller };
			} else if (name == TEXT("@a")) {
				//give priority to the caller's world, if caller is null, use global world instance
				return getConnectedPlayers(world);
			} else {
				//try to fetch player by name
				const FString playerName = name.c_str();
				AFGPlayerController* controller = GetPlayerByName(world, playerName);
				if (controller == nullptr) return {};
				return { controller };
			}
		}
	};
};
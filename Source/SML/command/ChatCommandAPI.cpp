#include "ChatCommandAPI.h"
#include "FGChatManager.h"
#include "util/Utility.h"
#include "player/PlayerUtility.h"
#include "FGRadioactivitySubsystem.h"
#include "player/component/SMLPlayerComponent.h"
#include "mod/hooking.h"

template <typename T>
inline TArray<T> singleElement(T element) {
	if (element == nullptr) {
		return TArray<T>();
	}
	return TArrayBuilder<T>().Add(element).Build();
}

class FunctionProto {
public: void SendChatMessage(const FChatMessageStruct&) {}
};

namespace SML {
	namespace ChatCommand {
		//holds the mapping of the command name/alias to the command registrar entry
		static TMap<FString, FCommandRegistrarEntry> registeredCommands;
		//holds the list of all registered commands
		static TArray<FCommandRegistrarEntry> registeredCommandsList;

		SML_API TOptional<FCommandRegistrarEntry> getCommandByName(const FString& name) {
			if (!registeredCommands.Contains(name)) {
				return TOptional<FCommandRegistrarEntry>();
			}
			return TOptional<FCommandRegistrarEntry>(registeredCommands[name]);
		}
		
		//returns the list of all registered commands
		SML_API const TArray<FCommandRegistrarEntry>& getRegisteredCommands() {
			return registeredCommandsList;
		}

		SML_API void registerCommand(const FCommandRegistrarEntry& commandEntry) {
			TArray<FString> allCommandNames = TArray<FString>(commandEntry.aliases);
			allCommandNames.AddUnique(commandEntry.commandName);
			//register all command aliases
			for (const FString& commandAlias : allCommandNames) {
				const FString fqCommandName = FString::Printf(TEXT("%s:%s"), *commandEntry.modid, *commandAlias);
				//register short command name
				registeredCommands.Add(commandAlias, commandEntry);
				//register fully qualified command name
				registeredCommands.Add(fqCommandName, commandEntry);
			}
			//register command entry
			registeredCommandsList.Add(commandEntry);
		}

		void printCommandNotFound(AFGPlayerController* player) {
			USMLPlayerComponent* component = USMLPlayerComponent::Get(player);
			component->SendChatMessage(TEXT("Unknown command. Type /help for a list of commands."), FLinearColor::Red);
		}

		SML_API void PrintCommandUsage(const FCommandData& Data) {
			USMLPlayerComponent* Component = USMLPlayerComponent::Get(Data.player);
			Component->SendChatMessage(FString::Printf(TEXT("Usage: %s"), *Data.Command->usage), FLinearColor::Red);
		}


		FString parseArgument(const FString& line, size_t& off);

		SML_API EExecutionStatus runChatCommand(const FString& commandLine, AFGPlayerController* player) {
			if (commandLine.IsEmpty()) {
				printCommandNotFound(player);
				return EExecutionStatus::BAD_ARGUMENTS;
			}
			TArray<FString> resultArgArray;
			size_t offset = 0;
			while (commandLine.Len() > offset) {
				FString resultArg = parseArgument(commandLine, offset);
				resultArgArray.Add(std::move(resultArg));
				offset++; //skip argument separator
			}
			const FString& commandName = resultArgArray[0];
			if (!registeredCommands.Contains(commandName)) {
				printCommandNotFound(player);
				return EExecutionStatus::BAD_ARGUMENTS;
			}
			const FCommandRegistrarEntry& commandEntry = registeredCommands[commandName];
			const FCommandData commandData{ resultArgArray, player, &commandEntry };
			const EExecutionStatus resultStatus = (*commandEntry.commandHandler)(commandData);
			return resultStatus;
		}

		FString parseArgument(const FString& line, size_t& off) {
			if (off >= line.Len()) return TEXT("");
			wchar_t escapeChar = TEXT('\\');
			wchar_t firstChar = line[off++];
			bool previousCharIsEscape = firstChar == escapeChar;
			bool isQuoted = firstChar == TEXT('"');
			wchar_t breakCharacter = isQuoted ? TEXT('"') : TEXT(' ');
			FString result;
			//if first char is not a quote, append it too!
			if (!isQuoted && !previousCharIsEscape) 
				result.AppendChar(firstChar);
			while (line.Len() > off) {
				const wchar_t character = line[off];
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
				result.AppendChar(character);
				previousCharIsEscape = false;
				off++;
			}
			return result;
		}

		SML_API TArray<AFGPlayerController*> parsePlayerName(AFGPlayerController* caller, const FString& name) {
			UWorld* world = caller != nullptr ? caller->GetWorld() : GWorld;
			if (name == TEXT("@s")) {
				//check if caller is null, then return empty vector
				return singleElement(caller);
			} else if (name == TEXT("@a")) {
				//give priority to the caller's world, if caller is null, use global world instance
				return getConnectedPlayers(world);
			} else {
				//try to fetch player by name
				AFGPlayerController* controller = GetPlayerByName(world, name);
				return singleElement(controller);
			}
		}
	};
};
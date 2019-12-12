#pragma once

#include <vector>
#include "FGPlayerController.h"
#include "SatisfactoryModLoader.h"

namespace SML {
	namespace ChatCommand {

		/**
		* Holds information about a command and it's arguments.
		*
		* Arguments are the values following the command, seperated by a space.
		* argc is the amount of args and argv is a string vector of the args.
		* The first arg is always the command itself.
		*/
		struct FCommandData {
			/**
			* The amount of arguments.
			*
			* The minimum value is 1.
			*/
			int argc;
			/**
			* The arguments in a string array.
			*
			* Always has the command and the following arguments seperated by a space.
			*/
			std::vector<std::wstring> argv;

			/**
			* The player that executed this command.
			*
			* Will be nullptr if executed by runCommand.
			*/
			AFGPlayerController* player;
		};

		/**
		 * Command Handler function prototype.
		 * Return true if command actually did something,
		 * false otherwise (e.g bad arguments)
		 */
		typedef bool(*CommandHandler)(FCommandData* commandData);
		
		struct FCommandRegistrarEntry {
			/**
			 * ModId of the mod registering the command
			 * Be sure to pass actual modid of your mod here, because
			 * it will be checked and verified
			 */
			std::wstring modid;
			/**
			 * Name of the command
			 * Not limited in any way, but consider using only ASCII chars there
			 */
			std::wstring commandName;
			/**
			 * Usage of the command
			 * Example:
			 * msg <username> <message>
			 * give <username> <item> [amount] [extra_data]
			 */
			std::wstring usage;
			/**
			 * Pointer to a command handler function to be called
			 * when command is executed
			 */
			CommandHandler commandHandler;
		};

		const std::vector<FCommandRegistrarEntry>& getRegisteredCommands();

		/**
		* Registers a chat command to be called
		* throws std::illegal_argument if specified modid is invalid or doesn't belong to the caller
		* throws std::illegal_argument if command with specified name is already registered
		*/
		SML_API void registerCommand(const FCommandRegistrarEntry& commandEntry);

		/**
		* Parses command line and executes given command
		* Characters enclosed in "" are considered a single argument
		* returns true if command is found and executed successfully, false otherwise
		*/
		SML_API bool runChatCommand(const std::wstring& commandLine, AFGPlayerController* player);

		/**
		 * Parses given player name, returning all players matching
		 * for now it just returns player with a matching username, or the player who called the command in case of @self
		 * it will be improved in future to support different use-cases
		 */
		SML_API std::vector<AFGPlayerController*> parsePlayerName(AFGPlayerController* caller, const std::wstring& name);
	}
}

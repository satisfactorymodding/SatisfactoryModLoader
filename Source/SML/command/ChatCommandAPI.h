#pragma once

#include "FGPlayerController.h"
#include <functional>

namespace SML {
	namespace ChatCommand {

		struct FCommandRegistrarEntry;

		/**
		 * Describes command execution result status
		 */
		enum class EExecutionStatus {
			/** command executed successfully */
			COMPLETED,
			/** command not executed, or had no effect */
			UNCOMPLETED,
			/** command not executed, user permissions are too low */
			INSUFFICIENT_PERMISSIONS,
			/** command failed due to user providing invalid arguments */
			BAD_ARGUMENTS
		};

		/**
		* Holds information about a command and it's arguments.
		*
		* Arguments are the values following the command, seperated by a space.
		* argc is the amount of args and argv is a string vector of the args.
		* The first arg is always the command itself.
		*/
		struct FCommandData {
			/**
			* The arguments in a string array.
			*
			* Always has the command and the following arguments seperated by a space.
			*/
			const TArray<FString>& argv;

			/**
			* The player that executed this command.
			*
			* Will be nullptr if executed by runCommand.
			*/
			AFGPlayerController* player;

			/**
			 * The command entry being executed
			 */
			const FCommandRegistrarEntry* Command;
		};

		/**
		 * Command Handler function prototype.
		 */
		typedef std::function<EExecutionStatus(const FCommandData&)> CommandHandler;
		
		struct FCommandRegistrarEntry {
			/**
			 * ModId of the mod registering the command
			 * Be sure to pass actual modid of your mod here, because
			 * it will be checked and verified
			 */
			const FString modid;
			/**
			 * Name of the command
			 * Not limited in any way, but consider using only ASCII chars there
			 */
			const FString commandName;

			/**
			 * List of the additional names command can be referenced by
			 */
			const TArray<FString> aliases;
			/**
			 * Usage of the command
			 * Example:
			 * msg <username> <message>
			 * give <username> <item> [amount] [extra_data]
			 */
			const FString usage;
			/**
			 * Pointer to a command handler function to be called
			 * when command is executed
			 */
			const CommandHandler* commandHandler;
		};

		SML_API void PrintCommandUsage(const FCommandData& Data);

		SML_API TOptional<FCommandRegistrarEntry> getCommandByName(const FString& name);

		SML_API const TArray<FCommandRegistrarEntry>& getRegisteredCommands();

		/**
		* Registers a chat command to be called
		*/
		SML_API void registerCommand(const FCommandRegistrarEntry& commandEntry);

		/**
		* Parses command line and executes given command
		* Characters enclosed in "" are considered a single argument
		* If command is not found, returns bad_arguments
		*/
		SML_API EExecutionStatus runChatCommand(const FString& commandLine, AFGPlayerController* player);

		/**
		 * Parses given player name, returning all players matching
		 * for now it just returns player with a matching username, or the player who called the command in case of @self
		 * it will be improved in future to support different use-cases
		 */
		SML_API TArray<AFGPlayerController*> parsePlayerName(AFGPlayerController* caller, const FString& name);
	}
}

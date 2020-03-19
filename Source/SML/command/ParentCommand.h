#pragma once
#include "ChatCommandAPI.h"

namespace SML {
	namespace ChatCommand {
		class SML_API FParentCommand {
		private:
			TMap<FString, FCommandRegistrarEntry> SubCommands;
			CommandHandler SelfCommandHandler;
		public:
			FParentCommand();

			/**
			 * Adds sub command to this parent command
			 * Sub command will be executable using it's name or any of the aliases
			 * as the argument to this command
			 * In case of alias/name conflict, last registered command takes priority
			 */
			void AddSubCommand(const FCommandRegistrarEntry& CommandEntry);

			/**
			 * Builds command handler
			 */
			const CommandHandler& GetCommandHandler() const {
				return SelfCommandHandler;
			};

			/**
			 * Creates command usage in format:
			 * /CommandName <subcommand1/subcommand2/subcommand3>
			 * TODO: what about multi-level command hierarchies?
			 */
			FString BuildCommandUsage(const FString& CommandName);
		};
	}
}
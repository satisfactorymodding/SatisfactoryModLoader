#pragma once
#include <Windows.h>
#include <vector>
#include <Lib.h>
#include <util/FString.h>
#include "Registry.h"

namespace SML {
	namespace Mod {
		namespace Functions {
			/**
			* Holds information about a command and it's arguments.
			*
			* Arguments are the values following the command, seperated by a space.
			* argc is the amount of args and argv is a string vector of the args.
			* The first arg is always the command itself.
			*/
			struct CommandData {
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
				std::vector<std::string> argv;
			};

			/**
			* Registers a command to be called when player does /[commandname] in Satisfactory's chat.
			*
			* The function *MUST* return void and have a Functions::CommandData in the parameters, with nothing else.
			*
			* @author Nomnom
			*/
			SML_API void registerCommand(std::string name, PVOID func);

			/**
			* Registers an API function that can be called by other mods.
			*
			* Throws an error if a function of the same name is already registered.
			*
			* @author SuperCoder79
			*/
			SML_API void registerAPIFunction(std::string name, PVOID func);

			/**
			* Returns a raw function pointer of the API function specified by name.
			*
			* If a function is not found, it throws an error.
			* The returned function must be cast to a true function pointer before it's able to be used.
			* It is best used in conjunction to isModLoaded().
			*
			* @author SuperCoder79
			*/
			SML_API PVOID getAPIFunction(std::string name);

			/**
			* Checks if a mod is loaded.
			*
			* Returns true if it is, false if it's not.
			* Sidenote: If you depend on something done in a mod's setup function, place that code in postSetup, because postSetup is called in respect to mod dependencies, while setup is not.
			*
			* @author SuperCoder79
			*/
			SML_API bool isModLoaded(std::string name);

			/**
			* Broadcasts an event to all the handlers registered under name to all the mods.
			*
			* Does nothing if a mod doesn't have a handler for the function.
			*
			* @author SuperCoder79
			*/
			SML_API void broadcastEvent(std::string name);

			/**
			* Register a handler for a custom event that is called when broadcastEvent is called with the same function name.
			*
			* @author SuperCoder79
			*/
			SML_API void registerEvent(std::string name, PVOID func);
		}
	}
}
#pragma once
#include <Windows.h>
#include <vector>
#include <Lib.h>
#include <util/FString.h>
#include "Registry.h"

namespace SML {
	namespace Mod {
		namespace Functions {
			/*
			Holds information about a command and it's arguments. Arguments are the values following the command, seperated by a space.
			argc is the amount of args and argv is a string vector of the args.
			The first arg is always the command itself.
			*/
			struct CommandData {
				/*
				The amount of arguments. The minimum value is 1.
				*/
				int argc;
				/*
				The arguments in a string array. Always has the command and the following arguments seperated by a space.
				*/
				std::vector<std::string> argv;
			};

			/*
			Registers a command to be called when player does /<name> in Satisfactory's chat.
			The function *MUST* return void and have a Functions::CommandData in the parameters, with nothing else.
			*/
			SML_API void registerCommand(std::string name, PVOID func);

			/*
			Registers an API function that can be called by other mods.
			Throws an error if a function of the same name is already registered.
			*/
			SML_API void registerAPIFunction(std::string name, PVOID func);

			/*
			Returns a raw function pointer of the API function specified by name.
			If a function is not found, it throws an error.
			The returned function must be cast to a true function pointer before it's able to be used.
			It is best used in conjunction to isModLoaded().
			*/
			SML_API PVOID getAPIFunction(std::string name);

			/*
			Checks if a mod is loaded.
			Returns true if it is, false if it's not.
			Sidenote: If you depend on something done in a mod's setup function, place that code in post__setup, because postInit is called in respect to mod dependencies, while setup is not.
			*/
			SML_API bool isModLoaded(std::string name);
		}
	}
}
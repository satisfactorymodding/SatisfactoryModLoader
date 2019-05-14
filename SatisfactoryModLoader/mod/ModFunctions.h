#pragma once
#include <Windows.h>
#include <vector>
#include <Lib.h>
#include <util/FString.h>
#include "Registry.h"

namespace SML {
	namespace Mod {
		namespace Functions {
			struct CommandData {
				int argc;
				std::vector<std::string> argv;
			};


			SML_API void registerCommand(std::string name, PVOID func);

			SML_API void registerAPIFunction(std::string name, PVOID func);

			SML_API PVOID getAPIFunction(std::string name);

			SML_API bool isModLoaded(std::string name);
		}
	}
}
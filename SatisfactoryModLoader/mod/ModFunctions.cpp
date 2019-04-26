#include <stdafx.h>
#include "ModFunctions.h"
#include <SatisfactoryModLoader.h>

SML_API void registerCommand(std::string name, PVOID func) {
	Registry r = {
		name,
		func
	};
	modHandler.commandRegistry.push_back(r);
}
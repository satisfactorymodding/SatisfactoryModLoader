#include "hooking.h"
#include <string>
#include <unordered_map>
#include "util/funchook.h"
#include "util/Internal.h"
#include "SatisfactoryModLoader.h"

//since templates are actually compiled for each module separately,
//we need to have a global handler map which will be shared by all hook invoker templates available in all modules
//to keep single hook instance for each method
static std::unordered_map<std::string, void*> registeredListenerMap;

//map of all currently installed hooks to their names
//to have exactly one hook installed for each function
static std::unordered_map<std::string, void*> installedHookMap;

void* getHandlerListInternal(const char* identifier) {
	return registeredListenerMap[identifier];
}

void setHandlerListInstanceInternal(const char* identifier, void* handlerList) {
	registeredListenerMap[identifier] = handlerList;
}

#define CHECK_FUNCHOOK_ERR(arg, message) \
	if (arg != FUNCHOOK_ERROR_SUCCESS) SML::shutdownEngine(SML::formatStr(message, convertStr(functionName), TEXT(": "), funchook_error_message(funchook)));

void* registerHookFunction(const char* functionName, void* hookFunction) {
	const std::string functionNameStr = functionName;
	if (installedHookMap[functionNameStr] == nullptr) {
		funchook* funchook = funchook_create();
		if (funchook == nullptr) {
			SML::shutdownEngine(TEXT("funchook_create() returned NULL"));
		}
		void* gameFunctionPtr = ResolveGameSymbol(functionName);
		if (gameFunctionPtr == nullptr) {
			SML::shutdownEngine(SML::formatStr(TEXT("Hook target function not found: "), convertStr(functionName)));
		}
		CHECK_FUNCHOOK_ERR(funchook_prepare(funchook, &gameFunctionPtr, hookFunction), TEXT("funchook_prepare returned error: "));
		CHECK_FUNCHOOK_ERR(funchook_install(funchook, 0), TEXT("funchook_install returned error:"));

		installedHookMap[functionNameStr] = gameFunctionPtr;
		return gameFunctionPtr;
	}
	return installedHookMap[functionNameStr];
}



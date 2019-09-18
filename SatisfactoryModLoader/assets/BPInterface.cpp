#include "stdafx.h"

#include <assets/BPInterface.h>
#include <util/Objects/UProperty.h>
#include <util/Objects/FName.h>
#include <util/Objects/FFrame.h>
#include <util/Objects/UFunction.h>
#include <util/Objects/UClass.h>

#include <Windows.h>
#include <detours.h>

using namespace SML::Objects;

namespace SML {
	namespace Paks {
		void(*delegateCallDetoured)(void*, void*);

		// hooking function
		void delegateCall(void* self, void* params) {
			try {
				auto& functions = registerdDispatchHandlers.at(self);
				for (DelegateFunction func : functions) {
					if (func) func(self, params);
				}
			} catch (std::out_of_range e) {}

			delegateCallDetoured(self, params);
		}

		void registerDelegateHandler(void* delegate, DelegateFunction function) {
			registerdDispatchHandlers[delegate].insert(function);
		}

		void* registerDelegateHandler(UObject* obj, const std::string& name, DelegateFunction function) {
			auto del = obj->findField<UProperty>(name);
			if (del) {
				registerDelegateHandler(del->getValue<void>(obj), function);
				return del->getValue<void>(obj);
			}
			return nullptr;
		}

		void unregisterDelegateHandler(void* delegate, DelegateFunction function) {
			registerdDispatchHandlers[delegate].erase(function);
		}

		void initBPInterface() {
			if (delegateCallDetoured) return;

			DetourTransactionBegin();
			delegateCallDetoured = (void(WINAPI*)(void*, void*))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "??$ProcessMulticastDelegate@VUObject@@@?$TMulticastScriptDelegate@UFWeakObjectPtr@@@@QEBAXPEAX@Z");
			DetourAttach((void**)&delegateCallDetoured, &delegateCall);
			DetourTransactionCommit();
		}
	}
}
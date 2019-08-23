#include "stdafx.h"

#include <assets/BPInterface.h>

namespace SML {
	namespace Paks {
		//std::map<void*, std::set<DelegateFunction>> registerdDispatchHandlers;

		// hooking function
		void delegateCall(void* self, void* params) {
			try {
				auto& functions = registerdDispatchHandlers.at(self);
				for (DelegateFunction func : functions) {
					func(self, params);
				}
			} catch (std::out_of_range e) {}

			delegateCallDetoured(self, params);
		}

		// chached detour func pointer
		bool(*UFunction::invoke_f)(SDK::UFunction*, SDK::UObject*, FFrame&, void*) = nullptr;
		bool UFunction::invoke(SDK::UObject* obj, void* parameters) {
			FFrame frame(obj, this, parameters);
			return invoke_f(this, obj, frame, nullptr);
		}


		void(*FName::fNameConstruct_f)(void*, const wchar_t*, EFindName) = nullptr;
		FName::FName(const wchar_t* Name, EFindName FindType) {
			fNameConstruct_f(this, Name, FindType);
		}

		// Cached Function Pointers for detours
		SDK::UFunction*(*findFunction_f)(SDK::UObject*, SDK::FName) = nullptr;
		UFunction* findFunction(SDK::UObject* obj, FName name) {
			return (UFunction*)findFunction_f(obj, name);
		}

		void registerDelegateHandler(void* delegate, DelegateFunction function) {
			registerdDispatchHandlers[delegate].insert(function);
		}

		void* registerDelegateHandler(SDK::UObject* obj, const std::string& name, DelegateFunction function) {
			auto del = findField<UProperty>(obj, name);
			if (del) {
				registerDelegateHandler(del->GetValue<void>(obj), function);
				return del->GetValue<void>(obj);
			}
			return nullptr;
		}

		void unregisterDelegateHandler(void* delegate, DelegateFunction function) {
			registerdDispatchHandlers[delegate].erase(function);
		}

		void initBPInterface() {
			UFunction::invoke_f = (bool (WINAPI*)(SDK::UFunction*, SDK::UObject*, FFrame&, void*)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UFunction::Invoke");
			FName::fNameConstruct_f = (void (WINAPI*)(void*, const wchar_t*, EFindName))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "FName::FName");
			findFunction_f = (SDK::UFunction* (WINAPI*)(SDK::UObject*, SDK::FName))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UObject::FindFunction");

			DetourTransactionBegin();
			delegateCallDetoured = (void(WINAPI*)(void*, void*))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "??$ProcessMulticastDelegate@VUObject@@@?$TMulticastScriptDelegate@UFWeakObjectPtr@@@@QEBAXPEAX@Z");
			DetourAttach((void**)&delegateCallDetoured, &delegateCall);
			DetourTransactionCommit();
		}
	}
}
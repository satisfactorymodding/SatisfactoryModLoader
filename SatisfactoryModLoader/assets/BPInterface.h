#pragma once

#include "../SatisfactorySDK/SDK.hpp"

#include <Lib.h>
#include <util/Utility.h>

#include <detours.h>
#include <map>
#include <set>

namespace SML {
	/// Predeclerations Begin
	class OutputDevice;
	class Stack;
	class FFrame;
	class FName;
	class UProperty;
	class UFunction;
	/// Predeclerations End

	typedef void(*DelegateFunction)(void*, void*);

	// register handlers
	SML_API std::map<void*, std::set<DelegateFunction>> registerdDispatchHandlers;

	namespace {
		// hooked function for delagte call
		void(*delegateCallDetoured)(void*, void*);

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
	}

	extern class OutputDevice {
	public:
		OutputDevice() : bSuppressEventTag(false), bAutoEmitLineTerminator(true) {}
		virtual ~OutputDevice() {}
		bool bSuppressEventTag;
		bool bAutoEmitLineTerminator;
	};

	extern class Stack : public SDK::TArray< UINT32 > {
		unsigned char uk[32];
	};

	extern class FFrame : public OutputDevice {
	private:
		SDK::UFunction* Node;
		SDK::UObject* Object;
		UINT8* Code;
		UINT8* Locals;
		SDK::UProperty* MostRecentProperty;
		UINT8* MostRecentPropertyAddress;
		Stack FlowStack;
		FFrame* PreviousFrame;
		void* OutParms;
		SDK::UField* PropertyChainForCompiledIn;
		SDK::UFunction* CurrentNativeFunction;
		bool bArrayContextFailed;
	public:
		FFrame(SDK::UObject* InObject, SDK::UFunction* InNode, void* InLocals, FFrame* InPreviousFrame = nullptr, SDK::UField* InPropertyChainForCompiledIn = nullptr)
			: Node(InNode)
			, Object(InObject)
			, Code((UINT8*)(InNode->Script.GetData()))
			, Locals((UINT8*)InLocals)
			, MostRecentProperty(NULL)
			, MostRecentPropertyAddress(NULL)
			, PreviousFrame(InPreviousFrame)
			, OutParms(NULL)
			, PropertyChainForCompiledIn(InPropertyChainForCompiledIn)
			, CurrentNativeFunction(NULL)
			, bArrayContextFailed(false) {}
	};

	// chached detour func pointer
	SML_API bool(*invoke_f)(SDK::UFunction*, SDK::UObject*, FFrame&, void*);
	extern class UFunction : public SDK::UFunction {
	public:
		bool Invoke(SDK::UObject* obj, void* parameters) {
			FFrame frame(obj, this, parameters);
			return invoke_f(this, obj, frame, nullptr);
		}
	};

	extern class UProperty : public SDK::UField {
	public:
		INT32			ArrayDim;
		INT32			ElementSize;
		UINT64	PropertyFlags;
		UINT16			RepIndex;
		UINT8 BlueprintReplicationCondition;
		INT32		Offset_Internal;
		SDK::FName		RepNotifyFunc;
		UProperty*	PropertyLinkNext;
		UProperty*  NextRef;
		UProperty*	DestructorLinkNext;
		UProperty*	PostConstructLinkNext;

		template<typename T>
		inline T* GetValue(SDK::UObject* container) {
			return (T*)((UINT64)container + (UINT64)Offset_Internal);
		}
	};

	enum EFindName {
		FNAME_Find,
		FNAME_Add,
		FNAME_Replace_Not_Safe_For_Threading,
	};

	// chached detour func pointer
	SML_API void(*fNameConstruct_f)(void*, const wchar_t*, EFindName);

	extern class FName : public SDK::FName {
	public:
		FName(const wchar_t* Name, EFindName FindType = FNAME_Add) {
			fNameConstruct_f(this, Name, FindType);
		}
	};

	template<typename T>
	extern T* FindField(SDK::UClass* clazz, const std::string& name) {
		SDK::UField* field = clazz->Children;
		while (field) {
			if (field->GetName() == name) {
				return (T*)field;
			} else {
				field = field->Next;
			}
		}
		return nullptr;
	}

	template<typename T>
	extern T* FindField(SDK::UObject* obj, const std::string& name) {
		return FindField<T>(obj->Class, name);
	}

	// Cached Function Pointers for detours
	SML_API SDK::UFunction*(*findFunction_f)(SDK::UObject*, SDK::FName);

	extern UFunction* FindFunction(SDK::UObject* obj, FName name) {
		return (UFunction*)findFunction_f(obj, name);
	}

	extern void RegisterDelegateHandler(void* delegate, DelegateFunction function) {
		registerdDispatchHandlers[delegate].insert(function);
	}

	extern void* RegisterDelegateHandler(SDK::UObject* obj, const std::string& name, DelegateFunction function) {
		auto del = FindField<UProperty>(obj, name);
		if (del) {
			RegisterDelegateHandler(del->GetValue<void>(obj), function);
			return del->GetValue<void>(obj);
		}
		return nullptr;
	}

	extern void UnregisterDelegateHandler(void* delegate, DelegateFunction function) {
		registerdDispatchHandlers[delegate].erase(function);
	}

	extern void Init() {
		invoke_f = (bool (WINAPI*)(SDK::UFunction*, SDK::UObject*, FFrame&, void*)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UFunction::Invoke");
		fNameConstruct_f = (void (WINAPI*)(void*, const wchar_t*, EFindName))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "FName::FName");
		findFunction_f = (SDK::UFunction* (WINAPI*)(SDK::UObject*, SDK::FName))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UObject::FindFunction");

		DetourTransactionBegin();
		delegateCallDetoured = (void(WINAPI*)(void*, void*))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "??$ProcessMulticastDelegate@VUObject@@@?$TMulticastScriptDelegate@UFWeakObjectPtr@@@@QEBAXPEAX@Z");
		DetourAttach((void**)&delegateCallDetoured, &delegateCall);
		DetourTransactionCommit();
	}
}
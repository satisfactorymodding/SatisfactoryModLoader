#pragma once

#ifndef BPINTERFACE_H
#define BPINTERFACE_H

#include "../SatisfactorySDK/SDK.hpp"

#include <Lib.h>
#include <util/Utility.h>

#include <detours.h>
#include <map>
#include <set>

namespace SML {
	namespace Paks {
		/// Predeclerations Begin
		class OutputDevice;
		class Stack;
		class FFrame;
		class FName;
		class UProperty;
		class UFunction;
		/// Predeclerations End

		typedef void(*DelegateFunction)(void*, void*);

		namespace {
			// hooked function for delagte call
			void(*delegateCallDetoured)(void*, void*);
		
			// register handlers
			std::map<void*, std::set<DelegateFunction>> registerdDispatchHandlers;
		}

		SML_API class OutputDevice {
		public:
			OutputDevice() : bSuppressEventTag(false), bAutoEmitLineTerminator(true) {}
			virtual ~OutputDevice() {}
			bool bSuppressEventTag;
			bool bAutoEmitLineTerminator;
		};

		SML_API class Stack : public SDK::TArray< UINT32 > {
			unsigned char uk[32];
		};

		SML_API class FFrame : public OutputDevice {
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

		SML_API class UFunction : public SDK::UFunction {
		public:
			// chached detour func pointer
			static bool(*invoke_f)(SDK::UFunction*, SDK::UObject*, FFrame&, void*);

			SML_API bool invoke(SDK::UObject* obj, void* parameters);
		};

		SML_API class UProperty : public SDK::UField {
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

		SML_API enum EFindName {
			FNAME_Find,
			FNAME_Add,
			FNAME_Replace_Not_Safe_For_Threading,
		};

		SML_API class FName : public SDK::FName {
		public:
			// chached detour func pointer
			static void(*fNameConstruct_f)(void*, const wchar_t*, EFindName);
			
			SML_API FName(const wchar_t* Name, EFindName FindType = FNAME_Add);
		};

		template<typename T>
		extern T* findField(SDK::UClass* clazz, const std::string& name) {
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
		extern T* findField(SDK::UObject* obj, const std::string& name) {
			return findField<T>(obj->Class, name);
		}

		SML_API extern UFunction* findFunction(SDK::UObject* obj, FName name);
		SML_API extern void registerDelegateHandler(void* delegate, DelegateFunction function);
		SML_API extern void* registerDelegateHandler(SDK::UObject* obj, const std::string& name, DelegateFunction function);
		SML_API extern void unregisterDelegateHandler(void* delegate, DelegateFunction function);
		SML_API extern void initBPInterface();
	}
}

#endif
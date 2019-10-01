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
		int getVtableSize(void** vtable) {
			if (vtable)
				for (int i = 0;; i++)
					if (!vtable[i])
						return i;

			return 0;
		}

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

		// --- PropertyBuilder --- //

		PropertyBuilder PropertyBuilder::retVal(EPropertyClass type, std::string name) {
			PropertyBuilder builder;
			builder.params.type = type;
			builder.params.dim = 1;
			builder.name(name);
			builder.addObjFlags(RF_MarkAsNative | RF_Transient | RF_Public);
			builder.addParamFlags(Prop_SkipSerialization | Prop_Parm | Prop_OutParm);
			return builder;
		}

		PropertyBuilder PropertyBuilder::param(EPropertyClass type, std::string name) {
			PropertyBuilder builder;
			builder.params.type = type;
			builder.params.dim = 1;
			builder.name(name);
			builder.addObjFlags(RF_MarkAsNative | RF_Transient | RF_Public);
			builder.addParamFlags(Prop_SkipSerialization | Prop_Parm);
			return builder;
		}

		PropertyBuilder PropertyBuilder::attrib(EPropertyClass type, std::string name) {
			PropertyBuilder builder;
			builder.params.type = type;
			builder.params.dim = 1;
			builder.name(name);
			builder.addObjFlags(RF_MarkAsNative | RF_Transient | RF_Public);
			builder.addParamFlags(Prop_SkipSerialization | Prop_BlueprintVisible);
			return builder;
		}

		FGenericPropertyParams* PropertyBuilder::build() {
			params.name = pname.c_str();
			return &params;
		}

		PropertyBuilder& PropertyBuilder::addObjFlags(EObjectFlags flags) {
			params.objFlags = (EObjectFlags)(params.objFlags | flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::addObjFlags(unsigned int flags) {
			params.objFlags = (EObjectFlags)(params.objFlags | flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::remObjFlags(EObjectFlags flags) {
			params.objFlags = (EObjectFlags)(params.objFlags & ~flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::addParamFlags(EPropertyFlags flags) {
			params.propFlags = (EPropertyFlags)(params.propFlags | flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::addParamFlags(unsigned int flags) {
			params.propFlags = (EPropertyFlags)(params.propFlags | flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::remParamFlags(EPropertyFlags flags) {
			params.propFlags = (EPropertyFlags)(params.propFlags & ~flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::name(std::string name) {
			pname = name;
			return *this;
		}

		size_t PropertyBuilder::getSize() {
			size_t size;
			switch (params.type) {
			case EPropertyClass::Bool:
				size = sizeof(bool);
				break;
			case EPropertyClass::Array:
				size = sizeof(TArray<void*>);
				break;
			case EPropertyClass::Byte:
				size = sizeof(std::byte);
				break;
			case EPropertyClass::Class:
				size = sizeof(UClass*);
				break;
				/*case EPropertyClass::Delegate:
				size = sizeof(SDK::FScriptDelegate);
				break;*/
			case EPropertyClass::Double:
				size = sizeof(double);
				break;
			case EPropertyClass::Enum:
				size = sizeof(int);
				break;
			case EPropertyClass::Float:
				size = sizeof(float);
				break;
			case EPropertyClass::Int:
				size = sizeof(int);
				break;
			case EPropertyClass::Int16:
				size = sizeof(std::int16_t);
				break;
			case EPropertyClass::Int64:
				size = sizeof(std::int64_t);
				break;
			case EPropertyClass::Int8:
				size = sizeof(std::int8_t);
				break;
				/*case EPropertyClass::Interface:
				size = sizeof(SDK::UInterface*);
				break;
				case EPropertyClass::LazyObject:
				size = sizeof(SDK::FLazyObjectPtr);
				break;
				case EPropertyClass::Map:
				size = sizeof(SDK::TMap<void, void>);
				break;
				case EPropertyClass::MulticastDelegate:
				size = sizeof(SDK::FScriptMulticastDelegate);
				break;*/
			case EPropertyClass::Name:
				size = sizeof(FName);
				break;
			case EPropertyClass::Object:
				size = sizeof(UObject*);
				break;
			case EPropertyClass::Str:
				size = sizeof(FString);
				break;
			case EPropertyClass::Struct:
				size = sizeof(void*);
				break;
			default: // missing set and all after struct
				throw std::exception("unsupported type");
			}
			return size;
		}

		// --- FunctionBuilder --- //

		FunctionBuilder FunctionBuilder::Method(std::string name) {
			FunctionBuilder builder;
			builder.name(name);
			builder.addObjFlags(RF_MarkAsNative | RF_Transient | RF_Public);
			builder.addFuncFlags(FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable);
			return builder;
		}
		
		FunctionBuilder FunctionBuilder::StaticFunction(std::string name) {
			FunctionBuilder builder;
			builder.name(name);
			builder.addObjFlags(RF_MarkAsNative | RF_Transient | RF_Public);
			builder.addFuncFlags(FUNC_Final | FUNC_Native | FUNC_Public | FUNC_BlueprintCallable | FUNC_Static);
			return builder;
		}
		
		UFunction * FunctionBuilder::construct(UClass * clazz) {
			if (constructed) return constructed;

			FGenericPropertyParams** props = new FGenericPropertyParams*[this->props.size()];
			params.structSize = 0;
			for (int i = 0; i < this->props.size(); ++i) {
				props[i] = this->props[i].build();
				props[i]->off = params.structSize;
				params.structSize += this->props[i].getSize();
			}
			params.propArr = props;
			params.propCount = this->props.size();

			params.name = fname.c_str();

			retVal = clazz;
			params.func = retFunc;

			auto constructUFunction = (void(*)(UFunction*&, FFunctionParams)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UE4CodeGen_Private::ConstructUFunction");
			constructUFunction(constructed, params);

			delete[] props;

			return constructed;
		}
		
		void FunctionBuilder::_registerFunc(UClass * clazz, void* func) {
			if (func) this->func = func;
			if (this->func) {
				auto reg = (void(*)(UClass*, const char*, void*))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "FNativeFunctionRegistrar::RegisterFunction");
				reg(clazz, fname.c_str(), this->func);
			}
		}
		
		UFunction * FunctionBuilder::_build(UClass * clazz, void* func) {
			if (func) _registerFunc(clazz, func);
			auto f = construct(clazz);
			return f;
		}
		
		void FunctionBuilder::_attach(UClass * clazz, void* func) {
			FClassFunctionLinkInfo links[1];
			retVal = _build(clazz, func);
			links[0].func = (UFunction*(*)())&retFunc;
			links[0].name = fname.c_str();
			auto addFuncToMap = (void(*)(UClass*, const FClassFunctionLinkInfo*, std::uint32_t)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UClass::CreateLinkAndAddChildFunctionsToMap");
			addFuncToMap((UClass*)clazz, links, 1);
		}
		
		FunctionBuilder & FunctionBuilder::addObjFlags(EObjectFlags flags) {
			params.objFlags = (EObjectFlags)(params.objFlags | flags);
			return *this;
		}
		
		FunctionBuilder & FunctionBuilder::addObjFlags(unsigned int flags) {
			params.objFlags = (EObjectFlags)(params.objFlags | flags);
			return *this;
		}
		
		FunctionBuilder & FunctionBuilder::remObjFlags(EObjectFlags flags) {
			params.objFlags = (EObjectFlags)(params.objFlags & ~flags);
			return *this;
		}
		
		FunctionBuilder & FunctionBuilder::addFuncFlags(EFunctionFlags flags) {
			params.funcFlags = (EFunctionFlags)(params.funcFlags | flags);
			return *this;
		}
		
		FunctionBuilder & FunctionBuilder::addFuncFlags(unsigned int flags) {
			params.funcFlags = (EFunctionFlags)(params.funcFlags | flags);
			return *this;
		}
		
		FunctionBuilder & FunctionBuilder::remFuncFlags(EFunctionFlags flags) {
			params.funcFlags = (EFunctionFlags)(params.funcFlags & ~flags);
			return *this;
		}
		
		FunctionBuilder & FunctionBuilder::name(std::string name) {
			fname = name;
			return *this;
		}

		FunctionBuilder & FunctionBuilder::param(const PropertyBuilder & prop) {
			props.push_back(prop);
			return *this;
		}

		UObject* FunctionBuilder::retVal = nullptr;
	}
}
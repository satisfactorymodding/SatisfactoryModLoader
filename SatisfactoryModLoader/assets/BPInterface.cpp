#include "stdafx.h"

#include <assets/BPInterface.h>
#include <util/Objects/UProperty.h>
#include <util/Objects/FName.h>
#include <util/Objects/FFrame.h>
#include <util/Objects/UFunction.h>
#include <util/Objects/UClass.h>

#include <Windows.h>
#include <detours.h>

#include <../SatisfactorySDK/SDK.hpp>

using namespace SML::Objects;

namespace SML {
	namespace Paks {
		// detour function cache //
		void(*constructUFunction)(UFunction*&, FFunctionParams) = nullptr;
		void(*registerFunction)(UClass*, const char*, void*) = nullptr;
		void(*addFunctionToMap)(UClass*, const FClassFunctionLinkInfo*, std::uint32_t) = nullptr;
		void(*objCompInDefer)(Objects::UClass*(*)(), Objects::UClass*(*)(), const TCHAR*, const TCHAR*, bool, const TCHAR*, void(*)()) = nullptr;
		void(*processNewObjs)() = nullptr;
		void(*constructUClass)(Objects::UClass*&, FClassParams) = nullptr;
		void(*privateStaticClassBody)(const TCHAR*, const TCHAR*, Objects::UClass*&, void(*)(), std::uint32_t, Objects::EClassFlags, Objects::EClassCastFlags, const TCHAR*, void(*)(FObjectInitializer&), Objects::UObject*(*)(FVtableHelper&), void(*)(Objects::UObject*, FReferenceCollector&), Objects::UClass*(*)(), Objects::UClass*(*)(), bool);

		int getVtableSize(void** vtable) {
			if (vtable) {
				for (int i = 0;; i++) {
					if (!vtable[i]) {
						return i;
					}
				}
			}

			return 0;
		}

		void initBPInterface() {
			constructUFunction = (void(*)(UFunction*&, FFunctionParams)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UE4CodeGen_Private::ConstructUFunction");
			registerFunction = (void(*)(UClass*, const char*, void*)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "FNativeFunctionRegistrar::RegisterFunction");
			addFunctionToMap = (void(*)(UClass*, const FClassFunctionLinkInfo*, std::uint32_t)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UClass::CreateLinkAndAddChildFunctionsToMap");
			objCompInDefer = (void(*)(Objects::UClass*(*)(), Objects::UClass*(*)(), const TCHAR*, const TCHAR*, bool, const TCHAR*, void(*)())) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UObjectCompiledInDefer");
			processNewObjs = (void(*)()) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "ProcessNewlyLoadedUObjects");
			constructUClass = (void(*)(Objects::UClass*&, FClassParams)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UE4CodeGen_Private::ConstructUClass");
			privateStaticClassBody = (void(*)(const TCHAR*, const TCHAR*, Objects::UClass*&, void(*)(), std::uint32_t, Objects::EClassFlags, Objects::EClassCastFlags, const TCHAR*, void(*)(FObjectInitializer&), Objects::UObject*(*)(FVtableHelper&), void(*)(Objects::UObject*, FReferenceCollector&), Objects::UClass*(*)(), Objects::UClass*(*)(), bool)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "GetPrivateStaticClassBody");
		}

		// --- PropertyBuilder --- //

		size_t PropertyBuilder::createStructFromType(const EPropertyClass type) {
			FPropertyParamsBase* p = nullptr;
			size_t size = 0;
			switch (type) {
			case EPropertyClass::Bool:
				p = (FPropertyParamsBase*) new FBoolPropertyParams();
				structType = EPropStructParamsType::Bool;
				size = sizeof(FBoolPropertyParams);
				break;
			case EPropertyClass::Byte:
				p = (FPropertyParamsBase*) new FBytePropertyParams();
				structType = (EPropStructParamsType)(EPropStructParamsType::Byte | EPropStructParamsType::WithOff);
				size = sizeof(FBytePropertyParams);
				break;
			case EPropertyClass::Class:
				p = (FPropertyParamsBase*) new FClassPropertyParams();
				structType = (EPropStructParamsType)(EPropStructParamsType::WithOff | EPropStructParamsType::Class);
				size = sizeof(FClassPropertyParams);
				break;
			case EPropertyClass::Delegate:
				p = (FPropertyParamsBase*) new FDelegatePropertyParams();
				structType = (EPropStructParamsType)(EPropStructParamsType::WithOff | EPropStructParamsType::Delegate);
				size = sizeof(FDelegatePropertyParams);
				break;
			case EPropertyClass::Enum:
				p = (FPropertyParamsBase*) new FEnumPropertyParams();
				structType = (EPropStructParamsType)(EPropStructParamsType::WithOff | EPropStructParamsType::Enum);
				size = sizeof(FEnumPropertyParams);
				break;
			case EPropertyClass::Interface:
				p = (FPropertyParamsBase*) new FInterfacePropertyParams();
				structType = (EPropStructParamsType)(EPropStructParamsType::WithOff | EPropStructParamsType::Interface);
				size = sizeof(FInterfacePropertyParams);
				break;
			case EPropertyClass::Object:
			case EPropertyClass::LazyObject:
			case EPropertyClass::SoftObject:
			case EPropertyClass::WeakObject:
				p = (FPropertyParamsBase*) new FObjectPropertyParams();
				structType = (EPropStructParamsType)(EPropStructParamsType::WithOff | EPropStructParamsType::Object);
				size = sizeof(FObjectPropertyParams);
				break;
			case EPropertyClass::MulticastDelegate:
				p = (FPropertyParamsBase*) new FMulticastDelegatePropertyParams();
				structType = (EPropStructParamsType)(EPropStructParamsType::WithOff | EPropStructParamsType::MulticastDelegate);
				size = sizeof(FMulticastDelegatePropertyParams);
				break;
			case EPropertyClass::SoftClass:
				p = (FPropertyParamsBase*) new FSoftClassPropertyParams();
				structType = (EPropStructParamsType)(EPropStructParamsType::WithOff | EPropStructParamsType::SoftClass);
				size = sizeof(FSoftClassPropertyParams);
				break;
			case EPropertyClass::Struct:
				p = (FPropertyParamsBase*) new FStructPropertyParams();
				structType = (EPropStructParamsType)(EPropStructParamsType::WithOff | EPropStructParamsType::Struct);
				size = sizeof(FStructPropertyParams);
				break;
			default:
				p = (FPropertyParamsBase*) new FGenericPropertyParams();
				structType = (EPropStructParamsType)(EPropStructParamsType::WithOff | EPropStructParamsType::Generic);
				size = sizeof(FGenericPropertyParams);
				break;
			}
			p->type = type;
			p->dim = 1;
			params = p;
			return size;
		}

		PropertyBuilder PropertyBuilder::retVal(const EPropertyClass type, const std::string name) {
			PropertyBuilder builder;
			builder.createStructFromType(type);
			builder.name(name);
			builder.addObjFlags(RF_MarkAsNative | RF_Transient | RF_Public);
			builder.addParamFlags(Prop_SkipSerialization | Prop_Parm | Prop_OutParm);
			return builder;
		}

		PropertyBuilder PropertyBuilder::param(const EPropertyClass type, const std::string name) {
			PropertyBuilder builder;
			builder.createStructFromType(type);
			builder.name(name);
			builder.addObjFlags(RF_MarkAsNative | RF_Transient | RF_Public);
			builder.addParamFlags(Prop_SkipSerialization | Prop_Parm);
			return builder;
		}

		PropertyBuilder PropertyBuilder::attrib(const EPropertyClass type, const std::string name) {
			PropertyBuilder builder;
			builder.createStructFromType(type);
			builder.name(name);
			builder.addObjFlags(RF_MarkAsNative | RF_Transient | RF_Public);
			builder.addParamFlags(Prop_SkipSerialization | Prop_BlueprintVisible);
			return builder;
		}

		FPropertyParamsBase* PropertyBuilder::build() {
			params->name = pname.c_str();
			params->notify = notify.c_str();
			params->notify = nullptr;
			return params;
		}

		PropertyBuilder& PropertyBuilder::addObjFlags(const EObjectFlags flags) {
			params->objFlags = (EObjectFlags)(params->objFlags | flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::addObjFlags(const unsigned int flags) {
			params->objFlags = (EObjectFlags)(params->objFlags | flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::remObjFlags(const EObjectFlags flags) {
			params->objFlags = (EObjectFlags)(params->objFlags & ~flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::addParamFlags(const EPropertyFlags flags) {
			params->propFlags = (EPropertyFlags)(params->propFlags | flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::addParamFlags(const std::uint64_t flags) {
			params->propFlags = (EPropertyFlags)(params->propFlags | flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::remParamFlags(const EPropertyFlags flags) {
			params->propFlags = (EPropertyFlags)(params->propFlags & ~flags);
			return *this;
		}

		PropertyBuilder& PropertyBuilder::name(const std::string name) {
			pname = name;
			return *this;
		}

		PropertyBuilder& PropertyBuilder::off(int offset) {
			if (params && (structType & EPropStructParamsType::WithOff)) {
				manualOff = true;
				((FPropertyParamsBaseWithOffset*)params)->off = offset;
			}
			return *this;
		}

		std::int32_t PropertyBuilder::getOff() {
			if (params && (structType & EPropStructParamsType::WithOff)) {
				if (manualOff) return ((FPropertyParamsBaseWithOffset*)params)->off;
				else return -1;
			}
			return -2;
		}

		PropertyBuilder & PropertyBuilder::classFunc(UClass *(*func)()) {
			switch (structType) {
			case Object:
				((FObjectPropertyParams*)params)->classFunc = func;
				break;
			case Class:
				((FClassPropertyParams*)params)->classFunc = func;
				break;
			case SoftClass:
				((FSoftClassPropertyParams*)params)->metaClassFunc = func;
				break;
			case Interface:
				((FInterfacePropertyParams*)params)->interfaceClassFunc = func;
				break;
			}
			return *this;
		}

		PropertyBuilder & PropertyBuilder::classFunc(SDK::UClass *(*func)()) {
			classFunc((UClass*(*)())func);
			return *this;
		}

		PropertyBuilder & PropertyBuilder::bitFunc(void(*func)(void *)) {
			switch (structType) {
			case Bool:
				((FBoolPropertyParams*)params)->setBitFunc = func;
			}
			return *this;
		}

		PropertyBuilder & PropertyBuilder::outerSize(size_t size) {
			switch (structType) {
			case Bool:
				((FBoolPropertyParams*)params)->outerSize = size;
			}
			return *this;
		}

		SML_API PropertyBuilder & PropertyBuilder::boolData(size_t size, ENativeBool native) {
			switch (structType) {
			case Bool:
				((FBoolPropertyParams*)params)->size = size;
				((FBoolPropertyParams*)params)->nativeBool = native;
			}
			return *this;
		}

		PropertyBuilder & PropertyBuilder::metaClassFunc(UClass *(*func)()) {
			switch (structType) {
			case Class:
				((FClassPropertyParams*)params)->metaClassFunc = func;
			}
			return *this;
		}

		PropertyBuilder & PropertyBuilder::enumFunc(Objects::UEnum *(*func)()) {
			switch (structType) {
			case Enum:
				((FEnumPropertyParams*)params)->enumFunc = func;
				break;
			case Byte:
				((FBytePropertyParams*)params)->enumFunc = func;
				break;
			}
			return *this;
		}

		PropertyBuilder & PropertyBuilder::funcFunc(void *(*func)()) {
			switch (structType) {
			case Delegate:
				((FDelegatePropertyParams*)params)->sigFunctionFunc = (UFunction*(*)()) func;
				break;
			case MulticastDelegate:
				((FDelegatePropertyParams*)params)->sigFunctionFunc = (UFunction*(*)()) func;
				break;
			}
			return *this;
		}

		PropertyBuilder & PropertyBuilder::structFunc(void *(*func)()) {
			switch (structType) {
			case Struct:
				((FStructPropertyParams*)params)->scriptStructFunc = (UScriptStruct*(*)()) func;
				break;
			}
			return *this;
		}

		size_t PropertyBuilder::getSize() {
			switch (structType) {
			case Struct:
				return ((SDK::UScriptStruct*)((FStructPropertyParams*)params)->scriptStructFunc())->PropertySize;
			}
			return getSize(params->type);
		}

		size_t PropertyBuilder::getSize(EPropertyClass type) {
			size_t size;
			switch (type) {
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
				case EPropertyClass::Delegate:
				size = sizeof(SDK::FScriptDelegate);
				break;
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
				size = sizeof(std::int32_t);
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
			case EPropertyClass::Interface:
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
				break;
			case EPropertyClass::Name:
				size = sizeof(FName);
				break;
			case EPropertyClass::Object:
				size = sizeof(UObject*);
				break;
			case EPropertyClass::Str:
				size = sizeof(FString);
				break;
			case EPropertyClass::Text:
				size = sizeof(SDK::FText);
				break;
			case EPropertyClass::UInt16:
				size = sizeof(std::uint16_t);
				break;
			case EPropertyClass::UInt32:
				size = sizeof(std::uint32_t);
				break;
			case EPropertyClass::UInt64:
				size = sizeof(std::uint64_t);
				break;
			case EPropertyClass::UnsizedInt:
				size = sizeof(int);
				break;
			case EPropertyClass::UnsizedUInt:
				size = sizeof(unsigned int);
				break;
			case EPropertyClass::WeakObject:
				size = sizeof(SDK::FWeakObjectPtr);
				break;
			default: // missing set
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

			FPropertyParamsBase** props = new FPropertyParamsBase*[this->props.size()];
			int nextOff = 0;
			params.structSize = 0;
			for (int i = this->props.size() - 1; i >= 0; --i) {
				auto& p = this->props[i];
				auto noff = p.getOff();
				auto nsize = p.getSize();
				if (noff >= 0) nextOff = noff + nsize;
				else {
					if (noff == -1) p.off(nextOff);
					nextOff += nsize;
				}

				params.structSize += nsize;
				auto pr = p.build();
				props[i] = pr;
			}
			params.propArr = props;
			params.propCount = static_cast<std::int32_t>(this->props.size());

			params.name = fname.c_str();

			retVal = clazz;
			params.func = retFunc;

			constructUFunction(constructed, params);

			delete[] props;

			return constructed;
		}
		
		void FunctionBuilder::_registerFunc(UClass * clazz, void* func) {
			if (func) this->func = func;
			if (this->func) {
				registerFunction(clazz, fname.c_str(), this->func);
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
			addFunctionToMap((UClass*)clazz, links, 1);
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
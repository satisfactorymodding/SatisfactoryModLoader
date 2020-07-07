#include "hooking.h"

#include <xkeycheck.h>

#include "util/funchook.h"
#include "util/Internal.h"
#include "SatisfactoryModLoader.h"
#include "CoreMinimal.h"
#include "util/bootstrapper_exports.h"

//since templates are actually compiled for each module separately,
//we need to have a global handler map which will be shared by all hook invoker templates available in all modules
//to keep single hook instance for each method
static TMap<FString, void*> RegisteredListenerMap;

//map of all currently installed hooks to their names
//to have exactly one hook installed for each function
static TMap<FString, void*> InstalledHookMap;

struct ConstructorHookInfoHolder {
	ConstructorHookThunk ConstructorHookThunk;
	TArray<FString> AlreadyHookedFunctions;
};

//map of all installed constructor hook thunks
//by constructor original address
static TMap<void*, ConstructorHookInfoHolder> InstalledConstructorThunks;

void* GetHandlerListInternal(const FString& SymbolId) {
	void** ExistingMapEntry = RegisteredListenerMap.Find(SymbolId);
	return ExistingMapEntry ? *ExistingMapEntry : nullptr;
}

void SetHandlerListInstanceInternal(const FString& SymbolId, void* HandlerList) {
	RegisteredListenerMap.Add(SymbolId, HandlerList);
}

#define CHECK_FUNCHOOK_ERR(arg) \
	if (arg != FUNCHOOK_ERROR_SUCCESS) SML::Logging::fatal(*FString::Printf(TEXT("Hooking symbol %s failed: funchook failed: %hs"), *SymbolId, funchook_error_message(funchook)));

bool HookStandardFunction(const FString& SymbolId, void* OriginalFunctionPointer, void* HookFunctionPointer, void** OutTrampolineFunction) {
	if (InstalledHookMap.Contains(SymbolId)) {
		//Hook already installed, set trampoline function and return
		*OutTrampolineFunction = InstalledHookMap.FindChecked(SymbolId);
		return false;
	}
	funchook* funchook = funchook_create();
	if (funchook == nullptr) {
		SML::Logging::fatal(*FString::Printf(TEXT("Hooking symbol %s failed: funchook_create() returned NULL"), *SymbolId));
		return false;
	}
	*OutTrampolineFunction = OriginalFunctionPointer;
	CHECK_FUNCHOOK_ERR(funchook_prepare(funchook, OutTrampolineFunction, HookFunctionPointer));
	CHECK_FUNCHOOK_ERR(funchook_install(funchook, 0));
	InstalledHookMap.Add(SymbolId, *OutTrampolineFunction);
	return true;
}

FString HookVirtualFunction(void* ConstructorAddress, void* HookFunctionAddress, void** OutTrampolineFunction, const MemberFunctionPointerInfo& SearchInfo) {
	if (!InstalledConstructorThunks.Contains(ConstructorAddress)) {
		//No hook installed on this constructor, install one and populate map
		const ConstructorHookThunk NewThunk = SML::GetBootstrapperAccessors().CreateConstructorHookThunk();
		const FString ConstructorSymbolId = FString::Printf(TEXT("ConstructorThunk_%llu"), (uint64_t) ConstructorAddress);
		HookStandardFunction(ConstructorSymbolId, ConstructorAddress, NewThunk.GeneratedThunkAddress, NewThunk.OutTrampolineAddress);
		InstalledConstructorThunks.Add(ConstructorAddress, ConstructorHookInfoHolder{NewThunk});
		SML::Logging::info(*FString::Printf(TEXT("Installed constructor thunk on constructor at %llu"), (uint64_t) ConstructorAddress));
	}
	
	ConstructorHookInfoHolder& InfoHolder = InstalledConstructorThunks.FindChecked(ConstructorAddress);
	const MemberFunctionPointerDigestInfo DigestInfo = SML::GetBootstrapperAccessors().DigestMemberFunctionPointer(SearchInfo);
	FString SymbolId = FString::Printf(TEXT("VirtualFunction_Constructor_%llu_Offset_%s"), (uint64) ConstructorAddress, DigestInfo.UniqueName.String);
	DigestInfo.UniqueName.Free();

	if (!DigestInfo.bIsVirtualFunctionPointer) {
		SML::Logging::fatal(*FString::Printf(TEXT("Hooking symbol %s failed: Provided member function pointer does not point to valid virtual function call thunk"), *SymbolId));
	}
	if (!InfoHolder.AlreadyHookedFunctions.Contains(SymbolId)) {
		//Function is not hooked yet, add constructor hook to thunk
		VirtualFunctionHookInfo VirtualFunctionHookInfo;
		VirtualFunctionHookInfo.PointerInfo = SearchInfo;
		VirtualFunctionHookInfo.FunctionToCallInstead = HookFunctionAddress;
		VirtualFunctionHookInfo.OutOriginalFunctionPtr = OutTrampolineFunction;
		SML::GetBootstrapperAccessors().AddConstructorHook(InfoHolder.ConstructorHookThunk, VirtualFunctionHookInfo);
		SML::Logging::info(TEXT("Hooking virtual function for constructor at "), ConstructorAddress, TEXT(" with name "), *SymbolId, TEXT(", Member Function Pointer Size: "), SearchInfo.MemberFunctionPointerSize);
		InfoHolder.AlreadyHookedFunctions.Add(SymbolId);
	}
	return SymbolId;
}

SML_API FString RegisterVirtualHookFunction(const VirtualFunctionOverrideInfo& SearchInfo, void* HookFunctionPointer, void** OutTrampolineFunction) {
	const FString& SymbolSearchName = SearchInfo.SymbolSearchName;
	//Class Name: Namespace::Class
	const FString& ClassName = SearchInfo.ClassTypeName;
	int32 LastDoubleColonIndex = INDEX_NONE;
	ClassName.FindLastChar(':', LastDoubleColonIndex);
	//Function Name: Class
	const FString ConstructorFunctionName = LastDoubleColonIndex == INDEX_NONE ? ClassName : ClassName.Mid(LastDoubleColonIndex + 1);
	//ExampleNamespace::AFGPlayerController::AFGPlayerController
	const FString ConstructorName = FString::Printf(TEXT("%s::%s"), *ClassName, *ConstructorFunctionName);
	//Resolve constructor symbol
	SML::Logging::info(*FString::Printf(TEXT("Hooking virtual function %s of class %s"), *SearchInfo.SymbolSearchName, *SearchInfo.ClassTypeName));
	const SymbolDigestInfo DigestInfo = SML::GetBootstrapperAccessors().DigestGameSymbol(*ConstructorName);
	if (DigestInfo.bSymbolNotFound || DigestInfo.bSymbolOptimizedAway) {
		SML::Logging::fatal(*FString::Printf(TEXT("Hooking virtual function symbol %s failed: class constructor %s not found in executable"), *SymbolSearchName, *ConstructorName));
	}
	if (DigestInfo.bMultipleSymbolsMatch) {
		SML::Logging::fatal(*FString::Printf(TEXT("Hooking symbol %s failed: Multiple constructors found. This is not supported for now"), *SymbolSearchName));
	}
	const MemberFunctionPointerInfo PointerInfo{SearchInfo.MemberFunctionPtr, SearchInfo.MemberFunctionPtrSize};
	const FString SymbolId = HookVirtualFunction(DigestInfo.SymbolImplementationPointer, HookFunctionPointer, OutTrampolineFunction, PointerInfo);
	SML::Logging::info(*FString::Printf(TEXT("Successfully hooked virtual function %s with constructor %s"), *SymbolSearchName, *ConstructorName));
	DigestInfo.SymbolName.Free();
	return SymbolId;
}

SML_API FString RegisterHookFunction(const FString& SymbolSearchName, void* HookFunctionPointer, void** OutTrampolineFunction) {
	const SymbolDigestInfo DigestInfo = SML::GetBootstrapperAccessors().DigestGameSymbol(*SymbolSearchName);
	SML::Logging::info(*FString::Printf(TEXT("Hooking symbol with search name %s"), *SymbolSearchName));
	if (DigestInfo.bSymbolNotFound) {
		SML::Logging::fatal(*FString::Printf(TEXT("Hooking symbol %s failed: symbol not found in game executable"), *SymbolSearchName));
	}
	if (DigestInfo.bSymbolOptimizedAway) {
		SML::Logging::fatal(*FString::Printf(TEXT("Hooking symbol %s failed: Symbol is not present in game executable as it was optimized away (inlined/stripped)"), *SymbolSearchName));
	}
	if (DigestInfo.bMultipleSymbolsMatch) {
		SML::Logging::fatal(*FString::Printf(TEXT("Hooking symbol %s failed: Multiple symbols matching that name found. Please use exact decorated name with MANUAL macros instead"), *SymbolSearchName));
	}
	FString SymbolId = DigestInfo.SymbolName.String;
	if (DigestInfo.bSymbolVirtual) {
		//Warn about hooking virtual function implementation without using SUBSCRIBE_VIRTUAL_METHOD
		SML::Logging::warning(*FString::Printf(TEXT("Warning: Hooking virtual function implementation with SUBSCRIBE_METHOD macro. You are hooking it for all classes who don't specifically have overrides, so be very careful with it. Use SUBSCRIBE_VIRTUAL_METHOD for more wise control and ability to override virtual function for exact class directly. Function: %s"), *SymbolSearchName));
	}
	HookStandardFunction(SymbolId, DigestInfo.SymbolImplementationPointer, HookFunctionPointer, OutTrampolineFunction);
	SML::Logging::info(*FString::Printf(TEXT("Successfully hooked normal function %s"), *SymbolId));
	DigestInfo.SymbolName.Free();
	return SymbolId;
}


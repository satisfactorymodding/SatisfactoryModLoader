#include "Patching/NativeHookManager.h"
#include "CoreMinimal.h"
#include "funchook.h"
#include "AssemblyAnalyzer.h"

DEFINE_LOG_CATEGORY(LogNativeHookManager);

//since templates are actually compiled for each module separately,
//we need to have a global handler map which will be shared by all hook invoker templates available in all modules
//to keep single hook instance for each method
static TMap<void*, void*> RegisteredListenerMap;

//Map of the function implementation pointer to the trampoline function pointer. Used to ensure one hook per function installed
static TMap<void*, void*> InstalledHookMap;

//Store the funchook instance used to hook each function
static TMap<void*, funchook_t*> FunchookMap;

void* FNativeHookManagerInternal::GetHandlerListInternal( const void* RealFunctionAddress ) {
	void** ExistingMapEntry = RegisteredListenerMap.Find(RealFunctionAddress);
	return ExistingMapEntry ? *ExistingMapEntry : nullptr;
}

void FNativeHookManagerInternal::SetHandlerListInstanceInternal(void* RealFunctionAddress, void* HandlerList)
{
	if ( HandlerList == nullptr )
	{
		RegisteredListenerMap.Remove( RealFunctionAddress );
	}
	else
	{
		RegisteredListenerMap.Add(RealFunctionAddress, HandlerList);
	}
}

#define CHECK_FUNCHOOK_ERR(arg) \
	if (arg != FUNCHOOK_ERROR_SUCCESS) UE_LOG(LogNativeHookManager, Fatal, TEXT("Hooking function %s failed: funchook failed: %hs"), *DebugSymbolName, funchook_error_message(funchook));

void LogDebugAssemblyAnalyzer(const ANSICHAR* Message) {
	UE_LOG(LogNativeHookManager, Display, TEXT("AssemblyAnalyzer Debug: %hs"), Message);
}

// Installs a hook a the original function. Returns true if a new hook is installed or false on error or
// a hook already exists and is reused.
bool HookStandardFunction(const FString& DebugSymbolName, void* OriginalFunctionPointer, void* HookFunctionPointer, void** OutTrampolineFunction) {
	if (InstalledHookMap.Contains(OriginalFunctionPointer)) {
		//Hook already installed, set trampoline function and return
		*OutTrampolineFunction = InstalledHookMap.FindChecked(OriginalFunctionPointer);
		UE_LOG(LogNativeHookManager, Display, TEXT("Hook already installed"));
		return false;
	}
	funchook* funchook = funchook_create();
	if (funchook == nullptr) {
		UE_LOG(LogNativeHookManager, Fatal, TEXT("Hooking function %s failed: funchook_create() returned NULL"), *DebugSymbolName);
		return false;
	}
	*OutTrampolineFunction = OriginalFunctionPointer;

	UE_LOG(LogNativeHookManager, Display, TEXT("Overriding %s at %p to %p"), *DebugSymbolName, OriginalFunctionPointer, HookFunctionPointer);

	CHECK_FUNCHOOK_ERR(funchook_prepare(funchook, OutTrampolineFunction, HookFunctionPointer));
	CHECK_FUNCHOOK_ERR(funchook_install(funchook, 0));
	InstalledHookMap.Add(OriginalFunctionPointer, *OutTrampolineFunction);
	FunchookMap.Add(OriginalFunctionPointer, funchook);
	return true;
}

// This method is provided for backwards-compatibility
SML_API void* FNativeHookManagerInternal::RegisterHookFunction(const FString& DebugSymbolName, void* OriginalFunctionPointer, const void* SampleObjectInstance, int ThisAdjustment, void* HookFunctionPointer, void** OutTrampolineFunction) {
	// Previous SML versions only supported Windows mods, which have no Vtable adjustment information
	// in the member function pointer, so we set that value to zero.
	FMemberFunctionPointer MemberFunctionPointer = {OriginalFunctionPointer, static_cast<uint32>(ThisAdjustment), 0};
	return FNativeHookManagerInternal::RegisterHookFunction(DebugSymbolName, MemberFunctionPointer, SampleObjectInstance, HookFunctionPointer, OutTrampolineFunction);
}

SML_API void* FNativeHookManagerInternal::RegisterHookFunction(const FString& DebugSymbolName, FMemberFunctionPointer MemberFunctionPointer, const void* SampleObjectInstance, void* HookFunctionPointer, void** OutTrampolineFunction) {
	SetDebugLoggingHook(&LogDebugAssemblyAnalyzer);

#ifdef _WIN64
	// On Windows, the OriginalFunctionPointer is a valid function pointer. We can simply check its info here.
	UE_LOG(LogNativeHookManager, Display, TEXT("Attempting to discover %s at %p"), *DebugSymbolName, MemberFunctionPointer.FunctionAddress);
	FunctionInfo FunctionInfo = DiscoverFunction((uint8 *)MemberFunctionPointer.FunctionAddress);
	checkf(FunctionInfo.bIsValid, TEXT("Attempt to hook invalid function %s: Provided code pointer %p is not valid"), *DebugSymbolName, MemberFunctionPointer.FunctionAddress);

	// We assign the vtable offset from the FunctionInfo struct whether we found a vtable offset or not. If the
	// method isn't virtual, this value isn't used.
	MemberFunctionPointer.VtableDisplacement = FunctionInfo.VirtualTableFunctionOffset;
	bool isVirtual = FunctionInfo.bIsVirtualFunction;
#else
	// On Linux, MemberFunctionPointer.FunctionAddress will not be a valid pointer if the method is virtual. See ConvertFunctionPointer
	// for more info.
	FunctionInfo FunctionInfo;

	bool isVirtual = (MemberFunctionPointer.FunctionAddress == nullptr);

	if (!isVirtual) {
		FunctionInfo = DiscoverFunction((uint8*) MemberFunctionPointer.FunctionAddress);
	}
#endif

	if (isVirtual) {
		// The patched call is virtual. Calculate the actual address of the function being called.
		checkf(SampleObjectInstance, TEXT("Attempt to hook virtual function override without providing object instance for implementation resolution"));
		UE_LOG(LogNativeHookManager, Display, TEXT("Attempting to resolve virtual function %s. This adjustment: 0x%x, virtual function table offset: 0x%x"), *DebugSymbolName, MemberFunctionPointer.ThisAdjustment, MemberFunctionPointer.VtableDisplacement);
		
		//Target Function Address = (this + ThisAdjustment)->vftable[VirtualFunctionOffset]
		void* AdjustedThisPointer = ((uint8*) SampleObjectInstance) + MemberFunctionPointer.ThisAdjustment;
		uint8** VirtualFunctionTableBase = *((uint8***) AdjustedThisPointer);
		//Offset is in bytes from the start of the virtual table, we need to convert it to pointer array index
		uint8* FunctionImplementationPointer = VirtualFunctionTableBase[MemberFunctionPointer.VtableDisplacement / 8];

		FunctionInfo = DiscoverFunction(FunctionImplementationPointer);

		//Perform basic checking to make sure calculation was correct, or at least seems to be so
		checkf(FunctionInfo.bIsValid, TEXT("Failed to resolve virtual function for thunk %s at %p, resulting address contains no executable code"), *DebugSymbolName, MemberFunctionPointer.FunctionAddress);
		checkf(!FunctionInfo.bIsVirtualFunction, TEXT("Failed to resolve virtual function for thunk %s at %p, resulting function still points to a thunk"), *DebugSymbolName, MemberFunctionPointer.FunctionAddress);

		UE_LOG(LogNativeHookManager, Display, TEXT("Successfully resolved virtual function thunk %s at %p to function implementation at %p"), *DebugSymbolName, MemberFunctionPointer.FunctionAddress, FunctionInfo.RealFunctionAddress);
	}

	//Log debugging information just in case
	void* ResolvedHookingFunctionPointer = FunctionInfo.RealFunctionAddress;
	UE_LOG(LogNativeHookManager, Display, TEXT("Hooking function %s: Provided address: %p, resolved address: %p"), *DebugSymbolName, MemberFunctionPointer.FunctionAddress, ResolvedHookingFunctionPointer);
	
	HookStandardFunction(DebugSymbolName, ResolvedHookingFunctionPointer, HookFunctionPointer, OutTrampolineFunction);
	UE_LOG(LogNativeHookManager, Display, TEXT("Successfully hooked function %s at %p"), *DebugSymbolName, ResolvedHookingFunctionPointer);
	return ResolvedHookingFunctionPointer;
}

void FNativeHookManagerInternal::UnregisterHookFunction(const FString& DebugSymbolName, const void* RealFunctionAddress) {
	funchook_t** funchookPtr = FunchookMap.Find(RealFunctionAddress);
	if (funchookPtr == nullptr) {
		UE_LOG(LogNativeHookManager, Warning, TEXT("Attempt to unregister hook for function %s at %p which was not registered"), *DebugSymbolName, RealFunctionAddress);
		return;
	}
	funchook_t* funchook = *funchookPtr;
	CHECK_FUNCHOOK_ERR(funchook_uninstall(funchook, 0));
	CHECK_FUNCHOOK_ERR(funchook_destroy(funchook));
	FunchookMap.Remove(RealFunctionAddress);
	InstalledHookMap.Remove(RealFunctionAddress);
	UE_LOG(LogNativeHookManager, Display, TEXT("Successfully unregistered hook for function %s at %p"), *DebugSymbolName, RealFunctionAddress);
}

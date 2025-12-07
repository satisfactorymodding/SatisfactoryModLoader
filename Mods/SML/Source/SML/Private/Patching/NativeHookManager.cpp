#include "Patching/NativeHookManager.h"
#include "CoreMinimal.h"
#include "funchook.h"
#include "AssemblyAnalyzer.h"
#include "HAL/PlatformMemory.h"

DEFINE_LOG_CATEGORY(LogNativeHookManager);

namespace
{
	struct FStandardHook
	{
		void* Trampoline;
		funchook* FuncHook;
	};
}

//since templates are actually compiled for each module separately,
//we need to have a global handler map which will be shared by all hook invoker templates available in all modules
//to keep single hook instance for each method
static TMap<void*, void*> HandlerListMap;
static TMap<const void* /* RealFunctionAddress */, FStandardHook> StandardHookMap;
static TMap<void** /* VtableEntry */, void* /* OriginalFunction */> VtableHookMap;
static TMap<UFunction*, FNativeFuncPtr /* OriginalFunction */> UFunctionHookMap;

void* FNativeHookManagerInternal::GetHandlerListInternal(const void* Key)
{
	void** ExistingMapEntry = HandlerListMap.Find(Key);
	return ExistingMapEntry ? *ExistingMapEntry : nullptr;
}

void FNativeHookManagerInternal::SetHandlerListInstanceInternal(void* Key, void* HandlerList)
{
	if (HandlerList == nullptr)
	{
		HandlerListMap.Remove(Key);
	}
	else
	{
		HandlerListMap.Add(Key, HandlerList);
	}
}

#define CHECK_FUNCHOOK_ERR(arg) \
	if (arg != FUNCHOOK_ERROR_SUCCESS) UE_LOG(LogNativeHookManager, Fatal, TEXT("Hooking function %s failed: funchook failed: %hs"), *DebugSymbolName, funchook_error_message(funchook));

static void LogDebugAssemblyAnalyzer(const ANSICHAR* Message) {
	UE_LOG(LogNativeHookManager, Display, TEXT("AssemblyAnalyzer Debug: %hs"), Message);
}

static FunctionInfo DiscoverMemberFunction(const FString& DebugSymbolName, FMemberFunctionPointer& MemberFunctionPointer) {
	SetDebugLoggingHook(&LogDebugAssemblyAnalyzer);

#ifndef _WIN64
	// On Linux, MemberFunctionPointer.FunctionAddress will not be a valid pointer if the method is virtual.
	// See ConvertFunctionPointer for more info.
	if (MemberFunctionPointer.FunctionAddress == nullptr) {
		return {
			.bIsValid = true,
			.bIsVirtualFunction = true,
			.RealFunctionAddress = nullptr,
			.VirtualTableFunctionOffset = MemberFunctionPointer.VtableDisplacement,
		};
	}
#endif

	// We should now always have a valid FunctionAddress in MemberFunctionPointer:
	//   * On Windows, all functions (virtual and non-virtual) have a valid address.
	//   * On Linux, only virtual functions don't and they have already been handled above.

	UE_LOG(LogNativeHookManager, Display, TEXT("Attempting to discover %s at %p"), *DebugSymbolName, MemberFunctionPointer.FunctionAddress);
	FunctionInfo FunctionInfo = DiscoverFunction((uint8*)MemberFunctionPointer.FunctionAddress);
	checkf(FunctionInfo.bIsValid, TEXT("Attempt to hook invalid function %s: Provided code pointer %p is not valid"), *DebugSymbolName, MemberFunctionPointer.FunctionAddress);

#ifdef _WIN64
	// We assign the vtable offset from the FunctionInfo struct whether we found a vtable offset or not. If the
	// method isn't virtual, this value isn't used.
	MemberFunctionPointer.VtableDisplacement = FunctionInfo.VirtualTableFunctionOffset;
#else
	// Just in case DiscoverFunction identifies a non-virtual function as a vtable thunk...
	FunctionInfo.bIsVirtualFunction = false;
#endif

	return FunctionInfo;
}

static void** GetVtableEntry(const FMemberFunctionPointer& MemberFunctionPointer, const void* SampleObjectInstance) {
	// Target Function Address = (this + ThisAdjustment)->vftable[VirtualFunctionOffset]
	void* AdjustedThisPointer = (uint8*)SampleObjectInstance + MemberFunctionPointer.ThisAdjustment;
	void* VirtualFunctionTableBase = *(void**)AdjustedThisPointer;
	return (void**)((uint8*)VirtualFunctionTableBase + MemberFunctionPointer.VtableDisplacement);
}

// Installs a hook a the original function. Returns true if a new hook is installed or false on error or
// a hook already exists and is reused.
static bool HookStandardFunction(const FString& DebugSymbolName, void* OriginalFunctionPointer, void* HookFunctionPointer, void** OutTrampolineFunction) {
	if (const FStandardHook* StandardHook = StandardHookMap.Find(OriginalFunctionPointer)) {
		//Hook already installed, set trampoline function and return
		*OutTrampolineFunction = StandardHook->Trampoline;
		UE_LOG(LogNativeHookManager, Display, TEXT("Hook already installed"));
		return false;
	}

	funchook* funchook = funchook_create();
	if (funchook == nullptr) {
		UE_LOG(LogNativeHookManager, Fatal, TEXT("Hooking function %s failed: funchook_create() returned NULL"), *DebugSymbolName);
		return false;
	}

	UE_LOG(LogNativeHookManager, Display, TEXT("Overriding %s at %p to %p"), *DebugSymbolName, OriginalFunctionPointer, HookFunctionPointer);
	*OutTrampolineFunction = OriginalFunctionPointer;
	CHECK_FUNCHOOK_ERR(funchook_prepare(funchook, OutTrampolineFunction, HookFunctionPointer));
	CHECK_FUNCHOOK_ERR(funchook_install(funchook, 0));
	StandardHookMap.Add(OriginalFunctionPointer, FStandardHook{*OutTrampolineFunction, funchook});

	return true;
}

// This method is provided for backwards-compatibility
void* FNativeHookManagerInternal::RegisterHookFunction(const FString& DebugSymbolName, void* OriginalFunctionPointer, const void* SampleObjectInstance, int ThisAdjustment, void* HookFunctionPointer, void** OutTrampolineFunction) {
	// Previous SML versions only supported Windows mods, which have no Vtable adjustment information
	// in the member function pointer, so we set that value to zero.
	FMemberFunctionPointer MemberFunctionPointer = {OriginalFunctionPointer, static_cast<uint32>(ThisAdjustment), 0};
	return FNativeHookManagerInternal::RegisterHookFunction(DebugSymbolName, MemberFunctionPointer, SampleObjectInstance, HookFunctionPointer, OutTrampolineFunction);
}

void* FNativeHookManagerInternal::RegisterHookFunction(const FString& DebugSymbolName, FMemberFunctionPointer MemberFunctionPointer, const void* SampleObjectInstance, void* HookFunctionPointer, void** OutTrampolineFunction) {
	FunctionInfo FunctionInfo = DiscoverMemberFunction(DebugSymbolName, MemberFunctionPointer);

	if (FunctionInfo.bIsVirtualFunction) {
		// The patched call is virtual. Calculate the actual address of the function being called.
		checkf(SampleObjectInstance, TEXT("Attempt to hook virtual function override without providing object instance for implementation resolution"));
		UE_LOG(LogNativeHookManager, Display, TEXT("Attempting to resolve virtual function %s. This adjustment: 0x%x, virtual function table offset: 0x%x"), *DebugSymbolName, MemberFunctionPointer.ThisAdjustment, MemberFunctionPointer.VtableDisplacement);

		void* FunctionImplementationPointer = *GetVtableEntry(MemberFunctionPointer, SampleObjectInstance);
		FunctionInfo = DiscoverFunction((uint8*)FunctionImplementationPointer);

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
	FStandardHook StandardHook;
	if (!StandardHookMap.RemoveAndCopyValue(RealFunctionAddress, StandardHook)) {
		UE_LOG(LogNativeHookManager, Warning, TEXT("Attempt to unregister hook for function %s at %p which was not registered"), *DebugSymbolName, RealFunctionAddress);
		return;
	}
	funchook_t* funchook = StandardHook.FuncHook;
	CHECK_FUNCHOOK_ERR(funchook_uninstall(funchook, 0));
	CHECK_FUNCHOOK_ERR(funchook_destroy(funchook));
	UE_LOG(LogNativeHookManager, Display, TEXT("Successfully unregistered hook for function %s at %p"), *DebugSymbolName, RealFunctionAddress);
}

static void SetVtableEntry(const FString& DebugSymbolName, void** VtableEntry, void* NewValue)
{
	// FPlatformMemory doesn't seem to have a way to get the old page protections back, but it's a good
	// bet that it was a read-only page.

	const size_t PageSize = FPlatformMemory::GetConstants().PageSize;
	void* PageStart = AlignDown(VtableEntry, PageSize);

	verifyf(FPlatformMemory::PageProtect(PageStart, PageSize, true, true),
		TEXT("Failed to un-protect vtable entry for function %s at %p"), *DebugSymbolName, VtableEntry);

	*VtableEntry = NewValue;

	verifyf(FPlatformMemory::PageProtect(PageStart, PageSize, true, false),
		TEXT("Failed to re-protect vtable entry for function %s at %p"), *DebugSymbolName, VtableEntry);
}

void** FNativeHookManagerInternal::RegisterVtableHook(const FString& DebugSymbolName, FMemberFunctionPointer MemberFunctionPointer, const void* SampleObjectInstance, void* HookFunctionPointer, void** OutOriginalFunction)
{
	const FunctionInfo FunctionInfo = DiscoverMemberFunction(DebugSymbolName, MemberFunctionPointer);
	checkf(FunctionInfo.bIsVirtualFunction, TEXT("Attempt to hook non-virtual function %s"), *DebugSymbolName);
	void** VtableEntry = GetVtableEntry(MemberFunctionPointer, SampleObjectInstance);
	void*& MapOriginalFunction = VtableHookMap.FindOrAdd(VtableEntry);

	if (MapOriginalFunction == nullptr)
	{
		MapOriginalFunction = *VtableEntry;
		SetVtableEntry(DebugSymbolName, VtableEntry, HookFunctionPointer);
		UE_LOG(LogNativeHookManager, Display, TEXT("Successfully hooked vtable entry for %s at %p"), *DebugSymbolName, VtableEntry);
	}

	*OutOriginalFunction = MapOriginalFunction;
	return VtableEntry;
}

void FNativeHookManagerInternal::UnregisterVtableHook(const FString& DebugSymbolName, void** VtableEntry)
{
	void* OriginalFunction;

	if (!VtableHookMap.RemoveAndCopyValue(VtableEntry, OriginalFunction))
	{
		UE_LOG(LogNativeHookManager, Warning, TEXT("Attempt to unregister vtable hook for %s at %p which was not registered"), *DebugSymbolName, VtableEntry);
		return;
	}

	SetVtableEntry(DebugSymbolName, VtableEntry, OriginalFunction);
	UE_LOG(LogNativeHookManager, Display, TEXT("Successfully unregistered vtable hook for %s at %p"), *DebugSymbolName, VtableEntry);
}

UFunction* FNativeHookManagerInternal::RegisterUFunctionHook(UClass* Class, FName FunctionName, FNativeFuncPtr HookFunctionPointer, FNativeFuncPtr* OutOriginalFunction)
{
	TStringBuilder<1024> DebugSymbolName;
	Class->GetFName().AppendString(DebugSymbolName);
	DebugSymbolName << TEXT("::");
	FunctionName.AppendString(DebugSymbolName);

	UFunction* Function = Class->FindFunctionByName(FunctionName);
	checkf(Function, TEXT("Failed to find UFunction %s"), *DebugSymbolName);
	FNativeFuncPtr& MapOriginalFunction = UFunctionHookMap.FindOrAdd(Function);

	if (MapOriginalFunction == nullptr)
	{
		MapOriginalFunction = Function->GetNativeFunc();
		Function->SetNativeFunc(HookFunctionPointer);
		UE_LOG(LogNativeHookManager, Display, TEXT("Successfully hooked UFunction %s (%p)"), *DebugSymbolName, Function);
	}

	*OutOriginalFunction = MapOriginalFunction;
	return Function;
}

void FNativeHookManagerInternal::UnregisterUFunctionHook(const FString& DebugSymbolName, UFunction* Function)
{
	FNativeFuncPtr OriginalFunction;

	if (!UFunctionHookMap.RemoveAndCopyValue(Function, OriginalFunction))
	{
		UE_LOG(LogNativeHookManager, Warning, TEXT("Attempt to unregister UFunction hook for %s which is not registered"), *DebugSymbolName);
		return;
	}

	Function->SetNativeFunc(OriginalFunction);
	UE_LOG(LogNativeHookManager, Display, TEXT("Successfully unregistered UFunction hook %s"), *DebugSymbolName);
}

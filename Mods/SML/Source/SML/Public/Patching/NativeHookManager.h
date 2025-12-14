#pragma once
#include "CoreMinimal.h"
#include "Reflection/FunctionThunkGenerator.h"
#include "Traits/MemberFunctionPtrOuter.h"
#include <concepts>
#include <type_traits>

SML_API DECLARE_LOG_CATEGORY_EXTERN(LogNativeHookManager, Log, Log);

//NOTE: This struct does not actually fully represent member function pointer even on MSVC,
//because it does not contain additional information for handling unknown inheritance
//Besides, MSVC layout for "unknown inheritance" and "virtual inheritance" is different
//See https://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible
//So yeah, casting function pointer to this struct is not really safe on other compilers, and even on MSVC
//But we're not really trying to support unknown inheritance, so it's fine.
struct FMemberFunctionPointer {
	void* FunctionAddress;
	uint32 ThisAdjustment;
	uint32 VtableDisplacement;
};

struct FLinuxMemberFunctionPointer {
	union {
		void *FunctionAddress; // For non-virtual members
		ptrdiff_t VtableDisplacementPlusOne; // For virtual members
		intptr_t IntPtr; // For determining whether this is virtual or not.
	};
	ptrdiff_t ThisAdjustment;
};

template<typename Ret, typename... Args>
FORCEINLINE FMemberFunctionPointer ConvertFunctionPointer(Ret(*SourcePointer)(Args...)) {
	// Non-member function pointer is just an address.
	return FMemberFunctionPointer
	{
		.FunctionAddress = (void*)SourcePointer,
	};
}

template<typename T>
FORCEINLINE FMemberFunctionPointer ConvertFunctionPointer(const T& SourcePointer) {
	static_assert(std::is_member_function_pointer_v<T>);
	const SIZE_T FunctionPointerSize = sizeof(SourcePointer);

#ifdef _WIN64
	//We only support non-virtual inheritance, so assert on virtual inheritance and unknown inheritance cases
	//Note that it might also mean that we are dealing with "proper" compiler with static function pointer size
	//(e.g anything different from Intel C++ and MSVC)
	checkf(FunctionPointerSize == 8 || FunctionPointerSize == 16, TEXT("Unsupported function pointer size received: \
		Hooking can only support non-virtual multiple inheritence. \
		This might be also caused by unsupported compiler. Currently, only MSVC and Intel C++ are supported on Windows. \
		Function pointer size: %d bytes."), FunctionPointerSize);

	const FMemberFunctionPointer* RawFunctionPointer = (const FMemberFunctionPointer*)&SourcePointer;
#else
	checkf(FunctionPointerSize == sizeof(FLinuxMemberFunctionPointer), TEXT("Unsupported function pointer size received: %d bytes, expected %d bytes."), FunctionPointerSize, sizeof(FLinuxMemberFunctionPointer));
	const FLinuxMemberFunctionPointer* RawFunctionPointer = (const FLinuxMemberFunctionPointer*)&SourcePointer;
#endif

	UE_LOG(LogNativeHookManager, Display, TEXT("Size of member pointer is %d"), FunctionPointerSize);

	//TODO we  cannot really make sure there is no virtual inheritance involved, so we just assume it for now
	FMemberFunctionPointer ResultPointer{};
#ifdef _WIN64
	ResultPointer.FunctionAddress = RawFunctionPointer->FunctionAddress;
	if (FunctionPointerSize >= 16) {
		ResultPointer.ThisAdjustment = RawFunctionPointer->ThisAdjustment;
		// The vtable displacement here is only valid if the method is NOT virtual. If the method IS virtual,
		// the vtable offset will be found in the thunk. See DiscoverMemberFunction().
		ResultPointer.VtableDisplacement = RawFunctionPointer->VtableDisplacement;
	} else {
		// The function pointer contains no information about a `this` adjustment or the vtable displacement.
		// We can conclude that there is no `this` adjustment, but the vtable index MUST be calculated from
		// the thunk at FunctionAddress. We set an intentionally bad value here to make that easier to identify.
		ResultPointer.ThisAdjustment = 0;
		ResultPointer.VtableDisplacement = 0xDEADBEEF;
	}
#else
	// On Linux, the first word is either the function pointer itself or the vtable offset in bytes depending on
	// whether the function is virtual or not. I don't think we can depend on the usage of this function to
	// determine whether the method is virtual or not. Instead, I assert that the vtable offset will be word-aligned,
	// as will any function pointer. However, the first word on Linux is the vtable offset PLUS ONE, meaning the
	// bottom 3 bits must be 0b001 for a virtual function and 0b000 for a direct pointer.
	if ((RawFunctionPointer->IntPtr & 0x7) == 1) {
		//UE_LOG(LogNativeHookManager, Display, TEXT("Member pointer looks like a Vtable offset: 0x%08x."), RawFunctionPointer->IntPtr);

		// We mark this method as virtual by leaving the original function pointer null. This works in concert with
		// DiscoverMemberFunction().
		ResultPointer.VtableDisplacement = RawFunctionPointer->VtableDisplacementPlusOne - 1;
	} else if ((RawFunctionPointer->IntPtr & 0x7) == 0) {
		//UE_LOG(LogNativeHookManager, Display, TEXT("Member pointer looks like a function pointer: 0x%08x"), RawFunctionPointer->IntPtr);

		ResultPointer.FunctionAddress = RawFunctionPointer->FunctionAddress;
	} else {
		UE_LOG(LogNativeHookManager, Fatal, TEXT("Unwilling to convert unaligned method pointer 0x%08x"), RawFunctionPointer->IntPtr);
	}

	// The offset to 'this' always has the same definition, whether this is a virtual method or not.
	ResultPointer.ThisAdjustment = RawFunctionPointer->ThisAdjustment;
#endif

	return ResultPointer;
}

class SML_API FNativeHookManagerInternal {
public:
	static void* GetHandlerListInternal(const void* Key);
	static void SetHandlerListInstanceInternal(void* Key, void* HandlerList);
	static void* RegisterHookFunction(const TCHAR* DebugSymbolName, FMemberFunctionPointer MemberFunctionPointer, const void* SampleObjectInstance,
	                                  void* HookFunctionPointer, void** OutTrampolineFunction);
	static void UnregisterHookFunction(const TCHAR* DebugSymbolName, const void* RealFunctionAddress);
	static void** RegisterVtableHook(const TCHAR* DebugSymbolName, FMemberFunctionPointer MemberFunctionPointer, const void* SampleObjectInstance,
	                                 void* HookFunctionPointer, void** OutOriginalFunction);
	static void UnregisterVtableHook(const TCHAR* DebugSymbolName, void** VtableEntry);
	static UFunction* RegisterUFunctionHook(const TCHAR* DebugSymbolName, UClass* Class, FName FunctionName,
	                                        FNativeFuncPtr HookFunctionPointer, FNativeFuncPtr* OutOriginalFunction);
	static void UnregisterUFunctionHook(const TCHAR* DebugSymbolName, UFunction* Function);

	// Calls to these functions are inlined in mods, keep them for backwards compatibility.
	static void* RegisterHookFunction(const FString& DebugSymbolName, void* OriginalFunctionPointer, const void* SampleObjectInstance, int ThisAdjustment, void* HookFunctionPointer, void** OutTrampolineFunction);
	static void* RegisterHookFunction(const FString& DebugSymbolName, FMemberFunctionPointer MemberFunctionPointer, const void* SampleObjectInstance, void* HookFunctionPointer, void** OutTrampolineFunction);
};

template <typename T, typename E>
struct THandlerLists {
	TArray<TSharedPtr<T>> HandlersBefore;
	TArray<TSharedPtr<E>> HandlersAfter;
	TMap<FDelegateHandle, TSharedPtr<T>> HandlerBeforeReferences;
	TMap<FDelegateHandle, TSharedPtr<E>> HandlerAfterReferences;
};

template <typename T, typename E>
static THandlerLists<T, E>* CreateHandlerLists(void* Key)
{
	void* HandlerListRaw = FNativeHookManagerInternal::GetHandlerListInternal(Key);
	if (HandlerListRaw == nullptr) {
		HandlerListRaw = new THandlerLists<T, E>();
		FNativeHookManagerInternal::SetHandlerListInstanceInternal(Key, HandlerListRaw);
	}
	return static_cast<THandlerLists<T, E>*>(HandlerListRaw);
}

template <typename T, typename E>
static void DestroyHandlerLists(void* Key)
{
	void* HandlerListRaw = FNativeHookManagerInternal::GetHandlerListInternal(Key);
	if (HandlerListRaw != nullptr) {
		const THandlerLists<T, E>* CastedHandlerList = static_cast<THandlerLists<T, E>*>(HandlerListRaw);
		delete CastedHandlerList;
		FNativeHookManagerInternal::SetHandlerListInstanceInternal(Key, nullptr);
	}
}

/// Manages handlers and invokes them when the hooked function is called.
/// The actual hooking is delegated to the backend, which can decide how it wants to hook.
/// Variant is an unused parameter that you can change to get a different template instantiation.
template<typename Backend, typename TCallable, typename Variant = void>
struct THookInvoker;

/// Context object that hooks can use to control function execution.
template<typename TCallable>
struct TCallScope;

template<typename ReturnType, typename... ArgTypes>
class TCallScopeBase
{
	template<typename Backend, typename Variant, bool bIsMemberFunction, typename /*ReturnType*/, typename... /*ArgTypes*/>
	friend class THookInvokerBase;

	using DerivedCallScope = TCallScope<ReturnType(*)(ArgTypes...)>;
	static constexpr bool bHasReturnValue = !std::is_void_v<ReturnType>;

public:
	// When the original function has a non-void return value, we store it as a TFunction instead of a
	// regular function pointer so that the caller can abstract away any ABI shenanigans.

	using OrigFuncSignature = ReturnType(ArgTypes...);
	using OrigCallable = std::conditional_t<bHasReturnValue, TFunction<OrigFuncSignature>, OrigFuncSignature*>;
	using HookFuncSignature = void(DerivedCallScope&, ArgTypes...);
	using HookCallable = TFunction<HookFuncSignature>;

	bool ShouldForwardCall() const
	{
		return bForwardCall;
	}

	ReturnType operator()(ArgTypes... Args)
	{
		const ArgsPreprocessor<ArgTypes...> ArgsPreprocessor(*this, Args...);

		if (FunctionList == nullptr || static_cast<size_t>(HandlerIndex) >= FunctionList->Num())
		{
			// Reached the end of the handler list, call the original function.
			if constexpr (bHasReturnValue)
			{
				ResultData = OrigFunc(Args...);
			}
			else
			{
				OrigFunc(Args...);
			}
			bForwardCall = false;
		}
		else
		{
			const uint32 CurrentHandlerIndex = HandlerIndex++;
			const uint32 NextHandlerIndex = HandlerIndex;

			// Call the current handler.
			const TSharedPtr<HookCallable>& Handler = (*FunctionList)[CurrentHandlerIndex];
			(*Handler)(static_cast<DerivedCallScope&>(*this), Args...);

			// If the handler didn't call back into the scope, either by calling the next handler or overriding
			// the result, then we do the next call for it.
			if (HandlerIndex == NextHandlerIndex && bForwardCall)
			{
				(*this)(Args...);
			}
		}

		return static_cast<ReturnType>(ResultData);
	}

protected:
	TCallScopeBase(const TArray<TSharedPtr<HookCallable>>* FunctionList, OrigCallable OrigFunc)
		: FunctionList(FunctionList)
		, OrigFunc(MoveTemp(OrigFunc))
	{
	}

	// We need a new variable to store ThisAdjustment, but we can't change the layout of this class
	// because we need to maintain compatibility with mods that were compiled before this change. We
	// also can't make use of existing padding because that won't necessarily be zero-initialized if an
	// old mod creates the scope. Fortunately there's a really hacky way around this: HandlerIndex was
	// size_t (64-bits) before, but we're obviously not going to have anywhere near that number of
	// handlers, so the upper bits of that variable are always going to be zero. It's now restricted to
	// a 32-bit value, which leaves the upper 32-bits for ThisAdjustment, The hacky thing about this is
	// that we need to make sure that those upper bits are set back to zero whenever we call into old
	// code, as it will be doing full 64-bit operations at that address.
	static_assert(PLATFORM_LITTLE_ENDIAN && sizeof(size_t) == 8,
		"TCallScope changes aren't backwards-compatible on this platform!");

	const TArray<TSharedPtr<HookCallable>>* FunctionList;
	uint32 HandlerIndex = 0;	// Used to be size_t
	uint32 ThisAdjustment = 0;
	OrigCallable OrigFunc;
	bool bForwardCall = true;
	std::conditional_t<bHasReturnValue, std::remove_cv_t<ReturnType>, std::monostate> ResultData{};

private:
	template<typename... /* ArgTypes */>
	struct ArgsPreprocessor
	{
		FORCEINLINE ArgsPreprocessor(const TCallScopeBase& Scope, const ArgTypes&...)
		{
			check(Scope.ThisAdjustment == 0);
		}
	};

	// Pre-processing for the 'this' pointer in member functions.
	// Technically this will also run for non-member functions that have a pointer as their first
	// argument, but in those cases ThisAdjustment will be zero so this won't end up doing anything.
	template<typename Pointee, typename... OtherArgTypes>
	struct ArgsPreprocessor<Pointee*, OtherArgTypes...>
	{
		TCallScopeBase& Scope;
		const uint32_t SavedThisAdjustment;

		FORCEINLINE ArgsPreprocessor(TCallScopeBase& Scope, Pointee*& Ptr, const OtherArgTypes&...)
			: Scope(Scope)
			, SavedThisAdjustment(Scope.ThisAdjustment)
		{
			// Handlers un-apply the ThisAdjustment so that they can have sane pointers for their callbacks, but
			// we need to re-apply it now as we're about to call into unknown code.
			Ptr = reinterpret_cast<Pointee*>(reinterpret_cast<uintptr_t>(Ptr) + SavedThisAdjustment);

			// Reset this to zero so it doesn't confuse old mods trying to use HandlerIndex.
			Scope.ThisAdjustment = 0;
		}

		FORCEINLINE ~ArgsPreprocessor()
		{
			Scope.ThisAdjustment = SavedThisAdjustment;
		}
	};
};

// non-void return
template<typename ReturnType, typename... ArgTypes>
struct TCallScope<ReturnType(*)(ArgTypes...)> : TCallScopeBase<ReturnType, ArgTypes...>
{
	using Base = TCallScopeBase<ReturnType, ArgTypes...>;

	TCallScope(const TArray<TSharedPtr<typename Base::HookCallable>>* FunctionList, Base::OrigCallable OrigFunc)
		: Base(FunctionList, OrigFunc)
	{
	}

	ReturnType GetResult() const
	{
		return this->ResultData;
	}

	void Override(const ReturnType& NewResult)
	{
		this->bForwardCall = false;
		this->ResultData = NewResult;
	}
};

// void return
template<typename ReturnType, typename... ArgTypes> requires std::is_void_v<ReturnType>
struct TCallScope<ReturnType(*)(ArgTypes...)> : TCallScopeBase<ReturnType, ArgTypes...>
{
	using Base = TCallScopeBase<ReturnType, ArgTypes...>;

	TCallScope(const TArray<TSharedPtr<typename Base::HookCallable>>* FunctionList, Base::OrigCallable OrigFunc)
		: Base(FunctionList, OrigFunc)
	{
	}

	void Cancel()
	{
		this->bForwardCall = false;
	}
};

/// Handle returned from hooking functions.
/// If you want to be able to unhook, you should store the handle and call Unsubscribe() when ready.
/// Otherwise you can safely ignore it.
class FNativeHookHandle
{
	template<typename Backend, typename Variant, bool bIsMemberFunction, typename ReturnType, typename... ArgTypes>
	friend class THookInvokerBase;

private:
	// Most people will ignore the return value from hooking functions, as they tend not to care about
	// unsubscribing. If we were to return a real handle then we'd be instantiating the unsubscribing
	// code for everyone, which would cause unecessary code bloat. Instead we return this intermediate
	// type that doesn't actually reference the unsubscribing functions unless a real handle is
	// constructed from it, which means that no one will pay that cost unless they want it. This should
	// be invisible to the user, they should either construct a handle or ignore the result; the
	// existence of this intermediate type is an implementation detail.
	template<typename HookInvoker>
	struct TDelayedInit
	{
		friend FNativeHookHandle;
		friend HookInvoker;

	private:
		TDelayedInit() = default;

		TDelayedInit(FDelegateHandle DelegateHandle, const TCHAR* DebugSymbolName)
			: DelegateHandle(DelegateHandle)
			, DebugSymbolName(DebugSymbolName)
		{
		}

		FDelegateHandle DelegateHandle = {};
		const TCHAR* DebugSymbolName = nullptr;

	public:
		// This function is provided in case someone stores this object directly with `auto` instead of
		// making a real FNativeHookHandle out of it.
		void Unsubscribe()
		{
			if (DelegateHandle.IsValid())
			{
				HookInvoker::RemoveHandler(DelegateHandle, DebugSymbolName);
				*this = {};
			}
		}
	};

public:
	FNativeHookHandle() = default;

	template<typename HookInvoker>
	FNativeHookHandle(TDelayedInit<HookInvoker> Params)
		: RemoveHandler(&HookInvoker::RemoveHandler)
		, DelegateHandle(Params.DelegateHandle)
		, DebugSymbolName(Params.DebugSymbolName)
	{
	}

	void Unsubscribe()
	{
		if (RemoveHandler != nullptr)
		{
			RemoveHandler(DelegateHandle, DebugSymbolName);
			*this = {};
		}
	}

private:
	void(*RemoveHandler)(FDelegateHandle, const TCHAR* DebugSymbolName) = nullptr;
	FDelegateHandle DelegateHandle = {};
	const TCHAR* DebugSymbolName = nullptr;
};

struct FNativeHookResult
{
	/// Value that uniquely identifies this hook, must be the same across all modules. The actual
	/// meaning of the value is up to the backend, it's never interpreted directly and is only used for
	/// comparisons.
	void* Key;

	/// Address of the code that will call the original implementation of the function. This must be an
	/// actual address and not some sort of (member/virtual) function pointer as it will be directly
	/// jumped to.
	void* OriginalFunctionCode;

	/// Offset, in bytes, added to the 'this' pointer before the function was called.
	/// Only relevant for non-static member functions, should be set to zero otherwise.
	ptrdiff_t ThisAdjustment;
};

template<typename TCallable, TCallable OriginalFunction>
struct TStandardHookBackend
{
	// Key = RealFunctionAddress

	static consteval auto GetNullSampleObject()
	{
		// Use a dummy nullptr_t instance on non-member functions to make it compile.
		// The sample object isn't used in that case anyway.
		if constexpr (std::is_member_function_pointer_v<TCallable>)
		{
			return static_cast<const TMemberFunctionPtrOuter_T<TCallable>*>(nullptr);
		}
		else
		{
			return nullptr;
		}
	}

	template<auto HookFunction>
	static FNativeHookResult RegisterHook(const TCHAR* DebugSymbolName, decltype(GetNullSampleObject()) SampleObjectInstance = nullptr)
	{
		FNativeHookResult Result;
		const FMemberFunctionPointer OriginalFunctionData = ConvertFunctionPointer(OriginalFunction);

		Result.Key = FNativeHookManagerInternal::RegisterHookFunction(
			DebugSymbolName,
			OriginalFunctionData,
			SampleObjectInstance,
			(void*)HookFunction,
			&Result.OriginalFunctionCode);
		Result.ThisAdjustment = static_cast<ptrdiff_t>(OriginalFunctionData.ThisAdjustment);

		return Result;
	}

	static void UnregisterHook(const TCHAR* DebugSymbolName, void* RealFunctionAddress)
	{
		FNativeHookManagerInternal::UnregisterHookFunction(DebugSymbolName, RealFunctionAddress);
	}
};

template<typename TCallable, TCallable OriginalFunction>
struct TVtableHookBackend
{
	// Key = VtableEntry

	template<auto HookFunction>
	static FNativeHookResult RegisterHook(const TCHAR* DebugSymbolName, const TMemberFunctionPtrOuter_T<TCallable>* SampleObjectInstance)
	{
		FNativeHookResult Result;
		const FMemberFunctionPointer OriginalFunctionData = ConvertFunctionPointer(OriginalFunction);

		Result.Key = FNativeHookManagerInternal::RegisterVtableHook(
			DebugSymbolName,
			OriginalFunctionData,
			SampleObjectInstance,
			(void*)HookFunction,
			&Result.OriginalFunctionCode);
		Result.ThisAdjustment = static_cast<ptrdiff_t>(OriginalFunctionData.ThisAdjustment);

		return Result;
	}

	static void UnregisterHook(const TCHAR* DebugSymbolName, void* Key)
	{
		auto VtableEntry = static_cast<void**>(Key);
		FNativeHookManagerInternal::UnregisterVtableHook(DebugSymbolName, VtableEntry);
	}
};

template<typename ClassType, auto ImplFunction>
struct TUFunctionHookBackend
{
	// Key = UFunction

	template<auto HookFunction>
	static consteval FNativeFuncPtr WrapHookFunction()
	{
		// Wrap the hook in a UFunction thunk.
		return &TFunctionThunkGenerator<decltype(ImplFunction)>::template Thunk<HookFunction>;
	}

	template<FNativeFuncPtr HookFunction>
	static FNativeHookResult RegisterHook(const TCHAR* DebugSymbolName, FName FunctionName)
	{
		FNativeHookResult Result;

		Result.Key = FNativeHookManagerInternal::RegisterUFunctionHook(
			DebugSymbolName,
			ClassType::StaticClass(),
			FunctionName,
			HookFunction,
			(FNativeFuncPtr*)&Result.OriginalFunctionCode);
		Result.ThisAdjustment = 0;

		return Result;
	}

	static void UnregisterHook(const TCHAR* DebugSymbolName, void* Key)
	{
		auto Function = static_cast<UFunction*>(Key);
		FNativeHookManagerInternal::UnregisterUFunctionHook(DebugSymbolName, Function);
	}
};

template<typename Backend, typename Variant, bool bIsMemberFunction, typename ReturnType, typename... ArgTypes>
class THookInvokerBase
{
	static_assert(!bIsMemberFunction || sizeof...(ArgTypes) >= 1,
		"Member functions must at least have a 'this' pointer!");

	// For non-void return types, the first parameter is the return value.
	template<typename R = ReturnType> struct GetHandlerAfterSignature { using type = void(const R&, ArgTypes...); };
	template<typename R> requires std::is_void_v<R> struct GetHandlerAfterSignature<R> { using type = void(ArgTypes...); };

public:
	using CallableType = ReturnType(ArgTypes...);
	using ScopeType = TCallScope<CallableType*>;
	using HandlerBeforeSignature = void(ScopeType&, ArgTypes...);
	using HandlerAfterSignature = GetHandlerAfterSignature<>::type;
	using HandlerBefore = TFunction<HandlerBeforeSignature>;
	using HandlerAfter = TFunction<HandlerAfterSignature>;

	template<std::convertible_to<HandlerBefore> InHandlerType, typename... BackendArgTypes>
	static auto AddHandlerBefore(InHandlerType&& InHandler, const TCHAR* DebugSymbolName, BackendArgTypes&&... BackendArgs)
	{
		InstallHook(DebugSymbolName, Forward<BackendArgTypes>(BackendArgs)...);
		const FDelegateHandle DelegateHandle = InternalAddHandler(
			WrapHandler<HandlerBefore>(Forward<InHandlerType>(InHandler)),
			*HandlersBefore,
			*HandlerBeforeReferences);
		return FNativeHookHandle::TDelayedInit<THookInvokerBase>(DelegateHandle, DebugSymbolName);
	}

	template<std::convertible_to<HandlerAfter> InHandlerType, typename... BackendArgTypes>
	static auto AddHandlerAfter(InHandlerType&& InHandler, const TCHAR* DebugSymbolName, BackendArgTypes&&... BackendArgs)
	{
		InstallHook(DebugSymbolName, Forward<BackendArgTypes>(BackendArgs)...);
		const FDelegateHandle DelegateHandle = InternalAddHandler(
			WrapHandler<HandlerAfter>(Forward<InHandlerType>(InHandler)),
			*HandlersAfter,
			*HandlerAfterReferences);
		return FNativeHookHandle::TDelayedInit<THookInvokerBase>(DelegateHandle, DebugSymbolName);
	}

	static void RemoveHandler(FDelegateHandle InHandlerHandle, const TCHAR* DebugSymbolName)
	{
		InternalRemoveHandler(InHandlerHandle, *HandlersBefore, *HandlerBeforeReferences);
		InternalRemoveHandler(InHandlerHandle, *HandlersAfter, *HandlerAfterReferences);

		if (HandlersBefore->IsEmpty() && HandlersAfter->IsEmpty())
		{
			// No handlers left, uninstall the hook.
			UninstallHook(DebugSymbolName);
		}
	}

private:
	template<typename HandlerType>
	using HandlersArray = TArray<TSharedPtr<HandlerType>>;
	template<typename HandlerType>
	using HandlersMap = TMap<FDelegateHandle, TSharedPtr<HandlerType>>;

	template<typename... BackendArgTypes>
	static void InstallHook(const TCHAR* DebugSymbolName, BackendArgTypes&&... BackendArgs)
	{
		if (OriginalFunctionCode != nullptr)
			return;	// Already installed.

		constexpr auto HookFunction = GetHookFunction();
		const FNativeHookResult Result = Backend::template RegisterHook<HookFunction>(DebugSymbolName, Forward<BackendArgTypes>(BackendArgs)...);
		auto* HandlerLists = CreateHandlerLists<HandlerBefore, HandlerAfter>(Result.Key);

		HandlersBefore = &HandlerLists->HandlersBefore;
		HandlersAfter = &HandlerLists->HandlersAfter;
		HandlerBeforeReferences = &HandlerLists->HandlerBeforeReferences;
		HandlerAfterReferences = &HandlerLists->HandlerAfterReferences;
		ThisAdjustment = Result.ThisAdjustment;
		OriginalFunctionCode = Result.OriginalFunctionCode;
		Key = Result.Key;
	}

	static void UninstallHook(const TCHAR* DebugSymbolName)
	{
		if (OriginalFunctionCode == nullptr)
			return;	// Not installed.

		Backend::UnregisterHook(DebugSymbolName, Key);
		DestroyHandlerLists<HandlerBefore, HandlerAfter>(Key);

		HandlersBefore = nullptr;
		HandlersAfter = nullptr;
		HandlerBeforeReferences = nullptr;
		HandlerAfterReferences = nullptr;
		ThisAdjustment = 0;
		OriginalFunctionCode = nullptr;
		Key = nullptr;
	}

	template<typename HandlerType>
	static FDelegateHandle InternalAddHandler(HandlerType&& Handler, HandlersArray<HandlerType>& Array, HandlersMap<HandlerType>& Map)
	{
		const TSharedPtr<HandlerType> NewHandlerPtr = MakeShared<HandlerType>(MoveTemp(Handler));
		const FDelegateHandle NewDelegateHandle(FDelegateHandle::GenerateNewHandle);

		Array.Add(NewHandlerPtr);
		Map.Add(NewDelegateHandle, NewHandlerPtr);

		return NewDelegateHandle;
	}

	template<typename HandlerType>
	static void InternalRemoveHandler(FDelegateHandle HandlerHandle, HandlersArray<HandlerType>& Array, HandlersMap<HandlerType>& Map)
	{
		if (TSharedPtr<HandlerType> HandlerPtr; Map.RemoveAndCopyValue(HandlerHandle, HandlerPtr))
		{
			Array.Remove(HandlerPtr);
		}
	}

	// If the actual function signature is different from what's presented to the user, e.g. if there's
	// a custom thunk that forwards to the user-facing function, then the backend can provide its own
	// hook function with the expectation that it'll forward the call on to our hook function.
	static constexpr bool bBackendWrapsHookFunction = requires
	{
		Backend::template WrapHookFunction<static_cast<CallableType*>(nullptr)>();
	};

	static consteval auto GetHookFunction()
	{
		constexpr auto DefaultHookFunction = &GenerateHookFunction<ArgTypes...>::ApplyCall;
		if constexpr (bBackendWrapsHookFunction)
		{
			return Backend::template WrapHookFunction<DefaultHookFunction>();
		}
		else
		{
			return DefaultHookFunction;
		}
	}

	template<typename... /* ArgTypes */>
	struct GenerateHookFunction
	{
		static ReturnType ApplyCall(ArgTypes... Args)
		{
			ScopeType Scope(HandlersBefore, reinterpret_cast<CallableType*>(OriginalFunctionCode));
			Scope(Args...);
			if constexpr (std::is_void_v<ReturnType>)
			{
				for (const TSharedPtr<HandlerAfter>& Handler : *HandlersAfter)
				{
					(*Handler)(Args...);
				}
			}
			else
			{
				for (const TSharedPtr<HandlerAfter>& Handler : *HandlersAfter)
				{
					(*Handler)(Scope.GetResult(), Args...);
				}
				return Scope.GetResult();
			}
		}
	};

#ifdef _WIN64
	// Depending on the type of the return value, the ABI might require that the caller allocates memory
	// for the result and passes a pointer to it as a hidden parameter to the function.
	//
	// We usually don't need to worry about this, the compiler will do the same to our hook function if
	// needed and it will just work, however Windows has an exception for non-static member functions
	// where it will pass the return address parameter after the "this" pointer. This is a problem for
	// us because our hook functions are never actually non-static member functions, we just emulate
	// them by having an explicit "this" parameter, so we can't rely on the compiler to do the right
	// thing.
	//
	// Fortunately the rules are very simple on Windows: a non-static member function will never return
	// a user-defined type (class/union) in a register, regardless of size or triviality.
	//
	// This isn't a problem on Linux because System V doesn't treat non-static member functions any
	// differently, so emulating one with an explicit "this" parameter doesn't cause any issues.
	template<typename ThisPointer, typename... OtherArgTypes>
		requires (bIsMemberFunction && !bBackendWrapsHookFunction
		          && (std::is_class_v<ReturnType> || std::is_union_v<ReturnType>))
	struct GenerateHookFunction<ThisPointer, OtherArgTypes...>
	{
		static ReturnType* ApplyCall(ThisPointer Self, ReturnType* OutReturnValue, OtherArgTypes... Args)
		{
			// Capture the pointer of the return value so ScopeType does not have to know about that special case.
			auto Trampoline = [OutReturnValue](ThisPointer Self, OtherArgTypes... OtherArgs) -> ReturnType
			{
				reinterpret_cast<ReturnType*(*)(ThisPointer, ReturnType*, OtherArgTypes...)>(OriginalFunctionCode)(Self, OutReturnValue, OtherArgs...);
				return *OutReturnValue;
			};

			ScopeType Scope(HandlersBefore, Trampoline);
			Scope(Self, Args...);
			for (const TSharedPtr<HandlerAfter>& Handler : *HandlersAfter)
			{
				(*Handler)(Scope.GetResult(), Self, Args...);
			}
			*OutReturnValue = Scope.GetResult();
			return OutReturnValue;
		}
	};
#endif

	// For some member functions we could end up with a 'this' pointer that has been adjusted to point
	// to a base class, which won't be compatible with the derived class pointer that the handler is
	// expecting. To work around this, we need to un-adjust the 'this' pointer before calling the
	// handler. It's tempting to do this in the hook function itself, we could modify the parameter as
	// soon as it's passed in and the new value could be passed on to all of the handlers, but we can't
	// do that because we need to be backwards-compatible with old mods; if an old mod is the first to
	// register the hook, then they'd define the hook function and they wouldn't know to do that
	// adjustment. The only thing that we know we have control over is our own handler, so that's the
	// only place where this can be done.
	template<typename HandlerType, typename InHandlerType>
	static HandlerType WrapHandler(InHandlerType&& InHandler)
	{
		if constexpr (!bIsMemberFunction)
		{
			// Non-member functions shouldn't have a ThisAdjustment.
			check(ThisAdjustment == 0);
			return Forward<InHandlerType>(InHandler);
		}
		else if (ThisAdjustment == 0)
		{
			// No adjustment, use the input handler as-is.
			return Forward<InHandlerType>(InHandler);
		}
		else if constexpr (std::is_same_v<HandlerType, HandlerBefore>)
		{
			// HandlerBefore
			return [Handler = Forward<InHandlerType>(InHandler)]
				<typename Pointee, typename... OtherArgTypes>
				(ScopeType& Scope, Pointee* This, OtherArgTypes&&... OtherArgs)
			{
				Scope.ThisAdjustment = ThisAdjustment;
				This = reinterpret_cast<Pointee*>(reinterpret_cast<uintptr_t>(This) - ThisAdjustment);
				Handler(Scope, This, Forward<OtherArgTypes>(OtherArgs)...);
				Scope.ThisAdjustment = 0;
			};
		}
		else
		{
			// HandlerAfter
			static_assert(std::is_same_v<HandlerType, HandlerAfter>);
			if constexpr (std::is_void_v<ReturnType>)
			{
				// void return
				return [Handler = Forward<InHandlerType>(InHandler)]
					<typename Pointee, typename... OtherArgTypes>
					(Pointee* This, OtherArgTypes&&... OtherArgs)
				{
					This = reinterpret_cast<Pointee*>(reinterpret_cast<uintptr_t>(This) - ThisAdjustment);
					Handler(This, Forward<OtherArgTypes>(OtherArgs)...);
				};
			}
			else
			{
				// non-void return
				return [Handler = Forward<InHandlerType>(InHandler)]
					<typename Pointee, typename... OtherArgTypes>
					(const ReturnType& ReturnValue, Pointee* This, OtherArgTypes&&... OtherArgs)
				{
					This = reinterpret_cast<Pointee*>(reinterpret_cast<uintptr_t>(This) - ThisAdjustment);
					Handler(ReturnValue, This, Forward<OtherArgTypes>(OtherArgs)...);
				};
			}
		}
	}

	static inline HandlersArray<HandlerBefore>* HandlersBefore;
	static inline HandlersArray<HandlerAfter>* HandlersAfter;
	static inline HandlersMap<HandlerBefore>* HandlerBeforeReferences;
	static inline HandlersMap<HandlerAfter>* HandlerAfterReferences;
	static inline ptrdiff_t ThisAdjustment;
	static inline void* OriginalFunctionCode;
	static inline void* Key;
};

// non-const non-static member function
template<typename Backend, typename Variant, typename R, typename C, typename... A>
struct THookInvoker<Backend, R(C::*)(A...), Variant>
	: THookInvokerBase<Backend, Variant, true, R, C*, A...> {};

// const non-static member function
template<typename Backend, typename Variant, typename R, typename C, typename... A>
struct THookInvoker<Backend, R(C::*)(A...) const, Variant>
	: THookInvokerBase<Backend, Variant, true, R, const C*, A...> {};

// free function or static member function
template<typename Backend, typename Variant, typename R, typename... A>
struct THookInvoker<Backend, R(*)(A...), Variant>
	: THookInvokerBase<Backend, Variant, false, R, A...> {};

UE_DEPRECATED( 5.2, "CallScope type is deprecated. Please migrate your code to use TCallScope" );
template<typename T>
using CallScope = TCallScope<T>;

/*
 * SUBSCRIBE_METHOD
 * Will trigger a runtime error if the given method is virtual.
 */

#define SUBSCRIBE_METHOD(MethodReference, Handler) \
	SUBSCRIBE_METHOD_EXPLICIT(decltype(&MethodReference), MethodReference, Handler)

#define SUBSCRIBE_METHOD_AFTER(MethodReference, Handler) \
	SUBSCRIBE_METHOD_EXPLICIT_AFTER(decltype(&MethodReference), MethodReference, Handler)

#define SUBSCRIBE_METHOD_EXPLICIT(MethodSignature, MethodReference, Handler) \
	INTERNAL_SUBSCRIBE_METHOD(Before, MethodSignature, MethodReference, Handler)

#define SUBSCRIBE_METHOD_EXPLICIT_AFTER(MethodSignature, MethodReference, Handler) \
	INTERNAL_SUBSCRIBE_METHOD(After, MethodSignature, MethodReference, Handler)

#define INTERNAL_SUBSCRIBE_METHOD(HandlerKind, MethodSignature, MethodReference, Handler) \
	THookInvoker<TStandardHookBackend<MethodSignature, &MethodReference>, MethodSignature> \
		::AddHandler##HandlerKind(Handler, TEXT(#MethodReference))

/*
 * SUBSCRIBE_METHOD_VIRTUAL
 * Uses the vtable from the given instance to locate the function.
 */

#define SUBSCRIBE_METHOD_VIRTUAL(MethodReference, SampleObjectInstance, Handler) \
	SUBSCRIBE_METHOD_EXPLICIT_VIRTUAL(decltype(&MethodReference), MethodReference, SampleObjectInstance, Handler)

#define SUBSCRIBE_METHOD_VIRTUAL_AFTER(MethodReference, SampleObjectInstance, Handler) \
	SUBSCRIBE_METHOD_EXPLICIT_VIRTUAL_AFTER(decltype(&MethodReference), MethodReference, SampleObjectInstance, Handler)

#define SUBSCRIBE_METHOD_EXPLICIT_VIRTUAL(MethodSignature, MethodReference, SampleObjectInstance, Handler) \
	INTERNAL_SUBSCRIBE_METHOD_VIRTUAL(Before, MethodSignature, MethodReference, SampleObjectInstance, Handler)

#define SUBSCRIBE_METHOD_EXPLICIT_VIRTUAL_AFTER(MethodSignature, MethodReference, SampleObjectInstance, Handler) \
	INTERNAL_SUBSCRIBE_METHOD_VIRTUAL(After, MethodSignature, MethodReference, SampleObjectInstance, Handler)

#define INTERNAL_SUBSCRIBE_METHOD_VIRTUAL(HandlerKind, MethodSignature, MethodReference, SampleObjectInstance, Handler) \
	[&] { \
		/* Each instantiation must be unique to support different SampleObjectInstance types at runtime. */ \
		struct TotallyUniqueType; \
		return THookInvoker<TStandardHookBackend<MethodSignature, &MethodReference>, MethodSignature, TotallyUniqueType> \
			::AddHandler##HandlerKind(Handler, TEXT(#MethodReference), SampleObjectInstance); \
	}()

/*
 * SUBSCRIBE_UOBJECT_METHOD
 * Uses the vtable from the CDO of the given class to locate the function.
 */

#define SUBSCRIBE_UOBJECT_METHOD(ObjectClass, MethodName, Handler) \
	SUBSCRIBE_METHOD_VIRTUAL(ObjectClass::MethodName, GetDefault<ObjectClass>(), Handler)

#define SUBSCRIBE_UOBJECT_METHOD_AFTER(ObjectClass, MethodName, Handler) \
	SUBSCRIBE_METHOD_VIRTUAL_AFTER(ObjectClass::MethodName, GetDefault<ObjectClass>(), Handler)

#define SUBSCRIBE_UOBJECT_METHOD_EXPLICIT(MethodSignature, ObjectClass, MethodName, Handler) \
	SUBSCRIBE_METHOD_EXPLICIT_VIRTUAL(MethodSignature, ObjectClass::MethodName, GetDefault<ObjectClass>(), Handler)

#define SUBSCRIBE_UOBJECT_METHOD_EXPLICIT_AFTER(MethodSignature, ObjectClass, MethodName, Handler) \
	SUBSCRIBE_METHOD_EXPLICIT_VIRTUAL_AFTER(MethodSignature, ObjectClass::MethodName, GetDefault<ObjectClass>(), Handler)

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// WARNING
// The hook types defined below are for very specific advanced use cases. In most cases, the
// functionality provided above should suffice.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/*
 * SUBSCRIBE_VTABLE_ENTRY
 * The hook will only be called if the function is called virtually!
 */

#define SUBSCRIBE_VTABLE_ENTRY(MethodReference, SampleObjectInstance, Handler) \
	SUBSCRIBE_VTABLE_ENTRY_EXPLICIT(decltype(&MethodReference), MethodReference, SampleObjectInstance, Handler)

#define SUBSCRIBE_VTABLE_ENTRY_AFTER(MethodReference, SampleObjectInstance, Handler) \
	SUBSCRIBE_VTABLE_ENTRY_EXPLICIT_AFTER(decltype(&MethodReference), MethodReference, SampleObjectInstance, Handler)

#define SUBSCRIBE_VTABLE_ENTRY_EXPLICIT(MethodSignature, MethodReference, SampleObjectInstance, Handler) \
	INTERNAL_SUBSCRIBE_VTABLE_ENTRY(Before, MethodSignature, MethodReference, SampleObjectInstance, Handler)

#define SUBSCRIBE_VTABLE_ENTRY_EXPLICIT_AFTER(MethodSignature, MethodReference, SampleObjectInstance, Handler) \
	INTERNAL_SUBSCRIBE_VTABLE_ENTRY(After, MethodSignature, MethodReference, SampleObjectInstance, Handler)

#define INTERNAL_SUBSCRIBE_VTABLE_ENTRY(HandlerKind, MethodSignature, MethodReference, SampleObjectInstance, Handler) \
	[&] { \
		/* Each instantiation must be unique to support different SampleObjectInstance types at runtime. */ \
		struct TotallyUniqueType; \
		return THookInvoker<TVtableHookBackend<MethodSignature, &MethodReference>, MethodSignature, TotallyUniqueType> \
			::AddHandler##HandlerKind(Handler, TEXT(#MethodReference), SampleObjectInstance); \
	}()

/*
 * SUBSCRIBE_UFUNCTION_VM
 * The hook will only be called if the function is called via the reflection system!
 */

// There're no "explicit" variants of these macros because UFunctions can't be overloaded.

#define SUBSCRIBE_UFUNCTION_VM(ObjectClass, MethodName, Handler) \
	INTERNAL_SUBSCRIBE_UFUNCTION_VM(Before, ObjectClass, MethodName, Handler)

#define SUBSCRIBE_UFUNCTION_VM_AFTER(ObjectClass, MethodName, Handler) \
	INTERNAL_SUBSCRIBE_UFUNCTION_VM(After, ObjectClass, MethodName, Handler)

#define INTERNAL_SUBSCRIBE_UFUNCTION_VM(HandlerKind, ObjectClass, MethodName, Handler) \
	THookInvoker<TUFunctionHookBackend<ObjectClass, &ObjectClass::MethodName>, decltype(&ObjectClass::MethodName)> \
		::AddHandler##HandlerKind(Handler, TEXT(#ObjectClass "::" #MethodName), TEXT(#MethodName))

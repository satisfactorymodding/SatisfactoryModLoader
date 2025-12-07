#pragma once
#include "CoreMinimal.h"
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
		// the vtable offset will be found in the thunk. See FNativeHookManagerInternal::RegisterHookFunction()
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
		// RegisterHookFunction().
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
	static void* RegisterHookFunction(const FString& DebugSymbolName, FMemberFunctionPointer MemberFunctionPointer, const void* SampleObjectInstance,
	                                  void* HookFunctionPointer, void** OutTrampolineFunction);
	static void UnregisterHookFunction(const FString& DebugSymbolName, const void* RealFunctionAddress);

	// A call to this function signature is inlined in mods
	// Keep it for backwards compatibility
	static void* RegisterHookFunction(const FString& DebugSymbolName, void* OriginalFunctionPointer, const void* SampleObjectInstance, int ThisAdjustment, void* HookFunctionPointer, void** OutTrampolineFunction);
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
template<typename Backend, typename TCallable>
struct THookInvoker;

template<typename TCallable>
struct TCallScope;

//CallResult specialization for void
template <typename... Args>
struct TCallScope<void(*)(Args...)> {
public:
	typedef void HookType(Args...);
	typedef void HookFuncSig(TCallScope<void(*)(Args...)>&, Args...);
	typedef TFunction<HookFuncSig> HookFunc;

private:
	TArray<TSharedPtr<HookFunc>>* FunctionList;
	SIZE_T HandlerPtr = 0;
	HookType* Function;

	bool bForwardCall = true;

public:
	TCallScope(TArray<TSharedPtr<HookFunc>>* InFunctionList, HookType* InFunction) : FunctionList(InFunctionList), Function(InFunction) {}

	FORCEINLINE bool ShouldForwardCall() const {
		return bForwardCall;
	}

	void Cancel() {
		bForwardCall = false;
	}

	FORCEINLINE void operator()(Args... InArgs) {
		if (FunctionList == nullptr || HandlerPtr >= FunctionList->Num()) {
			Function(InArgs...);
			bForwardCall = false;
		} else {
			const SIZE_T CachePtr = HandlerPtr + 1;
			const TSharedPtr<HookFunc>& Handler = (*FunctionList)[HandlerPtr++];
			(*Handler)(*this, InArgs...);
			if (HandlerPtr == CachePtr && bForwardCall) {
				(*this)(InArgs...);
			}
		}
	}
};

//general template for other types
template <typename Result, typename... Args>
struct TCallScope<Result(*)(Args...)> {
public:
	// typedef Result HookType(Args...);
	typedef void HookFuncSig(TCallScope<Result(*)(Args...)>&, Args...);
	typedef TFunction<HookFuncSig> HookFunc;

	typedef TFunction<Result(Args...)> HookType;
private:
	TArray<TSharedPtr<HookFunc>>* FunctionList;
	size_t HandlerPtr = 0;
	HookType Function;

	bool bForwardCall = true;
	Result ResultData{};
public:
	TCallScope(TArray<TSharedPtr<HookFunc>>* InFunctionList, HookType InFunction) : FunctionList(InFunctionList), Function(InFunction) {}

	FORCEINLINE	bool ShouldForwardCall() const {
		return bForwardCall;
	}

	FORCEINLINE Result GetResult() {
		return ResultData;
	}

	void Override(const Result& NewResult) {
		bForwardCall = false;
		ResultData = NewResult;
	}

	FORCEINLINE Result operator()(Args... args) {
		if (FunctionList == nullptr || HandlerPtr >= FunctionList->Num()) {
			ResultData = Function(args...);
			this->bForwardCall = false;
		} else {
			const SIZE_T CachePtr = HandlerPtr + 1;
			const TSharedPtr<HookFunc>& Handler = (*FunctionList)[HandlerPtr++];
			(*Handler)(*this, args...);
			if (HandlerPtr == CachePtr && bForwardCall) {
				(*this)(args...);
			}
		}
		return ResultData;
	}
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
};

template<typename TCallable, TCallable OriginalFunction>
struct TStandardHookBackend
{
	// Key = RealFunctionAddress

	template<auto HookFunction>
	static FNativeHookResult RegisterHook(const FString& DebugSymbolName, const void* SampleObjectInstance = NULL)
	{
		FNativeHookResult Result;

		Result.Key = FNativeHookManagerInternal::RegisterHookFunction(
			DebugSymbolName,
			ConvertFunctionPointer(OriginalFunction),
			SampleObjectInstance,
			(void*)HookFunction,
			&Result.OriginalFunctionCode);

		return Result;
	}

	static void UnregisterHook(const FString& DebugSymbolName, void* RealFunctionAddress)
	{
		FNativeHookManagerInternal::UnregisterHookFunction(DebugSymbolName, RealFunctionAddress);
	}
};

template<typename Backend, bool bIsMemberFunction, typename ReturnType, typename... ArgTypes>
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

	template<typename... BackendArgTypes>
	static FDelegateHandle AddHandlerBefore(HandlerBefore&& InHandler, BackendArgTypes&&... BackendArgs)
	{
		InstallHook(Forward<BackendArgTypes>(BackendArgs)...);
		return InternalAddHandler(MoveTemp(InHandler), *HandlersBefore, *HandlerBeforeReferences);
	}

	template<typename... BackendArgTypes>
	static FDelegateHandle AddHandlerAfter(HandlerAfter&& InHandler, BackendArgTypes&&... BackendArgs)
	{
		InstallHook(Forward<BackendArgTypes>(BackendArgs)...);
		return InternalAddHandler(MoveTemp(InHandler), *HandlersAfter, *HandlerAfterReferences);
	}

	template<typename... BackendArgTypes>
	static void RemoveHandler(FDelegateHandle InHandlerHandle, BackendArgTypes&&... BackendArgs)
	{
		InternalRemoveHandler(InHandlerHandle, *HandlersBefore, *HandlerBeforeReferences);
		InternalRemoveHandler(InHandlerHandle, *HandlersAfter, *HandlerAfterReferences);

		if (HandlersBefore->IsEmpty() && HandlersAfter->IsEmpty())
		{
			// No handlers left, uninstall the hook.
			UninstallHook(Forward<BackendArgTypes>(BackendArgs)...);
		}
	}

private:
	template<typename HandlerType>
	using HandlersArray = TArray<TSharedPtr<HandlerType>>;
	template<typename HandlerType>
	using HandlersMap = TMap<FDelegateHandle, TSharedPtr<HandlerType>>;

	template<typename... BackendArgTypes>
	static void InstallHook(BackendArgTypes&&... BackendArgs)
	{
		if (OriginalFunctionCode != nullptr)
			return;	// Already installed.

		constexpr auto HookFunction = &GenerateHookFunction<ArgTypes...>::ApplyCall;
		const FNativeHookResult Result = Backend::template RegisterHook<HookFunction>(Forward<BackendArgTypes>(BackendArgs)...);
		auto* HandlerLists = CreateHandlerLists<HandlerBefore, HandlerAfter>(Result.Key);

		HandlersBefore = &HandlerLists->HandlersBefore;
		HandlersAfter = &HandlerLists->HandlersAfter;
		HandlerBeforeReferences = &HandlerLists->HandlerBeforeReferences;
		HandlerAfterReferences = &HandlerLists->HandlerAfterReferences;
		OriginalFunctionCode = Result.OriginalFunctionCode;
		Key = Result.Key;
	}

	template<typename... BackendArgTypes>
	static void UninstallHook(BackendArgTypes&&... BackendArgs)
	{
		if (OriginalFunctionCode == nullptr)
			return;	// Not installed.

		Backend::UnregisterHook(Forward<BackendArgTypes>(BackendArgs)..., Key);
		DestroyHandlerLists<HandlerBefore, HandlerAfter>(Key);

		HandlersBefore = nullptr;
		HandlersAfter = nullptr;
		HandlerBeforeReferences = nullptr;
		HandlerAfterReferences = nullptr;
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
		requires (bIsMemberFunction && (std::is_class_v<ReturnType> || std::is_union_v<ReturnType>))
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

	static inline HandlersArray<HandlerBefore>* HandlersBefore;
	static inline HandlersArray<HandlerAfter>* HandlersAfter;
	static inline HandlersMap<HandlerBefore>* HandlerBeforeReferences;
	static inline HandlersMap<HandlerAfter>* HandlerAfterReferences;
	static inline void* OriginalFunctionCode;
	static inline void* Key;
};

// non-const non-static member function
template<typename Backend, typename R, typename C, typename... A>
struct THookInvoker<Backend, R(C::*)(A...)> : THookInvokerBase<Backend, true, R, C*, A...> {};

// const non-static member function
template<typename Backend, typename R, typename C, typename... A>
struct THookInvoker<Backend, R(C::*)(A...) const> : THookInvokerBase<Backend, true, R, const C*, A...> {};

// free function or static member function
template<typename Backend, typename R, typename... A>
struct THookInvoker<Backend, R(*)(A...)> : THookInvokerBase<Backend, false, R, A...> {};

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
	THookInvoker<TStandardHookBackend<MethodSignature, &MethodReference>, MethodSignature> \
		::AddHandler##HandlerKind(Handler, TEXT(#MethodReference), SampleObjectInstance)

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

/*
 * UNSUBSCRIBE_METHOD
 */

#define UNSUBSCRIBE_METHOD(MethodReference, HandlerHandle) \
	UNSUBSCRIBE_METHOD_EXPLICIT(decltype(&MethodReference), MethodReference, HandlerHandle)

#define UNSUBSCRIBE_METHOD_EXPLICIT(MethodSignature, MethodReference, HandlerHandle) \
	THookInvoker<TStandardHookBackend<MethodSignature, &MethodReference>, MethodSignature> \
		::RemoveHandler(HandlerHandle, TEXT(#MethodReference))

#define UNSUBSCRIBE_UOBJECT_METHOD(ObjectClass, MethodName, HandlerHandle) \
	UNSUBSCRIBE_METHOD(ObjectClass::MethodName, HandlerHandle)

#define UNSUBSCRIBE_UOBJECT_METHOD_EXPLICIT(MethodSignature, ObjectClass, MethodName, HandlerHandle) \
	UNSUBSCRIBE_METHOD_EXPLICIT(MethodSignature, ObjectClass::MethodName, HandlerHandle)

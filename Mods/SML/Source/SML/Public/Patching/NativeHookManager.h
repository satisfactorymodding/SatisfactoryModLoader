#pragma once
#include "CoreMinimal.h"
#include <type_traits>

DECLARE_LOG_CATEGORY_EXTERN(LogNativeHookManager, Log, Log);

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

template<typename T>
struct TMemberFunctionPointer {
	T MemberFunctionPointer;
};

template<typename T>
FORCEINLINE FMemberFunctionPointer ConvertFunctionPointer(const TMemberFunctionPointer<T>* SourcePointer) {
	const SIZE_T FunctionPointerSize = sizeof(SourcePointer);
	
	//We only support non-virtual inheritance, so assert on virtual inheritance and unknown inheritance cases
	//Note that it might also mean that we are dealing with "proper" compiler with static function pointer size
	//(e.g anything different from Intel C++ and MSVC)
	checkf(FunctionPointerSize == 8 || FunctionPointerSize == 16, TEXT("Unsupported function pointer size received: \
		Hooking can only support non-virtual multiple inheritence. \
		This might be also caused by unsupported compiler. Currently, only MSVC and Intel C++ are supported\
		Function pointer size: %d bytes."), FunctionPointerSize);

	const FMemberFunctionPointer* RawFunctionPointer = (const FMemberFunctionPointer*) SourcePointer;

	//TODO we  cannot really make sure there is no virtual inheritance involved, so we just assume it for now
	FMemberFunctionPointer ResultPointer{};
	ResultPointer.FunctionAddress = RawFunctionPointer->FunctionAddress;
	if (FunctionPointerSize >= 16) {
		ResultPointer.ThisAdjustment = RawFunctionPointer->ThisAdjustment;
		ResultPointer.VtableDisplacement = RawFunctionPointer->VtableDisplacement;
	}
	
	return ResultPointer;
}

class SML_API FNativeHookManagerInternal {
public:
	static void* GetHandlerListInternal( const void* RealFunctionAddress);
	static void SetHandlerListInstanceInternal(void* RealFunctionAddress, void* HandlerList);
	static void* RegisterHookFunction(const FString& DebugSymbolName, void* OriginalFunctionPointer, const void* SampleObjectInstance, int ThisAdjustment, void* HookFunctionPointer, void** OutTrampolineFunction);
	static void UnregisterHookFunction( const FString& DebugSymbolName, const void* RealFunctionAddress );
};

template <typename T, typename E>
struct THandlerLists {
	TArray<TSharedPtr<T>> HandlersBefore;
	TArray<TSharedPtr<E>> HandlersAfter;
	TMap<FDelegateHandle, TSharedPtr<T>> HandlerBeforeReferences;
	TMap<FDelegateHandle, TSharedPtr<E>> HandlerAfterReferences;
};

template <typename T, typename E>
static THandlerLists<T, E>* CreateHandlerLists( void* RealFunctionAddress )
{
	void* HandlerListRaw = FNativeHookManagerInternal::GetHandlerListInternal( RealFunctionAddress );
	if (HandlerListRaw == nullptr) {
		HandlerListRaw = new THandlerLists<T, E>();
		FNativeHookManagerInternal::SetHandlerListInstanceInternal( RealFunctionAddress, HandlerListRaw );
	}
	return static_cast<THandlerLists<T, E>*>( HandlerListRaw );
}

template <typename T, typename E>
static void DestroyHandlerLists( void* RealFunctionAddress )
{
	void* HandlerListRaw = FNativeHookManagerInternal::GetHandlerListInternal(RealFunctionAddress);

	if (HandlerListRaw != nullptr) {
		const THandlerLists<T, E>* CastedHandlerList = static_cast<THandlerLists<T, E>*>(HandlerListRaw);
		delete CastedHandlerList;
		
		FNativeHookManagerInternal::SetHandlerListInstanceInternal( RealFunctionAddress, nullptr );
	}
}

template <typename TCallable, TCallable Callable>
struct HookInvoker;

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

template<typename Ret, typename... A>
class HandlerAfterFunc {
public:
	typedef void Value(const Ret&, A...);
};
template<typename... A>
class HandlerAfterFunc<void, A...> {
public:
	typedef void Value(A...);
};

template<typename T>
struct FMemberFunctionStruct {
	T MemberFunctionPtr;
};

//Hook invoker for global functions
template <typename TCallable, TCallable Callable, typename ReturnType, typename... ArgumentTypes>
struct HookInvokerExecutorGlobalFunction {
public:
	using HookType = TCallable;
	using ScopeType = TCallScope<TCallable>;
	using HandlerSignature = void(ScopeType&, ArgumentTypes...);
	using HandlerSignatureAfter = typename HandlerAfterFunc<ReturnType, ArgumentTypes...>::Value;
	using Handler = TFunction<HandlerSignature>;
	using HandlerAfter = TFunction<HandlerSignatureAfter>;
private:
	static inline TArray<TSharedPtr<Handler>>* HandlersBefore{nullptr};
	static inline TArray<TSharedPtr<HandlerAfter>>* HandlersAfter{nullptr};
	static inline TMap<FDelegateHandle, TSharedPtr<Handler>>* HandlerBeforeReferences{nullptr};
	static inline TMap<FDelegateHandle, TSharedPtr<HandlerAfter>>* HandlerAfterReferences{nullptr};
	static inline TCallable FunctionPtr{nullptr};
	static inline void* RealFunctionAddress{nullptr};
	static inline bool bHookInitialized{false};
public:
	static ReturnType ApplyCall(ArgumentTypes... Args)
	{
		ScopeType Scope(HandlersBefore, FunctionPtr);
		Scope(Args...);
		for (const TSharedPtr<HandlerAfter>& Handler : *HandlersAfter)
		{
			(*Handler)(Scope.getResult(), Args...);
		}
		return Scope.getResult();
	}

	static void ApplyCallVoid(ArgumentTypes... Args)
	{
		ScopeType Scope(HandlersBefore, FunctionPtr);
		Scope(Args...);
		for (const TSharedPtr<HandlerAfter>& Handler : *HandlersAfter)
		{
			(*Handler)(Args...);
		}
	}

private:
	static TCallable GetApplyRef(std::true_type)
	{
		return &ApplyCallVoid;
	}

	static TCallable GetApplyRef(std::false_type)
	{
		return &ApplyCall;
	}

	static TCallable GetApplyCall()
	{
		return GetApplyRef(std::is_same<ReturnType, void>{});
	}
public:
	//This hook invoker is for global non-member static functions, so we don't have to deal with
	//member function pointers and virtual functions here
	static void InstallHook(const FString& DebugSymbolName)
	{
		if (!bHookInitialized)
		{
			bHookInitialized = true;
			void* HookFunctionPointer = static_cast<void*>( GetApplyCall() );
			RealFunctionAddress = FNativeHookManagerInternal::RegisterHookFunction( DebugSymbolName, Callable, NULL, 0, HookFunctionPointer, (void**) &FunctionPtr );
			THandlerLists<Handler, HandlerAfter>* HandlerLists = CreateHandlerLists<Handler, HandlerAfter>( RealFunctionAddress );

			HandlersBefore = &HandlerLists->HandlersBefore;
			HandlersAfter = &HandlerLists->HandlersAfter;
			HandlerBeforeReferences = &HandlerLists->HandlerBeforeReferences;
			HandlerAfterReferences = &HandlerLists->HandlerAfterReferences;
		}
	}

	// Uninstalls the hook. Also frees the handler lists object.
	static void UninstallHook(const FString& DebugSymbolName)
	{
		if (bHookInitialized)
		{
			FNativeHookManagerInternal::UnregisterHookFunction( DebugSymbolName, RealFunctionAddress );
			DestroyHandlerLists<Handler, HandlerAfter>( RealFunctionAddress );
			bHookInitialized = false;
			RealFunctionAddress = nullptr;
			
			HandlersBefore = nullptr;
			HandlersAfter = nullptr;
			HandlerBeforeReferences = nullptr;
			HandlerAfterReferences = nullptr;
		}
	}

	static FDelegateHandle AddHandlerBefore( Handler&& InHandler )
	{
		const TSharedPtr<Handler> NewHandlerPtr = MakeShared<Handler>( MoveTemp( InHandler ) );
		HandlersBefore->Add( NewHandlerPtr );

		FDelegateHandle NewDelegateHandle( FDelegateHandle::GenerateNewHandle );
		HandlerBeforeReferences->Add( NewDelegateHandle, NewHandlerPtr );
		return NewDelegateHandle;
	}

	static FDelegateHandle AddHandlerAfter( HandlerAfter&& InHandler ) {

		const TSharedPtr<HandlerAfter> NewHandlerPtr = MakeShared<HandlerAfter>( MoveTemp( InHandler ) );
		HandlersAfter->Add( NewHandlerPtr );

		FDelegateHandle NewDelegateHandle( FDelegateHandle::GenerateNewHandle );
		HandlerAfterReferences->Add( NewDelegateHandle, NewHandlerPtr );
		return NewDelegateHandle;
	}

	static void RemoveHandler(const FString& DebugSymbolName, FDelegateHandle InHandlerHandle )
	{
		if ( HandlerBeforeReferences->Contains( InHandlerHandle ) )
		{
			const TSharedPtr<Handler> HandlerPtr = HandlerBeforeReferences->FindAndRemoveChecked( InHandlerHandle );
			HandlersBefore->Remove( HandlerPtr );
		}
		if ( HandlerAfterReferences->Contains( InHandlerHandle ) )
		{
			const TSharedPtr<HandlerAfter> HandlerPtr = HandlerAfterReferences->FindAndRemoveChecked( InHandlerHandle );
			HandlersAfter->Remove( HandlerPtr );
		}

		if ( HandlersAfter->IsEmpty() && HandlersBefore->IsEmpty() )
		{
			UninstallHook(DebugSymbolName);
		}
	}
};

//Hook invoker for member functions
template <typename TCallable, TCallable Callable, bool bIsConst, typename ReturnType, typename CallableType, typename... ArgumentTypes>
struct HookInvokerExecutorMemberFunction {
public:
	using ConstCorrectThisPtr = std::conditional_t<bIsConst, const CallableType*, CallableType*>;
	using CallScopeFunctionSignature = ReturnType(*)(ConstCorrectThisPtr, ArgumentTypes...); 
	typedef TCallScope<CallScopeFunctionSignature> ScopeType;
	
	typedef void HandlerSignature(ScopeType&, ConstCorrectThisPtr, ArgumentTypes...);
	typedef typename HandlerAfterFunc<ReturnType, ConstCorrectThisPtr, ArgumentTypes...>::Value HandlerSignatureAfter;
	typedef ReturnType HookType(ConstCorrectThisPtr, ArgumentTypes...);

	using Handler = TFunction<HandlerSignature>;
	using HandlerAfter = TFunction<HandlerSignatureAfter>;
private:
	static inline TArray<TSharedPtr<Handler>>* HandlersBefore{nullptr};
	static inline TArray<TSharedPtr<HandlerAfter>>* HandlersAfter{nullptr};
	static inline TMap<FDelegateHandle, TSharedPtr<Handler>>* HandlerBeforeReferences{nullptr};
	static inline TMap<FDelegateHandle, TSharedPtr<HandlerAfter>>* HandlerAfterReferences{nullptr};
	static inline HookType* FunctionPtr{nullptr};
	static inline void* RealFunctionAddress{nullptr};
	static inline bool bHookInitialized{false};

	//Methods which return class/struct/union by value have out pointer inserted
	//as first parameter after this pointer, with all arguments shifted right by 1 for it
	static ReturnType* ApplyCallUserTypeByValue( CallableType* Self, ReturnType* OutReturnValue, ArgumentTypes... Args )
	{
		// Capture the pointer of the return value
		// so ScopeType does not have to know about that special case
		auto Trampoline = [&](ConstCorrectThisPtr Self_, ArgumentTypes... Args_) -> ReturnType
		{
			(reinterpret_cast<ReturnType*(*)(ConstCorrectThisPtr, ReturnType*, ArgumentTypes...)>(FunctionPtr))(Self_, OutReturnValue, Args_...);
			return *OutReturnValue;
		};

		ScopeType Scope(HandlersBefore, Trampoline);
		Scope(Self, Args...);
		for ( const TSharedPtr<HandlerAfter>& Handler : *HandlersAfter )
		{
			(*Handler)(Scope.GetResult(), Self, Args...);
		}
		//We always return outReturnValue, so copy our result to output variable and return it
		*OutReturnValue = Scope.GetResult();
		return OutReturnValue;
	}

	//Normal scalar type call, where no additional arguments are inserted
	//If it were returning user type by value, first argument would be R*, which is incorrect - that's why we need separate
	//applyCallUserType with correct argument order
	static ReturnType ApplyCallScalar(CallableType* Self, ArgumentTypes... Args)
	{
		ScopeType Scope(HandlersBefore, FunctionPtr);
		Scope(Self, Args...);
		for ( const TSharedPtr<HandlerAfter>& Handler : *HandlersAfter )
		{
			(*Handler)(Scope.GetResult(), Self, Args...);
		}
		return Scope.GetResult();
	}

	//Call for void return type - nothing special to do with void
	static void ApplyCallVoid(CallableType* Self, ArgumentTypes... Args)
	{
		ScopeType Scope(HandlersBefore, FunctionPtr);
		Scope(Self, Args...);
		for ( const TSharedPtr<HandlerAfter>& Handler : *HandlersAfter )
		{
			(*Handler)(Self, Args...);
		}
	}

    static void* GetApplyCall1(std::true_type) {
    	return (void*) &ApplyCallVoid; //true - type is void
    }
	static void* GetApplyCall1(std::false_type) {
	    return GetApplyCall2(std::is_class<ReturnType>{}); //not a void, try call 2
    }
	static void* GetApplyCall2(std::true_type) {
	    return (void*) &ApplyCallUserTypeByValue; //true - type is class
    }
	static void* GetApplyCall2(std::false_type) {
	    return GetApplyCall3(std::is_union<ReturnType>{});
    }
	static void* GetApplyCall3(std::true_type) {
    	return (void*) &ApplyCallUserTypeByValue; //true - type is union
    }
	static void* GetApplyCall3(std::false_type) {
    	return (void*) &ApplyCallScalar; //false - type is scalar type
    }
	
	static void* GetApplyCall() {
    	return GetApplyCall1(std::is_same<ReturnType, void>{});
	}
public:
	//Handles normal member function hooking, e.g hooking fixed symbol implementation in executable
	static void InstallHook(const FString& DebugSymbolName, const void* SampleObjectInstance = NULL)
	{
		if (!bHookInitialized)
		{
			bHookInitialized = true;
			void* HookFunctionPointer = GetApplyCall();
			TMemberFunctionPointer<TCallable> RawFunctionPointer{};
			RawFunctionPointer.MemberFunctionPointer = Callable;
			const FMemberFunctionPointer MemberFunctionPointer = ConvertFunctionPointer( &RawFunctionPointer );
			
			RealFunctionAddress = FNativeHookManagerInternal::RegisterHookFunction( DebugSymbolName,
				MemberFunctionPointer.FunctionAddress,
				SampleObjectInstance,
				MemberFunctionPointer.ThisAdjustment,
				HookFunctionPointer, (void**) &FunctionPtr );
			
			THandlerLists<Handler, HandlerAfter>* HandlerLists = CreateHandlerLists<Handler, HandlerAfter>( RealFunctionAddress );

			HandlersBefore = &HandlerLists->HandlersBefore;
			HandlersAfter = &HandlerLists->HandlersAfter;
			HandlerBeforeReferences = &HandlerLists->HandlerBeforeReferences;
			HandlerAfterReferences = &HandlerLists->HandlerAfterReferences;
		}
	}

	// Uninstalls the hook. Also frees the handler lists object.
	static void UninstallHook(const FString& DebugSymbolName)
	{
		if (bHookInitialized)
		{
			FNativeHookManagerInternal::UnregisterHookFunction( DebugSymbolName, RealFunctionAddress );
			DestroyHandlerLists<Handler, HandlerAfter>( RealFunctionAddress );
			bHookInitialized = false;
			RealFunctionAddress = nullptr;
			
			HandlersBefore = nullptr;
			HandlersAfter = nullptr;
			HandlerBeforeReferences = nullptr;
			HandlerAfterReferences = nullptr;
		}
	}

	static FDelegateHandle AddHandlerBefore( Handler&& InHandler )
	{
		const TSharedPtr<Handler> NewHandlerPtr = MakeShared<Handler>( MoveTemp( InHandler ) );
		HandlersBefore->Add( NewHandlerPtr );

		FDelegateHandle NewDelegateHandle( FDelegateHandle::GenerateNewHandle );
		HandlerBeforeReferences->Add( NewDelegateHandle, NewHandlerPtr );
		return NewDelegateHandle;
	}

	static FDelegateHandle AddHandlerAfter( HandlerAfter&& InHandler ) {

		const TSharedPtr<HandlerAfter> NewHandlerPtr = MakeShared<HandlerAfter>( MoveTemp( InHandler ) );
		HandlersAfter->Add( NewHandlerPtr );

		FDelegateHandle NewDelegateHandle( FDelegateHandle::GenerateNewHandle );
		HandlerAfterReferences->Add( NewDelegateHandle, NewHandlerPtr );
		return NewDelegateHandle;
	}

	static void RemoveHandler(const FString& DebugSymbolName, FDelegateHandle InHandlerHandle )
	{
		if ( HandlerBeforeReferences->Contains( InHandlerHandle ) )
		{
			const TSharedPtr<Handler> HandlerPtr = HandlerBeforeReferences->FindAndRemoveChecked( InHandlerHandle );
			HandlersBefore->Remove( HandlerPtr );
		}
		if ( HandlerAfterReferences->Contains( InHandlerHandle ) )
		{
			const TSharedPtr<HandlerAfter> HandlerPtr = HandlerAfterReferences->FindAndRemoveChecked( InHandlerHandle );
			HandlersAfter->Remove( HandlerPtr );
		}

		if ( HandlersAfter->IsEmpty() && HandlersBefore->IsEmpty() )
		{
			UninstallHook(DebugSymbolName);
		}
	}
};

//Hook invoker for member non-const functions
template<typename R, typename C, typename... A, R(C::*Callable)(A...)>
struct HookInvoker<R(C::*)(A...), Callable> : HookInvokerExecutorMemberFunction<R(C::*)(A...), Callable, false, R, C, A...> {
};

//Hook invoker for member const functions
template<typename R, typename C, typename... A, R(C::*Callable)(A...) const>
struct HookInvoker<R(C::*)(A...) const, Callable> : HookInvokerExecutorMemberFunction<R(C::*)(A...) const, Callable, true, R, C, A...> {
};

//Hook invoker for global functions
template<typename R, typename... A, R(*Callable)(A...)>
struct HookInvoker<R(*)(A...), Callable> : HookInvokerExecutorGlobalFunction<R(*)(A...), Callable, R, A...> {
};


UE_DEPRECATED( 5.2, "CallScope type is deprecated. Please migrate your code to use TCallScope" );
template<typename T>
using CallScope = TCallScope<T>;

#define SUBSCRIBE_METHOD(MethodReference, Handler) \
	Invoke( [&]() { \
		HookInvoker<decltype(&MethodReference), &MethodReference>::InstallHook(TEXT(#MethodReference)); \
		return HookInvoker<decltype(&MethodReference), &MethodReference>::AddHandlerBefore(Handler); \
	} )

#define SUBSCRIBE_METHOD_AFTER(MethodReference, Handler) \
	Invoke( [&]() { \
		HookInvoker<decltype(&MethodReference), &MethodReference>::InstallHook(TEXT(#MethodReference)); \
		return HookInvoker<decltype(&MethodReference), &MethodReference>::AddHandlerAfter(Handler); \
	} )

#define SUBSCRIBE_METHOD_VIRTUAL(MethodReference, SampleObjectInstance, Handler) \
	Invoke( [&]() { \
		HookInvoker<decltype(&MethodReference), &MethodReference>::InstallHook(TEXT(#MethodReference), SampleObjectInstance); \
		return HookInvoker<decltype(&MethodReference), &MethodReference>::AddHandlerBefore(Handler); \
	} )

#define SUBSCRIBE_METHOD_VIRTUAL_AFTER(MethodReference, SampleObjectInstance, Handler) \
	Invoke( [&]() { \
		HookInvoker<decltype(&MethodReference), &MethodReference>::InstallHook(TEXT(#MethodReference), SampleObjectInstance); \
		return HookInvoker<decltype(&MethodReference), &MethodReference>::AddHandlerAfter(Handler); \
	} )

#define SUBSCRIBE_METHOD_EXPLICIT_VIRTUAL_AFTER(MethodSignature, MethodReference, SampleObjectInstance, Handler) \
	Invoke( [&]() { \
		HookInvoker<MethodSignature, &MethodReference>::InstallHook(TEXT(#MethodReference), SampleObjectInstance); \
		return HookInvoker<MethodSignature, &MethodReference>::AddHandlerAfter(Handler); \
	} )

#define SUBSCRIBE_UOBJECT_METHOD(ObjectClass, MethodName, Handler) \
	Invoke( [&]() { \
		HookInvoker<decltype(&ObjectClass::MethodName), &ObjectClass::MethodName>::InstallHook(TEXT(#ObjectClass "::" #MethodName), GetDefault<ObjectClass>()); \
		return HookInvoker<decltype(&ObjectClass::MethodName), &ObjectClass::MethodName>::AddHandlerBefore(Handler); \
	} )

#define SUBSCRIBE_UOBJECT_METHOD_AFTER(ObjectClass, MethodName, Handler) \
	Invoke( [&]() { \
		HookInvoker<decltype(&ObjectClass::MethodName), &ObjectClass::MethodName>::InstallHook(TEXT(#ObjectClass "::" #MethodName), GetDefault<ObjectClass>()); \
		return HookInvoker<decltype(&ObjectClass::MethodName), &ObjectClass::MethodName>::AddHandlerAfter(Handler); \
	} )

#define UNSUBSCRIBE_METHOD(MethodReference, HandlerHandle) \
	HookInvoker<decltype(&MethodReference), &MethodReference>::RemoveHandler(TEXT(#MethodReference), HandlerHandle )

#define UNSUBSCRIBE_UOBJECT_METHOD(ObjectClass, MethodName, HandlerHandle) \
	HookInvoker<decltype(&ObjectClass::MethodName), &ObjectClass::MethodName>::RemoveHandler(TEXT(#ObjectClass "::" #MethodName), HandlerHandle )

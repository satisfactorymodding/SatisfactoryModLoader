#pragma once
#include "CoreMinimal.h"
#include <functional>
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
	static void* GetHandlerListInternal(void* RealFunctionAddress);
	static void SetHandlerListInstanceInternal(void* RealFunctionAddress, void* handlerList);
	static void* RegisterHookFunction(const FString& DebugSymbolName, void* OriginalFunctionPointer, void* SampleObjectInstance, int ThisAdjustment, void* HookFunctionPointer, void** OutTrampolineFunction);
};

template <typename T, typename E>
struct THandlerLists {
	TArray<T> HandlersBefore;
	TArray<E> HandlersAfter;
};

template <typename T, typename E>
THandlerLists<T, E>* createHandlerLists(void* RealFunctionAddress) {
	void* handlerListRaw = FNativeHookManagerInternal::GetHandlerListInternal(RealFunctionAddress);
	if (handlerListRaw == nullptr) {
		handlerListRaw = new THandlerLists<T, E>();
		FNativeHookManagerInternal::SetHandlerListInstanceInternal(RealFunctionAddress, handlerListRaw);
	}
	return static_cast<THandlerLists<T, E>*>(handlerListRaw);
}

template <typename TCallable, TCallable Callable, bool bIsConst>
struct HookInvoker;

template<typename TCallable>
struct CallScope;

//CallResult specialization for void
template <typename... Args>
struct CallScope<void(*)(Args...)> {
public:
	typedef void HookType(Args...);
	typedef void HookFuncSig(CallScope<void(*)(Args...)>&, Args...);
	typedef std::function<HookFuncSig> HookFunc;

private:
	TArray<HookFunc>* functionList;
	size_t handlerPtr = 0;
	HookType* function;

	bool forwardCall = true;

public:
	CallScope(TArray<HookFunc>* functionList, HookType* function) : functionList(functionList), function(function) {}

	inline bool shouldForwardCall() const {
		return forwardCall;
	}

	void Cancel() {
		forwardCall = false;
	}

	inline void operator()(Args... args) {
		if (functionList == nullptr || handlerPtr >= functionList->Num()) {
			function(args...);
			forwardCall = false;
		} else {
			auto cachePtr = handlerPtr + 1;
			auto& handler = (*functionList)[handlerPtr++];
			handler(*this, args...);
			if (handlerPtr == cachePtr && forwardCall) {
				(*this)(args...);
			}
		}
	}
};

//general template for other types
template <typename Result, typename... Args>
struct CallScope<Result(*)(Args...)> {
public:
	// typedef Result HookType(Args...);
	typedef void HookFuncSig(CallScope<Result(*)(Args...)>&, Args...);
	typedef std::function<HookFuncSig> HookFunc;

    typedef std::function<Result(Args...)> HookType;
private:
	TArray<HookFunc>* functionList;
	size_t handlerPtr = 0;
	HookType function;
	
	bool forwardCall = true;
	Result result;

public:
	CallScope(TArray<HookFunc>* functionList, HookType function) : functionList(functionList), function(function) {}

	inline bool shouldForwardCall() {
		return forwardCall;
	}
	inline Result getResult() {
		return result;
	}

	void Override(const Result& newResult) {
		this->forwardCall = false;
		this->result = newResult;
	}

	inline Result operator()(Args... args) {
		if (functionList == nullptr || handlerPtr >= functionList->Num()) {
			result = function(args...);
			this->forwardCall = false;
		} else {
			auto cachePtr = handlerPtr + 1;
			auto handler = (*functionList)[handlerPtr++];
			handler(*this, args...);
			if (handlerPtr == cachePtr && forwardCall) {
				(*this)(args...);
			}
		}
		return result;
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

struct None {};

//Hook invoker for global functions
template <typename R, typename... A, R(*PMF)(A...)>
struct HookInvoker<R(*)(A...), PMF, false> {
public:
	typedef CallScope<R(*)(A...)> ScopeType;
	// mod handler function
	typedef void HandlerSignature(ScopeType&, A...);
	typedef typename HandlerAfterFunc<R, A...>::Value HandlerSignatureAfter;
	typedef R HookType(A...);
	typedef R ReturnType;

	// support arbitrary context for handlers
	typedef std::function<HandlerSignature> Handler;
	typedef std::function<HandlerSignatureAfter> HandlerAfter;
private:
	static TArray<Handler>* handlersBefore;
	static TArray<HandlerAfter>* handlersAfter;
	static HookType* functionPtr;
	static bool bHookInitialized;
public:
	static R applyCall(A... args) {
		ScopeType scope(handlersBefore, functionPtr);
		scope(args...);
		if (handlersAfter) for (HandlerAfter& handler : * handlersAfter) handler(scope.getResult(), args...);
		return scope.getResult();
	}

	static void applyCallVoid(A... args) {
		ScopeType scope(handlersBefore, functionPtr);
		scope(args...);
		if (handlersAfter) for (HandlerAfter& handler : *handlersAfter) handler(args...);
	}

private:
	static HookType* getApplyRef(std::true_type) {
		return &applyCallVoid;
	}

	static HookType* getApplyRef(std::false_type) {
		return &applyCall;
	}

	static HookType* getApplyCall() {
		return getApplyRef(std::is_same<R, void>{});
	}
public:
	//This hook invoker is for global non-member static functions, so we don't have to deal with
	//member function pointers and virtual functions here
	static void InstallHook(const FString& DebugSymbolName) {
		if (!bHookInitialized) {
			bHookInitialized = true;
			void* HookFunctionPointer = static_cast<void*>(getApplyCall());
			void* RealFunctionAddress = FNativeHookManagerInternal::RegisterHookFunction(DebugSymbolName, PMF, NULL, 0, HookFunctionPointer, (void**) &functionPtr);
			auto* HandlerLists = createHandlerLists<Handler, HandlerAfter>(RealFunctionAddress);
			handlersBefore = &HandlerLists->HandlersBefore;
			handlersAfter = &HandlerLists->HandlersAfter;
		}
	}

	static void addHandlerBefore(Handler handler) {
		handlersBefore->Add(handler);
	}

	static void addHandlerAfter(HandlerAfter handler) {
		handlersAfter->Add(handler);
	}
};

//Template which is used for erasing const from method pointer
//passed to HookInvoker, since HookInvoker cannot properly handle const method hooks
template<typename TCallable, TCallable Callable>
struct HookInvokerWrapper {
public:
	using Value = HookInvoker<TCallable, (TCallable) Callable, false>;
};

template <typename R, typename C, typename... A, R(C::*PMF)(A...) const>
struct HookInvokerWrapper<R(C::*)(A...) const, PMF> {
public:
	using FunctionType = R(C::*)(A...);
    using Value = HookInvoker<FunctionType, (FunctionType) PMF, true>;
};

//Hook invoker for member functions
template <typename R, typename C, typename... A, R(C::*PMF)(A...), bool bIsConst>
struct HookInvoker<R(C::*)(A...), PMF, bIsConst>
{
public:
	using ConstCorrectThisPtr = std::conditional_t<bIsConst, const C*, C*>;
	using CallScopeFunctionSignature = R(*)(ConstCorrectThisPtr, A...); 
    typedef CallScope<CallScopeFunctionSignature> ScopeType;
	
	typedef void HandlerSignature(ScopeType&, ConstCorrectThisPtr, A...);
	typedef typename HandlerAfterFunc<R, ConstCorrectThisPtr, A...>::Value HandlerSignatureAfter;
	typedef R HookType(ConstCorrectThisPtr, A...);
	typedef R ReturnType;

	// support arbitrary context for handlers
	typedef std::function<HandlerSignature> Handler;
	typedef std::function<HandlerSignatureAfter> HandlerAfter;
private:
    static TArray<Handler>* handlersBefore;
	static TArray<HandlerAfter>* handlersAfter;
	static HookType* functionPtr;
	static bool bHookInitialized;
public:
    //Methods which return class/struct/union by value have out pointer inserted
    //as first parameter after this pointer, with all arguments shifted right by 1 for it
    static R* applyCallUserTypeByValue(C* self, R* outReturnValue, A... args) {
        // Capture the pointer of the return value
        // so ScopeType does not have to know about that special case
        auto Trampoline = [&](ConstCorrectThisPtr self_, A... args_) -> R {
            (reinterpret_cast<R*(*)(ConstCorrectThisPtr, R*, A...)>(functionPtr))(self_, outReturnValue, args_...);
            return *outReturnValue;
        };

    	ScopeType scope(handlersBefore, Trampoline);
    	scope(self, args...);
    	for (HandlerAfter& handler : *handlersAfter) handler(scope.getResult(), self, args...);
    	//We always return outReturnValue, so copy our result to output variable and return it
    	*outReturnValue = scope.getResult();
    	return outReturnValue;
    }

	//Normal scalar type call, where no additional arguments are inserted
	//If it were returning user type by value, first argument would be R*, which is incorrect - that's why we need separate
	//applyCallUserType with correct argument order
	static R applyCallScalar(C* self, A... args) {
    	ScopeType scope(handlersBefore, functionPtr);
    	scope(self, args...);
    	for (HandlerAfter& handler : *handlersAfter) handler(scope.getResult(), self, args...);
    	return scope.getResult();
    }

	//Call for void return type - nothing special to do with void
	static void applyCallVoid(C* self, A... args) {
    	ScopeType scope(handlersBefore, functionPtr);
    	scope(self, args...);
    	for (HandlerAfter& handler : *handlersAfter) handler(self, args...);
    }

private:
    static void* getApplyCall1(std::true_type) {
    	return (void*) applyCallVoid; //true - type is void
    }
	static void* getApplyCall1(std::false_type) {
	    return getApplyCall2(std::is_class<R>{}); //not a void, try call 2
    }
	static void* getApplyCall2(std::true_type) {
	    return (void*) applyCallUserTypeByValue; //true - type is class
    }
	static void* getApplyCall2(std::false_type) {
	    return getApplyCall3(std::is_union<R>{});
    }
	static void* getApplyCall3(std::true_type) {
    	return (void*) applyCallUserTypeByValue; //true - type is union
    }
	static void* getApplyCall3(std::false_type) {
    	return (void*) applyCallScalar; //false - type is scalar type
    }
	
	static void* getApplyCall() {
    	return getApplyCall1(std::is_same<R, void>{});
	}
public:
	//Handles normal member function hooking, e.g hooking fixed symbol implementation in executable
	static void InstallHook(const FString& DebugSymbolName, void* SampleObjectInstance = NULL) {
		if (!bHookInitialized) {
			bHookInitialized = true;
			void* HookFunctionPointer = getApplyCall();
			TMemberFunctionPointer<R(C::*)(A...)> RawFunctionPointer{};
			RawFunctionPointer.MemberFunctionPointer = PMF;
			const FMemberFunctionPointer MemberFunctionPointer = ConvertFunctionPointer(&RawFunctionPointer);
			
			void* RealFunctionAddress = FNativeHookManagerInternal::RegisterHookFunction(DebugSymbolName,
				MemberFunctionPointer.FunctionAddress,
				SampleObjectInstance,
				MemberFunctionPointer.ThisAdjustment,
				HookFunctionPointer, (void**) &functionPtr);
			
			auto* HandlerLists = createHandlerLists<Handler, HandlerAfter>(RealFunctionAddress);
			handlersBefore = &HandlerLists->HandlersBefore;
			handlersAfter = &HandlerLists->HandlersAfter;
		}
	}
	
	static void addHandlerBefore(Handler handler) {
		handlersBefore->Add(handler);
	}

	static void addHandlerAfter(HandlerAfter handler) {
		handlersAfter->Add(handler);
	}
};

template <typename R, typename C, typename... A, R(C::*PMF)(A...), bool bIsConst>
TArray<typename HookInvoker<R(C::*)(A...), PMF, bIsConst>::Handler>* HookInvoker<R(C::*)(A...), PMF, bIsConst>::handlersBefore = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...), bool bIsConst>
TArray<typename HookInvoker<R(C::*)(A...), PMF, bIsConst>::HandlerAfter>* HookInvoker<R(C::*)(A...), PMF, bIsConst>::handlersAfter = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...), bool bIsConst>
R(* HookInvoker<R(C::*)(A...), PMF, bIsConst>::functionPtr)(std::conditional_t<bIsConst, const C*, C*>,A...) = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...), bool bIsConst>
bool HookInvoker<R(C::*)(A...), PMF, bIsConst>::bHookInitialized = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
TArray<typename HookInvoker<R(*)(A...), PMF, false>::Handler>* HookInvoker<R(*)(A...), PMF, false>::handlersBefore = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
TArray<typename HookInvoker<R(*)(A...), PMF, false>::HandlerAfter>* HookInvoker<R(*)(A...), PMF, false>::handlersAfter = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
R(* HookInvoker<R(*)(A...), PMF, false>::functionPtr)(A...) = nullptr;
template <typename R, typename... A, R(*PMF)(A...)>
bool HookInvoker<R(*)(A...), PMF, false>::bHookInitialized = false;

#define SUBSCRIBE_METHOD(MethodReference, Handler) \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference>::Value::InstallHook(TEXT(#MethodReference)); \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference>::Value::addHandlerBefore(Handler);

#define SUBSCRIBE_METHOD_AFTER(MethodReference, Handler) \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference>::Value::InstallHook(TEXT(#MethodReference)); \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference>::Value::addHandlerAfter(Handler);

#define SUBSCRIBE_METHOD_VIRTUAL(MethodReference, SampleObjectInstance, Handler) \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference>::Value::InstallHook(TEXT(#MethodReference), SampleObjectInstance); \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference>::Value::addHandlerBefore(Handler);

#define SUBSCRIBE_METHOD_VIRTUAL_AFTER(MethodReference, SampleObjectInstance, Handler) \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference>::Value::InstallHook(TEXT(#MethodReference), SampleObjectInstance); \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference>::Value::addHandlerAfter(Handler);
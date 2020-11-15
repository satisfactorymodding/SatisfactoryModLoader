#pragma once
#include "CoreMinimal.h"
#include <functional>
#include <type_traits>

DECLARE_LOG_CATEGORY_EXTERN(LogNativeHookManager, Log, Log);
struct BootstrapAccessors;

class SML_API FNativeHookManagerInternal {
public:
	static void* GetHandlerListInternal(const FString& SymbolName);
	static void SetHandlerListInstanceInternal(const FString& SymbolName, void* handlerList);

	static FString RegisterVirtualHookFunction(const struct VirtualFunctionOverrideInfo& SearchInfo, void* HookFunctionPointer, void** OutTrampolineFunction);
	static FString RegisterHookFunction(const FString& SymbolSearchName, void* HookFunctionPointer, void** OutTrampolineFunction);
private:
	friend class FSatisfactoryModLoader;
	static TSharedPtr<BootstrapAccessors> BootstrapAccessorsPtr;

	static void SetupWithAccessors(const BootstrapAccessors& Accessors);
};

struct VirtualFunctionOverrideInfo {
	FString SymbolSearchName;
	FString ClassTypeName;
	void* MemberFunctionPtr;
	size_t MemberFunctionPtrSize;
};

template <typename T, typename E>
struct THandlerLists {
	TArray<T> HandlersBefore;
	TArray<E> HandlersAfter;
};

template <typename T, typename E>
THandlerLists<T, E>* createHandlerLists(const FString& identifier) {
	void* handlerListRaw = FNativeHookManagerInternal::GetHandlerListInternal(identifier);
	if (handlerListRaw == nullptr) {
		handlerListRaw = new THandlerLists<T, E>();
		FNativeHookManagerInternal::SetHandlerListInstanceInternal(identifier, handlerListRaw);
	}
	return static_cast<THandlerLists<T, E>*>(handlerListRaw);
}

template <typename TCallable, TCallable Callable, typename TargetClass, bool bIsConst>
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
struct HookInvoker<R(*)(A...), PMF, None, false> {
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
	static void InstallHook(const FString& SymbolName) {
#if !WITH_EDITOR
		if (!bHookInitialized) {
			bHookInitialized = true;
			void* HookFunctionPointer = static_cast<void*>(getApplyCall());
			const FString SymbolKey = FNativeHookManagerInternal::RegisterHookFunction(SymbolName, HookFunctionPointer, (void**) &functionPtr);
			auto* HandlerLists = createHandlerLists<Handler, HandlerAfter>(SymbolKey);
			handlersBefore = &HandlerLists->HandlersBefore;
			handlersAfter = &HandlerLists->HandlersAfter;
		}
#endif
	}
public:
	static void addHandlerBefore(Handler handler) {
#if !WITH_EDITOR
		handlersBefore->Add(handler);
#endif
	}

	static void addHandlerAfter(HandlerAfter handler) {
#if !WITH_EDITOR
		handlersAfter->Add(handler);
#endif
	}
};

template<typename CallableType, typename NewTarget>
struct RetargetFuncType;

//Template which purpose is re-targeting member function signature from type C to type NewTarget
//It is needed because when function is not overriden in child class,
//compiler will treat ChildClass::Function type as ParentClass::Function type, producing
//incorrect member function pointer and class name. Re-targeting to parent solves this,
//and function always gets correct child class this type
template <typename R, typename C, typename... A, typename NewTarget>
struct RetargetFuncType<R(C::*)(A...), NewTarget> {
public:
	typedef R(NewTarget::*Value)(A...);
};

//Template which is used for erasing const from method pointer
//passed to HookInvoker, since HookInvoker cannot properly handle const method hooks
template<typename TCallable, TCallable Callable, typename TargetClass>
struct HookInvokerWrapper {
public:
	using Value = HookInvoker<TCallable, (TCallable) Callable, TargetClass, false>;
};

template <typename R, typename C, typename... A, R(C::*PMF)(A...) const, typename TargetClass>
struct HookInvokerWrapper<R(C::*)(A...) const, PMF, TargetClass> {
public:
	using FunctionType = R(C::*)(A...);
    using Value = HookInvoker<FunctionType, (FunctionType) PMF, TargetClass, true>;
};

template <typename TCallable, TCallable Callable>
struct HookInvokerTest;

//Hook invoker for member functions
template <typename R, typename C, typename... A, R(C::*PMF)(A...)>
struct HookInvokerTest<R(C::*)(A...), PMF>
{
};

//Hook invoker for member functions
template <typename R, typename C, typename... A, R(C::*PMF)(A...), typename TargetClass, bool bIsConst>
struct HookInvoker<R(C::*)(A...), PMF, TargetClass, bIsConst>
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
        auto myTrampoline = [&](ConstCorrectThisPtr self_, A... args_) -> R {
            (reinterpret_cast<R*(*)(ConstCorrectThisPtr, R*, A...)>(functionPtr))(self_, outReturnValue, args_...);
            return *outReturnValue;
        };

    	ScopeType scope(handlersBefore, myTrampoline);
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
	static void InstallHook(const FString& SymbolSearchName) {
#if !WITH_EDITOR
		if (!bHookInitialized) {
			bHookInitialized = true;
			void* HookFunctionPointer = static_cast<void*>(getApplyCall());
			const FString SymbolKey = FNativeHookManagerInternal::RegisterHookFunction(SymbolSearchName, HookFunctionPointer, (void**) &functionPtr);
			auto* HandlerLists = createHandlerLists<Handler, HandlerAfter>(SymbolKey);
			handlersBefore = &HandlerLists->HandlersBefore;
			handlersAfter = &HandlerLists->HandlersAfter;
		}
#endif
	}

	//Handles virtual function hooking, which only requires correct function pointer for given class
	//To automatically infer class name, virtual table offset and this adjustment
	////and be able to override any virtual function for the class
	template<typename T>
	static void InstallVirtualFunctionHook(const FString& SymbolDisplayName, T MemberFunctionPointer) {
#if !WITH_EDITOR
		//TargetClass parameter matters when hooking virtual functions
		static_assert(std::is_base_of<C, TargetClass>::value, "SUBSCRIBE_VIRTUAL_FUNCTION: TargetClass is not a child of function pointer class");
		FMemberFunctionStruct<T> MemberStruct{MemberFunctionPointer};
		FString ClassName = typeid(TargetClass).name();
		//Strip (class | struct | union ) from type name
		int32 FirstSpaceIndex;
		ClassName.FindChar(' ', FirstSpaceIndex);
		if (FirstSpaceIndex != INDEX_NONE) {
			ClassName = ClassName.Mid(FirstSpaceIndex + 1);
		}
		const VirtualFunctionOverrideInfo OverrideInfo{SymbolDisplayName, ClassName, &MemberStruct, sizeof(MemberStruct)};
		void* HookFunctionPointer = static_cast<void*>(getApplyCall());
		const FString SymbolKey = FNativeHookManagerInternal::RegisterVirtualHookFunction(OverrideInfo, HookFunctionPointer, (void**) &functionPtr);
		auto* HandlerLists = createHandlerLists<Handler, HandlerAfter>(SymbolKey);
		handlersBefore = &HandlerLists->HandlersBefore;
		handlersAfter = &HandlerLists->HandlersAfter;
#endif
	}
public:
	static void addHandlerBefore(Handler handler) {
#if !WITH_EDITOR
		handlersBefore->Add(handler);
#endif
	}

	static void addHandlerAfter(HandlerAfter handler) {
#if !WITH_EDITOR
		handlersAfter->Add(handler);
#endif
	}
};

template <typename R, typename C, typename... A, R(C::*PMF)(A...), typename TargetClass, bool bIsConst>
TArray<typename HookInvoker<R(C::*)(A...), PMF, TargetClass, bIsConst>::Handler>* HookInvoker<R(C::*)(A...), PMF, TargetClass, bIsConst>::handlersBefore = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...), typename TargetClass, bool bIsConst>
TArray<typename HookInvoker<R(C::*)(A...), PMF, TargetClass, bIsConst>::HandlerAfter>* HookInvoker<R(C::*)(A...), PMF, TargetClass, bIsConst>::handlersAfter = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...), typename TargetClass, bool bIsConst>
R(* HookInvoker<R(C::*)(A...), PMF, TargetClass, bIsConst>::functionPtr)(std::conditional_t<bIsConst, const C*, C*>,A...) = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...), typename TargetClass, bool bIsConst>
bool HookInvoker<R(C::*)(A...), PMF, TargetClass, bIsConst>::bHookInitialized = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
TArray<typename HookInvoker<R(*)(A...), PMF, None, false>::Handler>* HookInvoker<R(*)(A...), PMF, None, false>::handlersBefore = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
TArray<typename HookInvoker<R(*)(A...), PMF, None, false>::HandlerAfter>* HookInvoker<R(*)(A...), PMF, None, false>::handlersAfter = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
R(* HookInvoker<R(*)(A...), PMF, None, false>::functionPtr)(A...) = nullptr;
template <typename R, typename... A, R(*PMF)(A...)>
bool HookInvoker<R(*)(A...), PMF, None, false>::bHookInitialized = false;

#define SUBSCRIBE_METHOD(MethodReference, Handler) \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference, None>::Value::InstallHook(#MethodReference); \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference, None>::Value::addHandlerBefore(Handler);

#define SUBSCRIBE_METHOD_AFTER(MethodReference, Handler) \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference, None>::Value::InstallHook(#MethodReference); \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference, None>::Value::addHandlerAfter(Handler);

#define SUBSCRIBE_VIRTUAL_FUNCTION(TargetClass, MethodReference, Handler) \
HookInvokerWrapper<RetargetFuncType<decltype(&MethodReference), TargetClass>::Value, (RetargetFuncType<decltype(&MethodReference), TargetClass>::Value) &MethodReference, TargetClass>::Value::InstallVirtualFunctionHook<RetargetFuncType<decltype(&MethodReference), TargetClass>::Value>(#MethodReference, &MethodReference); \
HookInvokerWrapper<RetargetFuncType<decltype(&MethodReference), TargetClass>::Value, (RetargetFuncType<decltype(&MethodReference), TargetClass>::Value) &MethodReference, TargetClass>::Value::addHandlerBefore(Handler);

#define SUBSCRIBE_VIRTUAL_FUNCTION_AFTER(TargetClass, MethodReference, Handler) \
HookInvokerWrapper<RetargetFuncType<decltype(&MethodReference), TargetClass>::Value, (RetargetFuncType<decltype(&MethodReference), TargetClass>::Value) &MethodReference, TargetClass>::Value::InstallVirtualFunctionHook<RetargetFuncType<decltype(&MethodReference), TargetClass>::Value>(#MethodReference, &MethodReference); \
HookInvokerWrapper<RetargetFuncType<decltype(&MethodReference), TargetClass>::Value, (RetargetFuncType<decltype(&MethodReference), TargetClass>::Value) &MethodReference, TargetClass>::Value::addHandlerAfter(Handler);

#define SUBSCRIBE_METHOD_MANUAL(MethodName, MethodReference, Handler) \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference, None>::Value::InstallHook(MethodName); \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference, None>::Value::addHandlerBefore(Handler);

#define SUBSCRIBE_METHOD_AFTER_MANUAL(MethodName, MethodReference, Handler) \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference, None>::Value::InstallHook(MethodName); \
HookInvokerWrapper<decltype(&MethodReference), &MethodReference, None>::Value::addHandlerAfter(Handler);

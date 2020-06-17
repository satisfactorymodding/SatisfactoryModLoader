#pragma once

#include "CoreMinimal.h"
#include <functional>
#include <type_traits>

SML_API void* GetHandlerListInternal(const FString& SymbolName);

SML_API void SetHandlerListInstanceInternal(const FString& SymbolName, void* handlerList);

struct VirtualFunctionOverrideInfo {
	FString SymbolSearchName;
	FString ClassTypeName;
	void* MemberFunctionPtr;
	size_t MemberFunctionPtrSize;
};

SML_API FString RegisterVirtualHookFunction(const VirtualFunctionOverrideInfo& SearchInfo, void* HookFunctionPointer, void** OutTrampolineFunction);
SML_API FString RegisterHookFunction(const FString& SymbolSearchName, void* HookFunctionPointer, void** OutTrampolineFunction);

template <typename T, typename E>
struct THandlerLists {
	TArray<T> HandlersBefore;
	TArray<E> HandlersAfter;
};

template <typename T, typename E>
THandlerLists<T, E>* createHandlerLists(const FString& identifier) {
	void* handlerListRaw = GetHandlerListInternal(identifier);
	if (handlerListRaw == nullptr) {
		handlerListRaw = new THandlerLists<T, E>();
		SetHandlerListInstanceInternal(identifier, handlerListRaw);
	}
	return static_cast<THandlerLists<T, E>*>(handlerListRaw);
}

template <typename TCallable, TCallable Callable, typename TargetClass>
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
	typedef Result HookType(Args...);
	typedef void HookFuncSig(CallScope<Result(*)(Args...)>&, Args...);
	typedef std::function<HookFuncSig> HookFunc;

private:
	TArray<HookFunc>* functionList;
	size_t handlerPtr = 0;
	HookType* function;
	
	bool forwardCall = true;
	Result result;

public:
	CallScope(TArray<HookFunc>* functionList, HookType* function) : functionList(functionList), function(function) {}

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

template <typename Result, typename C, typename... Args>
struct CallScope<Result(C::*)(Args...)> : public CallScope<Result(*)(C*, Args...)> {};

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
struct HookInvoker<R(*)(A...), PMF, None> {
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
		if (!bHookInitialized) {
			bHookInitialized = true;
			void* HookFunctionPointer = static_cast<void*>(getApplyCall());
			const FString SymbolKey = RegisterHookFunction(SymbolName, HookFunctionPointer, (void**) &functionPtr);
			auto* HandlerLists = createHandlerLists<Handler, HandlerAfter>(SymbolKey);
			handlersBefore = &HandlerLists->HandlersBefore;
			handlersAfter = &HandlerLists->HandlersAfter;
		}
	}
public:
	static void addHandlerBefore(Handler handler) {
		handlersBefore->Add(handler);
	}

	static void addHandlerAfter(HandlerAfter handler) {
		handlersAfter->Add(handler);
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

//Hook invoker for member functions
template <typename R, typename C, typename... A, R(C::*PMF)(A...), typename TargetClass>
struct HookInvoker<R(C::*)(A...), PMF, TargetClass> {
public:
	typedef CallScope<R(*)(C*, A...)> ScopeType;
	// mod handler function
	typedef void HandlerSignature(ScopeType&, C*, A...);
	typedef typename HandlerAfterFunc<R, C*, A...>::Value HandlerSignatureAfter;
	typedef R HookType(C*, A...);
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
	static R applyCall(C* self, A... args) {
		ScopeType scope(handlersBefore, functionPtr);
		scope(self, args...);
		if (handlersAfter) for (HandlerAfter& handler : *handlersAfter) handler(scope.getResult(), self, args...);
		return scope.getResult();
	}

	static void applyCallVoid(C* self, A... args) {
		ScopeType scope(handlersBefore, functionPtr);
		scope(self, args...);
		if (handlersAfter) for (HandlerAfter& handler : *handlersAfter) handler(self, args...);
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
	//Handles normal member function hooking, e.g hooking fixed symbol implementation in executable
	static void InstallHook(const FString& SymbolSearchName) {
		if (!bHookInitialized) {
			bHookInitialized = true;
			void* HookFunctionPointer = static_cast<void*>(getApplyCall());
			const FString SymbolKey = RegisterHookFunction(SymbolSearchName, HookFunctionPointer, (void**) &functionPtr);
			auto* HandlerLists = createHandlerLists<Handler, HandlerAfter>(SymbolKey);
			handlersBefore = &HandlerLists->HandlersBefore;
			handlersAfter = &HandlerLists->HandlersAfter;
		}
	}

	//Handles virtual function hooking, which only requires correct function pointer for given class
	//To automatically infer class name, virtual table offset and this adjustment
	////and be able to override any virtual function for the class
	template<typename T>
	static void InstallVirtualFunctionHook(const FString& SymbolDisplayName, T MemberFunctionPointer) {
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
		const FString SymbolKey = RegisterVirtualHookFunction(OverrideInfo, HookFunctionPointer, (void**) &functionPtr);
		auto* HandlerLists = createHandlerLists<Handler, HandlerAfter>(SymbolKey);
		handlersBefore = &HandlerLists->HandlersBefore;
		handlersAfter = &HandlerLists->HandlersAfter;
	}
public:
	static void addHandlerBefore(Handler handler) {
		handlersBefore->Add(handler);
	}

	static void addHandlerAfter(HandlerAfter handler) {
		handlersAfter->Add(handler);
	}
};

template <typename R, typename C, typename... A, R(C::*PMF)(A...), typename TargetClass>
TArray<std::function<void(CallScope<R(*)(C*,A...)>&, C*, A...)>>* HookInvoker<R(C::*)(A...), PMF, TargetClass>::handlersBefore = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...), typename TargetClass>
TArray<std::function<typename HandlerAfterFunc<R, C*, A...>::Value>>* HookInvoker<R(C::*)(A...), PMF, TargetClass>::handlersAfter = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...), typename TargetClass>
R(* HookInvoker<R(C::*)(A...), PMF, TargetClass>::functionPtr)(C*,A...) = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...), typename TargetClass>
bool HookInvoker<R(C::*)(A...), PMF, TargetClass>::bHookInitialized = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
TArray<std::function<void(CallScope<R(*)(A...)>&, A...)>>* HookInvoker<R(*)(A...), PMF, None>::handlersBefore = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
TArray<std::function<typename HandlerAfterFunc<R, A...>::Value>>* HookInvoker<R(*)(A...), PMF, None>::handlersAfter = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
R(* HookInvoker<R(*)(A...), PMF, None>::functionPtr)(A...) = nullptr;
template <typename R, typename... A, R(*PMF)(A...)>
bool HookInvoker<R(*)(A...), PMF, None>::bHookInitialized = false;

#define SUBSCRIBE_METHOD(MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference, None>::InstallHook(#MethodReference); \
HookInvoker<decltype(&MethodReference), &MethodReference, None>::addHandlerBefore(Handler);

#define SUBSCRIBE_METHOD_AFTER(MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference, None>::InstallHook(#MethodReference); \
HookInvoker<decltype(&MethodReference), &MethodReference, None>::addHandlerAfter(Handler);

#define SUBSCRIBE_VIRTUAL_FUNCTION(TargetClass, MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference, TargetClass>::InstallVirtualFunctionHook<RetargetFuncType<decltype(&MethodReference), TargetClass>::Value>(#MethodReference, &MethodReference); \
HookInvoker<decltype(&MethodReference), &MethodReference, TargetClass>::addHandlerBefore(Handler);

#define SUBSCRIBE_VIRTUAL_FUNCTION_AFTER(TargetClass, MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference, TargetClass>::InstallVirtualFunctionHook<RetargetFuncType<decltype(&MethodReference), TargetClass>::Value>(#MethodReference, &MethodReference); \
HookInvoker<decltype(&MethodReference), &MethodReference, TargetClass>::addHandlerAfter(Handler);

#define SUBSCRIBE_METHOD_MANUAL(MethodName, MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference, None>::InstallHook(MethodName); \
HookInvoker<decltype(&MethodReference), &MethodReference, None>::addHandlerBefore(Handler);

#define SUBSCRIBE_METHOD_AFTER_MANUAL(MethodName, MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference, None>::InstallHook(MethodName); \
HookInvoker<decltype(&MethodReference), &MethodReference, None>::addHandlerAfter(Handler);

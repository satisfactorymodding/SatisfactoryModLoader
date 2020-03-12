#pragma once

#include <vector>
#include <functional>
#include <string>
#include <type_traits>

SML_API void* getHandlerListInternal(const std::string& symbolName);

SML_API void setHandlerListInstanceInternal(const std::string& symbolName, void* handlerList);

SML_API void* registerHookFunction(const std::string& symbolName, void* hookFunction);

SML_API std::string decorateSymbolName(const char* functionName, const char* symbolType);

template <typename F>
std::vector<F>* createHandlerList(const std::string& identifier) {
	void* handlerListRaw = getHandlerListInternal(identifier);
	if (handlerListRaw == nullptr) {
		handlerListRaw = new std::vector<F>();
		setHandlerListInstanceInternal(identifier, handlerListRaw);
	}
	return static_cast<std::vector<F>*>(handlerListRaw);
}

template <typename TCallable, TCallable Callable>
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
	std::vector<HookFunc>* functionList;
	size_t handlerPtr = 0;
	HookType* function;

	bool forwardCall = true;

public:
	CallScope(std::vector<HookFunc>* functionList, HookType* function) : functionList(functionList), function(function) {}

	inline bool shouldForwardCall() {
		return forwardCall;
	}

	void Cancel() {
		forwardCall = false;
	}

	inline void operator()(Args... args) {
		if (functionList == nullptr || handlerPtr >= functionList->size()) {
			function(args...);
			forwardCall = false;
		} else {
			auto cachePtr = handlerPtr + 1;
			auto& handler = functionList->at(handlerPtr++);
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
	std::vector<HookFunc>* functionList;
	size_t handlerPtr = 0;
	HookType* function;
	
	bool forwardCall = true;
	Result result;

public:
	CallScope(std::vector<HookFunc>* functionList, HookType* function) : functionList(functionList), function(function) {}

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

	inline void operator()(Args... args) {
		if (functionList == nullptr || handlerPtr >= functionList->size()) {
			result = function(args...);
			this->forwardCall = false;
		} else {
			auto cachePtr = handlerPtr + 1;
			auto handler = functionList->at(handlerPtr++);
			handler(*this, args...);
			if (handlerPtr == cachePtr && forwardCall) {
				(*this)(args...);
			}
		}
	}
};

template <typename Result, typename C, typename... Args>
struct CallScope<Result(C::*)(Args...)> : public CallScope<Result(*)(C*, Args...)> {};

template<typename Ret, typename... A>
class HandlerAfterFunc : public std::function<void(Ret, A...)> {};
template<typename... A>
class HandlerAfterFunc<void, A...> : public std::function<void(A...)> {};

//Hook invoker for global functions
template <typename R, typename... A, R(*PMF)(A...)>
struct HookInvoker<R(*)(A...), PMF> {
public:
	typedef CallScope<R(*)(A...)> ScopeType;
	// mod handler function
	typedef void HandlerSignature(ScopeType&, A...);
	typedef void HandlerSignatureAfter(const R&, A...);
	typedef R HookType(A...);
	typedef R ReturnType;

	// support arbitrary context for handlers
	typedef std::function<HandlerSignature> Handler;
	typedef HandlerAfterFunc<R, A...> HandlerAfter;
private:
	static std::vector<Handler>* handlersBefore;
	static std::vector<HandlerAfter>* handlersAfter;
	static HookType* functionPtr;
public:
	static R applyCall(A... args) {
		ScopeType scope(handlersBefore, functionPtr);
		scope(args...);
		if (handlersAfter) for (HandlerAfter& handler : * handlersAfter) handler(result, args...);
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

	static void installHook(const std::string& symbolName) {
		if (handlersBefore == nullptr) {
			handlersBefore = createHandlerList<HandlerSignature>(symbolName);
			if (functionPtr == nullptr) functionPtr = (HookType*) registerHookFunction(symbolName, static_cast<void*>(getApplyCall()));
		}
	}

	static void installHookAfter(const std::string& symbolName) {
		if (handlersAfter == nullptr) {
			handlersAfter = createHandlerList<HandlerSignatureAfter>(symbolName);
			if (functionPtr == nullptr) functionPtr = (HookType*) registerHookFunction(symbolName, static_cast<void*>(getApplyCall()));
		}
	}

public:
	static void addHandlerBefore(const char* methodName, Handler handler) {
		const std::string symbolName = decorateSymbolName(methodName, typeid(PMF).name());
		installHook(symbolName);
		handlersBefore->push_back(handler);
	}

	static void addHandlerAfter(const char* methodName, HandlerAfter handler) {
		const std::string symbolName = decorateSymbolName(methodName, typeid(PMF).name());
		installHookAfter(symbolName);
		handlersAfter->push_back(handler);
	}
};

//Hook invoker for member functions
template <typename R, typename C, typename... A, R(C::*PMF)(A...)>
struct HookInvoker<R(C::*)(A...), PMF> {
public:
	typedef CallScope<R(*)(C*, A...)> ScopeType;
	// mod handler function
	typedef void HandlerSignature(ScopeType&, C*, A...);
	typedef R HookType(C*, A...);
	typedef R ReturnType;

	// support arbitrary context for handlers
	typedef std::function<HandlerSignature> Handler;
	typedef HandlerAfterFunc<R, C*, A...> HandlerAfter;
private:
	static std::vector<Handler>* handlersBefore;
	static std::vector<HandlerAfter>* handlersAfter;
	static HookType* functionPtr;
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

	static void installHook(const std::string& symbolName) {
		if (handlersBefore == nullptr) {
			handlersBefore = createHandlerList<Handler>(symbolName);
			if (functionPtr == nullptr) functionPtr = (HookType*) registerHookFunction(symbolName, static_cast<void*>(getApplyCall()));
		}
	}

	static void installHookAfter(const std::string& symbolName) {
		if (handlersAfter == nullptr) {
			handlersAfter = createHandlerList<HandlerAfter>(symbolName);
			if (functionPtr == nullptr) functionPtr = (HookType*) registerHookFunction(symbolName, static_cast<void*>(getApplyCall()));
		}
	}

public:
	static void addHandlerBefore(const char* methodName, Handler handler) {
		const std::string symbolName = decorateSymbolName(methodName, typeid(PMF).name());
		installHook(symbolName);
		handlersBefore->push_back(handler);
	}

	static void addHandlerAfter(const char* methodName, HandlerAfter handler) {
		const std::string symbolName = decorateSymbolName(methodName, typeid(PMF).name());
		installHook(symbolName);
		handlersAfter->push_back(handler);
	}
};

template <typename R, typename C, typename... A, R(C::*PMF)(A...)>
std::vector<std::function<void(CallScope<R(*)(C*,A...)>&, C*, A...)>>* HookInvoker<R(C::*)(A...), PMF>::handlersBefore = nullptr;

template <typename R, typename C, typename... A, R(C:: * PMF)(A...)>
std::vector<HandlerAfterFunc<R, C*, A...>>* HookInvoker<R(C::*)(A...), PMF>::handlersAfter = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...)>
R(* HookInvoker<R(C::*)(A...), PMF>::functionPtr)(C*,A...) = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
std::vector<std::function<void(CallScope<R(*)(A...)>&, A...)>>* HookInvoker<R(*)(A...), PMF>::handlersBefore = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
std::vector<HandlerAfterFunc<R, A...>>* HookInvoker<R(*)(A...), PMF>::handlersAfter = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
R(* HookInvoker<R(*)(A...), PMF>::functionPtr)(A...) = nullptr;

#define SUBSCRIBE_METHOD(MethodName, MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference>::addHandlerBefore(MethodName, Handler);

#define SUBSCRIBE_METHOD_AFTER(MethodName, MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference>::addHandlerAfter(MethodName, Handler);

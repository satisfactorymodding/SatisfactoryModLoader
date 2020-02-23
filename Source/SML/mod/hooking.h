#pragma once

#include <vector>
#include <functional>
#include <string>

SML_API void* getHandlerListInternal(const std::string& symbolName);

SML_API void setHandlerListInstanceInternal(const std::string& symbolName, void* handlerList);

SML_API void* registerHookFunction(const std::string& symbolName, void* hookFunction);

SML_API std::string decorateSymbolName(const char* functionName, const char* symbolType);

template <typename F>
std::vector<std::function<F>>* createHandlerList(const std::string& identifier) {
	void* handlerListRaw = getHandlerListInternal(identifier);
	if (handlerListRaw == nullptr) {
		handlerListRaw = new std::vector<std::function<F>>();
		setHandlerListInstanceInternal(identifier, handlerListRaw);
	}
	return static_cast<std::vector<std::function<F>>*>(handlerListRaw);
}

template <typename TCallable, TCallable Callable>
struct HookInvoker;

template<typename ResultType>
struct CallResult;

//CallResult specialization for void
template <>
struct CallResult<void> {
private:
	bool forwardCall = true;
public:
	inline bool shouldForwardCall() {
		return forwardCall;
	}
public:
	void Cancel() {
		this->forwardCall = false;
	}
};

//general template for other types
template <typename Result>
struct CallResult {
private:
	bool forwardCall = true;
	Result result;
public:
	inline bool shouldForwardCall() {
		return forwardCall;
	}
	inline Result getResult() {
		return result;
	}
public:
	void Override(const Result& newResult) {
		this->forwardCall = false;
		this->result = newResult;
	}
};

//Hook invoker for global functions
template <typename R, typename... A, R(*PMF)(A...)>
struct HookInvoker<R(*)(A...), PMF> {
public:
	// mod handler function
	typedef void HandlerSignature(CallResult<R>&, A...);
	typedef R HookType(A...);
	typedef R ReturnType;

	// support arbitrary context for handlers
	typedef std::function<HandlerSignature> Handler;
private:
	static std::vector<Handler>* handlers;
	static void* functionPtr;
public:
	static R applyCall(A... args) {
		CallResult<R> callResult;
		for (Handler& handler : *handlers) {
			handler(callResult, args...);
			if (!callResult.shouldForwardCall()) break;
		}
		if (callResult.shouldForwardCall()) {
			return ((HookType*)functionPtr)(args...);
		}
		return callResult.getResult();
	}

	static void applyCallVoid(A... args) {
		CallResult<R> callResult;
		for (Handler& handler : *handlers) {
			handler(callResult, args...);
			if (!callResult.shouldForwardCall()) break;
		}
		if (callResult.shouldForwardCall()) {
			((HookType*)functionPtr)(args...);
		}
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
		if (handlers == nullptr) {
			handlers = createHandlerList<HandlerSignature>(symbolName);
			functionPtr = registerHookFunction(symbolName, static_cast<void*>(getApplyCall()));
		}
	}

public:
	static void addHandler(const char* methodName, Handler handler) {
		const std::string symbolName = decorateSymbolName(methodName, typeid(PMF).name());
		installHook(symbolName);
		handlers->push_back(handler);
	}
};

//Hook invoker for member functions
template <typename R, typename C, typename... A, R(C::*PMF)(A...)>
struct HookInvoker<R(C::*)(A...), PMF> {
public:
	// mod handler function
	typedef void HandlerSignature(CallResult<R>&, C*, A...);
	typedef R HookType(C*, A...);
	typedef R ReturnType;

	// support arbitrary context for handlers
	typedef std::function<HandlerSignature> Handler;
private:
	static std::vector<Handler>* handlers;
	static void* functionPtr;
public:
	static R applyCall(C* self, A... args) {
		CallResult<R> callResult;
		for (Handler& handler : *handlers) {
			handler(callResult, self, args...);
			if (!callResult.shouldForwardCall()) break;
		}
		if (callResult.shouldForwardCall()) {
			return ((HookType*)functionPtr)(self, args...);
		}
		return callResult.getResult();
	}

	static void applyCallVoid(C* self, A... args) {
		CallResult<R> callResult;
		for (Handler& handler : *handlers) {
			handler(callResult, self, args...);
			if (!callResult.shouldForwardCall()) break;
		}
		if (callResult.shouldForwardCall()) {
			((HookType*)functionPtr)(self, args...);
		}
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
		if (handlers == nullptr) {
			handlers = createHandlerList<HandlerSignature>(symbolName);
			functionPtr = registerHookFunction(symbolName, static_cast<void*>(getApplyCall()));
		}
	}

public:
	static void addHandler(const char* methodName, Handler handler) {
		const std::string symbolName = decorateSymbolName(methodName, typeid(PMF).name());
		installHook(symbolName);
		handlers->push_back(handler);
	}
};

template <typename R, typename C, typename... A, R(C::*PMF)(A...)>
std::vector<std::function<void(CallResult<R>&, C*, A...)>>* HookInvoker<R(C::*)(A...), PMF>::handlers = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...)>
void* HookInvoker<R(C::*)(A...), PMF>::functionPtr = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
std::vector<std::function<void(CallResult<R>&, A...)>>* HookInvoker<R(*)(A...), PMF>::handlers = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
void* HookInvoker<R(*)(A...), PMF>::functionPtr = nullptr;

#define SUBSCRIBE_METHOD(MethodName, MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference>::addHandler(MethodName, Handler);

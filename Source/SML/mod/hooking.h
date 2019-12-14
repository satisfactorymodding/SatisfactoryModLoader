#pragma once

#include <vector>
#include <functional>

SML_API void* getHandlerListInternal(const char* identifier);

SML_API void setHandlerListInstanceInternal(const char* identifier, void* handlerList);

SML_API void* registerHookFunction(const char* functionName, void* hookFunction);

template <typename F>
std::vector<std::function<F>>* createHandlerList(const char* identifier) {
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

	static void installHook(const char* methodName) {
		if (handlers == nullptr) {
			handlers = createHandlerList<HandlerSignature>(methodName);
			functionPtr = registerHookFunction(methodName, static_cast<void*>(getApplyCall()));
		}
	}

public:
	static void addHandler(const char* methodName, Handler handler) {
		installHook(methodName);
		handlers->push_back(handler);
	}
};

template <typename R, typename C, typename... A, R(C::*PMF)(A...)>
std::vector<std::function<void(CallResult<R>&, C*, A...)>>* HookInvoker<R(C::*)(A...), PMF>::handlers = nullptr;

#define SUBSCRIBE_METHOD(MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference>::addHandler("MethodReference", Handler);

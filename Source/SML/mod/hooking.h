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

//general template for other types
template <typename Result, typename Member>
struct CallScope {
private:
	std::vector<void*>* functionList;
	size_t handlerPtr = 0;
	void* functionPtr;
	
public:
	template<typename T>
	CallScope(void* functionPtr, std::vector<T>* functionList) : functionList((std::vector<void*>*)functionList), functionPtr(functionPtr) {}

	template<typename... Args>
	Result operator()(Member* m, Args&&... args) {
		auto funcList = (std::vector<std::function<Result(CallScope<Result, Member>&, Member*, Args...)>>*)functionList;
		if (handlerPtr >= funcList->size()) {
			return ((Result(*)(Member*, Args...))functionPtr)(m, args...);
		}
		else return (funcList)->at(handlerPtr++)(*this, m, args...);
	}
};

template <typename Result>
struct CallScope<Result, void> {
private:
	std::vector<void*>* functionList;
	size_t handlerPtr = 0;
	void* functionPtr;

public:
	template<typename T>
	CallScope(void* functionPtr, std::vector<T>* functionList) : functionList((std::vector<void*>*)functionList), functionPtr(functionPtr) {}

	template<typename... Args>
	Result operator()(Args&&... args) {
		if (functionList == nullptr || handlerPtr >= functionList->size()) {
			return ((Result(*)(Args...))functionPtr)(args...);
		} else return ((std::vector<std::function<Result(CallScope<Result, void>&, Args...)>>*)functionList)->at(handlerPtr++)(*this, args...);
	}
};

template<typename Ret, typename... A>
class HandlerAfterFunc : public std::function<void(Ret, A...)> {};
template<typename... A>
class HandlerAfterFunc<void, A...> : public std::function<void(A...)> {};

//Hook invoker for global functions
template <typename R, typename... A, R(*PMF)(A...)>
struct HookInvoker<R(*)(A...), PMF> {
public:
	// mod handler function
	typedef R HandlerSignature(CallScope<R, void>&, A...);
	typedef void HandlerSignatureAfter(const R&, A...);
	typedef R HookType(A...);
	typedef R ReturnType;

	// support arbitrary context for handlers
	typedef std::function<HandlerSignature> Handler;
	typedef HandlerAfterFunc<R, A...> HandlerAfter;
private:
	static std::vector<Handler>* handlersBefore;
	static std::vector<HandlerAfter>* handlersAfter;
	static void* functionPtr;
public:
	static R applyCall(A... args) {
		R result = CallScope<R, void>(functionPtr, handlersBefore)(args...);
		if (handlersAfter) for (HandlerAfter& handler : * handlersAfter) handler(result, args...);
		return result;
	}

	static void applyCallVoid(A... args) {
		CallScope<R, void>(functionPtr, handlersBefore)(args...);
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
			if (functionPtr == nullptr) functionPtr = registerHookFunction(symbolName, static_cast<void*>(getApplyCall()));
		}
	}

	static void installHookAfter(const std::string& symbolName) {
		if (handlersAfter == nullptr) {
			handlersAfter = createHandlerList<HandlerSignatureAfter>(symbolName);
			if (functionPtr == nullptr) functionPtr = registerHookFunction(symbolName, static_cast<void*>(getApplyCall()));
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
	// mod handler function
	typedef R HandlerSignature(CallScope<R, C>&, C*, A...);
	typedef R HookType(C*, A...);
	typedef R ReturnType;

	// support arbitrary context for handlers
	typedef std::function<HandlerSignature> Handler;
	typedef HandlerAfterFunc<R, C*, A...> HandlerAfter;
private:
	static std::vector<Handler>* handlersBefore;
	static std::vector<HandlerAfter>* handlersAfter;
	static void* functionPtr;
public:
	static R applyCall(C* self, A... args) {
		R result = CallScope<R, C>(functionPtr, handlersBefore)(self, args...);
		if (handlersAfter) for (HandlerAfter& handler : *handlersAfter) handler(result, self, args...);
		return result;
	}

	static void applyCallVoid(C* self, A... args) {
		CallScope<void, C>(functionPtr, handlersBefore)(self, args...);
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
			if (functionPtr == nullptr) functionPtr = registerHookFunction(symbolName, static_cast<void*>(getApplyCall()));
		}
	}

	static void installHookAfter(const std::string& symbolName) {
		if (handlersAfter == nullptr) {
			handlersAfter = createHandlerList<HandlerAfter>(symbolName);
			if (functionPtr == nullptr) functionPtr = registerHookFunction(symbolName, static_cast<void*>(getApplyCall()));
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
std::vector<std::function<R(CallScope<R, C>&, C*, A...)>>* HookInvoker<R(C::*)(A...), PMF>::handlersBefore = nullptr;

template <typename R, typename C, typename... A, R(C:: * PMF)(A...)>
std::vector<HandlerAfterFunc<R, C*, A...>>* HookInvoker<R(C::*)(A...), PMF>::handlersAfter = nullptr;

template <typename R, typename C, typename... A, R(C::*PMF)(A...)>
void* HookInvoker<R(C::*)(A...), PMF>::functionPtr = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
std::vector<std::function<R(CallScope<R, void>&, A...)>>* HookInvoker<R(*)(A...), PMF>::handlersBefore = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
std::vector<HandlerAfterFunc<R, A...>>* HookInvoker<R(*)(A...), PMF>::handlersAfter = nullptr;

template <typename R, typename... A, R(*PMF)(A...)>
void* HookInvoker<R(*)(A...), PMF>::functionPtr = nullptr;

#define SUBSCRIBE_METHOD(MethodName, MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference>::addHandlerBefore(MethodName, Handler);

#define SUBSCRIBE_METHOD_AFTER(MethodName, MethodReference, Handler) \
HookInvoker<decltype(&MethodReference), &MethodReference>::addHandlerAfter(MethodName, Handler);

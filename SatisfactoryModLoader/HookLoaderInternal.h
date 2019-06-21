#pragma once

/*

This header defines utilities for exposing and hooking into functions in the game binary.

*/

/*

We use the Microsoft Detours library to perform the in-memory patching required for
function hooking. In this case we include a custom header with the necessary forward-
declarations from the Detours library, so that we don't need to include the massive
Windows.h infrastructure everywhere.

*/

#include <util/DetoursFwd.h>

/*

For storage of hook subscribers from loaded mods, we use the standard vector and function
templates.

*/

#include <vector>
#include <functional>

namespace SML {
	namespace Mod {
		namespace Functions {
			/*
			Important data about a hook that SML needs.
			 * use_original_function specifies whether the hooked function should be run or not.
			*/
			struct ModReturns {
				bool useOriginalFunction = true;
			};
		}
	}
}

/*

C++ templates are able to accept values in addition to types, and we use this fact to
create a separate compile-time instantiation for each hookable function.

Typically template value parameters could be used for example to define the size of
a mathematical vector:

template <typename Element, size_t Size>
struct vec;

typedef vec<float, 2> vecf2;
typedef vec<float, 3> vecf3;
typedef vec<float, 4> vecf4;

In our case, however, we actually pass a pointer to a function as the template parameter.
How does this work, if the address of the function is only known after linking?
The answer is that the compiler does not instantiate the template with a physical numeric
address, but a placeholder value that contains the full symbol name of the function in question.

This means that as long as our compiler settings match, and we never actually try to read
the function pointer's value (for example by calling it), we can use the template argument
as an "abstract reference" to a function, allowing us to link together the mod loader
and loaded mods so that they can all refer to the *same* template instantiation, and thus
the same list of subscribers etc.

The HookInvoker template is instantiated once for each game binary function exposed by
the mod loader.

HookInvoker<void (AFGPlayerController::*)(), &AFGPlayerController::BeginPlay>

*/

template <typename TCallable, TCallable Callable>
struct HookInvoker;

/*

HandlerStorage defines the actual objects that store the per-function list of subscribers
and the pointer to the original function in the game binary. Because HandlerStorage is
parameterized by the function in question, each function in the game binary gets its
own vector of handlers.

These per-function vectors exist in the mod loader dll, and are under its control.
Individual mods link against accessor functions defined in the loader dll and thus
are able to subscribe to the shared hook subscriber lists.

HandlerStorage is only ever instantiated by the loader dll, and not by the individual mod dlls.

*/

template <auto Callable, typename Handler>
struct HandlerStorage {
	static std::vector<Handler> handlers;

	/*

	The original field stores a pointer to the original function in the game binary.
	It is used by the global call<>() function to allow calling the original hooked function.

	*/
	static void* original;
};

/*

Define the storage for these objects separately, as required by C++.

*/

template <auto Callable, typename Handler>
std::vector<Handler> HandlerStorage<Callable, Handler>::handlers;

template <auto Callable, typename Handler>
void* HandlerStorage<Callable, Handler>::original;

/*

The HookName template struct is used as a helper to store the exact symbol name
for each hookable function; this name is then passed on to DetourFindFunction.

*/

template <auto Callable>
struct HookName;

/*

This template partial specialization of HookInvoker applies to global functions
and static member functions; there is no this parameter.

We specialize using the return type R and variadic argument types A..., which allows
us to extract the exact return and argument types for the function in question.

These extracted types are then used to generate fast and type-safe invocation code.

*/

template <typename R, typename... A, R(*PF)(A...)>
struct HookInvoker<R(*)(A...), PF> {
public:
	/* The signature that the mod handler functions must conform to. */
	typedef R HandlerSignature(SML::Mod::Functions::ModReturns*, A...);

	/* Expose the return type so that it can be accessed from outside HookInvoker */
	typedef R ReturnType;

	/*

	We use std::function as the handler storage type so that subscribers can pass
	arbitrary additional context to the handlers. For example a mod can use this to
	bind to a class member function with a this parameter instead of a global function,
	or to a lambda function with captured local variables.

	*/
	typedef std::function<HandlerSignature> Handler;

	/*

	A lower-overhead alternative to std::function would be to store a raw function pointer
	instead, but this would lose the ability for mods to pass along additional context,
	which makes mod development more difficult.

	*/
	// typedef HandlerSignature* Handler;

private:
	/*

	This is the full signature of the function in the original game binary.
	We assume that all functions have __fastcall calling convention.

	*/
	typedef R __fastcall HookType(A...);

	/*

	The actual invocation of the registered subscribers happens in the apply and apply_void functions.
	Unfortunately due to limitations of C++ syntax, we need two separate functions here
	because we cannot define a no-op void local variable as the "return value" when the return type
	is void.

	A pointer to the apply function is passed directly to the Detours library, which then patches
	the game in-memory to call this apply function instead of the original function.

	We use the return type and argument types that we extracted from the function signature to
	define the code that accepts those arguments, passes them along to the registered mod subscriber
	functions. The compiler's optimizer has full knowledge of the argument types and is able to
	create an optimal set of instructions to make the invocations very fast. This is especially
	important when hooking functions that are called very frequently by the game.

	*/

	template <typename>
	static R __fastcall apply(A... args) {
		SML::Mod::Functions::ModReturns returns;
		returns.useOriginalFunction = true;

		R ret{};

		for (auto&& handler : HandlerStorage<PF, Handler>::handlers)
			ret = handler(&returns, args...);

		if (returns.useOriginalFunction)
			return ((HookType*)HandlerStorage<PF, Handler>::original)(args...);

		return ret;
	}

	/*

	The void-returning version of the above; the same except there is no return value.

	*/

	template <typename>
	static void __fastcall apply_void(A... args) {
		SML::Mod::Functions::ModReturns returns;
		returns.useOriginalFunction = true;

		for (auto&& handler : HandlerStorage<PF, Handler>::handlers)
			handler(&returns, args...);

		if (returns.useOriginalFunction)
			((HookType*)HandlerStorage<PF, Handler>::original)(args...);
	}

	static constexpr const char gameModule[] = "FactoryGame-Win64-Shipping.exe";

	/*

	Here we need to employ a little bit of C++ arcana to prevent the compiler from trying
	to compile the wrong version of the above functions. We must explicitly choose whether
	we want the void-returning version or not, because the wrong one will cause a syntax
	error and fail compilation.

	Additionally we have to use the superfluous X parameter to prevent the compiler from
	automatically instantiating both functions when the HookInvoker class template instantation
	is exported from the mod loader DLL.

	*/

	template <typename X>
	static HookType* getApply(std::true_type) {
		return &apply_void<X>;
	}

	template <typename X>
	static HookType* getApply(std::false_type) {
		return &apply<X>;
	}

	/*

	Here we check if the hook for the particular game function has already been installed,
	and install it if it's not yet present. install_hook is called whenever a handler is
	registered through subscribe() or called through call(), which means that we do not
	need a separate registration procedure to go through all the functions we want.

	*/

	static void installHook() {
		if (!HandlerStorage<PF, Handler>::original) {
			Detours::DetourTransactionBegin();
			HandlerStorage<PF, Handler>::original = Detours::DetourFindFunction(gameModule, HookName<PF>::Name);
			Detours::DetourAttach(&HandlerStorage<PF, Handler>::original, (void*)getApply<R>(std::is_same<R, void>{}));
			Detours::DetourTransactionCommit();
		}
	}

public:
	/*

	Finally, we have the templated subscribe and call functions, which first
	check that the given function has been detoured, and then either add
	the supplied handler to the list of subscribers, or return a pointer to
	the original game function.

	*/

	static void subscribe(Handler handler) {
		installHook();
		HandlerStorage<PF, Handler>::handlers.push_back(handler);
	}

	static HookType* getOriginal() {
		installHook();
		return (HookType*)HandlerStorage<PF, Handler>::original;
	}
};

/*

Here follows a template partial specialization for instance member functions,
which is very similar to the above except that there is an additional this-parameter
which is passed to the handler functions.

*/

template <typename R, typename C, typename... A, R(C::*PMF)(A...)>
struct HookInvoker<R(C::*)(A...), PMF> {
public:
	// mod handler function
	typedef R HandlerSignature(SML::Mod::Functions::ModReturns*, C*, A...);

	typedef R ReturnType;

	// support arbitrary context for handlers
	typedef std::function<HandlerSignature> Handler;

	// if std::function seems like too much overhead, this typedef can be used for raw function pointers instead
	// typedef HandlerSignature* Handler;

private:
	// detoured function
	typedef R __fastcall HookType(C*, A...);

	template <typename X>
	static HookType* getApply(std::true_type) {
		return &applyVoid<X>;
	}

	template <typename X>
	static HookType* getApply(std::false_type) {
		return &apply<X>;
	}

	template <typename X>
	static R __fastcall apply(C* thiz, A... args) {
		SML::Mod::Functions::ModReturns returns;
		returns.useOriginalFunction = true;

		R ret{};

		for (auto&& handler : HandlerStorage<PMF, Handler>::handlers)
			ret = handler(&returns, thiz, args...);

		if (returns.useOriginalFunction)
			return ((HookType*)HandlerStorage<PMF, Handler>::original)(thiz, args...);

		return ret;
	}

	template <typename X>
	static void __fastcall applyVoid(C* thiz, A... args) {
		SML::Mod::Functions::ModReturns returns;
		returns.useOriginalFunction = true;

		for (auto&& handler : HandlerStorage<PMF, Handler>::handlers)
			handler(&returns, thiz, args...);

		if (returns.useOriginalFunction)
			((HookType*)HandlerStorage<PMF, Handler>::original)(thiz, args...);
	}

	static constexpr const char gameModule[] = "FactoryGame-Win64-Shipping.exe";

	static void installHook() {
		// only if not already installed
		if (!HandlerStorage<PMF, Handler>::original) {
			Detours::DetourTransactionBegin();
			HandlerStorage<PMF, Handler>::original = Detours::DetourFindFunction(gameModule, HookName<PMF>::Name);
			Detours::DetourAttach(&HandlerStorage<PMF, Handler>::original, (void*)getApply<R>(std::is_same<R, void>{}));
			Detours::DetourTransactionCommit();
		}
	}

public:
	static void subscribe(Handler handler) {
		installHook();
		HandlerStorage<PMF, Handler>::handlers.push_back(handler);
	}

	static HookType* getOriginal() {
		installHook();
		return (HookType*)HandlerStorage<PMF, Handler>::original;
	}
};

/*

Here we define a few utility macros to make it easier to export game functions from the mod loader.


SML_HOOK_API - This is either dllexport or dllimport, depending on where it's used from.

EXPORT_METHOD - This uses the "extern template" functionality in C++ to control where the HookInvoker
template code is actually generated, ensuring that it is generated in the mod loader dll and not in
the individual mod dlls.

DEFINE_METHOD - An additional convenience that wraps EXPORT_METHOD and specializes HookName with a
useful default for finding functions from the game binary.

*/

#if defined(HOOKLOADER_EXPORTS)
#if defined(SATISFACTORYMODLOADER_EXPORTS)
#define SML_HOOK_API __declspec(dllexport)
#else
#error Exports must only be done from ModLoader dll
#endif

// Make method available for hooking in mod launcher dll.
// Usage: EXPORT_METHOD(&Foo::Bar).
#define EXPORT_METHOD(...) \
template struct SML_HOOK_API HookInvoker<decltype(&__VA_ARGS__), &__VA_ARGS__>; \
template SML_HOOK_API void subscribe<&__VA_ARGS__>(HookInvoker<decltype(&__VA_ARGS__), &__VA_ARGS__>::Handler handler);
#else
#if defined(SATISFACTORYMODLOADER_EXPORTS)
#define SML_HOOK_API
#else
#define SML_HOOK_API __declspec(dllimport)
#endif

// Import method from mod launcher dll.
// Usage: EXPORT_METHOD(&Foo::Bar).
#define EXPORT_METHOD(...) \
extern template struct SML_HOOK_API HookInvoker<decltype(&__VA_ARGS__), &__VA_ARGS__>; \
extern template SML_HOOK_API void subscribe<&__VA_ARGS__>(HookInvoker<decltype(&__VA_ARGS__), &__VA_ARGS__>::Handler handler);
#endif

// Make method available for hooking in mod API.
// Usage: DEFINE_METHOD(&Foo::Bar).
#define DEFINE_METHOD(PMF) \
template <> struct HookName<&PMF> { static constexpr const char Name[] = #PMF; }; \
EXPORT_METHOD(PMF)

// Make method available as constructor for hooking in mod API.
// Usage: DEFINE_CONSTRUCTOR(Foo, Constructor).
#define DEFINE_CONSTRUCTOR(CLASS, STATICMETHOD) \
template <> struct HookName<&CLASS::STATICMETHOD> { static constexpr const char Name[] = #CLASS "::" #CLASS; }; \
EXPORT_METHOD(CLASS::STATICMETHOD)

// Make method available for hooking in mod API.
// Usage: DEFINE_METHOD_PRE("U", &Foo::Bar) would search for "UFoo::Bar".
#define DEFINE_METHOD_PRE(PREFIX, PMF) \
template <> struct HookName<&PMF> { static constexpr const char Name[] = PREFIX #PMF; }; \
EXPORT_METHOD(PMF)
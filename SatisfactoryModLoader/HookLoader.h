#pragma once

#include "HookLoaderInternal.h"

// Subscribe a handler to a function defined in the game binary.
template <auto HookableFunction>
void subscribe(typename HookInvoker<decltype(HookableFunction), HookableFunction>::Handler handler) {
	HookInvoker<decltype(HookableFunction), HookableFunction>::subscribe(handler);
}

// Directly call a function defined in the game binary.
template <auto HookableFunction, typename... A>
typename HookInvoker<decltype(HookableFunction), HookableFunction>::ReturnType
call(A... args) {
	return HookInvoker<decltype(HookableFunction), HookableFunction>::getOriginal()(args...);
}

namespace SML {
	template <auto HookableFunction>
	void subscribe(typename HookInvoker<decltype(HookableFunction), HookableFunction>::Handler handler) {
		::subscribe(handler);
	}

	template <auto HookableFunction, typename... A>
	typename HookInvoker<decltype(HookableFunction), HookableFunction>::ReturnType
		call(A... args) {
		return HookInvoker<decltype(HookableFunction), HookableFunction>::getOriginal()(args...);
	}
}

namespace SML {
	namespace Objects {
		template <auto HookableFunction>
		void subscribe(typename HookInvoker<decltype(HookableFunction), HookableFunction>::Handler handler) {
			::subscribe(handler);
		}

		template <auto HookableFunction, typename... A>
		typename HookInvoker<decltype(HookableFunction), HookableFunction>::ReturnType
			call(A... args) {
			return HookInvoker<decltype(HookableFunction), HookableFunction>::getOriginal()(args...);
		}
	}
}

namespace SML {
	namespace Mod {
		template <auto HookableFunction>
		void subscribe(typename HookInvoker<decltype(HookableFunction), HookableFunction>::Handler handler) {
			::subscribe(handler);
		}

		template <auto HookableFunction, typename... A>
		typename HookInvoker<decltype(HookableFunction), HookableFunction>::ReturnType
			call(A... args) {
			return HookInvoker<decltype(HookableFunction), HookableFunction>::getOriginal()(args...);
		}
	}
}

namespace SML {
	namespace Utility {
		template <auto HookableFunction>
		void subscribe(typename HookInvoker<decltype(HookableFunction), HookableFunction>::Handler handler) {
			::subscribe(handler);
		}

		template <auto HookableFunction, typename... A>
		typename HookInvoker<decltype(HookableFunction), HookableFunction>::ReturnType
			call(A... args) {
			return HookInvoker<decltype(HookableFunction), HookableFunction>::getOriginal()(args...);
		}
	}
}

namespace SDK {
	template <auto HookableFunction>
	void subscribe(typename HookInvoker<decltype(HookableFunction), HookableFunction>::Handler handler) {
		::subscribe(handler);
	}

	template <auto HookableFunction, typename... A>
	typename HookInvoker<decltype(HookableFunction), HookableFunction>::ReturnType
		call(A... args) {
		return HookInvoker<decltype(HookableFunction), HookableFunction>::getOriginal()(args...);
	}
}
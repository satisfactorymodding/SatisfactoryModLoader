#include "stdafx.h"
#include "FMemory.h"

#include <Windows.h>
#include <detours.h>

#include <util/Utility.h>

namespace SML {
	namespace Objects {
		void*(*FMemory::malloc_f)(std::uint64_t, std::int32_t);
		void*(*FMemory::realloc_f)(void*, std::uint64_t, std::int32_t);
		void(*FMemory::free_f)(void*);

		void FMemory::init() {
			malloc_f = (void*(*)(std::uint64_t, std::int32_t))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "?Malloc@FMemory@@SAPEAX_KI@Z");
			realloc_f = (void*(*)(void*, std::uint64_t, std::int32_t))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "?Realloc@FMemory@@SAPEAXPEAX_KI@Z");
			free_f = (void(*)(void*))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "?Free@FMemory@@SAXPEAX@Z");
		}

		void * FMemory::malloc(std::uint64_t count, std::int32_t alignment) {
			return malloc_f(count, alignment);
		}

		void * FMemory::realloc(void* original, std::uint64_t count, std::int32_t alignment) {
			return realloc_f(original, count, alignment);
		}

		void FMemory::free(void* original) {
			return free_f(original);
		}
	}
}
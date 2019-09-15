#pragma once

#include <Lib.h>

namespace SML {
	namespace Objects {
		class FMemory {
		public:
			enum {
				DEFAULT_ALIGNMENT = 0,
				MIN_ALIGNMENT = 8,
			};

		private:
			SML_API static void*(*malloc_f)(std::uint64_t, std::int32_t);
			SML_API static void*(*realloc_f)(void*, std::uint64_t, std::int32_t);
			SML_API static void(*free_f)(void*);

		public:
			SML_API static void init();

			SML_API static void* malloc(std::uint64_t count, std::int32_t alignment = DEFAULT_ALIGNMENT);
			SML_API static void* realloc(void* original, std::uint64_t count, std::int32_t alignment = DEFAULT_ALIGNMENT);
			SML_API static void free(void* original);
		};
	}
}
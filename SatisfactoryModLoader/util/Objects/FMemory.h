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
			static void*(*malloc_f)(std::uint64_t, std::int32_t);
			static void*(*realloc_f)(void*, std::uint64_t, std::int32_t);
			static void(*free_f)(void*);

		public:
			/**
			* Initializes function pointers
			* gets called automaticly by SML
			*
			* @author Panakotta00
			*/
			SML_API static void init();
			
			/**
			* Allocates a new memory block on unreals heap with the given size
			*
			* @author Panakotta00
			*/
			SML_API static void* malloc(std::uint64_t count, std::int32_t alignment = DEFAULT_ALIGNMENT);
			
			/**
			* Reallocates the given unreal-heap memory block to the given new size
			*
			* @author Panakotta00
			*/
			SML_API static void* realloc(void* original, std::uint64_t count, std::int32_t alignment = DEFAULT_ALIGNMENT);
			
			/**
			* Frees the given unreal-heap memory block
			*
			* @author Panakotta00
			*/
			SML_API static void free(void* original);
		};
	}
}
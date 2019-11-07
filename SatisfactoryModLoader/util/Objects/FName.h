#pragma once

#include <stdint.h>

#include <Lib.h>

namespace SML {
	namespace Objects {
		/**
		* Entry object in global names list
		*/
		class FNameEntry {
		public:
			int index;
			FNameEntry* next;

			union {
				char ansi[1024];
				wchar_t wide[1024];
			};
		};

		/**
		* Container for global names list
		*/
		class TNameEntryArray {
		public:
			enum {
				elemsPerChunk = 16 * 1024,
				chunkTSize = (2 * 1024 * 1024 + elemsPerChunk - 1) / elemsPerChunk
			};

			FNameEntry** chunks[chunkTSize];
			int elemCount;
			int chunkCount;

			FNameEntry const* const& operator[](int index) const;
			FNameEntry const* const* getIPtr(int index) const;
		};

		/**
		* Reference container for a global Name
		*/
		struct FName {
		public:
			int index;
			int count;

			enum EFindName {
				Find,
				Add,
				ReplNotSafe4Threads,
			};

			/**
			* Constructs a empty FName
			*/
			SML_API FName();

			/**
			* Constructs a FName and sets its reference
			*/
			SML_API FName(int i);

			/**
			* Constructs a FName trys to find the global name by the given string or creates a new one
			*/
			SML_API FName(const wchar_t* nameToFind, EFindName FindType = Add);

			/**
			* FName constructor pointer
			*/
			static void(*fNameConstruct_f)(void*, const wchar_t*, EFindName);

			/**
			* Pointer to global names list
			*/
			SML_API static TNameEntryArray *names;

			/**
			* Returns a reference to the global names list
			*/
			SML_API static TNameEntryArray& getNames();

			/**
			* Returns the referenced name as string
			*/
			SML_API const char* getName() const;

			/**
			* Checks if both FNames reference the same name
			*/
			SML_API bool operator==(const FName &other) const;
		};
	}
}
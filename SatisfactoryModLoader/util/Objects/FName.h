#pragma once

#include <stdint.h>

#include <Lib.h>

namespace SML {
	namespace Objects {
		SML_API class FNameEntry {
		public:
			int index;
			FNameEntry* next;

			union {
				char ansi[1024];
				wchar_t wide[1024];
			};
		};

		SML_API class TNameEntryArray {
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

		SML_API struct FName {
		public:
			int index;
			int count;

			enum EFindName {
				Find,
				Add,
				ReplNotSafe4Threads,
			};

			SML_API FName();
			SML_API FName(int i);
			SML_API FName(const wchar_t* nameToFind, EFindName FindType = Add);

			SML_API static void(*fNameConstruct_f)(void*, const wchar_t*, EFindName);
			SML_API static TNameEntryArray *names;
			SML_API static TNameEntryArray& getNames();

			SML_API const char* getName() const;
			SML_API bool operator==(const FName &other) const;
		};
	}
}
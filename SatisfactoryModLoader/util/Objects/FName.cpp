#include <stdafx.h>

#include <unordered_set>

#include "FString.h"
#include "FName.h"

namespace SML {
	namespace Objects {

		// TNameEntryArray

		FNameEntry const* const& TNameEntryArray::operator[](int index) const {
			return *getIPtr(index);
		}

		FNameEntry const* const* TNameEntryArray::getIPtr(int index) const {
			auto chunkI = index / elemsPerChunk;
			auto inChunk = index % elemsPerChunk;
			auto chunk = chunks[chunkI];
			return chunk + inChunk;
		}

		/* FName */

		TNameEntryArray *FName::names = nullptr;

		FName::FName() : index(0), count(0) {}

		FName::FName(int i) : index(i), count(0) {}

		FName::FName(const wchar_t* nameToFind, EFindName FindType) : index(0), count(0) {
			fNameConstruct_f(this, nameToFind, FindType);
		}

		void(*FName::fNameConstruct_f)(void*, const wchar_t*, FName::EFindName) = nullptr;

		TNameEntryArray& FName::getNames() {
			return *names;
		}

		const char* FName::getName() const {
			return getNames()[index]->ansi;
		}

		bool FName::operator==(const FName &other) const {
			return index == other.index;
		};
	}
}
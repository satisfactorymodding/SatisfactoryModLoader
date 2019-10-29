#pragma once

#include "UObject.h"

namespace SML {
	namespace Objects {
		struct FWeakObjectPtr {
			std::int32_t index;
			std::int32_t serial;

			SML_API FWeakObjectPtr(UObject* o);

			SML_API bool isValid() const;
			SML_API UObject* get() const;
			SML_API UObject* operator*() const;
			SML_API UObject* operator->() const;
			SML_API bool operator==(const FWeakObjectPtr& o) const;
			SML_API void operator=(const FWeakObjectPtr& o);
			SML_API void operator=(UObject* o);
			SML_API bool operator<(const FWeakObjectPtr& o) const;
		};
	}
}
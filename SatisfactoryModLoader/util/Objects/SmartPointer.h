#pragma once

#include "UObject.h"

namespace SML {
	namespace Objects {
		struct FWeakObjectPtr {
			std::int32_t index;
			std::int32_t serial;

			SML_API FWeakObjectPtr(UObject* o);

			SML_API bool isValid();
			SML_API UObject* get();
			SML_API UObject* operator*();
			SML_API UObject* operator->();
			SML_API bool operator==(const FWeakObjectPtr& o) const;
			SML_API void operator=(const FWeakObjectPtr& o);
			SML_API void operator=(UObject* o);
			SML_API bool operator<(const FWeakObjectPtr& o) const;
		};
	}
}
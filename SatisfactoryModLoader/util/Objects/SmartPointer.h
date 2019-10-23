#pragma once

#include "UObject.h"

namespace SML {
	namespace Objects {
		class WeakPtr {
		private:
			int serial;
			int index;

		public:
			SML_API WeakPtr(UObject* o);

			SML_API bool isValid();
			SML_API UObject* get();
			SML_API UObject* operator*();
			SML_API UObject* operator->();
			SML_API bool operator==(const WeakPtr& o) const;
			SML_API void operator=(const WeakPtr& o);
			SML_API void operator=(UObject* o);
			SML_API bool operator<(const WeakPtr& o) const;
		};
	}
}
#pragma once

#include "UObject.h"

namespace SML {
	namespace Objects {
		SML_API class UField : public UObject {
		public:
			UField*	next;

			SML_API static UClass* staticClass();
		};
	}
}
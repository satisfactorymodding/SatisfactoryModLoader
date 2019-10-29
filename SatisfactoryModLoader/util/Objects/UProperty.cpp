#include <stdafx.h>

#include "UProperty.h"

namespace SML {
	namespace Objects {
		UClass* UProperty::staticClass() {
			static auto ptr = UObject::findClass("Class CoreUObject.Field");
			return ptr;
		}

		bool UBoolProperty::isSet(void* container) {
			return *getValue<char>(container) & bMask;
		}
	}
}
#include <stdafx.h>

#include "UProperty.h"

namespace SML {
	namespace Objects {
		UClass* UProperty::staticClass() {
			static auto ptr = UObject::findClass("Class CoreUObject.Field");
			return ptr;
		}
	}
}
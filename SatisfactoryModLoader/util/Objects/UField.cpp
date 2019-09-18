#include <stdafx.h>

#include "UField.h"

namespace SML {
	namespace Objects {
		UClass* UField::staticClass() {
			static auto ptr = UObject::findClass("Class CoreUObject.Field");
			return ptr;
		}
	}
}
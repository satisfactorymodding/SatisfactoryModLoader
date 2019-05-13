#define WIN32_LEAN_AND_MEAN

#include <stdafx.h>
#include "Reflection.h"

#include <windows.h>

namespace SML {
	namespace Utility {
		void* get_field_value(void* module, const char* procName) {
			return GetProcAddress((HMODULE)module, procName);
		}
	}
}
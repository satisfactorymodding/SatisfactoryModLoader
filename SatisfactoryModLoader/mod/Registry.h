#pragma once
#include <string>
#include <Windows.h>

namespace SML {
	namespace Mod {
		struct Registry {
			std::string name;
			PVOID func;
		};
	}
}
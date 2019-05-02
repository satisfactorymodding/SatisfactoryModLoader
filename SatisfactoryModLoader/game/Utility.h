#pragma once

#include <HookLoader.h>

#pragma warning (push)
#pragma warning (disable: 4667)

namespace Classes {
	class BuildSettings {
	public:
		// ; const wchar_t *__fastcall BuildSettings::GetBuildVersion()
		static const wchar_t* GetBuildVersion();

	};
}

DEFINE_METHOD(Classes::BuildSettings::GetBuildVersion);

#pragma warning (pop)

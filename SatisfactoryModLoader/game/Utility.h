#pragma once

#include <HookLoader.h>

#pragma warning (push)
#pragma warning (disable: 4667)

namespace SML {
	namespace Objects {
		class BuildSettings {
		public:
			// ; const wchar_t *__fastcall BuildSettings::GetBuildVersion()
			static const wchar_t* GetBuildVersion();
		};

		DEFINE_METHOD(BuildSettings::GetBuildVersion);
	}
}

#pragma warning (pop)

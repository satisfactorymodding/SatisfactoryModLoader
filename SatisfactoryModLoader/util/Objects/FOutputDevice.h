#pragma once

#include <Lib.h>

namespace SML {
	namespace Objects {
		/**
		* Currently we dont know what it does
		*/
		class FOutputDevice {
		public:
			void* vtable;
			bool bSuppressEventTag = false;
			bool bAutoEmitLineTerminator = true;
		};
	}
}
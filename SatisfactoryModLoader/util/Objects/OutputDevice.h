#pragma once

#include <Lib.h>

namespace SML {
	namespace Objects {
		/**
		* Currently we dont know what it does
		*/
		SML_API class OutputDevice {
		public:
			void* vtable;
			bool bSuppressEventTag = false;
			bool bAutoEmitLineTerminator = true;
		};
	}
}
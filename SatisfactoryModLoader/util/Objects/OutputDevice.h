#pragma once

#include <Lib.h>

namespace SML {
	namespace Objects {
		/**
		* Currently we dont know what it does
		*/
		SML_API class OutputDevice {
		public:
			bool bSuppressEventTag = false;
			bool bAutoEmitLineTerminator = true;
		};
	}
}
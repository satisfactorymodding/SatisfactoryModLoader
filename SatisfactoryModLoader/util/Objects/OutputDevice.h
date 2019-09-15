#pragma once

#include <Lib.h>

namespace SML {
	namespace Objects {
		SML_API class OutputDevice {
		public:
			bool bSuppressEventTag = false;
			bool bAutoEmitLineTerminator = true;
		};
	}
}
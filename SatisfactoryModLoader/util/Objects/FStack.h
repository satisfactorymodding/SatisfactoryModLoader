#pragma once

#include <Lib.h>

#include "TArray.h"

namespace SML {
	namespace Objects {
		SML_API class FStack : public TArray<std::uint16_t> {
		public:
			unsigned char uk[32];
		};
	}
}
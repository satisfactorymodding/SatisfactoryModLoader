#pragma once

#include <Lib.h>

#include "TArray.h"

namespace SML {
	namespace Objects {
		/**
		* We currently dont know what it does...
		*/
		class FStack : public TArray<std::uint16_t> {
		public:
			unsigned char unknownData[32];
		};
	}
}
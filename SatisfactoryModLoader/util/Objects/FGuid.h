#pragma once

#include <stdint.h>
#include <Lib.h>
#include "../SatisfactorySDK/SDK.hpp"

namespace SML {
	namespace Objects {
		struct FGuid {
			std::uint32_t a;
			std::uint32_t b;
			std::uint32_t c;
			std::uint32_t d;

			SML_API FGuid(std::uint32_t a = 0, std::uint32_t b = 0, std::uint32_t c = 0, std::uint32_t d = 0);
			SML_API FGuid(const SDK::FGuid& other);
			SML_API FGuid(std::string str);

			SML_API operator SDK::FGuid() const;
			SML_API bool operator==(const FGuid& g) const;

			SML_API std::string toStr() const;
		};
	}
}
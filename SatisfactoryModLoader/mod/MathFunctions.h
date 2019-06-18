#pragma once
#include <../SatisfactorySDK/SDK.hpp>

namespace SML {
	namespace Mod {
		namespace Functions {
			/**
			* Returns a quaternion from a rotator
			*/
			static SDK::FQuat toQuat(const SDK::FRotator& rotator);

			/**
			* Returns a rotator from a quaternion
			*/
			static SDK::FRotator toEuler(const SDK::FQuat& quat);
		}
	}
}
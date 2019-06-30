#pragma once
#include <../SatisfactorySDK/SDK.hpp>
#include <Lib.h>

namespace SML {
	namespace Mod {
		namespace Functions {
			/**
			* Returns a quaternion from a rotator
			*/
			SML_API SDK::FQuat toQuat(const SDK::FRotator& rotator);

			/**
			* Returns a rotator from a quaternion
			*/
			SML_API SDK::FRotator toEuler(const SDK::FQuat& quat);

			/**
			* Initialize an FVector
			*/
			SML_API SDK::FVector makeVector(float x, float y, float z);

			/**
			* Initialize an FRotator
			*/
			SML_API SDK::FRotator makeRotator(float pitch, float roll, float yaw);
		}
	}
}
#pragma once
#include <../SatisfactorySDK/SDK.hpp>
#include <Lib.h>

namespace SML {
	namespace Mod {
		namespace Functions {
			/**
			* Returns a quaternion from a rotator
			*
			* @author Brabb3l
			*/
			SML_API SDK::FQuat toQuat(const SDK::FRotator& rotator);

			/**
			* Returns a rotator from a quaternion
			*
			* @author Brabb3l
			*/
			SML_API SDK::FRotator toEuler(const SDK::FQuat& quat);

			/**
			* Initialize an FVector
			*
			* @author SuperCoder79
			*/
			SML_API SDK::FVector makeVector(float x, float y, float z);

			/**
			* Initialize an FRotator
			*
			* @author SuperCoder79
			*/
			SML_API SDK::FRotator makeRotator(float pitch, float roll, float yaw);
		}
	}
}
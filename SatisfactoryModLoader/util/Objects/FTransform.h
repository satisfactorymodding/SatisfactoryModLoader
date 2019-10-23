#pragma once

#include "FVector.h"
#include "FQuat.h"

namespace SML {
	namespace Objects {
		struct alignas(0x10) FTransform {
			FQuat rotation;
			FVector location;
			FVector scale;
			
			inline FTransform(const FQuat& rotation = FQuat(), const FVector& location = FVector(), const FVector& scale = FVector(1.0f,1.0f,1.0f)) : rotation(rotation), location(location), scale(scale) {}
			inline FTransform(const SDK::FTransform& other) : rotation(other.Rotation), location(other.Translation), scale(other.Scale3D) {}
			
			inline operator SDK::FTransform() { return SDK::FTransform{rotation,location,{},scale}; }
		};
	}
}
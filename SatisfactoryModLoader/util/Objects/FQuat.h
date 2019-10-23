#pragma once

#include "../SatisfactorySDK/SDK.hpp"

namespace SML {
	namespace Objects {
		struct FQuat {
			float X;
			float Y;
			float Z;
			float W;

			inline FQuat(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 0.0f) : X(X), Y(Y), Z(Z), W(W) {}
			inline FQuat(const SDK::FQuat& other) : X(other.X), Y(other.Y), Z(other.Z), W(other.W) {}

			inline operator SDK::FQuat() {
				return SDK::FQuat{X, Y, Z, W};
			}
		};
	}
}
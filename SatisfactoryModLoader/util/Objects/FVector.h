#pragma once

#include <math.h>

#include "../SatisfactorySDK/SDK.hpp"

namespace SML {
	namespace Objects {
		struct FVector {
			float X = 0.0;
			float Y = 0.0;
			float Z = 0.0;

			inline FVector(float X = 0.0) : FVector(X, X, X) {}
			inline FVector(float X, float Y, float Z = 0.0) : X(X), Y(Y), Z(Z) {}
			inline FVector(const SDK::FVector& v) : X(v.X), Y(v.Y), Z(v.Z) {}

			inline operator SDK::FVector() {
				return SDK::FVector{X,Y,Z};
			}

			inline FVector operator+(const FVector& o) {
				return FVector {
					X + o.X,
					Y + o.Y,
					Z + o.Z,
				};
			}

			inline FVector operator-(const FVector& o) {
				return FVector {
					X - o.X,
					Y - o.Y,
					Z - o.Z,
				};
			}

			inline FVector operator*(const FVector& o) {
				return FVector {
					X * o.X,
					Y * o.Y,
					Z * o.Z
				};
			}

			inline FVector operator/(const FVector& o) {
				return FVector {
					X / o.X,
					Y / o.Y,
					Z / o.Z
				};
			}

			inline double scalar(const FVector& o) {
				return X * o.X + Y * o.Y + Z * o.Z;
			}

			inline float length() {
				return sqrt(X*X + Y*Y + Z*Z);
			}
		};
	}
}
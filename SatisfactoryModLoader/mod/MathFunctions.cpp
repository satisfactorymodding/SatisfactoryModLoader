#include <stdafx.h>
#include "MathFunctions.h"


namespace SML {
	namespace Mod {
		namespace Functions {
			SML_API SDK::FQuat toQuat(const SDK::FRotator& rotator) {
				float cy = cosf(rotator.Yaw * 0.5f);
				float sy = sinf(rotator.Yaw * 0.5f);
				float cp = cosf(rotator.Pitch * 0.5f);
				float sp = sinf(rotator.Pitch * 0.5f);
				float cr = cosf(rotator.Roll * 0.5f);
				float sr = sinf(rotator.Roll * 0.5f);

				SDK::FQuat q;
				q.W = cy * cp * cr + sy * sp * sr;
				q.X = cy * cp * sr - sy * sp * cr;
				q.Y = sy * cp * sr + cy * sp * cr;
				q.Z = sy * cp * cr - cy * sp * sr;
				return q;
			}

			SML_API SDK::FRotator toEuler(const SDK::FQuat& quat) {
				float roll;
				float pitch;
				float yaw;

				float sinr_cosp = 2.0f * (quat.W * quat.X + quat.Y * quat.Z);
				float cosr_cosp = 1.0f - 2.0f * (quat.X * quat.X + quat.Y * quat.Y);
				roll = atan2f(sinr_cosp, cosr_cosp);

				float sinp = 2.0f * (quat.W * quat.Y - quat.Z * quat.X);
				if (fabs(sinp) >= 1)
					pitch = copysign(3.14159265358979323846f / 2, sinp); //TODO: Replace with pi
				else
					pitch = asin(sinp);

				float siny_cosp = 2.0f * (quat.W * quat.Z + quat.X * quat.Y);
				float cosy_cosp = 1.0f - 2.0f * (quat.Y * quat.Y + quat.Z * quat.Z);
				yaw = atan2f(siny_cosp, cosy_cosp);

				SDK::FRotator rot = SDK::FRotator();
				rot.Pitch = pitch;
				rot.Roll = roll;
				rot.Yaw = yaw;
				return rot;
			}
			SML_API SDK::FVector makeVector(float x, float y, float z) {
				SDK::FVector vec = SDK::FVector();
				vec.X = x;
				vec.Y = y;
				vec.Z = z;
				return vec;
			}

			SML_API SDK::FRotator makeRotator(float pitch, float roll, float yaw) {
				SDK::FRotator rot = SDK::FRotator();
				rot.Pitch = pitch;
				rot.Roll = roll;
				rot.Yaw = yaw;
				return rot;
			}
		}
	}
}
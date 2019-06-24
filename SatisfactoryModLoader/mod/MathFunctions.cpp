#include <stdafx.h>
#include "MathFunctions.h"


namespace SML {
	namespace Mod {
		namespace Functions {
			SML_API SDK::FQuat toQuat(const SDK::FRotator& rotator) {
				double cy = cos(rotator.Yaw * 0.5);
				double sy = sin(rotator.Yaw * 0.5);
				double cp = cos(rotator.Pitch * 0.5);
				double sp = sin(rotator.Pitch * 0.5);
				double cr = cos(rotator.Roll * 0.5);
				double sr = sin(rotator.Roll * 0.5);

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

				double sinr_cosp = 2.0 * (quat.W * quat.X + quat.Y * quat.Z);
				double cosr_cosp = 1.0 - 2.0 * (quat.X * quat.X + quat.Y * quat.Y);
				roll = atan2(sinr_cosp, cosr_cosp);

				double sinp = 2.0 * (quat.W * quat.Y - quat.Z * quat.X);
				if (fabs(sinp) >= 1)
					pitch = copysign(3.14159265358979323846 / 2, sinp); //TODO: Replace with pi
				else
					pitch = asin(sinp);

				double siny_cosp = 2.0 * (quat.W * quat.Z + quat.X * quat.Y);
				double cosy_cosp = 1.0 - 2.0 * (quat.Y * quat.Y + quat.Z * quat.Z);
				yaw = atan2(siny_cosp, cosy_cosp);

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
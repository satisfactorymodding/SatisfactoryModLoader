// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

/**
 * A collection of unit conversions to make code more readable.
 */
struct FACTORYGAME_API FUnits
{
	/** Distance */
	static constexpr FORCEINLINE float CmToM( float cm ) { return cm / 100.0f; }
	static constexpr FORCEINLINE float MToCm( float m ) { return m * 100.0f; }

	/** Area and Volume */
	static constexpr FORCEINLINE float M2ToCm2( float m2 ) { return m2 * 100.f * 100.f; }
	static constexpr FORCEINLINE float Cm2ToM2( float cm2 ) { return cm2 / ( 100.f * 100.f ); }

	/** Speed */
	static constexpr FORCEINLINE float KmHToCmS( float kmH ) { return kmH * 100000.f / 3600.f; }
	static constexpr FORCEINLINE float CmSToKmH( float cmS ) { return cmS * 3600.f / 100000.f; }

	/** Forces */
	static constexpr FORCEINLINE float kNToN( float kN ) { return kN * 1000.0f; }
	static constexpr FORCEINLINE float NTokN( float kN ) { return kN / 1000.0f; }

	/** Radians to a grade in percent. */
	static FORCEINLINE float RadiansToGrade( float rad )
	{
		const float clamped = FMath::Min( FMath::Abs( rad ), PI / 4.0f );
		return FMath::Tan( clamped ) * 100.0f;
	}

	/** Volume */
	static constexpr FORCEINLINE float LiterToM3( float liter ) { return liter * 1000.f; }
	static constexpr FORCEINLINE float M3ToLiter( float m3 ) { return m3 / 1000.f; }
};

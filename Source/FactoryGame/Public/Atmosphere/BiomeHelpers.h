// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "UFGBiome.h"


inline float GetCurveValue( const FRuntimeFloatCurve& Curve, float Time )
{
	return Curve.ExternalCurve ? Curve.ExternalCurve->GetFloatValue( Time ) : Curve.GetRichCurveConst()->Eval( Time );
}

inline FLinearColor GetCurveValue( const FRuntimeCurveLinearColor& Curve, float Time )
{
	return Curve.GetLinearColorValue( Time );
}

inline void UpdateOrAddKey( FRuntimeFloatCurve& Curve, float time, float value )
{
	fgcheck( !Curve.ExternalCurve );
	Curve.GetRichCurve()->UpdateOrAddKey( time, value );
}

inline void UpdateOrAddKey( FRuntimeCurveLinearColor& Curve, float time, FLinearColor value )
{
	fgcheck( !Curve.ExternalCurve );
	Curve.ColorCurves[0].UpdateOrAddKey( time, value.R );
	Curve.ColorCurves[1].UpdateOrAddKey( time, value.G );
	Curve.ColorCurves[2].UpdateOrAddKey( time, value.B );
	Curve.ColorCurves[3].UpdateOrAddKey( time, value.A );
}

#define BIOME_ATTRIBUTE_NAME( AttrName ) AttrName ## 2


template <typename CurveType>
struct CurveValueTypeImpl;

template <>
struct CurveValueTypeImpl<FRuntimeFloatCurve>
{
	using ValueType = float;
};

template <>
struct CurveValueTypeImpl<FRuntimeCurveLinearColor>
{
	using ValueType = FLinearColor;
};

template <typename CurveType>
using CurveValueType = typename CurveValueTypeImpl<CurveType>::ValueType;

/**
 * Accessors for all of the UFGBiome properties. 
 */ 
struct FBiomeHelpers
{
#define NAMED_ATTRIBUTE( AttrName ) \
	static TOptional< CurveValueType<decltype(UFGBiome :: BIOME_ATTRIBUTE_NAME(AttrName) )> > Get ## AttrName ( UFGBiome *biome, const float TimeOfDay ) \
	{ \
		while ( biome != nullptr && !biome->Override ## AttrName ) \
		{ \
			biome = biome->BaseBiome; \
		} \
		if ( biome ) \
		{ \
			return GetCurveValue( biome->BIOME_ATTRIBUTE_NAME(AttrName), TimeOfDay ); \
		} \
		return {}; \
	}
#include "BiomeAttributes.inl"



	static void GetExponentialFogSettings( UFGBiome *biome, float atTime, struct FExponentialFogSettings& out_settings );
	static void GetSkySphereSettings( UFGBiome *biome, float atTime, struct FSkySphereSettings& out_settings );
	static void GetAtmosphereSettings( UFGBiome *biome, float atTime, struct FSkyAtmosphereSettings& out_settings );
};


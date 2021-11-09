// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Atmosphere/UFGBiome.h"


/**
 * Accessors for all of the UFGBiome properties. 
 */ 
struct FBiomeHelpers
{
#define NAMED_ATTRIBUTE( AttrName ) \
	static TOptional< decltype(UFGBiome :: AttrName)::ValueType > Get ## AttrName ( UFGBiome *biome, const float TimeOfDay ) \
	{ \
		while ( biome != nullptr && !biome->Override ## AttrName ) \
		{ \
			biome = biome->BaseBiome; \
		} \
		if ( biome ) \
		{ \
			return biome->AttrName.ValueAt( TimeOfDay ); \
		} \
		return {}; \
	}
#include "BiomeAttributes.inl"



	static void GetExponentialFogSettings( UFGBiome *biome, float atTime, struct FExponentialFogSettings& out_settings );
	static void GetSkySphereSettings( UFGBiome *biome, float atTime, struct FSkySphereSettings& out_settings );
	static void GetAtmosphereSettings( UFGBiome *biome, float atTime, struct FSkyAtmosphereSettings& out_settings );
};


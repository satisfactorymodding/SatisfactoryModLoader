// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

/**
 * Utility header used for declaratively declaring all of a Biome's attributes. It is a way of implementing pseudo static reflection. Define one (or more)
 * of the interface macros then include this header when you want to generate code for each property of UFGBiome. 
 * Take a look at the example in BiomeHelpers.h
 */

#ifndef NAMED_ATTRIBUTE
    #define NAMED_ATTRIBUTE( AttrName )
#endif 

#ifndef PP_ATTRIBUTE
    #define PP_ATTRIBUTE( AttrName ) NAMED_ATTRIBUTE( AttrName )
#endif 

#ifndef EHF_ATTRIBUTE
    #define EHF_ATTRIBUTE( AttrName ) NAMED_ATTRIBUTE( AttrName )
#endif 

#ifndef SKB_ATTRIBUTE
    #define SKB_ATTRIBUTE( AttrName ) NAMED_ATTRIBUTE( AttrName )
#endif 

#ifndef SKA_ATTRIBUTE
    #define SKA_ATTRIBUTE( AttrName ) NAMED_ATTRIBUTE( AttrName )
#endif 

#ifndef PP_FLOAT_CURVE_ATTRIB
#define PP_FLOAT_CURVE_ATTRIB( AttrName ) PP_ATTRIBUTE( AttrName )
#endif

#ifndef PP_COLOR_CURVE_ATTRIB
#define PP_COLOR_CURVE_ATTRIB( AttrName ) PP_ATTRIBUTE( AttrName )
#endif

#ifndef EHF_FLOAT_CURVE_ATTRIB
#define EHF_FLOAT_CURVE_ATTRIB( AttrName ) EHF_ATTRIBUTE( AttrName ) 
#endif

#ifndef EHF_COLOR_CURVE_ATTRIB
#define EHF_COLOR_CURVE_ATTRIB( AttrName ) EHF_ATTRIBUTE( AttrName )
#endif

#ifndef SKB_FLOAT_CURVE_ATTRIB
#define SKB_FLOAT_CURVE_ATTRIB( AttrName ) SKB_ATTRIBUTE( AttrName )
#endif

#ifndef SKB_COLOR_CURVE_ATTRIB
#define SKB_COLOR_CURVE_ATTRIB( AttrName ) SKB_ATTRIBUTE( AttrName )
#endif

#ifndef SKA_FLOAT_CURVE_ATTRIB
#define SKA_FLOAT_CURVE_ATTRIB( AttrName ) SKA_ATTRIBUTE( AttrName )
#endif

#ifndef SKA_COLOR_CURVE_ATTRIB
#define SKA_COLOR_CURVE_ATTRIB( AttrName ) SKA_ATTRIBUTE( AttrName )
#endif

#ifndef INCLUDE_ADVANCED_ATTRIBUTES
#define INCLUDE_ADVANCED_ATTRIBUTES true
#endif

// Exponential height fog attributes

EHF_FLOAT_CURVE_ATTRIB( FogDensity )
EHF_COLOR_CURVE_ATTRIB( FogInscatteringColor )
EHF_FLOAT_CURVE_ATTRIB( FullyDirectionalInscatteringColorDistance )
EHF_FLOAT_CURVE_ATTRIB( NonDirectionalInscatteringColorDistance )
EHF_FLOAT_CURVE_ATTRIB( DirectionalInscatteringExponent )
EHF_FLOAT_CURVE_ATTRIB( DirectionalInscatteringStartDistance )
EHF_COLOR_CURVE_ATTRIB( DirectionalInscatteringColor )
EHF_FLOAT_CURVE_ATTRIB( FogHeightFalloff )
EHF_FLOAT_CURVE_ATTRIB( FogMaxOpacity )
EHF_FLOAT_CURVE_ATTRIB( StartDistance )
EHF_FLOAT_CURVE_ATTRIB( FogCutoffDistance )
#if INCLUDE_ADVANCED_ATTRIBUTES
EHF_FLOAT_CURVE_ATTRIB( FogHeight )
EHF_FLOAT_CURVE_ATTRIB( SecondFogDensity )
EHF_FLOAT_CURVE_ATTRIB( SecondFogHeightFalloff )
EHF_FLOAT_CURVE_ATTRIB( SecondFogHeightOffset )
#endif


// Skybox attributes
SKB_COLOR_CURVE_ATTRIB( CloudColor )
SKB_COLOR_CURVE_ATTRIB( SunLightColor )
SKB_COLOR_CURVE_ATTRIB( MoonLightColor )
SKB_FLOAT_CURVE_ATTRIB( SunIntensity )
SKB_FLOAT_CURVE_ATTRIB( MoonIntensity )
SKB_FLOAT_CURVE_ATTRIB( CloudOpacity )

// Postprocessing attributes
PP_FLOAT_CURVE_ATTRIB( WhiteTemp )
PP_FLOAT_CURVE_ATTRIB( WhiteTint )

PP_COLOR_CURVE_ATTRIB( ColorSaturation )
PP_COLOR_CURVE_ATTRIB( ColorContrast )
PP_COLOR_CURVE_ATTRIB( ColorGamma )
PP_COLOR_CURVE_ATTRIB( ColorGain )
PP_COLOR_CURVE_ATTRIB( ColorOffset )
PP_COLOR_CURVE_ATTRIB( ColorSaturationShadows )
PP_COLOR_CURVE_ATTRIB( ColorContrastShadows )
PP_COLOR_CURVE_ATTRIB( ColorGammaShadows )
PP_COLOR_CURVE_ATTRIB( ColorGainShadows )
PP_COLOR_CURVE_ATTRIB( ColorOffsetShadows )
PP_COLOR_CURVE_ATTRIB( ColorSaturationMidtones )
PP_COLOR_CURVE_ATTRIB( ColorContrastMidtones )
PP_COLOR_CURVE_ATTRIB( ColorGammaMidtones )
PP_COLOR_CURVE_ATTRIB( ColorGainMidtones )
PP_COLOR_CURVE_ATTRIB( ColorOffsetMidtones )
PP_COLOR_CURVE_ATTRIB( ColorSaturationHighlights )
PP_COLOR_CURVE_ATTRIB( ColorContrastHighlights )
PP_COLOR_CURVE_ATTRIB( ColorGammaHighlights )
PP_COLOR_CURVE_ATTRIB( ColorGainHighlights )
PP_COLOR_CURVE_ATTRIB( ColorOffsetHighlights )
PP_FLOAT_CURVE_ATTRIB( ColorCorrectionHighlightsMin )
PP_FLOAT_CURVE_ATTRIB( ColorCorrectionShadowsMax )
PP_FLOAT_CURVE_ATTRIB( BlueCorrection )
PP_FLOAT_CURVE_ATTRIB( ExpandGamut )
PP_COLOR_CURVE_ATTRIB( SceneColorTint )

PP_FLOAT_CURVE_ATTRIB( FilmSlope )
PP_FLOAT_CURVE_ATTRIB( FilmToe )
PP_FLOAT_CURVE_ATTRIB( FilmShoulder )
PP_FLOAT_CURVE_ATTRIB( FilmBlackClip )
PP_FLOAT_CURVE_ATTRIB( FilmWhiteClip )

SKA_COLOR_CURVE_ATTRIB( RayleighScattering )
SKA_FLOAT_CURVE_ATTRIB( RayleighScatteringScale )
SKA_FLOAT_CURVE_ATTRIB( RayleighExponentialDistribution )
SKA_FLOAT_CURVE_ATTRIB( MieScatteringScale )
SKA_COLOR_CURVE_ATTRIB( MieScattering )
SKA_FLOAT_CURVE_ATTRIB( MieAbsorptionScale )
SKA_COLOR_CURVE_ATTRIB( MieAbsorption )
SKA_FLOAT_CURVE_ATTRIB( MieAnisotropy )
SKA_FLOAT_CURVE_ATTRIB( MieExponentialDistribution )
SKA_FLOAT_CURVE_ATTRIB( OtherAbsorptionScale )
SKA_COLOR_CURVE_ATTRIB( OtherAbsorption )


#undef NAMED_ATTRIBUTE

#undef PP_ATTRIBUTE
#undef PP_COLOR_CURVE_ATTRIB
#undef PP_FLOAT_CURVE_ATTRIB

#undef EHF_ATTRIBUTE
#undef EHF_FLOAT_CURVE_ATTRIB
#undef EHF_COLOR_CURVE_ATTRIB

#undef SKB_ATTRIBUTE
#undef SKB_FLOAT_CURVE_ATTRIB
#undef SKB_COLOR_CURVE_ATTRIB

#undef SKA_ATTRIBUTE
#undef SKA_FLOAT_CURVE_ATTRIB
#undef SKA_COLOR_CURVE_ATTRIB

#undef INCLUDE_ADVANCED_ATTRIBUTES

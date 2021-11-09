// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGCyclicCurve.h"
#include "UFGBiome.generated.h"


UENUM()
enum class EWeatherStateMask : uint8
{
	Clear,
	Cloudy,
	Rainy,
	Windy,
	Stormy,
	Foggy
};

ENUM_CLASS_FLAGS( EWeatherStateMask );
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, Category="Atmosphere & Weather")
class FACTORYGAME_API UFGBiome : public UObject
{
	GENERATED_BODY()

public:
	UFGBiome();

	UPROPERTY( EditAnywhere )
	UFGBiome* BaseBiome = nullptr;
	
	UPROPERTY( EditAnywhere )
	FName DebugName;

	UPROPERTY( EditAnywhere, Category = "Weather", meta = ( Bitmask, BitmaskEnum = "EWeatherStateMask" ) )
	uint8 WeatherStatesMask;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "OverrideFogHeight") )
	FCyclicRuntimeFloatCurve FogHeight;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "OverrideFogDensity") )
	FCyclicRuntimeFloatCurve FogDensity;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "OverrideFogInscatteringColor") )
	FCyclicRuntimeColorCurve FogInscatteringColor;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, meta=(editcondition = "OverrideFullyDirectionalInscatteringColorDistance") )
	FCyclicRuntimeFloatCurve FullyDirectionalInscatteringColorDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, meta=(editcondition = "OverrideNonDirectionalInscatteringColorDistance") )
	FCyclicRuntimeFloatCurve NonDirectionalInscatteringColorDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, meta=(editcondition = "OverrideDirectionalInscatteringExponent") )
	FCyclicRuntimeFloatCurve DirectionalInscatteringExponent;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, meta=(editcondition = "OverrideDirectionalInscatteringStartDistance") )
	FCyclicRuntimeFloatCurve DirectionalInscatteringStartDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "OverrideDirectionalInscatteringColor") )
	FCyclicRuntimeColorCurve DirectionalInscatteringColor;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "OverrideFogHeightFalloff") )
	FCyclicRuntimeFloatCurve FogHeightFalloff;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, meta=(editcondition = "OverrideFogMaxOpacity") )
	FCyclicRuntimeFloatCurve FogMaxOpacity;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "OverrideStartDistance") )
	FCyclicRuntimeFloatCurve StartDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "OverrideFogCutoffDistance") )
	FCyclicRuntimeFloatCurve FogCutoffDistance;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog|SecondFog", meta=(editcondition = "OverrideSecondFogDensity") )
	FCyclicRuntimeFloatCurve SecondFogDensity;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog|SecondFog", meta=(editcondition = "OverrideSecondFogHeightFalloff") )
	FCyclicRuntimeFloatCurve SecondFogHeightFalloff;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog|SecondFog", meta=(editcondition = "OverrideSecondFogHeightOffset") )
	FCyclicRuntimeFloatCurve SecondFogHeightOffset;

	/** How the color of clouds zenith changes during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = (editcondition = "OverrideCloudColor") )
	FCyclicRuntimeColorCurve CloudColor;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = (editcondition = "OverrideSunLightColor") )
	FCyclicRuntimeColorCurve SunLightColor;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = ( editcondition = "OverrideMoonLightColor" ) )
	FCyclicRuntimeColorCurve MoonLightColor;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = ( editcondition = "OverrideSunIntensity" ) )
	FCyclicRuntimeFloatCurve SunIntensity;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = ( editcondition = "OverrideMoonIntensity" ) )
	FCyclicRuntimeFloatCurve MoonIntensity;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", DisplayName="mCloudiness", meta = ( editcondition = "OverrideCloudOpacity" ) )
	FCyclicRuntimeFloatCurve CloudOpacity;
	
	/** The blend weight of the post process volume */
	UPROPERTY( EditAnywhere, Category = "PostProcess" )
	float mBlendWeight;


	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|WhiteBalance", meta = ( UIMin = "1500.0", UIMax = "15000.0", editcondition = "OverrideWhiteTemp", DisplayName = "Temp" ) )
	FCyclicRuntimeFloatCurve WhiteTemp;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|WhiteBalance", meta = ( UIMin = "-1.0", UIMax = "1.0", editcondition = "OverrideWhiteTint", DisplayName = "Tint" ) )
	FCyclicRuntimeFloatCurve WhiteTint;

	// Color Correction controls
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorSaturation", DisplayName = "Saturation" ) )
	FCyclicRuntimeColorCurve ColorSaturation;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorContrast", DisplayName = "Contrast" ) )
	FCyclicRuntimeColorCurve ColorContrast;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGamma", DisplayName = "Gamma" ) )
	FCyclicRuntimeColorCurve ColorGamma;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGain", DisplayName = "Gain" ) )
	FCyclicRuntimeColorCurve ColorGain;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "OverrideColorOffset", DisplayName = "Offset" ) )
	FCyclicRuntimeColorCurve ColorOffset;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorSaturationShadows", DisplayName = "Saturation" ) )
	FCyclicRuntimeColorCurve ColorSaturationShadows;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorContrastShadows", DisplayName = "Contrast" ) )
	FCyclicRuntimeColorCurve ColorContrastShadows;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGammaShadows", DisplayName = "Gamma" ) )
	FCyclicRuntimeColorCurve ColorGammaShadows;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGainShadows", DisplayName = "Gain" ) )
	FCyclicRuntimeColorCurve ColorGainShadows;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "OverrideColorOffsetShadows", DisplayName = "Offset" ) )
	FCyclicRuntimeColorCurve ColorOffsetShadows;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorSaturationMidtones", DisplayName = "Saturation" ) )
	FCyclicRuntimeColorCurve ColorSaturationMidtones;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorContrastMidtones", DisplayName = "Contrast" ) )
	FCyclicRuntimeColorCurve ColorContrastMidtones;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGammaMidtones", DisplayName = "Gamma" ) )
	FCyclicRuntimeColorCurve ColorGammaMidtones;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGainMidtones", DisplayName = "Gain" ) )
	FCyclicRuntimeColorCurve ColorGainMidtones;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "OverrideColorOffsetMidtones", DisplayName = "Offset" ) )
	FCyclicRuntimeColorCurve ColorOffsetMidtones;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorSaturationHighlights", DisplayName = "Saturation" ) )
	FCyclicRuntimeColorCurve ColorSaturationHighlights;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorContrastHighlights", DisplayName = "Contrast" ) )
	FCyclicRuntimeColorCurve ColorContrastHighlights;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGammaHighlights", DisplayName = "Gamma" ) )
	FCyclicRuntimeColorCurve ColorGammaHighlights;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGainHighlights", DisplayName = "Gain" ) )
	FCyclicRuntimeColorCurve ColorGainHighlights;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "OverrideColorOffsetHighlights", DisplayName = "Offset" ) )
	FCyclicRuntimeColorCurve ColorOffsetHighlights;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "-1.0", UIMax = "1.0", editcondition = "OverrideColorCorrectionHighlightsMin", DisplayName = "HighlightsMin" ) )
	FCyclicRuntimeFloatCurve ColorCorrectionHighlightsMin;

	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "-1.0", UIMax = "1.0", editcondition = "OverrideColorCorrectionShadowsMax", DisplayName = "ShadowsMax" ) )
	FCyclicRuntimeFloatCurve ColorCorrectionShadowsMax;

	/** Correct for artifacts with "electric" blues due to the ACEScg color space. Bright blue desaturates instead of going to violet. */
	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Misc", meta = ( ClampMin = "0.0", ClampMax = "1.0", editcondition = "OverrideBlueCorrection" ) )
	FCyclicRuntimeFloatCurve BlueCorrection;

	/** Expand bright saturated colors outside the sRGB gamut to fake wide gamut rendering. */
	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Misc", meta = ( ClampMin = "0.0", UIMax = "1.0", editcondition = "OverrideExpandGamut" ) )
	FCyclicRuntimeFloatCurve ExpandGamut;

	/** Scene tint color */
	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Misc", meta = ( editcondition = "OverrideSceneColorTint", HideAlphaChannel ) )
	FCyclicRuntimeColorCurve SceneColorTint;

	// Film Controls
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "OverrideFilmSlope", DisplayName = "Slope" ) )
	FCyclicRuntimeFloatCurve FilmSlope;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "OverrideFilmToe", DisplayName = "Toe" ) )
	FCyclicRuntimeFloatCurve FilmToe;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "OverrideFilmShoulder", DisplayName = "Shoulder" ) )
	FCyclicRuntimeFloatCurve FilmShoulder;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "OverrideFilmBlackClip", DisplayName = "Black clip" ) )
	FCyclicRuntimeFloatCurve FilmBlackClip;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "OverrideFilmWhiteClip", DisplayName = "White clip" ) )
	FCyclicRuntimeFloatCurve FilmWhiteClip;

	// Sky atmosphere controls
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Rayleigh Scattering", meta = ( editcondition = "OverrideRayleighScattering" ) )
	FCyclicRuntimeColorCurve RayleighScattering;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Rayleigh Scattering", meta = ( editcondition = "OverrideRayleighScatteringScale", UIMin = 0.0, UIMax = 2.0, ClampMin = 0.0, SliderExponent = 4.0 ))
	FCyclicRuntimeFloatCurve RayleighScatteringScale;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Rayleigh Scattering", meta = ( editcondition = "OverrideRayleighExponentialDistribution" ) )
	FCyclicRuntimeFloatCurve RayleighExponentialDistribution;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", meta = ( editcondition = "OverrideMieScatteringScale" ) )
	FCyclicRuntimeFloatCurve MieScatteringScale;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", meta = ( editcondition = "OverrideMieScattering" ) )
	FCyclicRuntimeColorCurve MieScattering;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", meta = ( editcondition = "OverrideMieAbsorptionScale" ) )
	FCyclicRuntimeFloatCurve MieAbsorptionScale;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", meta = ( editcondition = "OverrideMieAbsorption" ) )
	FCyclicRuntimeColorCurve MieAbsorption;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", meta = ( editcondition = "OverrideMieAnisotropy" ) )
	FCyclicRuntimeFloatCurve MieAnisotropy;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", meta = ( editcondition = "OverrideMieExponentialDistribution" ) )
	FCyclicRuntimeFloatCurve MieExponentialDistribution;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Absorption", meta = ( editcondition = "OverrideOtherAbsorptionScale" ) )
	FCyclicRuntimeFloatCurve OtherAbsorptionScale;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Absorption", meta = ( editcondition = "OverrideOtherAbsorption" ) )
	FCyclicRuntimeColorCurve OtherAbsorption;

	// Height fog bools
	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFogDensity : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFogInscatteringColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFullyDirectionalInscatteringColorDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideNonDirectionalInscatteringColorDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideDirectionalInscatteringExponent : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideDirectionalInscatteringStartDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideDirectionalInscatteringColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFogHeightFalloff : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFogMaxOpacity : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideStartDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFogCutoffDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFogHeight : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideSecondFogDensity : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideSecondFogHeightFalloff : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideSecondFogHeightOffset : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideZenithColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideCloudColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideSunLightColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideMoonLightColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideSunIntensity : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideMoonIntensity : 1;

	/** This is disabled for now, see FGAtmosphereUpdater.cpp */
	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideCloudOpacity : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideWhiteTemp : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideWhiteTint : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorSaturation : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorContrast : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorGamma : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorGain : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorOffset : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorSaturationShadows : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorContrastShadows : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorGammaShadows : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorGainShadows : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorOffsetShadows : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorSaturationMidtones : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorContrastMidtones : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorGammaMidtones : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorGainMidtones : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorOffsetMidtones : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorSaturationHighlights : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorContrastHighlights : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorGammaHighlights : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorGainHighlights : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorOffsetHighlights : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorCorrectionHighlightsMin : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideColorCorrectionShadowsMax : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideBlueCorrection : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideExpandGamut : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideSceneColorTint : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFilmSlope : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFilmToe : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFilmShoulder : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFilmBlackClip : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFilmWhiteClip : 1;

	// Sky atmosphere toggles
	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideRayleighScattering : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideRayleighScatteringScale : 1;
	
	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideRayleighExponentialDistribution : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideMieScatteringScale : 1;
	
	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideMieScattering : 1;
	
	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideMieAbsorptionScale : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideMieAbsorption : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideMieAnisotropy : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideMieExponentialDistribution : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideOtherAbsorptionScale : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideOtherAbsorption : 1;

};
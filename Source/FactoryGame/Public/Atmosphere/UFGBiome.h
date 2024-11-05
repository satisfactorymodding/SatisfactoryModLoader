// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

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

	UPROPERTY()
	FCyclicRuntimeFloatCurve FogHeight_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", DisplayName="FogHeight", meta=(editcondition = "OverrideFogHeight") );
	FRuntimeFloatCurve FogHeight2;

	UPROPERTY()
	FCyclicRuntimeFloatCurve FogDensity_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", DisplayName="FogDensity", meta=(editcondition = "OverrideFogDensity") )
	FRuntimeFloatCurve FogDensity2;

	UPROPERTY()
	FCyclicRuntimeColorCurve FogInscatteringColor_DEPRECATED;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve FogInscatteringLuminance_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", DisplayName="FogInscatteringLuminance", meta=(editcondition = "OverrideFogInscatteringLuminance") )
	FRuntimeCurveLinearColor FogInscatteringLuminance2;

	UPROPERTY()
	FCyclicRuntimeFloatCurve FullyDirectionalInscatteringColorDistance_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, DisplayName="FullyDirectionalInscatteringColorDistance", meta=(editcondition = "OverrideFullyDirectionalInscatteringColorDistance") )
	FRuntimeFloatCurve FullyDirectionalInscatteringColorDistance2;

	UPROPERTY()
	FCyclicRuntimeFloatCurve NonDirectionalInscatteringColorDistance_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, DisplayName="NonDirectionalInscatteringColorDistance", meta=(editcondition = "OverrideNonDirectionalInscatteringColorDistance") )
	FRuntimeFloatCurve NonDirectionalInscatteringColorDistance2;

	UPROPERTY()
	FCyclicRuntimeFloatCurve DirectionalInscatteringExponent_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, DisplayName="DirectionalInscatteringExponent", meta=(editcondition = "OverrideDirectionalInscatteringExponent") )
	FRuntimeFloatCurve DirectionalInscatteringExponent2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve DirectionalInscatteringStartDistance_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, DisplayName="DirectionalInscatteringStartDistance", meta=(editcondition = "OverrideDirectionalInscatteringStartDistance") )
	FRuntimeFloatCurve DirectionalInscatteringStartDistance2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve DirectionalInscatteringColor_DEPRECATED;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve DirectionalInscatteringLuminance_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", DisplayName="DirectionalInscatteringLuminance", meta=(editcondition = "OverrideDirectionalInscatteringLuminance") )
	FRuntimeCurveLinearColor DirectionalInscatteringLuminance2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve FogHeightFalloff_DEPRECATED;
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", DisplayName="FogHeightFalloff", meta=(editcondition = "OverrideFogHeightFalloff") )
	FRuntimeFloatCurve FogHeightFalloff2;

	UPROPERTY()
	FCyclicRuntimeFloatCurve FogMaxOpacity_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, DisplayName="FogMaxOpacity", meta=(editcondition = "OverrideFogMaxOpacity") )
	FRuntimeFloatCurve FogMaxOpacity2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve StartDistance_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", DisplayName="StartDistance", meta=(editcondition = "OverrideStartDistance") )
	FRuntimeFloatCurve StartDistance2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve FogCutoffDistance_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", DisplayName="FogCutoffDistance", meta=(editcondition = "OverrideFogCutoffDistance") )
	FRuntimeFloatCurve FogCutoffDistance2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve SecondFogDensity_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog|SecondFog", DisplayName="SecondFogDensity", meta=(editcondition = "OverrideSecondFogDensity") )
	FRuntimeFloatCurve SecondFogDensity2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve SecondFogHeightFalloff_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog|SecondFog", meta=(editcondition = "OverrideSecondFogHeightFalloff") )
	FRuntimeFloatCurve SecondFogHeightFalloff2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve SecondFogHeightOffset_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog|SecondFog", DisplayName="SecondFogHeightOffset", meta=(editcondition = "OverrideSecondFogHeightOffset") )
	FRuntimeFloatCurve SecondFogHeightOffset2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve CloudColor_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", DisplayName="CloudColor", meta = (editcondition = "OverrideCloudColor") )
	FRuntimeCurveLinearColor CloudColor2;

	UPROPERTY()
	FCyclicRuntimeColorCurve SunLightColor_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", DisplayName="SunLightColor", meta = (editcondition = "OverrideSunLightColor") )
	FRuntimeCurveLinearColor SunLightColor2;

	UPROPERTY()
	FCyclicRuntimeColorCurve MoonLightColor_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", DisplayName="MoonLightColor", meta = ( editcondition = "OverrideMoonLightColor" ) )
	FRuntimeCurveLinearColor MoonLightColor2;

	UPROPERTY()
	FCyclicRuntimeFloatCurve SunIntensity_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", DisplayName="SunIntensity", meta = ( editcondition = "OverrideSunIntensity" ) )
	FRuntimeFloatCurve SunIntensity2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve MoonIntensity_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", DisplayName="MoonIntensity", meta = ( editcondition = "OverrideMoonIntensity" ) )
	FRuntimeFloatCurve MoonIntensity2;

	UPROPERTY()
	FCyclicRuntimeFloatCurve CloudOpacity_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", DisplayName="Cloudiness", meta = ( editcondition = "OverrideCloudOpacity" ) )
	FRuntimeFloatCurve CloudOpacity2;
	
	/** The blend weight of the post process volume */
	UPROPERTY( EditAnywhere, Category = "PostProcess" )
	float mBlendWeight;


	UPROPERTY()
	FCyclicRuntimeFloatCurve WhiteTemp_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|WhiteBalance", meta = ( UIMin = "1500.0", UIMax = "15000.0", editcondition = "OverrideWhiteTemp", DisplayName = "Temp" ) )
	FRuntimeFloatCurve WhiteTemp2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve WhiteTint_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|WhiteBalance", meta = ( UIMin = "-1.0", UIMax = "1.0", editcondition = "OverrideWhiteTint", DisplayName = "Tint" ) )
	FRuntimeFloatCurve WhiteTint2;

	// Color Correction controls
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorSaturation_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorSaturation", DisplayName = "Saturation" ) )
	FRuntimeCurveLinearColor ColorSaturation2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorContrast_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorContrast", DisplayName = "Contrast" ) )
	FRuntimeCurveLinearColor ColorContrast2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorGamma_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGamma", DisplayName = "Gamma" ) )
	FRuntimeCurveLinearColor ColorGamma2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorGain_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGain", DisplayName = "Gain" ) )
	FRuntimeCurveLinearColor ColorGain2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorOffset_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "OverrideColorOffset", DisplayName = "Offset" ) )
	FRuntimeCurveLinearColor ColorOffset2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorSaturationShadows_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorSaturationShadows", DisplayName = "Saturation" ) )
	FRuntimeCurveLinearColor ColorSaturationShadows2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorContrastShadows_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorContrastShadows", DisplayName = "Contrast" ) )
	FRuntimeCurveLinearColor ColorContrastShadows2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorGammaShadows_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGammaShadows", DisplayName = "Gamma" ) )
	FRuntimeCurveLinearColor ColorGammaShadows2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorGainShadows_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGainShadows", DisplayName = "Gain" ) )
	FRuntimeCurveLinearColor ColorGainShadows2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorOffsetShadows_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "OverrideColorOffsetShadows", DisplayName = "Offset" ) )
	FRuntimeCurveLinearColor ColorOffsetShadows2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorSaturationMidtones_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorSaturationMidtones", DisplayName = "Saturation" ) )
	FRuntimeCurveLinearColor ColorSaturationMidtones2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorContrastMidtones_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorContrastMidtones", DisplayName = "Contrast" ) )
	FRuntimeCurveLinearColor ColorContrastMidtones2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorGammaMidtones_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGammaMidtones", DisplayName = "Gamma" ) )
	FRuntimeCurveLinearColor ColorGammaMidtones2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorGainMidtones_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGainMidtones", DisplayName = "Gain" ) )
	FRuntimeCurveLinearColor ColorGainMidtones2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorOffsetMidtones_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "OverrideColorOffsetMidtones", DisplayName = "Offset" ) )
	FRuntimeCurveLinearColor ColorOffsetMidtones2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorSaturationHighlights_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorSaturationHighlights", DisplayName = "Saturation" ) )
	FRuntimeCurveLinearColor ColorSaturationHighlights2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorContrastHighlights_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorContrastHighlights", DisplayName = "Contrast" ) )
	FRuntimeCurveLinearColor ColorContrastHighlights2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorGammaHighlights_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGammaHighlights", DisplayName = "Gamma" ) )
	FRuntimeCurveLinearColor ColorGammaHighlights2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorGainHighlights_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "OverrideColorGainHighlights", DisplayName = "Gain" ) )
	FRuntimeCurveLinearColor ColorGainHighlights2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve ColorOffsetHighlights_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "OverrideColorOffsetHighlights", DisplayName = "Offset" ) )
	FRuntimeCurveLinearColor ColorOffsetHighlights2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve ColorCorrectionHighlightsMin_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights",  meta = ( UIMin = "-1.0", UIMax = "1.0", editcondition = "OverrideColorCorrectionHighlightsMin", DisplayName = "HighlightsMin" ) )
	FRuntimeFloatCurve ColorCorrectionHighlightsMin2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve ColorCorrectionShadowsMax_DEPRECATED;

	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "-1.0", UIMax = "1.0", editcondition = "OverrideColorCorrectionShadowsMax", DisplayName = "ShadowsMax" ) )
	FRuntimeFloatCurve ColorCorrectionShadowsMax2;
	
	/** Correct for artifacts with "electric" blues due to the ACEScg color space. Bright blue desaturates instead of going to violet. */
	UPROPERTY()
	FCyclicRuntimeFloatCurve BlueCorrection_DEPRECATED;

	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Misc", DisplayName="BlueCorrection", meta = ( ClampMin = "0.0", ClampMax = "1.0", editcondition = "OverrideBlueCorrection" ) )
	FRuntimeFloatCurve BlueCorrection2;
	
	/** Expand bright saturated colors outside the sRGB gamut to fake wide gamut rendering. */
	UPROPERTY()
	FCyclicRuntimeFloatCurve ExpandGamut_DEPRECATED;

	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Misc", DisplayName="ExpandGamut", meta = ( ClampMin = "0.0", UIMax = "1.0", editcondition = "OverrideExpandGamut" ) )
	FRuntimeFloatCurve ExpandGamut2;
	
	/** Scene tint color */
	UPROPERTY()
	FCyclicRuntimeColorCurve SceneColorTint_DEPRECATED;

	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Misc", DisplayName="SceneColorTint", meta = ( editcondition = "OverrideSceneColorTint", HideAlphaChannel ) )
	FRuntimeCurveLinearColor SceneColorTint2;
	
	// Film Controls
	UPROPERTY()
	FCyclicRuntimeFloatCurve FilmSlope_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "OverrideFilmSlope", DisplayName = "Slope" ) )
	FRuntimeFloatCurve FilmSlope2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve FilmToe_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "OverrideFilmToe", DisplayName = "Toe" ) )
	FRuntimeFloatCurve FilmToe2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve FilmShoulder_DEPRECATED;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "OverrideFilmShoulder", DisplayName = "Shoulder" ) )
	FRuntimeFloatCurve FilmShoulder2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve FilmBlackClip_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "OverrideFilmBlackClip", DisplayName = "Black clip" ) )
	FRuntimeFloatCurve FilmBlackClip2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve FilmWhiteClip_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "OverrideFilmWhiteClip", DisplayName = "White clip" ) )
	FRuntimeFloatCurve FilmWhiteClip2;
	
	// Sky atmosphere controls
	UPROPERTY()
	FCyclicRuntimeColorCurve RayleighScattering_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Rayleigh Scattering", DisplayName="RayleighScattering", meta = ( editcondition = "OverrideRayleighScattering" ) )
	FRuntimeCurveLinearColor RayleighScattering2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve RayleighScatteringScale_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Rayleigh Scattering", DisplayName="RayleighScatteringScale", meta = ( editcondition = "OverrideRayleighScatteringScale", UIMin = 0.0, UIMax = 2.0, ClampMin = 0.0, SliderExponent = 4.0 ))
	FRuntimeFloatCurve RayleighScatteringScale2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve RayleighExponentialDistribution_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Rayleigh Scattering", DisplayName="RayleighExponentialDistribution", meta = ( editcondition = "OverrideRayleighExponentialDistribution" ) )
	FRuntimeFloatCurve RayleighExponentialDistribution2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve MieScatteringScale_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", DisplayName="MieScatteringScale", meta = ( editcondition = "OverrideMieScatteringScale" ) )
	FRuntimeFloatCurve MieScatteringScale2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve MieScattering_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", DisplayName="MieScattering", meta = ( editcondition = "OverrideMieScattering" ) )
	FRuntimeCurveLinearColor MieScattering2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve MieAbsorptionScale_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", DisplayName="MieAbsorptionScale", meta = ( editcondition = "OverrideMieAbsorptionScale" ) )
	FRuntimeFloatCurve MieAbsorptionScale2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve MieAbsorption_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", DisplayName="MieAbsorption", meta = ( editcondition = "OverrideMieAbsorption" ) )
	FRuntimeCurveLinearColor MieAbsorption2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve MieAnisotropy_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", DisplayName="MieAnisotropy", meta = ( editcondition = "OverrideMieAnisotropy" ) )
	FRuntimeFloatCurve MieAnisotropy2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve MieExponentialDistribution_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Mie Scattering", DisplayName="MieExponentialDistribution", meta = ( editcondition = "OverrideMieExponentialDistribution" ) )
	FRuntimeFloatCurve MieExponentialDistribution2;
	
	UPROPERTY()
	FCyclicRuntimeFloatCurve OtherAbsorptionScale_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Absorption", DisplayName="OtherAbsorptionScale", meta = ( editcondition = "OverrideOtherAbsorptionScale" ) )
	FRuntimeFloatCurve OtherAbsorptionScale2;
	
	UPROPERTY()
	FCyclicRuntimeColorCurve OtherAbsorption_DEPRECATED;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Sky Atmosphere|Absorption", DisplayName="OtherAbsorption", meta = ( editcondition = "OverrideOtherAbsorption" ) )
	FRuntimeCurveLinearColor OtherAbsorption2;
	
	// Height fog bools
	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFogDensity : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFogInscatteringLuminance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideFullyDirectionalInscatteringColorDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideNonDirectionalInscatteringColorDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideDirectionalInscatteringExponent : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideDirectionalInscatteringStartDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 OverrideDirectionalInscatteringLuminance : 1;

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

protected:
	virtual void Serialize(FArchive& Ar) override;

};
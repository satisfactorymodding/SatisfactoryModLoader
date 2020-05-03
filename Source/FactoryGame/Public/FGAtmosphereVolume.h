#pragma once
#include "Engine/Scene.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Interfaces/Interface_PostProcessVolume.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "FGSkySphere.h"
#include "FGAtmosphereVolume.generated.h"

USTRUCT()
struct FACTORYGAME_API FExponentialFogSettings
{
	GENERATED_BODY()

	/** Set defaults */
	FExponentialFogSettings();

	/** The ZValue of the fog */
	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog" )
	float FogHeight;

	/** Density of the fog */
	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog", meta = ( UIMin = "0", UIMax = ".05" ) )
	float FogDensity;

	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog" )
	FLinearColor FogInscatteringColor;

	/** Distance at which InscatteringColorCubemap should be used directly for the Inscattering Color. */
	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog", meta = ( UIMin = "1000", UIMax = "1000000" ) )
	float FullyDirectionalInscatteringColorDistance;

	/** Distance at which only the average color of InscatteringColorCubemap should be used as Inscattering Color. */
	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog", meta = ( UIMin = "1000", UIMax = "1000000" ) )
	float NonDirectionalInscatteringColorDistance;

	/**
	* Controls the size of the directional inscattering cone, which is used to approximate inscattering from a directional light.
	* Note: there must be a directional light with bUsedAsAtmosphereSunLight enabled for DirectionalInscattering to be used.
	*/
	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog", meta = ( UIMin = "2", UIMax = "64" ) )
	float DirectionalInscatteringExponent;

	/**
	* Controls the start distance from the viewer of the directional inscattering, which is used to approximate inscattering from a directional light.
	* Note: there must be a directional light with bUsedAsAtmosphereSunLight enabled for DirectionalInscattering to be used.
	*/
	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog" )
	float DirectionalInscatteringStartDistance;

	/**
	* Controls the color of the directional inscattering, which is used to approximate inscattering from a directional light.
	* Note: there must be a directional light with bUsedAsAtmosphereSunLight enabled for DirectionalInscattering to be used.
	*/
	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog" )
	FLinearColor DirectionalInscatteringColor;

	/**
	* Height density factor, controls how the density increases as height decreases.
	* Smaller values make the visible transition larger.
	*/
	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog", meta = ( UIMin = "0.001", UIMax = "2" ) )
	float FogHeightFalloff;

	/**
	* Maximum opacity of the fog.
	* A value of 1 means the fog can become fully opaque at a distance and replace scene color completely,
	* A value of 0 means the fog color will not be factored in at all.
	*/
	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog", meta = ( UIMin = "0", UIMax = "1" ) )
	float FogMaxOpacity;

	/** Distance from the camera that the fog will start, in world units. */
	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog", meta = ( UIMin = "0", UIMax = "5000" ) )
	float StartDistance;

	/** Scene elements past this distance will not have fog applied.  This is useful for excluding skyboxes which already have fog baked in. */
	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog", meta = ( UIMin = "100000", UIMax = "20000000" ) )
	float FogCutoffDistance;

	void Reset()
	{
		*this = FExponentialFogSettings();
	}

	uint8 EnableFogHeight : 1;
	uint8 EnableFogDensity : 1;
	uint8 EnableFogInscatteringColor : 1;
	uint8 EnableFullyDirectionalInscatteringColorDistance : 1;
	uint8 EnableNonDirectionalInscatteringColorDistance : 1;
	uint8 EnableDirectionalInscatteringExponent : 1;
	uint8 EnableDirectionalInscatteringStartDistance : 1;
	uint8 EnableDirectionalInscatteringColor : 1;
	uint8 EnableFogHeightFalloff : 1;
	uint8 EnableFogMaxOpacity : 1;
	uint8 EnableStartDistance : 1;
	uint8 EnableFogCutoffDistance : 1;

public:
	FORCEINLINE ~FExponentialFogSettings() = default;
};


UCLASS(HideCategories=(Collision,Tags,Cooking,Actor,Mobile))
class FACTORYGAME_API AFGAtmosphereVolume : public AVolume, public ICurvePanningInterface, public IInterface_PostProcessVolume
{
	GENERATED_BODY()
public:
	AFGAtmosphereVolume();

	//~ Begin UObject interface
#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent& propertyChangedEvent ) override;
#endif
	virtual void PostLoad() override;
	//~ End UObject interface

	//~ Begin AActor Interface
	virtual void PostRegisterAllComponents() override;
	virtual void PostUnregisterAllComponents( void ) override;
	//~ End AActor Interface

	//	Begin ICurvePanningInterface
#if WITH_EDITOR
	virtual float GetViewMinInput() const override;
	virtual float GetViewMaxInput() const override;
	virtual void SetViewRange( float min, float max ) override;
#endif
	// End ICurvePanningInterface

	//~ Begin IInterface_PostProcessVolume Interface
	virtual bool EncompassesPoint( FVector point, float sphereRadius = 0.f, float* out_distanceToPoint = nullptr ) override;
	virtual FPostProcessVolumeProperties GetProperties() const override;
	//~ End IInterface_PostProcessVolume Interface

	// Get the settings of this volume
	void GetSettings( FExponentialFogSettings& out_settings ) const;
	void GetSettings( float atTime, FExponentialFogSettings& out_settings ) const;
	void GetSkySphereSettings( float atTime, FSkySphereSettings& out_settings ) const;

	// Get the blend priority, higher number is higher priority.
	FORCEINLINE float GetPriority() const { return mPriority; }
	// Get the blend distance of this volume
	FORCEINLINE float GetBlendDistance() const { return mBlendDistance; }
protected:
	/** Add the volume to the world */
	void AddVolume();

	/** Remove the volume from the world */
	void RemoveVolume();
protected:
	UPROPERTY( EditInstanceOnly, Category = "Shared" )
	float mPriority; //@todoFog change to int since people use it like that anyway.

	// The distance that the fog blends over
	UPROPERTY( EditInstanceOnly, Category = "Shared" )
	float mBlendDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "mEnableFogHeight") )
	FRuntimeFloatCurve mFogHeight;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "mEnableFogDensity") )
	FRuntimeFloatCurve mFogDensity;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "mEnableFogInscatteringColor") )
	FRuntimeCurveLinearColor mFogInscatteringColor;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, meta=(editcondition = "mEnableFullyDirectionalInscatteringColorDistance") )
	FRuntimeFloatCurve mFullyDirectionalInscatteringColorDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, meta=(editcondition = "mEnableNonDirectionalInscatteringColorDistance") )
	FRuntimeFloatCurve mNonDirectionalInscatteringColorDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, meta=(editcondition = "mEnableDirectionalInscatteringExponent") )
	FRuntimeFloatCurve mDirectionalInscatteringExponent;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, meta=(editcondition = "mEnableDirectionalInscatteringStartDistance") )
	FRuntimeFloatCurve mDirectionalInscatteringStartDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "mEnableDirectionalInscatteringColor") )
	FRuntimeCurveLinearColor mDirectionalInscatteringColor;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "mEnableFogHeightFalloff") )
	FRuntimeFloatCurve mFogHeightFalloff;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay, meta=(editcondition = "mEnableFogMaxOpacity") )
	FRuntimeFloatCurve mFogMaxOpacity;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "mEnableStartDistance") )
	FRuntimeFloatCurve mStartDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", meta=(editcondition = "mEnableFogCutoffDistance") )
	FRuntimeFloatCurve mFogCutoffDistance;

	/** How the color of the horizon changes during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = (EditCondition = "mOverrideHorizonColor") )
	FRuntimeCurveLinearColor mHorizonColorCurve;

	/** How the color of the zenith changes during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = (EditCondition = "mOverrideZenithColor") )
	FRuntimeCurveLinearColor mZenithColorCurve;

	/** How the color of clouds zenith changes during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = (EditCondition = "mOverrideCloudColor") )
	FRuntimeCurveLinearColor mCloudColorCurve;


	/** How the opaqueness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = (EditCondition = "mOverrideSunLightColor") )
	FRuntimeCurveLinearColor mSunLightColorCurve;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = ( EditCondition = "mOverrideMoonLightColor" ) )
	FRuntimeCurveLinearColor mMoonLightColorCurve;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = ( EditCondition = "mOverrideSunIntensity" ) )
	FRuntimeFloatCurve mSunIntensity;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = ( EditCondition = "mOverrideMoonIntensity" ) )
	FRuntimeFloatCurve mMoonIntensity;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", DisplayName="mCloudiness", meta = ( EditCondition = "mOverrideCloudOpacity" ) )
	FRuntimeFloatCurve mCloudOpacity;
	
	/** The blend weight of the post process volume */
	UPROPERTY( EditAnywhere, Category = "PostProcess" )
	float mBlendWeight;


	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|WhiteBalance", meta = ( UIMin = "1500.0", UIMax = "15000.0", editcondition = "mEnableWhiteTemp", DisplayName = "Temp" ) )
	FRuntimeFloatCurve mWhiteTemp;
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|WhiteBalance", meta = ( UIMin = "-1.0", UIMax = "1.0", editcondition = "mEnableWhiteTint", DisplayName = "Tint" ) )
	FRuntimeFloatCurve mWhiteTint;

	// Color Correction controls
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorSaturation", DisplayName = "Saturation" ) )
	FRuntimeCurveLinearColor mColorSaturation;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorContrast", DisplayName = "Contrast" ) )
	FRuntimeCurveLinearColor mColorContrast;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorGamma", DisplayName = "Gamma" ) )
	FRuntimeCurveLinearColor mColorGamma;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorGain", DisplayName = "Gain" ) )
	FRuntimeCurveLinearColor mColorGain;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Global", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "mEnableColorOffset", DisplayName = "Offset" ) )
	FRuntimeCurveLinearColor mColorOffset;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorSaturationShadows", DisplayName = "Saturation" ) )
	FRuntimeCurveLinearColor mColorSaturationShadows;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorContrastShadows", DisplayName = "Contrast" ) )
	FRuntimeCurveLinearColor mColorContrastShadows;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorGammaShadows", DisplayName = "Gamma" ) )
	FRuntimeCurveLinearColor mColorGammaShadows;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorGainShadows", DisplayName = "Gain" ) )
	FRuntimeCurveLinearColor mColorGainShadows;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "mEnableColorOffsetShadows", DisplayName = "Offset" ) )
	FRuntimeCurveLinearColor mColorOffsetShadows;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorSaturationMidtones", DisplayName = "Saturation" ) )
	FRuntimeCurveLinearColor mColorSaturationMidtones;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorContrastMidtones", DisplayName = "Contrast" ) )
	FRuntimeCurveLinearColor mColorContrastMidtones;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorGammaMidtones", DisplayName = "Gamma" ) )
	FRuntimeCurveLinearColor mColorGammaMidtones;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorGainMidtones", DisplayName = "Gain" ) )
	FRuntimeCurveLinearColor mColorGainMidtones;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Midtones", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "mEnableColorOffsetMidtones", DisplayName = "Offset" ) )
	FRuntimeCurveLinearColor mColorOffsetMidtones;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorSaturationHighlights", DisplayName = "Saturation" ) )
	FRuntimeCurveLinearColor mColorSaturationHighlights;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorContrastHighlights", DisplayName = "Contrast" ) )
	FRuntimeCurveLinearColor mColorContrastHighlights;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorGammaHighlights", DisplayName = "Gamma" ) )
	FRuntimeCurveLinearColor mColorGammaHighlights;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gain", ShiftMouseMovePixelPerDelta = "10", SupportDynamicSliderMaxValue = "true", editcondition = "mEnableColorGainHighlights", DisplayName = "Gain" ) )
	FRuntimeCurveLinearColor mColorGainHighlights;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", ShiftMouseMovePixelPerDelta = "20", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true", editcondition = "mEnableColorOffsetHighlights", DisplayName = "Offset" ) )
	FRuntimeCurveLinearColor mColorOffsetHighlights;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Color Grading|Highlights", meta = ( UIMin = "-1.0", UIMax = "1.0", editcondition = "mEnableColorCorrectionHighlightsMin", DisplayName = "HighlightsMin" ) )
	FRuntimeFloatCurve mColorCorrectionHighlightsMin;

	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Shadows", meta = ( UIMin = "-1.0", UIMax = "1.0", editcondition = "mEnableColorCorrectionShadowsMax", DisplayName = "ShadowsMax" ) )
	FRuntimeFloatCurve mColorCorrectionShadowsMax;

	/** Correct for artifacts with "electric" blues due to the ACEScg color space. Bright blue desaturates instead of going to violet. */
	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Misc", meta = ( ClampMin = "0.0", ClampMax = "1.0", editcondition = "mEnableBlueCorrection" ) )
	FRuntimeFloatCurve mBlueCorrection;

	/** Expand bright saturated colors outside the sRGB gamut to fake wide gamut rendering. */
	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Misc", meta = ( ClampMin = "0.0", UIMax = "1.0", editcondition = "mEnableExpandGamut" ) )
	FRuntimeFloatCurve mExpandGamut;

	/** Scene tint color */
	UPROPERTY( EditAnywhere, Category = "PostProcess|Color Grading|Misc", meta = ( editcondition = "mEnableSceneColorTint", HideAlphaChannel ) )
	FRuntimeCurveLinearColor mSceneColorTint;

	// Film Controls
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "mEnableFilmSlope", DisplayName = "Slope" ) )
	FRuntimeFloatCurve mFilmSlope;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "mEnableFilmToe", DisplayName = "Toe" ) )
	FRuntimeFloatCurve mFilmToe;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "mEnableFilmShoulder", DisplayName = "Shoulder" ) )
	FRuntimeFloatCurve mFilmShoulder;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "mEnableFilmBlackClip", DisplayName = "Black clip" ) )
	FRuntimeFloatCurve mFilmBlackClip;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess|Film", meta = ( UIMin = "0.0", UIMax = "1.0", editcondition = "mEnableFilmWhiteClip", DisplayName = "White clip" ) )
	FRuntimeFloatCurve mFilmWhiteClip;

	// BEGIN DEPRECATED @todo Just found this, when do we clean up the code? -G2 2020-04-15
	UPROPERTY()
	FRuntimeCurveLinearColor mContrast_DEPRECATED;

	UPROPERTY()
	FRuntimeCurveLinearColor mGain_DEPRECATED;

	UPROPERTY()
	FRuntimeCurveLinearColor mSaturation_DEPRECATED;

	UPROPERTY()
	uint8 mEnableContrast_DEPRECATED : 1;

	UPROPERTY()
	uint8 mEnableGain_DEPRECATED : 1;

	UPROPERTY()
	uint8 mEnableSaturation_DEPRECATED : 1;
	// END DEPRECATED

	// Height fog bools
	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFogHeight : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFogDensity : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFogInscatteringColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFullyDirectionalInscatteringColorDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableNonDirectionalInscatteringColorDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableDirectionalInscatteringExponent : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableDirectionalInscatteringStartDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableDirectionalInscatteringColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFogHeightFalloff : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFogMaxOpacity : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableStartDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFogCutoffDistance : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mOverrideHorizonColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mOverrideMoonIntensity : 1;

	/** This is disabled for now, see FGAtmosphereUpdater.cpp */
	UPROPERTY( EditAnywhere, DisplayName = "mOverrideCloudiness", meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mOverrideCloudOpacity : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mOverrideSunIntensity : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mOverrideZenithColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mOverrideCloudColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mOverrideSunLightColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mOverrideMoonLightColor : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableWhiteTemp : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableWhiteTint : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorSaturation : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorContrast : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorGamma : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorGain : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorOffset : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFilmSlope : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFilmToe : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFilmShoulder : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFilmBlackClip : 1;

	UPROPERTY( EditAnywhere, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableFilmWhiteClip : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorSaturationShadows : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorContrastShadows : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorGammaShadows : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorGainShadows : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorOffsetShadows : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorSaturationMidtones : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorContrastMidtones : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorGammaMidtones : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorGainMidtones : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorOffsetMidtones : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorSaturationHighlights : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorContrastHighlights : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorGammaHighlights : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorGainHighlights : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorOffsetHighlights : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorCorrectionShadowsMax : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableColorCorrectionHighlightsMin : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableBlueCorrection : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableExpandGamut : 1;

	UPROPERTY( EditAnywhere, Category = Overrides, meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableSceneColorTint : 1;


private:
	// The base settings for our post process
	// @todo: Remove mutable
	mutable struct FPostProcessSettings mPostProcessSettings;

#if WITH_EDITORONLY_DATA
	/** A stampdown in time, where we want to show of the preview settings */
	UPROPERTY( EditInstanceOnly, Category="Preview",meta = ( UIMin = 0, UIMax = 24, ClampMin = 0, ClampMax = 24 ) )
	float mPreviewTime;

	/** A preview of all the settings in the current fog-volume*/
	UPROPERTY( VisibleInstanceOnly, Category = "Preview", meta = ( ShowOnlyInnerProperties ) )
	FExponentialFogSettings mPreviewSettings;

	// For ICurvePanningInterface 
	float mViewMinInput;
	float mViewMaxInput;
#endif

public:
	FORCEINLINE ~AFGAtmosphereVolume() = default;
};

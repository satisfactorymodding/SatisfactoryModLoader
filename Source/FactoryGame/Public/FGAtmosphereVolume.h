// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Interfaces/Interface_PostProcessVolume.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "FGSkySphere.h"
#include "Components/ExponentialHeightFogComponent.h"

#include "FGAtmosphereVolume.generated.h"


USTRUCT()
struct FExponentialFogSettings
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

	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog" )
	float SecondFogDensity;

	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog" )
	float SecondFogHeightFalloff;

	UPROPERTY( EditAnywhere, Category = "ExponentialHeightFog" )
	float SecondFogHeightOffset;

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
	uint8 EnableSecondFogDensity : 1;
	uint8 EnableSecondFogHeightFalloff : 1;
	uint8 EnableSecondFogHeightOffset : 1;
};

USTRUCT()
struct FSkyAtmosphereSettings
{
	GENERATED_BODY()

	FSkyAtmosphereSettings();
	
	float RayleighScatteringScale;
	FLinearColor RayleighScattering;
	float RayleighExponentialDistribution;

	float MieScatteringScale;
	FLinearColor MieScattering;
	float MieAbsorptionScale;
	FLinearColor MieAbsorption;
	float MieAnisotropy;
	float MieExponentialDistribution;

	float OtherAbsorptionScale;
	FLinearColor OtherAbsorption;
	
	uint8 OverrideRayleighScatteringScale : 1;
	uint8 OverrideRayleighScattering : 1;
	uint8 OverrideRayleighExponentialDistribution : 1;

	uint8 OverrideMieScatteringScale : 1;
	uint8 OverrideMieScattering : 1;
	uint8 OverrideMieAbsorptionScale : 1;
	uint8 OverrideMieAbsorption : 1;
	uint8 OverrideMieAnisotropy : 1;
	uint8 OverrideMieExponentialDistribution : 1;

	uint8 OverrideOtherAbsorptionScale : 1;
	uint8 OverrideOtherAbsorption : 1;

};


UCLASS( HideCategories = ( Collision, Tags, Cooking, Actor, Mobile, LOD, Replication ))
class FACTORYGAME_API AFGAtmosphereVolume : public AVolume, public IInterface_PostProcessVolume
{
	GENERATED_BODY()
public:
	AFGAtmosphereVolume();

	void BeginPlay() override;

	UPROPERTY( EditAnywhere, Instanced, Category="Atmosphere & Weather" )
	class UFGBiome* mBiome = nullptr;

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

	//~ Begin IInterface_PostProcessVolume Interface
	virtual bool EncompassesPoint( FVector point, float sphereRadius = 0.f, float* out_distanceToPoint = nullptr ) override;
	virtual FPostProcessVolumeProperties GetProperties() const override;
	//~ End IInterface_PostProcessVolume Interface

	// Get the settings of this volume
	void GetSettings( FExponentialFogSettings& out_settings ) const;
	void GetSettings( float atTime, FExponentialFogSettings& out_settings ) const;
	void GetSkySphereSettings( float atTime, FSkySphereSettings& out_settings ) const;
	void GetAtmosphereSettings( float atTime, FSkyAtmosphereSettings& out_settings ) const;

	// Get the blend priority, higher number is higher priority.
	FORCEINLINE float GetPriority() const { return mPriority; }
	// Get the blend distance of this volume
	FORCEINLINE float GetBlendDistance() const { return mBlendDistance; }

	/// Performs initialization post construction
	virtual void OnConstruction( const FTransform& Transform ) override;

#if WITH_EDITOR
	/// Moves all the curves and their enabled states to the BaseBiome, resetting all the values on this Volume's biome. 
	UFUNCTION( CallInEditor, Category = "Atmosphere & Weather"  )
	void MoveCurvesToBaseBiome();

	/// Copies the values of the legacy curves to this Volume's biome instance.
	void CopyLegacyPropertiesToAsset();
#endif
protected:
	/** Add the volume to the world */
	void AddVolume();

	/** Remove the volume from the world */
	void RemoveVolume();
	 
	UPROPERTY( EditInstanceOnly, Category = "Shared" )
	float mPriority; //@todoFog change to int since people use it like that anyway.

	// The distance that the fog blends over
	UPROPERTY( EditInstanceOnly, Category = "Shared" )
	float mBlendDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeFloatCurve mFogHeight;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeFloatCurve mFogDensity;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeCurveLinearColor mFogInscatteringColor;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeFloatCurve mFullyDirectionalInscatteringColorDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeFloatCurve mNonDirectionalInscatteringColorDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeFloatCurve mDirectionalInscatteringExponent;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeFloatCurve mDirectionalInscatteringStartDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeCurveLinearColor mDirectionalInscatteringColor;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeFloatCurve mFogHeightFalloff;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeFloatCurve mFogMaxOpacity;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeFloatCurve mStartDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY()
	FRuntimeFloatCurve mFogCutoffDistance;

	/** How the color of the horizon changes during the day */
	UPROPERTY()
	FRuntimeCurveLinearColor mHorizonColorCurve;

	/** How the color of the zenith changes during the day */
	UPROPERTY()
	FRuntimeCurveLinearColor mZenithColorCurve;

	/** How the color of clouds zenith changes during the day */
	UPROPERTY()
	FRuntimeCurveLinearColor mCloudColorCurve;


	/** How the opaqueness of the clouds change during the day */
	UPROPERTY()
	FRuntimeCurveLinearColor mSunLightColorCurve;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY()
	FRuntimeCurveLinearColor mMoonLightColorCurve;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY()
	FRuntimeFloatCurve mSunIntensity;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY()
	FRuntimeFloatCurve mMoonIntensity;

	/** How the opaqueness of the clouds change during the day */
	UPROPERTY()
	FRuntimeFloatCurve mCloudOpacity;
	
	/** The blend weight of the post process volume */
	UPROPERTY()
	float mBlendWeight;


	UPROPERTY()
	FRuntimeFloatCurve mWhiteTemp;
	UPROPERTY()
	FRuntimeFloatCurve mWhiteTint;

	// Color Correction controls
	UPROPERTY()
	FRuntimeCurveLinearColor mColorSaturation;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorContrast;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorGamma;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorGain;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorOffset;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorSaturationShadows;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorContrastShadows;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorGammaShadows;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorGainShadows;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorOffsetShadows;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorSaturationMidtones;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorContrastMidtones;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorGammaMidtones;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorGainMidtones;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorOffsetMidtones;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorSaturationHighlights;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorContrastHighlights;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorGammaHighlights;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorGainHighlights;

	UPROPERTY()
	FRuntimeCurveLinearColor mColorOffsetHighlights;

	UPROPERTY()
	FRuntimeFloatCurve mColorCorrectionHighlightsMin;

	UPROPERTY()
	FRuntimeFloatCurve mColorCorrectionShadowsMax;

	/** Correct for artifacts with "electric" blues due to the ACEScg color space. Bright blue desaturates instead of going to violet. */
	UPROPERTY()
	FRuntimeFloatCurve mBlueCorrection;

	/** Expand bright saturated colors outside the sRGB gamut to fake wide gamut rendering. */
	UPROPERTY()
	FRuntimeFloatCurve mExpandGamut;

	/** Scene tint color */
	UPROPERTY()
	FRuntimeCurveLinearColor mSceneColorTint;

	// Film Controls
	UPROPERTY()
	FRuntimeFloatCurve mFilmSlope;

	UPROPERTY()
	FRuntimeFloatCurve mFilmToe;

	UPROPERTY()
	FRuntimeFloatCurve mFilmShoulder;
	
	UPROPERTY()
	FRuntimeFloatCurve mFilmBlackClip;
	
	UPROPERTY()
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
	UPROPERTY()
	uint8 mEnableFogHeight : 1;

	UPROPERTY()
	uint8 mEnableFogDensity : 1;

	UPROPERTY()
	uint8 mEnableFogInscatteringColor : 1;

	UPROPERTY()
	uint8 mEnableFullyDirectionalInscatteringColorDistance : 1;

	UPROPERTY()
	uint8 mEnableNonDirectionalInscatteringColorDistance : 1;

	UPROPERTY()
	uint8 mEnableDirectionalInscatteringExponent : 1;

	UPROPERTY()
	uint8 mEnableDirectionalInscatteringStartDistance : 1;

	UPROPERTY()
	uint8 mEnableDirectionalInscatteringColor : 1;

	UPROPERTY()
	uint8 mEnableFogHeightFalloff : 1;

	UPROPERTY()
	uint8 mEnableFogMaxOpacity : 1;

	UPROPERTY()
	uint8 mEnableStartDistance : 1;

	UPROPERTY()
	uint8 mEnableFogCutoffDistance : 1;

	UPROPERTY()
	uint8 mOverrideHorizonColor : 1;

	UPROPERTY()
	uint8 mOverrideMoonIntensity : 1;

	/** This is disabled for now, see FGAtmosphereUpdater.cpp */
	UPROPERTY()
	uint8 mOverrideCloudOpacity : 1;

	UPROPERTY()
	uint8 mOverrideSunIntensity : 1;

	UPROPERTY()
	uint8 mOverrideZenithColor : 1;

	UPROPERTY()
	uint8 mOverrideCloudColor : 1;

	UPROPERTY()
	uint8 mOverrideSunLightColor : 1;

	UPROPERTY()
	uint8 mOverrideMoonLightColor : 1;

	UPROPERTY()
	uint8 mEnableWhiteTemp : 1;

	UPROPERTY()
	uint8 mEnableWhiteTint : 1;

	UPROPERTY()
	uint8 mEnableColorSaturation : 1;

	UPROPERTY()
	uint8 mEnableColorContrast : 1;

	UPROPERTY()
	uint8 mEnableColorGamma : 1;

	UPROPERTY()
	uint8 mEnableColorGain : 1;

	UPROPERTY()
	uint8 mEnableColorOffset : 1;

	UPROPERTY()
	uint8 mEnableFilmSlope : 1;

	UPROPERTY()
	uint8 mEnableFilmToe : 1;

	UPROPERTY()
	uint8 mEnableFilmShoulder : 1;

	UPROPERTY()
	uint8 mEnableFilmBlackClip : 1;

	UPROPERTY()
	uint8 mEnableFilmWhiteClip : 1;

	UPROPERTY()
	uint8 mEnableColorSaturationShadows : 1;

	UPROPERTY()
	uint8 mEnableColorContrastShadows : 1;

	UPROPERTY()
	uint8 mEnableColorGammaShadows : 1;

	UPROPERTY()
	uint8 mEnableColorGainShadows : 1;

	UPROPERTY()
	uint8 mEnableColorOffsetShadows : 1;

	UPROPERTY()
	uint8 mEnableColorSaturationMidtones : 1;

	UPROPERTY()
	uint8 mEnableColorContrastMidtones : 1;

	UPROPERTY()
	uint8 mEnableColorGammaMidtones : 1;

	UPROPERTY()
	uint8 mEnableColorGainMidtones : 1;

	UPROPERTY()
	uint8 mEnableColorOffsetMidtones : 1;

	UPROPERTY()
	uint8 mEnableColorSaturationHighlights : 1;

	UPROPERTY()
	uint8 mEnableColorContrastHighlights : 1;

	UPROPERTY()
	uint8 mEnableColorGammaHighlights : 1;

	UPROPERTY()
	uint8 mEnableColorGainHighlights : 1;

	UPROPERTY()
	uint8 mEnableColorOffsetHighlights : 1;

	UPROPERTY()
	uint8 mEnableColorCorrectionShadowsMax : 1;

	UPROPERTY()
	uint8 mEnableColorCorrectionHighlightsMin : 1;

	UPROPERTY()
	uint8 mEnableBlueCorrection : 1;

	UPROPERTY()
	uint8 mEnableExpandGamut : 1;

	UPROPERTY()
	uint8 mEnableSceneColorTint : 1;

private:
	// The base settings for our post process
	// @todo: Remove mutable
	mutable struct FPostProcessSettings mPostProcessSettings;

#if WITH_EDITORONLY_DATA
	/** A preview of all the settings in the current fog-volume*/
	UPROPERTY( VisibleInstanceOnly, Category = "Preview", meta = ( ShowOnlyInnerProperties ) )
	FExponentialFogSettings mPreviewSettings;

	/** Unless this flag is set, every time BeginPlay is called all the curve data from this actor's own properties will be copied to it's instance of Biome */
	UPROPERTY( EditAnywhere )
	uint8 mMigrated : 1;
#endif
};

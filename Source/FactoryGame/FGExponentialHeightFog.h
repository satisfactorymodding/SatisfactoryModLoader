#pragma once
#include "Engine/Scene.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Interfaces/Interface_PostProcessVolume.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "FGSkySphere.h"
#include "GameFramework/Volume.h"
#include "FGExponentialHeightFog.generated.h"

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
};

// @todo: Should be renamed to something else, as it does a lot more than give settings to fog
UCLASS(HideCategories=(Collision,Tags,Cooking,Actor,Mobile))
class AFGDynamicExponentialFogVolume : public AVolume/*, public ICurvePanningInterface MODDING EDIT*/, public IInterface_PostProcessVolume
{
	GENERATED_BODY()
public:
	/** Ctor */
	AFGDynamicExponentialFogVolume();

	//~ Begin UObject interface
#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent& propertyChangedEvent ) override;
#endif
	//~ End UObject interface

	//	Begin ICurvePanningInterface
#if WITH_EDITOR
	// MODDING EDIT
	//virtual float GetViewMinInput() const override;
	//virtual float GetViewMaxInput() const override;
	//virtual void SetViewRange( float min, float max ) override;
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

	// Get the blend distance of this volume
	FORCEINLINE float GetBlendDistance() const{ return mBlendDistance; }

	//~ Begin AActor Interface
	virtual void PostUnregisterAllComponents( void ) override;
protected:
	virtual void PostRegisterAllComponents() override;
	//~ End AActor Interface
protected:
	/** Add the volume to the world */
	void AddVolume();

	/** Remove the volume from the world */
	void RemoveVolume();
protected:
	UPROPERTY( EditInstanceOnly, Category="Shared")
	float mPriority;

	// The distance that the fog blends over
	UPROPERTY( EditInstanceOnly, Category="Shared")
	float mBlendDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog" )
	FRuntimeFloatCurve mFogHeight;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog" )
	FRuntimeFloatCurve mFogDensity;

	// MODDING EDIT
	///** Interpolate the fog height during the day */
	//UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog" )
	//FRuntimeCurveLinearColor mFogInscatteringColor;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay )
	FRuntimeFloatCurve mFullyDirectionalInscatteringColorDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay )
	FRuntimeFloatCurve mNonDirectionalInscatteringColorDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay )
	FRuntimeFloatCurve mDirectionalInscatteringExponent;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay )
	FRuntimeFloatCurve mDirectionalInscatteringStartDistance;

	// MODDING EDIT
	///** Interpolate the fog height during the day */
	//UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog" )
	//FRuntimeCurveLinearColor mDirectionalInscatteringColor;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog" )
	FRuntimeFloatCurve mFogHeightFalloff;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog", AdvancedDisplay )
	FRuntimeFloatCurve mFogMaxOpacity;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog" )
	FRuntimeFloatCurve mStartDistance;

	/** Interpolate the fog height during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HeightFog" )
	FRuntimeFloatCurve mFogCutoffDistance;

	UPROPERTY( EditAnywhere, Category = "SkySphere", meta = (PinHiddenByDefault, InlineEditConditionToggle) )
	bool mOverrideHorizonColor;

	// MODDING EDIT
	///** How the color of the horizon changes during the day */
	//UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = (EditCondition = "mOverrideHorizonColor") )
	//FRuntimeCurveLinearColor mHorizonColorCurve;

	UPROPERTY( EditAnywhere, Category = "SkySphere", meta = (PinHiddenByDefault, InlineEditConditionToggle) )
	bool mOverrideZenithColor;

	// MODDING EDIT
	///** How the color of the zenith changes during the day */
	//UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = (EditCondition = "mOverrideZenithColor") )
	//FRuntimeCurveLinearColor mZenithColorCurve;

	UPROPERTY( EditAnywhere, Category = "SkySphere", meta = (PinHiddenByDefault, InlineEditConditionToggle) )
	bool mOverrideCloudColor;

	// MODDING EDIT
	///** How the color of clouds zenith changes during the day */
	//UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = (EditCondition = "mOverrideCloudColor") )
	//FRuntimeCurveLinearColor mCloudColorCurve;

	UPROPERTY( EditAnywhere, Category = "SkySphere", meta = (PinHiddenByDefault, InlineEditConditionToggle) )
	bool mOverrideCloudOpacity;

	/** How the opakeness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "SkySphere", meta = (EditCondition = "mOverrideCloudOpacity") )
	FRuntimeFloatCurve mCloudOpacity;
	
	/** The blend weight of the post process volume */
	UPROPERTY( EditAnywhere, Category = "PostProcess" )
	float mBlendWeight;

	UPROPERTY( EditAnywhere, Category = "PostProcess", meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableSaturation:1;

	// MODDING EDIT
	///** Interpolate the saturation during the day */
	//UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess", meta=(EditCondition="mEnableSaturation"))
	//FRuntimeCurveLinearColor mSaturation;
	
	UPROPERTY( EditAnywhere, Category = "PostProcess", meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableContrast:1;

	// MODDING EDIT
	///** Interpolate the contrast during the day */
	//UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess", meta = ( EditCondition = "mEnableContrast" ) )
	//FRuntimeCurveLinearColor mContrast;
	
	UPROPERTY( EditAnywhere, Category = "PostProcess", meta = ( PinHiddenByDefault, InlineEditConditionToggle ) )
	uint8 mEnableGain:1;

	// MODDING EDIT
	///** Interpolate the fog gain during the day */
	//UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "PostProcess", meta = ( EditCondition = "mEnableGain" ) )
	//FRuntimeCurveLinearColor mGain;
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
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Actor.h"
#include "Curves/CurveLinearColor.h"
#include "FGSkySphere.generated.h"

USTRUCT( BlueprintType )
struct FSkySphereSettings
{
	GENERATED_BODY()

	FSkySphereSettings();
	
	// Color of the horizon after blending the skysphere curve with all volumes curves
	UPROPERTY( BlueprintReadOnly, Category = "SkySphere" )
	FLinearColor HorizonColor = {};
	
	// Color of the zenith after blending the skysphere curve with all volumes curves
	UPROPERTY( BlueprintReadOnly, Category = "SkySphere" )
	FLinearColor ZenithColor = {};

	// Color of the clouds after blending the skysphere curve with all volumes curves
	UPROPERTY( BlueprintReadOnly, Category = "SkySphere" )
	FLinearColor CloudColor = {};

	// Color of the clouds after blending the skysphere curve with all volumes curves
	UPROPERTY( BlueprintReadOnly, Category = "SkySphere" )
	FLinearColor SunLightColor = {};

	// Color of the clouds after blending the skysphere curve with all volumes curves
	UPROPERTY( BlueprintReadOnly, Category = "SkySphere" )
	float SunIntensity = {};

	// Color of the clouds after blending the skysphere curve with all volumes curves
	UPROPERTY( BlueprintReadOnly, Category = "SkySphere" )
	FLinearColor MoonLightColor = {};

	// Color of the clouds after blending the skysphere curve with all volumes curves
	UPROPERTY( BlueprintReadOnly, Category = "SkySphere" )
	float MoonIntensity = {};

	// opacity of the clouds after blending the skysphere curve with all volumes curves
	UPROPERTY( BlueprintReadOnly, Category = "SkySphere" )
	float CloudOpacity = {};

	uint8 OverrideHorizonColor : 1;
	uint8 OverrideZenithColor : 1;
	uint8 OverrideCloudColor : 1;
	uint8 OverrideCloudOpacity : 1;
	uint8 OverrideSunLightColor : 1;
	uint8 OverrideSunIntensity : 1;
	uint8 OverrideMoonLightColor : 1;
	uint8 OverrideMoonIntensity : 1;
};

UCLASS(HideCategories=(Input,Rendering))
class FACTORYGAME_API AFGSkySphere : public AActor, public ICurvePanningInterface
{
	GENERATED_BODY()
public:
	AFGSkySphere();

	// Begin AActor interface
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	virtual void BeginDestroy() override;
#if WITH_EDITOR
	virtual void PostEditChangeChainProperty( struct FPropertyChangedChainEvent& propertyChangedEvent ) override;
#endif
	// End AActor interface

	//	Begin ICurvePanningInterface
#if WITH_EDITOR
	virtual float GetViewMinInput() const override;
	virtual float GetViewMaxInput() const override;
	virtual void SetViewRange( float min, float max ) override;
#endif
	// End ICurvePanningInterface

	UFUNCTION( BlueprintImplementableEvent, Category="SkySphere", meta = (CallInEditor = "true") )
	void ApplySkySphereSettings( UPARAM(ref) const FSkySphereSettings& settings );

	/** Update the preview of the skysphere in the editor */	
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, meta=( CallInEditor = "true" ) )
	void UpdatePreview();

	/** Expose getting a value from a FRuntimeCurveLinearColor to bp */
	UFUNCTION( BlueprintPure, Category="Color",meta= ( DefaultToSelf = "worldContext" ) )
	static FLinearColor GetColorCurveValue( const FRuntimeCurveLinearColor& curve, float time );

	/** Expose getting a value from a FRuntimeFloatCurve to bp */
	UFUNCTION( BlueprintPure, Category = "Color", meta = ( DefaultToSelf = "worldContext" ) )
	static float GetFloatCurveValue( const FRuntimeFloatCurve& curve, float time );

	// Get the settings for the sky sphere
	void GetSkySphereSettings( float atTime, FSkySphereSettings& out_settings ) const;
protected:
#if WITH_EDITOR
	/** Setup so that we get calls to UpdatePreview whenever time of day is updated in the editor */
	void SetupPreviewDelegate();
#endif
protected:
	/** How the sunlight changes during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="Curves|Sun")
	FRuntimeCurveLinearColor mSunLightColorCurve;

	/** How does the suns intensity change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Sun" )
	FRuntimeFloatCurve mSunIntensity;

	/** Unlogical property, basically tells how the suns location in it's curve should change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Sun" )
	FRuntimeFloatCurve mSunRotationPitch;

	/** Changes how the lightshafts changes during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Sun" )
	FRuntimeFloatCurve mSunLightShaftOcclusionCurve;

	/** How the moonlight changes during the NIGHT */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Moon" )
	FRuntimeCurveLinearColor mMoonLightColorCurve;

	/** How does the moons intensity change during the NIGHT */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Moon" )
	FRuntimeFloatCurve mMoonIntensity;

	/** Unlogical property, basically tells how the moons location in it's curve should change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Moon" )
	FRuntimeFloatCurve mMoonRotationPitch;

	/** Changes how the lightshafts changes during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Moon" )
	FRuntimeFloatCurve mMoonLightShaftOcclusionCurve;

	/** How does the sky light intensity change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|SkyLight" )
	FRuntimeFloatCurve mSkyLightIntensity;

	/** How does the occlusion tint intensity change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|SkyLight" )
	FRuntimeCurveLinearColor mOcclusionTintColor;

	/** How the color of the horizon changes during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|SkySphere" )
	FRuntimeCurveLinearColor mHorizonColorCurve;

	/** How the color of the zenith changes during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|SkySphere" )
	FRuntimeCurveLinearColor mZenithColorCurve;

	/** How the color of clouds zenith changes during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|SkySphere" )
	FRuntimeCurveLinearColor mCloudColorCurve;

	/** How the opakeness of the clouds change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|SkySphere", DisplayName="Cloudiness" )
	FRuntimeFloatCurve mCloudOpacity;

	/** How does the stars brightness change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|SkySphere" )
	FRuntimeFloatCurve mStarBrightness;

	/** How does the ambient light color change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|SkySphere" )
	FRuntimeCurveLinearColor mSkyLightColor;

	/** How does the sun multiplier change during the day in the atmospheric fog */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|AtmosphericFog" )
	FRuntimeFloatCurve mSunFogMultiplier;

#if WITH_EDITORONLY_DATA
	// In editor, receive updates for whenever the time of day is updated
	FDelegateHandle mTimeOfDayUpdated;

	// For ICurvePanningInterface 
	float mViewMinInput;
	float mViewMaxInput;
#endif
};

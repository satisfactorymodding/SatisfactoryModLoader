// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/DirectionalLightComponent.h"
#include "Components/VolumetricCloudComponent.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/Actor.h"
#include "Curves/CurveLinearColor.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"


#include "FGSkySphere.generated.h"

class UFGWeatherReaction;
UENUM( BlueprintType )
enum class EWeatherType : uint8
{
	Weather_Default,
	Weather_Thunder,
	Weather_Rain,
	Weather_Clear,
	Weather_Overcast,
	Weather_Unset
};

UENUM( BlueprintType )
enum class EWeatherIntensity : uint8
{
	WeatherIntensity_Calm,
	WeatherIntensity_Medium,
	WeatherIntensity_High,
	WeatherIntensity_Insane
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FWeatherChanceEntry
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly )
	FName EntryName;
	
	/* Expected from 0 - 100 it will normalize. */
	UPROPERTY( EditDefaultsOnly )
	float mProbability;

	/* Blueprintable class that applies weather effects to the world. */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class AFGWeatherReaction > mWeatherBehaviour;

	/* Number of days that must pass before the weather can start.*/
	UPROPERTY( EditDefaultsOnly )
	int32 mWeatherStartupDelayDays;

	/* Can this weather effect repeat it self? */
	UPROPERTY( EditDefaultsOnly )
	bool bAllowedToRunInSequence;

	/* Do we need a capture rain occlusion depth map?*/
	UPROPERTY( EditDefaultsOnly )
	bool bRequiresOcclusionRenderTarget;

	UPROPERTY( EditDefaultsOnly )
	FFloatInterval mWeatherEffectDuration;

	void Normalize( float max ) { mProbability *= 100 / max; }

	FWeatherChanceEntry()
	: 	mProbability( 1.f )
	,	mWeatherStartupDelayDays( 0 )
	,	bAllowedToRunInSequence( false )
	, 	mWeatherEffectDuration(120,300)
	{
		
	}
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FSkySphereSettings
{
	GENERATED_BODY()

	FSkySphereSettings();

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
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void OnConstruction(const FTransform& Transform) override;
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

	//////////////////////////////////////////////////////////////////////////////
	// Begin sky sphere mesh & material
	/* Used when volumetric clouds are on. */
	UPROPERTY(EditDefaultsOnly, Category = "SkySphere|Material")
	UMaterialInterface* mDefaultMaterial;

	/* Used when volumetric clouds are off. */
	UPROPERTY(EditDefaultsOnly, Category = "SkySphere|Material")
	UMaterialInterface* mDefaultLowSpecMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "SkySphere")
	UStaticMesh* mDefaultMesh;

	UPROPERTY(BlueprintReadOnly)
	UStaticMeshComponent* mSkyMeshComponent;
	
	/* Called when volumetric clouds settings are changed. */
	UFUNCTION(BlueprintCallable)
	void UpdateMaterial( bool bWithVolumetricClouds );

	UFUNCTION(BlueprintCallable)
	static void SetDirectionalLightIntensityMultiplierOverride( float multiplier );

	UFUNCTION(BlueprintCallable)
	static float GetDirectionalLightIntensityMultiplierOverride();

	// End sky sphere mesh & materials.
	///////////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////////
	// Begin Weather
	/* Index in the WeatherStateList */
	UPROPERTY( VisibleAnywhere,ReplicatedUsing=OnRep_OnWeatherChanged, SaveGame )
	int32 mCurrentSelectedWeather;
	
	UFUNCTION( BlueprintCallable, Category = "Weather" )
    FWeatherChanceEntry GetNewWeatherState();

	UFUNCTION( BlueprintPure, Category = "Weather" )
    FWeatherChanceEntry GetCurrentWeatherState() const { return mWeatherStateList[ mCurrentSelectedWeather ]; }

	UFUNCTION( BlueprintPure, Category = "Weather" )
	int32 GetCurrentWeatherStateID() const { return mCurrentSelectedWeather; }

	UFUNCTION( BlueprintCallable, Category = "Weather" )
	void SetWeatherState( int32 NewTypeID );

	UFUNCTION()
	void OnRep_OnWeatherChanged( int32 OldState );

	/* Set intensity on both moon and sun light directly. */
	UFUNCTION(BlueprintCallable, Category = "Weather")
	void SetCloudShadowIntensity(float NewValue);

	/* Moon & sun should have the same values, so we only check one of them. */
	UFUNCTION(BlueprintPure, Category = "Weather")
	float GetCloudShadowIntensity() const;

	UFUNCTION(BlueprintCallable, Category = "Weather")
	void TryUpdateSceneCaptureLocation( bool bForce = false);

	void UpdateOcclusionDistance();

	/* Array with the same size of mWeatherStateList containing pointers to weather reaction actors. */
	UPROPERTY()
	TArray< TWeakObjectPtr< class AFGWeatherReaction > > mWeatherReactionActors;
		
	UPROPERTY( EditDefaultsOnly, Category = "Weather" )
	TArray< FWeatherChanceEntry > mWeatherStateList;

	/* Fallback entry id.*/
	UPROPERTY( EditDefaultsOnly, Category = "Weather" )
	int32 mDefaultWeatherEntry;

	UPROPERTY( EditDefaultsOnly, Category = "Weather" )
	FFloatInterval mWeatherChangeDelayTime;

	/* Last time we changed the weather state. */
	float mLastWeatherUpdateTime;

	/* Set when new weather type is picked.*/
	float mCurrentWeatherDelay;

	/* Texture used for rain occlusion. Updated on tick with grid snapping to the player location.*/
	UPROPERTY( VisibleAnywhere, Category = "Weather|Occlusion" )
	class USceneCaptureComponent2D* mRainOcclusionSceneCapture2DComponent;

	UPROPERTY( EditDefaultsOnly, Category = "Weather|Occlusion" )
	class UTextureRenderTarget2D* mRainOcclusionRT;

	UPROPERTY( EditDefaultsOnly, Category = "Weather|Occlusion" )
	class UMaterialParameterCollection* mRainOcclusionMaterialParameterCollection;

	//TODO deprecate this or move this to weather data.
	UPROPERTY( EditDefaultsOnly)
	UMaterialParameterCollection* mTimeOfDayCollection;

	// TODO maybe we want to save this in the future.
	UPROPERTY()
	FRandomStream mWeatherSeed;

	/* Cached occlusion actor for rain and maybe grass in the future. */
	UPROPERTY()
	class AFGRainOcclusionActor* mRainOcclusionActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFGRainOcclusionActor> mDefaultRainOcclusionActorClass;

	/* Cached alpha value for randomization from FRandomStream mWeatherSeed */
	float mCachedSeedResult;

	UPROPERTY(EditAnywhere,Category = "Weather|Occlusion")
	float mRainCaptureDistance;

	// TOOD should we have this?
	UPROPERTY( EditDefaultsOnly, Category = "Weather|Occlusion" )
	float mSceneCaptureGridSnap;

	bool bLockWeatherState;
	// End weather
	//////////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////////
	// Begin light control
	UFUNCTION( )
	void UpdateLightRotation();

	UFUNCTION( )
	void UpdateCurvesFromTime();

	UFUNCTION( )
	void CalculateDominantLight();

	void UpdateDominantLight( ADirectionalLight* NewDominantLight);
	
	UFUNCTION( BlueprintCallable )
	FRotator CalculateLightRotation( FRotator OriginalRotation, FRotator RotationAxis, FRuntimeFloatCurve LightRotationCurve ) const;
	// End light control
	//////////////////////////////////////////////////////////////////////////////

	/* Is everything initialized and are the components valid? */
	UFUNCTION( BlueprintPure )
	bool CanUpdate();

	/* Editor version excluding the time of day subsystem.*/
	UFUNCTION( BlueprintPure )
	bool CanUpdatePreview() const;

	UFUNCTION( BlueprintNativeEvent, Category="SkySphere", meta = (CallInEditor = "true") )
	void ApplySkySphereSettings( UPARAM(ref) const FSkySphereSettings& settings );

	/** Update the preview of the skysphere in the editor */	
	UFUNCTION( BlueprintCallable, meta=( CallInEditor = "true" ) )
	void UpdatePreview();

	/** Expose getting a value from a FRuntimeCurveLinearColor to bp */
	UFUNCTION( BlueprintPure, Category="Color",meta= ( DefaultToSelf = "worldContext" ) )
	static FLinearColor GetColorCurveValue( const FRuntimeCurveLinearColor& curve, float time );

	/** Expose getting a value from a FRuntimeFloatCurve to bp */
	UFUNCTION( BlueprintPure, Category = "Color", meta = ( DefaultToSelf = "worldContext" ) )
	static float GetFloatCurveValue( const FRuntimeFloatCurve& curve, float time );

	// Get the settings for the sky sphere
	void GetSkySphereSettings( float atTime, FSkySphereSettings& out_settings ) const;
	
	UFUNCTION( BlueprintPure )
	static bool DoesWeatherEffectNeedOcclusion( const FWeatherChanceEntry& Type );

	UFUNCTION( BlueprintCallable )
	void UpdateGlobalMaterialCollection();
protected:
#if WITH_EDITOR
	friend class AFGWorldSettings;

	/** Setup so that we get calls to UpdatePreview whenever time of day is updated in the editor */
	void SetupPreviewDelegate();
#endif

	/** How the sunlight changes during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="Curves|Sun")
	FRuntimeCurveLinearColor mSunLightColorCurve;

	/** How does the suns intensity change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Sun" )
	FRuntimeFloatCurve mSunIntensity;

	/** Unlogical property, basically tells how the suns location in it's curve should change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Sun" )
	FRuntimeFloatCurve mSunRotationPitch;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Moon" )
	FRuntimeCurveLinearColor mMoonLightColorCurve;

	/** How does the moons intensity change during the NIGHT */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Moon" )
	FRuntimeFloatCurve mMoonIntensity;

	/** Unlogical property, basically tells how the moons location in it's curve should change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|Moon" )
	FRuntimeFloatCurve mMoonRotationPitch;

	/** How does the occlusion tint intensity change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|SkyLight" )
	FRuntimeCurveLinearColor mOcclusionTintColor;

	/** How does the ambient light color change during the day */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Curves|SkySphere" )
	FRuntimeCurveLinearColor mSkyLightColor;

	UPROPERTY( Transient )
	ADirectionalLight* mCurrentLight;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "World Actors")
	ASkyLight* mSkyLight;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "World Actors")
	ADirectionalLight* mSunLight;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "World Actors")
	ADirectionalLight* mMoonLight;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "World Actors")
	AVolumetricCloud* mClouds;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Default Settings")
	FRotator mSunOriginRotation;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Default Settings")
	FRotator mSunRotationAxis;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Default Settings")
	FRotator mMoonOriginRotation;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Default Settings")
	FRotator mMoonRotationAxis;	

	/* Tick rate control for day time, this is to avoid the shadow jitter / artifacts. */
	UPROPERTY(EditDefaultsOnly,Category = "Default Settings")
	float mDayTickRate;

	/* Tick rate control for night time, this is to avoid the shadow jitter / artifacts. */
	UPROPERTY(EditDefaultsOnly,Category = "Default Settings")
	float mNightTickRate;

	UPROPERTY(Transient)
	class AFGTimeOfDaySubsystem* mCachedTimeOfDaySubSystem;

	bool mIsInitialized;

#if WITH_EDITORONLY_DATA
	// In editor, receive updates for whenever the time of day is updated
	FDelegateHandle mTimeOfDayUpdated;

	// For ICurvePanningInterface 
	float mViewMinInput;
	float mViewMaxInput;
#endif
};

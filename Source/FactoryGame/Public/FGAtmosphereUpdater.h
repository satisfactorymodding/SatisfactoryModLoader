// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "UObject/Object.h"
#include "FGAtmosphereVolume.h"
#include "FGAtmosphereUpdater.generated.h"


/**
* Struct containing debugging info for monitoring atmosphere volumes in the editor.
*/
USTRUCT()
struct FAtmosphereVolumeBlend
{
	GENERATED_BODY()
	
	FORCEINLINE FString ToString() const
	{
		if( Volume.IsValid() )
		{
			return FString::Printf( TEXT( "Blend: %.01f %%, Priority: %.02f, Volume: %s" ), BlendRatio * 100.f, Volume->GetPriority(), *Volume->GetName() );
		}

		return FString( TEXT( "Invalid volume" ) );
	}

	UPROPERTY()
	TWeakObjectPtr< AFGAtmosphereVolume > Volume = nullptr;

	float BlendRatio = 0.f;
};


/**
 * Exists both in EditorEngine and GameEngine, encapsulates the interpolation ExponentialHeightFog
 */
UCLASS()
class FACTORYGAME_API UFGAtmosphereUpdater : public UObject
{
	GENERATED_BODY()
public:
	UFGAtmosphereUpdater();
	
	/** Update the value of the height fog in each world */
	void Tick( float dt );
	
	const TArray< FAtmosphereVolumeBlend > &GetEffectiveAtmosphereVolumes() const;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	class UFGBiome *BiomeOverride = nullptr;

	bool SuspendSkyAtmosphereUpdates = false;
	bool SuspendSkyBoxUpdates = false;
	bool SuspendExponentialHeightFogUpdates = false;

	FORCEINLINE bool ShouldUpdateSkyAtmosphere() const
	{
		return !SuspendSkyAtmosphereUpdates;
	}

	FORCEINLINE bool ShouldUpdateSkyBox() const
	{
		return !SuspendSkyBoxUpdates;
	}

	FORCEINLINE bool ShouldUpdateExponentialHeightFog() const
	{
		return !SuspendExponentialHeightFogUpdates;
	}
#else
	constexpr bool ShouldUpdateSkyAtmosphere() const
	{
		return true;
	}

	constexpr bool ShouldUpdateSkyBox() const
	{
		return true;
	}

	constexpr bool ShouldUpdateExponentialHeightFog() const
	{
		return true;
	}

#endif 
	
protected:
	/** Apply the fog settings to the current world */
	void ApplyFogSettings( const FExponentialFogSettings& fogSettings, class UWorld* world ) const;

	void ApplySkyAtmosphereSettings( const struct FSkyAtmosphereSettings& settings, class UWorld* world ) const;

	/** Interpolate in src settings into destination, when alpha is 1, then take entire src */
	void InterpolateFogSettings( FExponentialFogSettings& dest, const FExponentialFogSettings& src, float alpha ) const;

	/** Interpolate in src settings into destination, when alpha is 1, then take entire src */
	void InterpolateSkySphereSettings( struct FSkySphereSettings& dest, const struct FSkySphereSettings& src, float alpha ) const;

	void InterpolateAtmosphereSettings( struct FSkyAtmosphereSettings& dest, const struct FSkyAtmosphereSettings &src, float alpha ) const;

	/** Update a single world */
	void UpdateWorld( UWorld* world );

	/** returns true if we should update the given world */
	bool ShouldUpdateWorld( UWorld* world ) const;

private:
	void AtmosphereDebuggingChanged(IConsoleVariable *var);
	
	UPROPERTY()
	TArray< FAtmosphereVolumeBlend > mBlendingVolumes;

	bool mDebuggingEnabled = false;
	FDelegateHandle mDebugMessageDelegateHandle;
};

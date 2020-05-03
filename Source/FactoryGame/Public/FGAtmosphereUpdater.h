#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UObject/Class.h"

#include "Object.h"
#include "FGAtmosphereVolume.h"
#include "FGAtmosphereUpdater.generated.h"

/**
 * Exists both in EditorEngine and GameEngine, encapsulates the interpolation ExponentialHeightFog
 */
UCLASS()
class FACTORYGAME_API UFGAtmosphereUpdater : public UObject
{
	GENERATED_BODY()
public:
	/** Update the value of the height fog in each world */
	void Tick( float dt );
public: //MODDING EDIT
	/** Apply the fog settings to the current world */
	void ApplyFogSettings( const FExponentialFogSettings& fogSettings, class UWorld* world );
protected: // MODDING EDIT
	/** Interpolate in src settings into destination, when alpha is 1, then take entire src */
	void InterpolateFogSettings( FExponentialFogSettings& dest, const FExponentialFogSettings& src, float alpha ) const;

	/** Interpolate in src settings into destination, when alpha is 1, then take entire src */
	void InterpolateSkySphereSettings( struct FSkySphereSettings& dest, const struct FSkySphereSettings& src, float alpha ) const;

	/** Update a single world */
	void UpdateWorld( UWorld* world );

	/** returns true if we should update the given world */
	bool ShouldUpdateWorld( UWorld* world ) const;
protected:
	/** The worlds we want to affect */
	UPROPERTY()
	TArray< class UWorld* > mActiveWorlds;

public:
	FORCEINLINE ~UFGAtmosphereUpdater() = default;
};

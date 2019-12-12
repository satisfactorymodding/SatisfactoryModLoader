#pragma once
#include "Engine/Scene.h"
#include "Array.h"
#include "UObject/Class.h"
#include "Interfaces/Interface_PostProcessVolume.h"
#include "Object.h"
#include "FGSharedPostProcessSettings.generated.h"

void InsertPPVolume( IInterface_PostProcessVolume* volume, TArray< IInterface_PostProcessVolume* >& out_volumeArray );

/**
* Presets for post process settings for water volumes
*/
UCLASS( Abstract, Blueprintable )
class UFGSharedPostProcessSettings : public UObject
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGSharedPostProcessSettings();

	// Accessors
	FORCEINLINE const FPostProcessSettings& GetPostProcessSettings() const{ return mPostProcessSettings; }
	FORCEINLINE float GetBlendRadius() const{ return mBlendRadius; }
	FORCEINLINE float GetBlendWeight() const{ return mBlendWeight; }
	FORCEINLINE float GetPriority() const{ return mPriority; }
protected:
	/** Normal settings for post process  */
	UPROPERTY( EditDefaultsOnly, Category = "PostProcess" )
	FPostProcessSettings mPostProcessSettings;

	/** At what distance do we want to blend in the post process settings for the water */
	UPROPERTY( EditDefaultsOnly, Category = "PostProcess" )
	float mBlendRadius;

	/** How much do we want to blend in the post process effect */
	UPROPERTY( EditDefaultsOnly, Category = "PostProcess" )
	float mBlendWeight;

	/** Priority of the post process effect */
	UPROPERTY( EditDefaultsOnly, Category = "PostProcess" )
	float mPriority;
};
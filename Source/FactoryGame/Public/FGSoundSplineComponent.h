// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AkComponent.h"
#include "FGSoundSplineComponent.generated.h"

//@todo-cleanup Is this still in use? Move to Ak maybe?
UCLASS(meta=(BlueprintSpawnableComponent))
class FACTORYGAME_API UFGSoundSplineComponent : public UAkComponent
{
	GENERATED_BODY()
public:
	UFGSoundSplineComponent();

	//~ Begin UActorComponent interface
	virtual void Activate( bool reset ) override;
	virtual void SetAutoActivate( bool newAutoActivate ) override;
	//~ End UActorComponent interface

	/** Set the interval of emitters */
	UFUNCTION(BlueprintCallable, Category="Audio|Spline", meta=(CallInEditor=true))
	void SetEmitterInterval( float newEmitterInterval );

	/** Get the distance between each emitter of the spline  */
	UFUNCTION(BlueprintPure, Category="Audio|Spline", meta=(CallInEditor=true))
	FORCEINLINE float GetEmitterInterval( float newEmitterInterval ) const { return mEmitterInterval; }

	// Begin UAkComponent interface
	virtual void UpdateGameObjectPosition(); // override; // MODDING EDIT: original is not virtual
	// End UAkComponent interface
protected:
	/** Distance between each emitter on our parent spline, this might be scaled slightly so that we get a point on both start and end */
	UPROPERTY( EditAnywhere, Category="Audio",Meta=(UIMin=100,UIMax=1000,ClampMin=50))
	float mEmitterInterval;
};

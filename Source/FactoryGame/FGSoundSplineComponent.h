#pragma once
#include "UObject/Class.h"

#include "AkComponent.h"
#include "FGSoundSplineComponent.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class UFGSoundSplineComponent : public UAkComponent
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
	// MODDING EDIT: Does not override error
	//virtual void UpdateGameObjectPosition() override;
	// End UAkComponent interface
protected:
	/** Distance beween each emitter on our parent spline, this might be scaled slightly so that we get a point on both start and end */
	UPROPERTY( EditAnywhere, Category="Audio",Meta=(UIMin=100,UIMax=1000,ClampMin=50))
	float mEmitterInterval;
};

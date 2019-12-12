#pragma once
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGRiverSpline.generated.h"

UCLASS()
class AFGRiverSpline : public AActor
{
	GENERATED_BODY()
public:
	AFGRiverSpline();

	//~ Begin AActor interface
	virtual void PostLoad() override;
	//~ End AActor interface

#if WITH_EDITOR
	// Check if this is properly setup
	virtual void CheckForErrors() override;
#endif
protected:
	/** The audio event this river plays */
	UPROPERTY( BlueprintReadOnly, EditInstanceOnly, Category="Audio", Meta=(EditCondition=mShouldHaveAudio) )
	class UAkAudioEvent* mAudioEvent;

	/** Distance between each emitter on the spline */
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category="Audio", Meta = ( EditCondition = mShouldHaveAudio,UIMin=100,ClampMin=50,UIMax=1000) )
	float mEmitterInterval;

	/** The component that has our sound spline */
	UPROPERTY()
	class UFGSoundSplineComponent* mSoundSplineComponent_DEPRECATED;

	/** If true, then we should have no audio */
	UPROPERTY( BlueprintReadOnly, EditInstanceOnly, Category = "Audio" )
	bool mShouldHaveAudio;
};
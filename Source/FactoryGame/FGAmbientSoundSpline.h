// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSignificanceInterface.h"
#include "FGAmbientSoundSpline.generated.h"

UCLASS()
class FACTORYGAME_API AFGAmbientSoundSpline : public AActor, public IFGSignificanceInterface
{
	GENERATED_BODY()
	 
public:	
	AFGAmbientSoundSpline();  

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
public:
	//IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override; 
	virtual float GetSignificanceRange() override;
	//End
public:
	/** Gets the spline component */
	UFUNCTION()
	FORCEINLINE class USplineComponent* GetSplineComponent(){ return mSpline; }
protected:
	/** Spline to put multiple positions along. */
	UPROPERTY( EditAnywhere, Category = "Ambient Sound Spline" )
	class USplineComponent* mSpline;

	/** AkComponent that plays the sound on the spline. */
	UPROPERTY( EditAnywhere, Category = "Ambient Sound Spline" )
	class UFGSoundSplineComponent* mSoundSpline;

	/** Range that this volume should be significant within */
	UPROPERTY( EditInstanceOnly, Category = "Significance" )
	float mSignificanceRange;
};

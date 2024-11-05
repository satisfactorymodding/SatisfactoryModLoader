// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCreatureActionAnimated.h"
#include "FGCreatureActionRoar.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FACTORYGAME_API UFGCreatureActionRoar : public UFGCreatureActionAnimated
{
	GENERATED_BODY()
public:
	UFGCreatureActionRoar( const FObjectInitializer& ObjectInitializer );

	// Begin UFGAction Interface
	virtual void PerformAction_Implementation() override;
	virtual void InternalActionCleanup( bool actionSuccess ) override;
	// End UFGAction Interface

	// Begin UFGCreatureActionAnimatedBase Interface
	virtual void OnAnimNotify_Implementation( const UFGAnimNotify* Notify ) override;
	virtual void OnAnimationFinished_Implementation( class UAnimMontage* montage, bool WasInterrupted ) override;
	// End UFGCreatureActionAnimatedBase Interface

	/** Called when the roar has begun in the animation. */
	UFUNCTION( BlueprintNativeEvent, Category = "Roar" )
	void OnBeginRoar();

	/** Called when the roar ends in the animation. */
	UFUNCTION( BlueprintNativeEvent, Category = "Roar" )
	void OnEndRoar();

protected:
	UFUNCTION( NetMulticast, Reliable )
	void BeginRoar();

	UFUNCTION( NetMulticast, Reliable )
	void EndRoar();

	UFUNCTION()
	void MakeRoarNoise();

private:
	void StopNoiseTimer();

protected:
	/** What kind of noise to make. */
	UPROPERTY( EditDefaultsOnly, Category = "Roar" )
	TSubclassOf< class UFGNoise > mNoiseClass;

	/** Whether or not we are currently roaring. */
	UPROPERTY( BlueprintReadOnly, Category = "Roar" )
	bool mIsRoaring;

private:
	/** How often we want to make the noise for the roar. */
	UPROPERTY( EditDefaultsOnly, Category = "Roar" )
	float mRoarNoiseTickrate;
	
	FTimerHandle mRoarNoiseTimerHandle;
};

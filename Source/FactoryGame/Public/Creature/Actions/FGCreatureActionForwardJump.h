// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCreatureActionAnimatedBase.h"
#include "FGCreatureActionForwardJump.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCreatureActionForwardJump : public UFGCreatureActionAnimatedBase
{
	GENERATED_BODY()

public:
	UFGCreatureActionForwardJump( const FObjectInitializer& ObjectInitializer );

	virtual void PerformAction_Implementation() override;
	virtual void CleanupAction_Implementation( bool actionSuccess ) override;

protected:
	/** Called in order to launch the creature forward. */
	UFUNCTION( BlueprintNativeEvent, Category = "Jump" )
	void Jump();

	/** Called whenever the creature lands after jumping. */
	UFUNCTION( BlueprintNativeEvent, Category = "Jump" )
	void OnLanded();

	/** Returns the launch velocity for the jump. Override for easter eggs or whatever. */
	UFUNCTION( BlueprintNativeEvent, Category = "Jump" )
	FVector GetLaunchVelocity();

	virtual void OnAnimationFinished_Implementation( UAnimMontage* montage, bool WasInterrupted ) override;

private:
	UFUNCTION()
	void OnCreatureLandedCallback( const FHitResult& hitResult );

private:
	/** The amount of forward force to apply. */
	UPROPERTY( EditDefaultsOnly, Category = "Jump" )
	float mForwardVelocity;

	/** The amount of upward force to apply. */
	UPROPERTY( EditDefaultsOnly, Category = "Jump" )
	float mUpwardVelocity;

	/** The montage to play before starting the jump. */
	UPROPERTY( EditDefaultsOnly, Category = "Animation" )
	class UAnimMontage* mJumpStartMontage;

	bool mIsStartingJump;
	bool mIsJumping;
};

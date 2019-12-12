// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "Animation/AnimInstance.h"
#include "FGCharacterAnimInstance.generated.h"

/**
 * Common base class for player and enemies so we can add functionality for hit animations and such
 */
UCLASS()
class FACTORYGAME_API UFGCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	/** Constructor */
	UFGCharacterAnimInstance();
	
	/** Caching stuff */
	virtual void NativeUpdateAnimation( float DeltaSeconds );

	/** Our pawn has taken point damage */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Pawn" )
	void OnPointDamageTaken( FVector shootDIrection );


	/** Our pawn has taken any damage */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Pawn" )
	void OnAnyDamageTaken();

	/** Our pawn has taken radial damage */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Pawn" )
	void OnRadialDamageTaken();

	/** Return desired character rotation based on floor */
	UFUNCTION( BlueprintPure, Category = "Animation" )
	FRotator GetDesiredWalkRotation();

	/** Return desired character rotation based on floor */
	UFUNCTION( BlueprintPure, Category = "Animation" )
	FRotator GetDesiredRunLeanRotation();

	/** cached character of this animation */
	UFUNCTION( BlueprintPure, Category = "Animation" )
	FORCEINLINE AFGCharacterBase* GetCachedCharacter(){ return mCachedCharacter; }

	/** Returns velocity */
	UFUNCTION( BlueprintPure, Category = "Animation" )
	FORCEINLINE FVector GetVelocity(){ return mVelocity; }

	/** Returns velocitys direction in degrees */
	UFUNCTION( BlueprintPure, Category = "Animation" )
	FORCEINLINE float GetVelocityDirection(){ return mDirection; }

	/** Returns velocitys direction in degrees */
	UFUNCTION( BlueprintPure, Category = "Animation" )
	FORCEINLINE float GetAccelerationVectorLength(){ return mAccelerationVectorLength; }
private: 
	/** Event fired when creature turns in place */
	void TurnInPlaceEvent( float dt );
public:
	/** in degrees */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	float mDirection;

	/**acceleration length normalized */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	float mAccelerationVectorLength;

	/** Velocity */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	FVector mVelocity;

	/** Velocity normalized in local space */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	FVector mVelocityLocalNormalized;

	/** Acceleration normalized in local space */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	FVector mAccelerationLocalNormalized;

	/** Velocity normalized in local space */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	FTransform mActorTransform;

	/** Caching the character one */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	AFGCharacterBase* mCachedCharacter;

	/** Caching movement mode */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	TEnumAsByte< EMovementMode > mCachedMovementMode;

	/** Cached default value of movement mode */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	TEnumAsByte< EMovementMode > mCachedDefaultWalkMode;

	/** Speed in movement */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	float mSpeed;

	/** Saved speed from last time we checked */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	float mSpeedLastFrame;

	/** Speed in movement Z */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	float mSpeedZ;

	/** Walk rotation */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	float mWalkRotation;

	/** Are we standing still */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	bool mIsStandingStill;

	/** Did we begin movement */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	bool mIsAccelerating;

	/** Used for lean/run calculations */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	float mYawDelta;

	/** Where do we want to aim */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	float mAimYaw;

	/** Configable interpspeed */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mAimYawInterpSpeed;

	/** Rotation of root component */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	FRotator mRootRotation;

	/** should we turn left */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	bool mTurnInPlaceLeft;
	
	/** or right */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	bool mTurnInPlaceRight;

	/** are we done turning? */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	bool mTurnInPlaceComplete;

	/** Rotation values when turning left */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	UCurveFloat* mTurnLeftCurve;

	/** Rotation values when turning right */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	UCurveFloat* mTurnRightCurve;

	/** I don't even know anymore, converting BP stuff */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	FVector mActorRotationForwardVector;

	/** I don't even know anymore, converting BP stuff */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	FVector mActorRotationForwardVectorReference;

	/** I don't even know anymore, converting BP stuff */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	float mAimYawReductionStartTime;

	/** I don't even know anymore, converting BP stuff */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	float mAimYawReductionCurrentTime;

	/** Last Rotation saved */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	FRotator mActorRotationLastTick;

	/**Editable for Bigges sake */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mYawRotationStrength;

	/**Editable for Bigges sake */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mYawRotationInterpSpeed;

	/** Configable interp speed for root rotation */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mRootRotationInterpSpeed;

	/** reset variable for turn stuff */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	bool mAllowedToTurn;

	/** Time we started a turninplace */
	float mTurnInPlaceTimer;

	/** How long the turn should take */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mTurnInPlaceDefaultTime;

	/** should we run the turn in place code */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	bool mUseTurnInPlace;

	/** should we run the turn in place code */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	bool mCanUpdateActorRotationReference;

	/** When should we turn to the right */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Anim" )
	float mYawAimMaxValue;

	/** when should we turn to the left */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Anim" )
	float mYawAimMinValue;

	/** Look up */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	float mAimPitch;

	/** Interpspeed */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mAimPitchInterpSpeed;  

	/** Used in the 1p anim of the player only */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	bool mGetDeltaPitchRotation;

	/** Should we do pre land calculations? */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	bool mUsePreLand;

	/** Pre land value */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	bool mPreLand;

	/** Multiplier for velocity that determines how long the preland trace is */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mPreLandVelocityMultiplier;

	/** What to collide against in pre land */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	TArray< TEnumAsByte< ECollisionChannel > > mPreLandCollisionChannels;
};

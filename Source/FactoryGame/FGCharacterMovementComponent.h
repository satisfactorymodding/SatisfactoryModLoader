// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "FGCharacterMovementComponent.generated.h"

/**
 * Custom states we can be in
 */
UENUM( BlueprintType )
enum class ECustomMovementMode : uint8
{
	CMM_None = 0		UMETA( DisplayName = "None" ),
	CMM_Ladder			UMETA( DisplayName = "Ladder" )
};


UCLASS()
class FACTORYGAME_API UFGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UFGCharacterMovementComponent();
	
	// Begin UActorComponent
	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction ) override;
	// End UActorComponent

	// Begin UCharacterMovementComponent
	virtual class FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	virtual bool DoJump( bool isReplayingMoves ) override;
	virtual void CalcVelocity( float dt, float friction, bool isFluid, float brakingDeceleration ) override;
	virtual float GetMaxSpeed() const override;
	virtual void SetDefaultMovementMode() override;
	// End UCharacterMovementComponent


	UFUNCTION( Reliable, Server, WithValidation )
	void ServerSetHookLocation( const FVector& hookLocation );

	/** Sets the location of the current hook */
	void SetHookLocation( const FVector& hookLocation);

	/** Get hook location */
	FORCEINLINE const FVector& GetHookLocation() const { return mHookLocation; }

	/** Get mIsSprinting */
	UFUNCTION( BlueprintPure, Category = "Sprint" )
	FORCEINLINE bool GetIsSprinting() const { return mIsSprinting; }

	/** Get mGetWantsToSprint */
	UFUNCTION( BlueprintPure, Category = "Sprint" )
	FORCEINLINE bool GetWantsToSprint() const { return mWantsToSprint; }

	/** Set if the player wants to sprint or not */
	void SetWantsToSprint( bool wantsToSprint );

	/** Gets the accumulated impulse we want to apply */
	FORCEINLINE FVector GetPendingImpulseToApply(){ return PendingImpulseToApply; }

	/** Setter for the chute */
	FORCEINLINE void SetCachedParachute( class AFGParachute* inParachute ) { mCachedParachute = inParachute; } 

	/** Setter for the chute */
	FORCEINLINE void SetCachedJumpingStilts( class AFGJumpingStilts* inJumpingStilts ) { mCachedJumpingStilts = inJumpingStilts; }

	/** Ladder functions */
	bool CanGrabLadder( class UFGLadderComponent* ladder ) const;
	void StartClimbLadder( class UFGLadderComponent* ladder );
	void StopClimbLadder();
	bool IsClimbingOnLadder() const { return CustomMovementMode == ( uint8 )ECustomMovementMode::CMM_Ladder; }
	void JumpOffLadder();

	/** @return The ladder we're climbing on; nullptr if not climbing. */
	UFUNCTION( BlueprintPure, Category = "Ladder" )
	class UFGLadderComponent* GetOnLadder() const;

protected:
	// Begin UCharacterMovementComponent
	virtual void UpdateFromCompressedFlags(uint8 flags) override;
	virtual void OnMovementUpdated(float deltaSeconds, const FVector & oldLocation, const FVector & oldVelocity) override;
	virtual void OnMovementModeChanged( EMovementMode PreviousMovementMode, uint8 PreviousCustomMode ) override;
	virtual void PhysCustom( float deltaTime, int32 Iterations ) override;
	// End UCharacterMovementComponent

	void SetOnLadder( class UFGLadderComponent* ladder );



	virtual void PhysFlying( float deltaTime, int32 Iterations ) override;

private:
	/** Apply ladder climb physics */
	void PhysLadder( float deltaTime, int32 iterations );

	/** Updates everything that has to do with JetPack */
	void UpdateJetPack( float deltaSeconds );

	/** Updates everything that has to do with Hookshot */
	void UpdateHookshot( float deltaSeconds, FVector oldLocation );

	/** Checks if we still can sprint */
	void UpdateSprintStatus( float delta );

	/** Updates everything that has to do with Parachute */
	void UpdateParachute( float delta );

	/** Updates everything that has to do with the jumping stilts */
	void UpdateJumpingStilts( float deltaSeconds );

	/** Returns true if the player is allowed to sprint */
	bool CanSprint();

	/** Returns or finds the jet pack */
	class AFGJetPack* GetCachedJetPack();

	/** Returns or finds the cached hookshot */
	class AFGHookshot* GetCachedHookshot();

	/** Returns or finds the parachute */
	class AFGParachute* GetCachedParachute();

	/** Returns or finds the parachute */
	class AFGJumpingStilts* GetCachedJumpingStilts();

public:
	/** Timestamp of last time we jumped */
	UPROPERTY( BlueprintReadOnly, Category = "Jump" )
	float mLastJumpTimeStamp;

	/** If true, try to parachuting on next update. If false, try to stop parachuting on next update. */
	UPROPERTY( BlueprintReadOnly, Category = "JetPack" )
	uint32 mIsParachuting : 1;

	/** The speed at which a character climbs ladders */
	UPROPERTY( EditDefaultsOnly, Category = "Sprint" )
	float mClimbSpeed;

	/** The speed at witch a character sprints */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint" )//ReadWrite is only to enable blueprint prototoyping of shit.
	float mMaxSprintSpeed;

	/** True if the player wants to sprint */
	bool mWantsToSprint;

	/** Keeps is the player sprinting this update or not? */
	bool mIsSprinting;

	/** The minimum dot value between velocity and character forward to allow sprint.*/
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Sprint" )
	float mSprintMinDotResult;

	/** Force to apply when jumping off a ladder. */
	UPROPERTY( EditDefaultsOnly, Category = "Ladder" )
	float mJumpOffLadderVelocity;

private:
	friend class FSavedMove_FGMovement;

	/** A cached instance of the equipment that issued jet pack thrust */
	UPROPERTY()
	class AFGJetPack* mCachedJetPack;

	/** A cached instance of the equipment that issued parachuting */
	UPROPERTY()
	class AFGParachute* mCachedParachute;

	/** A cached instance of the equipment that set our hookshot location */
	UPROPERTY()
	class AFGHookshot* mCachedHookshot;

	/** A cached instance of the equipment that set our jumping stilts */
	UPROPERTY()
	class AFGJumpingStilts* mCachedJumpingStilts;

	/** The location that our hook sits at */
	FVector mHookLocation;

	/** The ladder we're climbing; null if not climbing. */
	UPROPERTY()
	UFGLadderComponent* mOnLadder;


	//Cheat
	public:
	bool mCheatIsPressingJump: 1;
	bool mCheatIsPressingCrouch : 1;
	bool mCheatGhost : 1;
	float CheatFlySpeedVertical;
	void ZeroOutFallVelocity();
	//end Cheat
};

class FSavedMove_FGMovement : public FSavedMove_Character
{
	typedef FSavedMove_Character Super;
public:
	///@brief Resets all saved variables.
	virtual void Clear() override;

	///@brief Store input commands in the compressed flags.
	virtual uint8 GetCompressedFlags() const override;

	///@brief This is used to check whether or not two moves can be combined into one.
	///Basically you just check to make sure that the saved variables are the same.
	virtual bool CanCombineWith(const FSavedMovePtr& newMove, ACharacter* character, float maxDelta) const override;

	///@brief Sets up the move before sending it to the server. 
	virtual void SetMoveFor(ACharacter* character, float inDeltaTime, FVector const& newAccel, class FNetworkPredictionData_Client_Character & clientData) override;
	///@brief Sets variables on character movement component before making a predictive correction.
	virtual void PrepMoveFor(class ACharacter* character) override;

	uint8 mSavedIsThrusting : 1;

	uint8 mSavedIsSprinting : 1;

	uint8 mSavedIsParachuting : 1;

	FVector mSavedHookLocation;
};

class FNetworkPredictionData_Client_FGMovement : public FNetworkPredictionData_Client_Character
{
public:
	FNetworkPredictionData_Client_FGMovement(const UCharacterMovementComponent& clientMovement);

	typedef FNetworkPredictionData_Client_Character Super;

	///@brief Allocates a new copy of our custom saved move
	virtual FSavedMovePtr AllocateNewMove() override;
};

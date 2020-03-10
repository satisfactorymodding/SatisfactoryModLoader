// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "FGCharacterMovementComponent.generated.h"

class AFGBuildablePipeBase;


USTRUCT( BlueprintType )
struct FACTORYGAME_API FPlayerPipeHyperData
{
	GENERATED_BODY()
	/** The pipe we are currently traveling in */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Hyper Tube" )
	AActor* mTravelingPipeHyper;
	AActor* mTravelingPipeHyperLast;
	float mTravelingPipeHyperLastLength; //used for faster position calc if needed. If negative, it means we moved ot through it's start
	float mLastTransitTime = 0;

	/**The spline progress in the pipe we are currently in*/
	float mPipeProgressReal;
	/**The velocity we are currently traveling in along the spline of the pipe*/
	float mPipeVelocityReal;
	float mPipeCurrentLength;

	/**The spline progress in the pipe we are currently in*/
	float mPipeProgressLast;
	/**The velocity we are currently traveling in along the spline of the pipe*/
	float mPipeVelocityLast;

	float mTimeInterpreter;

	/**The spline progress in the pipe we are currently in */
	float mPipeProgress;

	/**The velocity we are currently traveling in along the spline of the pipe*/
	float mPipeVelocity;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mMinPipeSpeed = 300;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeGravityStrength = 1500.0f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeFriction = 0.05f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeConstantAcceleration = 110.0f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeCurveDamping = 0.4f;;

	/**World space direction of pipe last frame.*/
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	FVector mPipeDirectionLast;

	/**World space direction of pipe in current location.*/
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	FVector mPipeDirection;

	/**Distance to the end of the whole pipe chain, but maximum of 2000 (To save time on calculating it on update)*/
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	float mDistanceToEndOfPipe;
	
	/** maximum of 2000 (To save time on calculating it on update)*/
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	float mCombinedLengthTillEndOfPipesINcludingCurrent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	float mMaxCurveDiffThisFrame;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	float mMaxCurveDiffSmooth;


	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	float mPipeTempMinSpeed; //used so we can reduce even further due to curves, but not have the pipes too slow in upwards slopes


	/**World space position of the end of the pipe chain.. Only guaranteed to be accurate if the end is within 2000 units.*/
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	FVector mFulPipeEndPoint;
	/**World space direction of the end of the pipe chain.. Only guaranteed to be accurate if the end is within 2000 units.*/
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	FVector mFulPipeEndDir;

	FVector mSoftVelocity;
	FVector mCameraPush;
	float mCamFovMod;

public:
	FORCEINLINE ~FPlayerPipeHyperData() = default;
};


/**
 * Used for deferred collision state changes. Needed to make sure overlap updates don't happen mid logic steps and can cause recursive triggering of event calls.
 //[DavalliusA:Thu/27-02-2020] added when working on hyper tube bugs, as leaving one hyper tube and turning on collision in the movement mode change function could cause over movement mode changed functions to trigger.

 */
UENUM( BlueprintType )
enum class EDeferredCollisionChange : uint8
{
	DCC_None = 0		UMETA( DisplayName = "Do nothing" ),
	DCC_TURN_ON		UMETA( DisplayName = "Turn On Collision" ),
	DCC_TURN_OFF	UMETA( DisplayName = "Turn Off Collision" ),
};

/**
 * Custom states we can be in
 */
UENUM( BlueprintType )
enum class ECustomMovementMode : uint8
{
	CMM_None = 0		UMETA( DisplayName = "None" ),
	CMM_Ladder			UMETA( DisplayName = "Ladder" ),
	CMM_PipeHyper		UMETA( DisplayName = "Hyper Pipe" ),
};
inline bool operator==(const uint8 a, const ECustomMovementMode b)
{
	return a == (uint8 )b;
}

inline bool operator==(const ECustomMovementMode b , const uint8 a)
{
	return a == (uint8 )b;
}

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
	virtual void StartNewPhysics( float deltaTime, int32 Iterations ) override;
	virtual void SetDefaultMovementMode() override;
	virtual float GetMaxJumpZVelocity() const override;
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

	/** Get mBaseVelocity */
	UFUNCTION( BlueprintPure, Category = "Movement" )
	FORCEINLINE FVector GetBaseVelocity() const { return mBaseVelocity; }

	/** Set if the player wants to sprint or not */
	void SetWantsToSprint( bool wantsToSprint );

	/** Get mIsSliding */
	FORCEINLINE bool IsSliding() const { return mIsSliding; }

	/** Gets the accumulated impulse we want to apply */
	FORCEINLINE FVector GetPendingImpulseToApply(){ return PendingImpulseToApply; }

	/** Gets last slide time */
	FORCEINLINE float GetLastSlideTime() const{ return mLastSlideTime; }

	/** Gets last slide time */
	FORCEINLINE float GetBoostJumpTimeWindow() const { return mBoostJumpTimeWindow; }

	/** Setter for the chute */
	FORCEINLINE void SetCachedParachute( class AFGParachute* inParachute ) { mCachedParachute = inParachute; } 

	/** Setter for the chute */
	FORCEINLINE void SetCachedJumpingStilts( class AFGJumpingStilts* inJumpingStilts ) { mCachedJumpingStilts = inJumpingStilts; }

	//////////////////Ladder functions//////////////////
	bool CanGrabLadder( class UFGLadderComponent* ladder ) const;
	void StartClimbLadder( class UFGLadderComponent* ladder );
	void StopClimbLadder();
	bool IsClimbingOnLadder() const { return CustomMovementMode == (uint8 )ECustomMovementMode::CMM_Ladder; }
	void JumpOffLadder();

	/** @return The ladder we're climbing on; nullptr if not climbing. */
	UFUNCTION( BlueprintPure, Category = "Ladder" )
	class UFGLadderComponent* GetOnLadder() const;


	//////////////////Hyper Pipe Functions///////////////////////
	
	/** IsInHyperPipe
	 * @return	bool - returns true if we are currently moving in a hyper tube
	 */
	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	 bool IsInHyperPipe() const { return CustomMovementMode == (uint8 )ECustomMovementMode::CMM_PipeHyper; }

	/** EnterHyperPipe
	 * Enter a pipe and change movement mode to custom pipe movement. You can not enter pipes directly. You always need a part as an entracne. That is how it's designed atm. Only start parts as well. But we'll see how that changes.
	 * @param	pipe - the pipe start we want to enter
	 * @return	bool - returns true if we could enter.
	 */
	UFUNCTION( BlueprintCallable, Category = "Hyper Tube" )
	bool EnterPipeHyper( class AFGBuildablePipeHyperPart* pipe );

	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	FVector GetPipeTravelDirectionWorld();

	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	FRotator GetPipeCharacterTransform(FVector cameraForwardAxis);

	void PipeHyperForceExit();
	/** updates if the player wants to slide*/
	void UpdateWantsToSlide();

	/** Get mBoostJumpVelocityMultiplier */
	FORCEINLINE float GetBoostJumpVelocityMultiplier() const { return mBoostJumpVelocityMultiplier; }

	/** Checks if we still can slide */
	void UpdateSlideStatus();

	inline void SetPipeTempMinSpeed( float speed )
	{
		mPipeData.mPipeTempMinSpeed = speed;
	}
	bool SetTravelingPipeHyperActor( AActor* hyperPipeInterfaceActor );
	inline void SetPipeProgress( float distnace )
	{
		mPipeData.mPipeProgress = distnace;
	}
	inline void SetPipeVelocity( float speed )
	{
		mPipeData.mPipeVelocity = speed;
	}
	inline void SetGeneralVelocity( FVector vel)
	{
		Velocity = vel;
	}
	inline void SetPipeDirectionLast( FVector dir )
	{
		mPipeData.mPipeDirectionLast = dir;
	}
	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	inline float GetPipeVelocity() const{ return mPipeData.mPipeVelocity; }
	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	inline float GetPipeMinSpeed() const{ return mPipeData.mMinPipeSpeed; }
	inline float GetPipeTempMinSpeed() const{ return mPipeData.mPipeTempMinSpeed; }
	inline float GetPipeProgress() const{ return mPipeData.mPipeProgress; }
	inline float GetPipeConstantAcceleration() const{ return mPipeData.mPipeConstantAcceleration; }
	inline float GetPipeGravityStrength() const{ return mPipeData.mPipeGravityStrength; }
	inline float GetPipeCurveDamping() const{ return mPipeData.mPipeCurveDamping; }
	inline float GetPipeFriction() const{ return mPipeData.mPipeFriction; }
	inline FVector GetVelocity() const{ return Velocity; }
	inline FVector GetPipeDirectionLast() const{ return mPipeData.mPipeDirectionLast; }
	inline AActor* GetTravelingPipeHyperActor() const{ return mPipeData.mTravelingPipeHyper; }
	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	inline FPlayerPipeHyperData& GetPipeHyperDataRef() { return mPipeData; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Hyper Tube" )
	void OnNewTravelPipeSection();

	const USceneComponent* GetUpdateComponent() const;

protected:
	// Begin UCharacterMovementComponent
	virtual void UpdateFromCompressedFlags(uint8 flags) override;
	virtual void OnMovementUpdated(float deltaSeconds, const FVector & oldLocation, const FVector & oldVelocity) override;
	virtual void OnMovementModeChanged( EMovementMode PreviousMovementMode, uint8 PreviousCustomMode ) override;
	virtual void PhysCustom( float deltaTime, int32 Iterations ) override;

	void ExecuteDeferredCollisionChange();

		// End UCharacterMovementComponent

	void SetOnLadder( class UFGLadderComponent* ladder );

	virtual void PhysFlying( float deltaTime, int32 Iterations ) override;
private:
	/** Apply ladder climb physics */
	void PhysLadder( float deltaTime, int32 iterations );

	/** Apply Hyper Tube physics */
	void PhysPipe( float deltaTime, int32 iterations );


	/** Updates everything that has to do with JetPack */
	void UpdateJetPack( float deltaSeconds );

	/** Updates everything that has to do with Hookshot */
	void UpdateHookshot( float deltaSeconds, FVector oldLocation );

	/** Checks if we still can sprint */
	void UpdateSprintStatus();

	/** Updates everything that has to do with Parachute */
	void UpdateParachute( float delta );

	/** Updates everything that has to do with the jumping stilts */
	void UpdateJumpingStilts( float deltaSeconds );

	/** Returns true if the player is allowed to sprint */
	bool CanSprint() const;

	/** Returns true if the player can slide with current values */
	bool CanSlide() const;

	/** Returns true if the player is allowed to start a slide */
	bool CanStartSlide() const;

	/** Returns or finds the jet pack */
	class AFGJetPack* GetCachedJetPack();

	/** Returns or finds the cached hookshot */
	class AFGHookshot* GetCachedHookshot();

	/** Returns or finds the parachute */
	class AFGParachute* GetCachedParachute();

	/** Returns or finds the parachute */
	class AFGJumpingStilts* GetCachedJumpingStilts();

	/** Ticks the slide timer so we know for how long the slide has been ongoing */
	void TickSlide( float delta );
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

	/** True if the player wants to sprint */
	bool mWantsToSlide;

	/** Keeps is the player sprinting this update or not? */
	bool mIsSliding;

	/** Keep track of what status was for mIsSliding */
	bool mLastIsSliding; 

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

	UPROPERTY(EditAnywhere, meta = ( ShowOnlyInnerProperties ) )
	FPlayerPipeHyperData mPipeData;

	/** Get velocity from curve when sliding */
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	UCurveFloat* mSlideCurve;

	/** Gets the multiplier for slope velocity */
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	UCurveFloat* mSlopeCurve;

	/** How long have we been sliding */
	float mSlideTime;

	/** Max angle ( in radians ) for allowing to slide */
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	float mMaxSlideAngle;

	/** Velocity added from conveyor belts or other sources */
	FVector mAddedVelocity;

	/** Velocity for the actor without external influence like conveyor belts */
	UPROPERTY()
	FVector mBaseVelocity;

	/* Multiplier for boost jump for Z velocity */
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	float mBoostJumpZMultiplier;

	/* Multiplier for velocity in 2D when boost jumping */
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	float mBoostJumpVelocityMultiplier;

	/** Timestamp for when we ended the last slide */
	float mLastSlideTime;

	/* How long time after a slide a jump can be input and be counted as a boost jump*/
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	float mBoostJumpTimeWindow;

	EDeferredCollisionChange mDeferredCollisionAction = EDeferredCollisionChange::DCC_None;

	//Cheat
	public:
	bool mCheatIsPressingJump: 1;
	bool mCheatIsPressingCrouch : 1;
	bool mCheatGhost : 1;
	float CheatFlySpeedVertical;
	void ZeroOutFallVelocity();
	//end Cheat

public:
	FORCEINLINE ~UFGCharacterMovementComponent() = default;
};

class FACTORYGAME_API FSavedMove_FGMovement : public FSavedMove_Character
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

	uint8 mSavedIsSliding : 1;

	FVector mSavedHookLocation;

	float mPipeMoveProgress;
	float mPipeMoveVel;
	float mPipeMoveTime;
	AActor* mPipeMovePipe = nullptr;

public:
	FORCEINLINE ~FSavedMove_FGMovement() = default;
	FORCEINLINE FSavedMove_FGMovement() = default;
};

class FACTORYGAME_API FNetworkPredictionData_Client_FGMovement : public FNetworkPredictionData_Client_Character
{
public:
	FNetworkPredictionData_Client_FGMovement(const UCharacterMovementComponent& clientMovement);

	typedef FNetworkPredictionData_Client_Character Super;

	///@brief Allocates a new copy of our custom saved move
	virtual FSavedMovePtr AllocateNewMove() override;

public:
	FORCEINLINE ~FNetworkPredictionData_Client_FGMovement() = default;
};

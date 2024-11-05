// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/CharacterMovementComponent.h"
#include "Buildables/FGBuildablePipeHyperJunction.h"
#include "FGCharacterMovementComponent.generated.h"

class AFGParachute;
class AFGBuildablePipeHyperJunction;
class UFGPipeConnectionComponentBase;
struct FFGPipeHyperJunctionConnectionInfo;
struct FFGPipeHyperBasePipeData;

/** Info on the pending hypertube junction */
USTRUCT(BlueprintType)
struct FACTORYGAME_API FFGPendingHyperJunctionInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pipe Hyper")
	AFGBuildablePipeHyperJunction* mJunction = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pipe Hyper")
	UFGPipeConnectionComponentBase* mConnectionEnteredThrough = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pipe Hyper")
	float mDistanceToJunction = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hyper Tube")
	float mLastJunctionCheckDistance = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hyper Tube")
	TArray<FFGPipeHyperJunctionConnectionInfo> mAvailableOutputConnections;
};

/** A struct used as a wrapper for dynamically typed TStructOnScope<FFGPipeHyperBasePipeData> */
USTRUCT()
struct FACTORYGAME_API FFGPipeHyperDynamicPipeData
{
	GENERATED_BODY()
	using StructOnScopeType = TStructOnScope<FFGPipeHyperBasePipeData>;
private:
	StructOnScopeType Data;
public:
	FFGPipeHyperDynamicPipeData();
	FFGPipeHyperDynamicPipeData(const FFGPipeHyperDynamicPipeData& Other);
	FFGPipeHyperDynamicPipeData(FFGPipeHyperDynamicPipeData&& Other) noexcept;
	FFGPipeHyperDynamicPipeData( const StructOnScopeType& InStructOnScope );

	FFGPipeHyperDynamicPipeData& operator=(const FFGPipeHyperDynamicPipeData& Other);
	FFGPipeHyperDynamicPipeData& operator=(FFGPipeHyperDynamicPipeData&& Other) noexcept;
	
	bool Serialize(FArchive& Ar);
	void AddStructReferencedObjects(class FReferenceCollector& Collector);

	/** Convenient accessors with both const and non-const versions */
	FORCEINLINE StructOnScopeType& operator*() { return Data; }
	FORCEINLINE StructOnScopeType& operator->() { return Data; }
	FORCEINLINE const StructOnScopeType& operator*() const { return Data; }
	FORCEINLINE const StructOnScopeType& operator->() const { return Data; }
};

template<>
struct TStructOpsTypeTraits< FFGPipeHyperDynamicPipeData > : public TStructOpsTypeTraitsBase2< FFGPipeHyperDynamicPipeData >
{
	enum
	{
		WithAddStructReferencedObjects = true,
		WithSerializer = true
	};
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FPlayerPipeHyperData
{
	GENERATED_BODY()
	
	/** The pipe we are currently traveling in (real) */
	UPROPERTY()
	AActor* mTravelingPipeHyperReal;
	/** Pipe data associated with our travel in mTravelingPipeHyper */
	UPROPERTY()
	FFGPipeHyperDynamicPipeData mTravelingPipeHyperRealData;

	/** The pipe that we have been traveling during the last substep */
	UPROPERTY()
	AActor* mTravelingPipeHyperLast;
	/** Pipe data associated with our travel in mTravelingPipeHyperLast */
	UPROPERTY()
	FFGPipeHyperDynamicPipeData mTravelingPipeHyperLastData;
	/** True if we transitioned into the current pipe from the end of the previous pipe, used for interpolation. If false, we transitioned from the start */
	bool bTransitionedFromLastPipeHyperEnd;

	/**The spline progress in the pipe we are currently in*/
	float mPipeProgressReal;
	/**The velocity we are currently traveling in along the spline of the pipe*/
	float mPipeVelocityReal;
	FVector mPipeDirectionReal;
	float mPipeLengthReal;

	/**The spline progress in the pipe we are currently in*/
	float mPipeProgressLast;
	/**The velocity we are currently traveling in along the spline of the pipe*/
	float mPipeVelocityLast;
	FVector mPipeDirectionLast;
	float mPipeLengthLast;

	/** Accumulated delta time counter */
	float mTimeInterpreter;

	/** True if we have a pending eject on the next sub step of the movement simulation */
	bool bPendingEject;
	float mPendingEjectOffset;
	UPROPERTY()
	class UFGPipeConnectionComponentBase* mConnectionToEjectThrough;
	float mEjectTimeWorldSeconds;

	/** Total distance travelled to this point, unsigned and irrelevant of direction changes */
	float mTotalTravelDistanceReal;

	/** The pipe we are traveling in right now */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Hyper Tube" )
	AActor* mTravelingPipeHyper;
	/**The spline progress in the pipe we are currently in */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeProgress;
	/**The velocity we are currently traveling in along the spline of the pipe*/
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeVelocity;
	/** The forward direction of the pipe we are currently traveling */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Hyper Tube" )
	FVector mPipeDirection;
	UPROPERTY()
	FFGPipeHyperDynamicPipeData mTravelingPipeHyperData;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mMinPipeSpeed = 300;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeGravityStrength = 1500.0f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeFriction = 0.05f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeConstantAcceleration = 110.0f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeCurveDamping = 0.4f;

	/** The time for which curvature dumping will be applied at the very least after a very sharp turn. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeCurveDumpingTime = 0.05f;

	// @Nick: Changed this from 50 to 100 to hopefully fix the issues with people getting stuck inside of the poles at high velocity
	/** Offset in the connector direction to use when ejecting the player out of the hypertube */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeEjectOffset = 100.0f;

	/** Amount of time the player is immune to being sucked into the same entrance they just exited from */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mPipeEntranceImmunityTime = 0.5f;

	/** When the velocity is below this, player can manually control it's direction by input acceleration */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mMinManualControlVelocity = 3.0f;

	/** Maximum distance to search for junctions */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Hyper Tube" )
	float mMaxJunctionSearchDistance = 4000.0f;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	float mMaxCurveDiffThisFrame = 0.f;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	float mMaxCurveDiffTimeLeft = 0.0f;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Hyper Tube" )
	float mPipeTempMinSpeed = 0.f; //used so we can reduce even further due to curves, but not have the pipes too slow in upwards slopes

	FVector mSoftVelocity;
	FVector mCameraPush;
	float mCamFovMod;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FPlayerZiplineData
{
	GENERATED_BODY()

	/** Multiplier that controls speed based on angle of travel */
	UPROPERTY( BlueprintReadOnly, Category = "Zipline Data" )
	float SpeedMultiplier = 0.f;

	/* World direction we're headed */
	UPROPERTY( BlueprintReadOnly, Category = "Zipline Data" )
	FVector Direction = FVector::ZeroVector;
	
	FVector Point1 = FVector::ZeroVector;
	FVector Point2 = FVector::ZeroVector;

	/* Velocity applied last frame from zipline movement */
	FVector LastVelocityApplied = FVector::ZeroVector;
	
	FVector LastCorrectionVelocityApplied = FVector::ZeroVector;
	
	FVector ProjectedZiplineLocation = FVector::ZeroVector;
	
	UPROPERTY()
	AActor* AttachActor = nullptr;
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
	CMM_None = 0			UMETA( DisplayName = "None" ),
	CMM_Ladder				UMETA( DisplayName = "Ladder" ),
	CMM_PipeHyper			UMETA( DisplayName = "Hyper Pipe" ),
	CMM_Zipline				UMETA( DisplayName = "Zipline" ),
	CMM_Hover				UMETA( DisplayName = "Hover" ),
	CMM_HoverSlowFall		UMETA( DisplayName = "Hover Slow Fall" ),
	CMM_Parachute			UMETA( DisplayName = "Parachute" ),
	CMM_Cinematic			UMETA( DisplayName = "Cinematic (Root Motion/Intro Sequence)" )
};
inline bool operator==(const uint8 a, const ECustomMovementMode b)
{
	return a == static_cast<uint8>( b );
}

inline bool operator==(const ECustomMovementMode b , const uint8 a)
{
	return a == static_cast<uint8>( b );
}

UCLASS()
class FACTORYGAME_API UFGCharacterMovementComponent final : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UFGCharacterMovementComponent();
	
	// Begin UActorComponent
	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction ) override;
	// End UActorComponent

	// Begin UCharacterMovementComponent
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	virtual bool DoJump( bool isReplayingMoves ) override;
	virtual void CalcVelocity( float dt, float friction, bool isFluid, float brakingDeceleration ) override;
	virtual float GetMaxSpeed() const override;
	virtual void StartNewPhysics( float deltaTime, int32 Iterations ) override;
	virtual void SetDefaultMovementMode() override;
	virtual float GetMaxJumpZVelocity() const override;
	virtual bool CanCrouchInCurrentState() const override;
	virtual void SmoothClientPosition( float DeltaSeconds ) override;
	virtual void SmoothCorrection(const FVector& OldLocation, const FQuat& OldRotation, const FVector& NewLocation, const FQuat& NewRotation) override;
	virtual float ImmersionDepth() const override;
	virtual float BoostAirControl(float DeltaTime, float TickAirControl, const FVector& FallAcceleration) override;
	virtual FRotator ComputeOrientToMovementRotation(const FRotator& CurrentRotation, float DeltaTime, FRotator& DeltaRotation) const override;
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

	/** Toggles mWantsToSprint and sets mHoldToSprint to true. */
	void ToggleWantsToSprintAndSetAutoRelease( bool holdToSprint, bool autoReleaseSprint );
	
	/** Get mBaseVelocity */
	UFUNCTION( BlueprintPure, Category = "Movement" )
	FORCEINLINE FVector GetBaseVelocity() const { return mBaseVelocity; }

	/** Set if the player wants to sprint or not */
	void SetWantsToSprintAndHoldSprint( bool wantsToSprint, bool holdToSprint, bool autoReleaseSprint );

	/** Get mIsSliding */
	FORCEINLINE bool IsSliding() const { return mIsSliding; }

	/** Gets the accumulated impulse we want to apply */
	FORCEINLINE FVector GetPendingImpulseToApply() const { return PendingImpulseToApply; }

	/** Gets last slide time */
	FORCEINLINE float GetLastSlideTime() const{ return mLastSlideTime; }

	/** Gets last slide time */
	FORCEINLINE float GetBoostJumpTimeWindow() const { return mBoostJumpTimeWindow; }

	/** Setter for the chute */
	FORCEINLINE void SetCachedJumpingStilts( class AFGJumpingStilts* inJumpingStilts ) { mCachedJumpingStilts = inJumpingStilts; }

	//////////////////Ladder functions//////////////////
	bool CanGrabLadder( const class UFGLadderComponent* ladder ) const;
	void StartClimbLadder( class UFGLadderComponent* ladder );
	void StopClimbLadder();
	bool IsClimbingOnLadder() const { return CustomMovementMode == static_cast<uint8>(ECustomMovementMode::CMM_Ladder); }
	void JumpOffLadder();

	/** @return The ladder we're climbing on; nullptr if not climbing. */
	UFUNCTION( BlueprintPure, Category = "Ladder" )
	class UFGLadderComponent* GetOnLadder() const;
	
	/** IsInHyperPipe
	 * @return	bool - returns true if we are currently moving in a hyper tube
	 */
	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	bool IsInHyperPipe() const { return CustomMovementMode == static_cast<uint8>(ECustomMovementMode::CMM_PipeHyper); }

	/** IsOnZipline
	* @return	bool - returns true if we are currently moving on a zipline
	*/
	UFUNCTION( BlueprintPure, Category = "Zipline" )
    bool IsOnZipline() const { return CustomMovementMode == static_cast<uint8>(ECustomMovementMode::CMM_Zipline); }

	/** @return true if the player is currently parachuting */
	UFUNCTION( BlueprintPure, Category = "Parachute" )
	bool IsParachuting() const { return CustomMovementMode == static_cast<uint8>(ECustomMovementMode::CMM_Parachute); }

	/** EnterHyperPipe
	 * Enter a pipe and change movement mode to custom pipe movement. You can not enter pipes directly. You always need a part as an entrance. That is how it's designed atm. Only start parts as well. But we'll see how that changes.
	 * @param	pipe - the pipe start we want to enter
	 * @return	bool - returns true if we could enter.
	 */
	UFUNCTION( BlueprintCallable, Category = "Hyper Tube" )
	bool EnterPipeHyper( class AFGPipeHyperStart* pipe );
	
	bool EnterPipeHyperDirect( UFGPipeConnectionComponentBase* connectionEnteredThrough, const float InitialMinSpeedFactor = 1.0f );

	/** Internal version of EnterPipeHyper, used for sync */
	bool EnterPipeHyperInternal( UFGPipeConnectionComponentBase* connectionEnteredThrough, const float initialPipeVelocity, const float initialPipeProgress, const float accumulatedDeltaTime );

	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	FVector GetPipeTravelDirectionWorld() const;

	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	FRotator GetPipeCharacterTransform(const FVector& cameraForwardAxis) const;

	void PipeHyperForceExit( const bool bRagdollCharacter = true);
	/** updates if the player wants to slide*/
	bool WantsToSlide() const;

	/** Get mBoostJumpVelocityMultiplier */
	FORCEINLINE float GetBoostJumpVelocityMultiplier() const { return mBoostJumpVelocityMultiplier; }

	/** Checks if we still can slide */
	void UpdateSlideStatus();

	// Use this to attempt to climb over an obstacle in front of the player
	bool AttemptLedgeClimb();

	UFUNCTION()
	void OnLedgeClimbFinished();

	/** Update loop for if we are zip lining */
	void UpdateZiplineEffects() const;
	
	inline void SetGeneralVelocity( const FVector& velocity )
	{
		Velocity = velocity;
	}

	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	inline float GetPipeVelocity() const{ return mPipeData.mPipeVelocity; }

	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	inline float GetPipeMinSpeed() const{ return mPipeData.mMinPipeSpeed; }

	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	inline float GetTotalTravelDistanceReal() const { return mPipeData.mTotalTravelDistanceReal; }

	inline float GetPipeTempMinSpeed() const{ return mPipeData.mPipeTempMinSpeed; }
	inline float GetPipeProgress() const{ return mPipeData.mPipeProgress; }
	inline float GetPipeConstantAcceleration() const{ return mPipeData.mPipeConstantAcceleration; }
	inline float GetPipeGravityStrength() const{ return mPipeData.mPipeGravityStrength; }
	inline float GetPipeCurveDamping() const{ return mPipeData.mPipeCurveDamping; }
	inline float GetPipeFriction() const{ return mPipeData.mPipeFriction; }
 	inline FVector GetVelocity() const{ return Velocity; }
	inline FVector GetPipeDirectionLast() const{ return mPipeData.mPipeDirectionLast; }
	inline AActor* GetTravelingPipeHyperActor() const{ return mPipeData.mTravelingPipeHyper; }
	inline AActor* GetTravelingPipeHyperActorReal() const { return mPipeData.mTravelingPipeHyperReal; }

	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	inline FPlayerPipeHyperData& GetPipeHyperDataRef() { return mPipeData; }

	/** The next junction we have when traveling a hyper tube */
	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	FORCEINLINE FFGPendingHyperJunctionInfo GetPendingHyperJunction() const { return mPendingHyperJunction; };

	/** Updates the mPendingJunctionInfo if inside of the hypertube, otherwise invalidates it */
	void UpdatePendingJunctionInfo();

	const USceneComponent* GetUpdateComponent() const;

	void SetZiplineData( const FPlayerZiplineData &inData ) { mZiplineData = inData; }

	UFUNCTION( BlueprintPure, Category = "Zipline" )
	FORCEINLINE FPlayerZiplineData& GetZiplineDataRef() { return mZiplineData; }
	
	UFUNCTION( BlueprintPure, Category = "Zipline" )
	const FVector& GetZipLineDirection() const { return mZiplineData.Direction; }
	
	UFUNCTION( BlueprintPure, Category = "Zipline" )
	const float& GetZipLineSpeedMultiplier() const { return mZiplineData.SpeedMultiplier; }
	
	bool IsZiplineAttachActorValid() const { return IsValid( mZiplineData.AttachActor ); }
	
	UFUNCTION( BlueprintPure, Category = "Zipline" )
	float GetZiplineSpeed() const;

	void StopZiplineMovement( const FVector& exitForce = FVector::ZeroVector );

	void StartZiplineMovement( AActor* ziplineActor, const FVector& point1, const FVector& point2, const FVector& actorForward );
	
protected:
	// Begin UCharacterMovementComponent
	virtual void UpdateFromCompressedFlags(uint8 flags) override;
	virtual void OnMovementUpdated(float deltaSeconds, const FVector & oldLocation, const FVector & oldVelocity) override;
	virtual void OnMovementModeChanged( EMovementMode PreviousMovementMode, uint8 PreviousCustomMode ) override;
	virtual void PhysCustom( float deltaTime, int32 Iterations ) override;
#if WITH_EDITOR
	virtual bool MoveUpdatedComponentImpl(const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult* OutHit, ETeleportType Teleport) override;
#endif
	void ExecuteDeferredCollisionChange();
	// End UCharacterMovementComponent

	void SetOnLadder( class UFGLadderComponent* ladder );
	
	virtual void PhysFlying( float deltaTime, int32 iterations ) override;

	UFUNCTION( Reliable, Server )
	void Server_LandSafelyFromFlyingState( AFGCharacterPlayer* characterPlayer );
	
	void LandSafelyFromFlyingState( AFGCharacterPlayer* characterPlayer );
	
private:
	/** Apply ladder climb physics */
	void PhysLadder( const float deltaTime, int32 iterations );

	/** Apply Hyper Tube physics */
	void PhysPipe( const float deltaTime );

	/** Apply Zipline physics */
	void PhysZipline( const float deltaTime );

	/** Apply Hover physics */
	void PhysHover( const float deltaTime );

	/** Apply parachute physics */
	void PhysParachute( const float deltaTime, int32 iterations );

	/** Applies cinematic root motion physics, and nothing else */
	void PhysCinematic( const float deltaTime, int32 iterations );

	/** Updates everything that has to do with JetPack */
	void UpdateJetPack( float deltaSeconds );

	/** Updates everything that has to do with Hookshot */
	void UpdateHookshot( const float deltaSeconds, const FVector& oldLocation );

	/** Checks if we still can sprint */
	void UpdateSprintStatus();
	
	/** Returns true if the player is allowed to sprint */
	bool CanSprint() const;

	/** Returns true if the player can slide with current values */
	bool CanSlide() const;

	/** Returns true if the player is allowed to start a slide */
	bool CanStartSlide() const;

	/** Returns or finds the jet pack */
	class AFGJetPack* GetCachedJetPack();

	/** Returns or finds the cached Hookshot */
	class AFGHookshot* GetCachedHookshot();

	/** Returns or finds the jumping stilts */
	class AFGJumpingStilts* GetCachedJumpingStilts();

	/** Returns or finds the Hoverpack */
	class AFGHoverPack* GetCachedHoverPack();
	
	/** Ticks the slide timer so we know for how long the slide has been ongoing */
	void TickSlide( const float delta );

	/** Used by AttemptLedgeClimb in order to move the character up over a duration. */
	bool StartLedgeClimb( const float duration, const float speed );

	/** Used to stop ledge climbing. */
	void StopLedgeClimb( const bool interrupt );

	/** Attempts to find and enter the closest hypertube at the provided location. Used for movement replication on simulated proxies */
	AActor* FindClosestPipeHyper( const FVector& worldLocation, const FVector& velocity, float& out_distanceAlongSpline, TStructOnScope<FFGPipeHyperBasePipeData>& out_pipeData ) const;
	
	/** Updates the hypertube movement data based on the movement information received as a part of network correction or smoothing */
	void UpdatePipeMovementDataFromCorrectionResult( const FVector& newLocation, const FVector& newVelocity );
public:
	/** Timestamp of last time we jumped */
	UPROPERTY( BlueprintReadOnly, Category = "Jump" )
	float mLastJumpTimeStamp;
	
	/** The speed at which a character climbs ladders */
	UPROPERTY( BlueprintReadOnly, Category = "Sprint" )
	float mClimbSpeed;

	/** The speed at witch a character sprints */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Sprint" )//ReadWrite is only to enable blueprint prototyping of shit.
	float mMaxSprintSpeed;
	
	/** True if the player wants to sprint. */
	bool mWantsToSprint;

	/** True if the player wants to sprint while on Zipline. */
	bool mWantsToSprintOnZipline;
	
	/** Keeps is the player sprinting this update or not? */
	bool mIsSliding;

	/** Keep track of what status was for mIsSliding */
	bool mLastIsSliding; 

	/** True if the player is pressing jump */
	bool mIsPressingJump;

	/** The minimum dot value between velocity and character forward to allow sprint.*/
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Sprint" )
	float mSprintMinDotResult;

	/** Force to apply when jumping off a ladder. */
	UPROPERTY( EditDefaultsOnly, Category = "Ladder" )
	float mJumpOffLadderVelocity;

	/** Cached Reference to the Owning FGPlayerCharacter */
	UPROPERTY()
	class AFGCharacterPlayer* mFGCharacterOwner;

	UPROPERTY( VisibleInstanceOnly, Category = "Movement|Parachute" )
	class UFGParachuteSettings* mParachuteSettings;
private:
	friend class FSavedMove_FGMovement;

	/** Keeps is the player sprinting this update or not? */
	bool mIsSprinting;

	/** Holds if sprint toggle is on from FGCharacterPlayer. Updates every time SetWantsToSprint() is called.*/
	bool mHoldToSprint;
	/** True if sprint button should be auto released when the character stops moving */
	bool mAutoReleaseSprint;
	
	/** A cached instance of the equipment that issued jet pack thrust */
	UPROPERTY()
	class AFGJetPack* mCachedJetPack;

	/** A cached instance of the equipment that set our hookshot location */
	UPROPERTY()
	class AFGHookshot* mCachedHookshot;

	/** A cached instance of the equipment that set our jumping stilts */
	UPROPERTY()
	class AFGJumpingStilts* mCachedJumpingStilts;

	/** A cached instance of the equipment that set our hover pack */
	UPROPERTY()
	class AFGHoverPack* mCachedHoverPack;

	/** A cached instance of rail we're surfing with the hoverpack */
	UPROPERTY()
	class AFGBuildableRailroadTrack* mCachedSurfedRailroadTrack;

	/** The location that our hook sits at */
	FVector mHookLocation;

	/** The ladder we're climbing; null if not climbing. */
	UPROPERTY()
	UFGLadderComponent* mOnLadder;

	UPROPERTY(EditAnywhere, meta = ( ShowOnlyInnerProperties ) )
	FPlayerPipeHyperData mPipeData;

	UPROPERTY()
	FFGPendingHyperJunctionInfo mPendingHyperJunction;

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
	
	// TODO: PROTOTYPE
	/** Whether or not to enabled the vault / ledge climb prototype. */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Vault" )
	bool mEnableVaultPrototype;
	
	/** How far forward we should sweep to check if vaulting is possible. */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Vault" )
	float mVaultSweepDistance;

	/** How high something can be for us to vault over it. */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Vault" )
	float mVaultHeightThreshold;

	/** How much forward velocity to add when vaulting. */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Vault" )
	float mVaultForwardVelocity;

	/** How much vertical velocity to add when vaulting. */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Vault" )
	float mVaultVerticalVelocity;

	/** How high something can be for us to ledge climb over it, should be higher than vault height limit. */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Vault" )
	float mLedgeClimbHeightThreshold;

	FTimerHandle mLedgeClimbTimerHandle;

	float mCurrentLedgeClimbingSpeed;
	
	bool mIsLedgeClimbing;
	bool mIsVaulting;

	EDeferredCollisionChange mDeferredCollisionAction = EDeferredCollisionChange::DCC_None;

	UPROPERTY( EditAnywhere, meta = ( ShowOnlyInnerProperties ) )
    FPlayerZiplineData mZiplineData;
	
	/* Base speed for moving straight on zipline */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Zipline" )
	float mZiplineSpeed;

	/* Sprint speed for moving straight on zipline */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Zipline" )
	float mZiplineSprintSpeed;
	
	/* The speed of which the character corrects its position when zip lining. */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Zipline" )
	float mZiplineCorrectionSpeedMultiplier;

	/* How fast we interpolate to max speed when zip lining. */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Zipline" )
	float mZiplineVelocityInterpolationSpeed;

	/* How fast we interpolate to max speed when zip lining while sprinting. */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Zipline" )
	float mZiplineVelocityInterpolationSprintSpeed;
	
	/* Speed multiplier used when going upwards on zipline */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Zipline" )
	float mZiplineSpeedMultiplierUp;

	/* Speed multiplier used when going downwards on zipline */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Zipline" )
	float mZiplineSpeedMultiplierDown;

	/* When sprinting on zipline we use the normal interpolation speed until we reach this percentage of the normal zipline velocity. */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Zipline", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f ))
	float mZiplineSprintSettingsCutoff;

	/* When hitting the end of a zipline, this is the maximum allowed angle of the new wire we keep ziplining on. (Degrees) */
	UPROPERTY( EditDefaultsOnly, Category = "Movement|Zipline", meta=(ClampMin=0.0f, ClampMax=180.0f, UIMin=0.0f, UIMax=180.0f ) )
	float mZiplineContinuousTravelMaxAngle;

	/* Vertical speed when flying. */
	UPROPERTY( EditDefaultsOnly, Category = "Character Movement: Flying" )
	float mVerticalFlyingSpeed;

	/* Vertical speed when flying and sprinting. */
	UPROPERTY( EditDefaultsOnly, Category = "Character Movement: Flying" )
	float mVerticalFlyingSprintSpeed;

	/* Speed when flying and sprinting. */
	UPROPERTY( EditDefaultsOnly, Category = "Character Movement: Flying" )
	float mMaxFlySprintSpeed;
	
	//Cheat
	public:
	bool mCheatGhost : 1;
	//end Cheat
};

class FSavedMove_FGMovement final : public FSavedMove_Character
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

	uint8 mSavedIsPressingJump : 1;

	uint8 mSavedWantsToSprintOnZipline : 1;
	
	FVector mSavedHookLocation;

	TSoftObjectPtr<UFGParachuteSettings> mParachuteSettings;

	// TODO @Nick: We should probably remember pipe data here to make sure the player takes the same junction path if their movement is rolled back, but this is not important enough right now to look into
};

class FNetworkPredictionData_Client_FGMovement final : public FNetworkPredictionData_Client_Character
{
public:
	explicit FNetworkPredictionData_Client_FGMovement(const UCharacterMovementComponent& clientMovement);

	typedef FNetworkPredictionData_Client_Character Super;

	///@brief Allocates a new copy of our custom saved move
	virtual FSavedMovePtr AllocateNewMove() override;
};

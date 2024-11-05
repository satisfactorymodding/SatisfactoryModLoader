// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimationTypes.h"
#include "FGCharacterAnimInstance.h"
#include "FGAnimPlayer.generated.h"

enum class ECustomMovementMode : uint8;
/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAnimPlayer : public UFGCharacterAnimInstance
{
	GENERATED_BODY()
public:	
	/** Caching stuff */
	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;
	virtual void NativeUninitializeAnimation() override;
	/** Sets value for arm slot */
	void CacheArmSlotData();

	/** Executed when the Animation is uninitialized */
	UFUNCTION(BlueprintImplementableEvent)
    void BlueprintUninitializeAnimation();
	
	/** Sets value for back slot */
	void CacheBackSlotData();
private:
	/* Begin AFGCharacterAnimInstance*/
	virtual FVector GetCharacterVelocity() const override;
	/* End AFGCharacterAnimInstance*/
public: 
	/** Is first or third person mesh? */
	UPROPERTY( EditDefaultsOnly, Category = "Anim Player" )
	bool mIsFirstPerson; 

	/** Saved value of arm equipment */
	UPROPERTY( BlueprintReadOnly, Category = "Anim Player" )
	EArmEquipment mArmSlotType; 

	/** Saved value of back equipment */
	UPROPERTY( BlueprintReadOnly, Category = "Anim Player" )
	EBackEquipment mBacklotType;

	/** Character this anim belongs to */
	UPROPERTY( BlueprintReadOnly, Category = "Anim Player" )
	class AFGCharacterPlayer* mCharacter;

	/** is this character not controlled by anyone */
	UPROPERTY( BlueprintReadOnly, Category = "Anim Player" )
	bool mIsIdling;
};


/* Specialized 1p native class.*/
UCLASS()
class FACTORYGAME_API UFGAnimPlayer1p : public UFGAnimPlayer
{
	GENERATED_BODY()
	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	USkeletalMeshComponent* mSkeletalmeshComponent;
	
	UPROPERTY(BlueprintReadOnly)
	bool mIsPlayerSlidingCached;
	
	UPROPERTY(BlueprintReadOnly)
	bool mIsPlayerCrouchedCached;

	UPROPERTY(BlueprintReadOnly)
	FVector mPlayerArmTranslationCached;

	UPROPERTY(BlueprintReadOnly)
	FRotator mPlayerSlideFloorAngle;
	
	UPROPERTY(BlueprintReadOnly)
	bool mIsPlayingAnyMontagesCached;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	bool mChainsawHasFuelCached;
	
	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	bool mHasNobeliskAmmo;
	
	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	bool mIsJetpackThrustingCached;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	bool mIsParachuteDeployed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool mStandingStill;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	TEnumAsByte< EMovementMode > mMovementMode;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	ECustomMovementMode mCustomMovementMode;

	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	float mAimPitchLag;

	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	float mAimYawLag;

	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	FRotator mAimRotation;

	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	FRotator mAimRotationDelta;
	
	UPROPERTY(BlueprintReadOnly, Category = "Aim")
	FRotator mAimRotationLastTick;

	UPROPERTY(BlueprintReadOnly, Category = "ChangeStop")
	float mDesiredDirection;

	UPROPERTY(BlueprintReadOnly, Category = "ChangeStop")
	float mChangeDirectionAngle;

	UPROPERTY(BlueprintReadOnly, Category = "ChangeStop")
	FVector mVelocityLocalNormalizedLastTick;

	// Read write since its managed by as anim notify.
	UPROPERTY(BlueprintReadWrite, Category = "ChangeStop")
	float mStopDirection;

	UPROPERTY(BlueprintReadOnly)
	bool mStandingStillLastTick;

	UPROPERTY(BlueprintReadOnly)
	float mSpeedLastTick;

	// Read write since its managed by as anim notify.
	UPROPERTY(BlueprintReadWrite)
	FVector mStandingStillLocation;

	// Read write since its managed by as anim notify.
	UPROPERTY(BlueprintReadWrite)
	bool mPlayDirectionChange;

	// Read write since its managed by as anim notify.
	UPROPERTY(BlueprintReadWrite)
	bool mPlayStop;

	UPROPERTY(BlueprintReadOnly)
	float mStandingStillLeanDirection;

	UPROPERTY(BlueprintReadOnly)
	float mStandingStillLeanDistance;

	UPROPERTY(BlueprintReadOnly)
	bool mPlayStopLean;

	UPROPERTY(BlueprintReadOnly)
	float mStandingStillStopDirection;

	UPROPERTY(BlueprintReadOnly)
	float mIKFootLOffset;

	UPROPERTY(BlueprintReadOnly)
	FRotator mIKFootLRotationOffset;

	UPROPERTY(BlueprintReadOnly)
	float mIKFootROffset;

	UPROPERTY(BlueprintReadOnly)
	FRotator mIKFootRRotationOffset;

	UPROPERTY(BlueprintReadOnly)
	UAnimSequence* mEquipmentIdlePose;

	// Ladder
	UPROPERTY(BlueprintReadOnly)
	float m1pLadderMeshRotation;

	UPROPERTY(BlueprintReadOnly)
	float m1pLadderLookYaw;

	// Zipline
	UPROPERTY(BlueprintReadOnly)
	float m1pZiplineAimYaw;

	UPROPERTY(BlueprintReadOnly)
	FRotator m1pZiplineAimPitchRotator;

	// Hoverpack.
	UPROPERTY(BlueprintReadOnly)
	FRotator m1pHoverPackAimPitch;
	
	UPROPERTY(BlueprintReadOnly)
	float m1pHoverPackAimPitchYawLag;

	UPROPERTY(BlueprintReadOnly)
	FRotator m1pHoverPackAimRotation;

	UPROPERTY(BlueprintReadOnly)
	FRotator m1pHoverPackAimRotationDelta;

	UPROPERTY(BlueprintReadOnly)
	FRotator m1pHoverPackRotationLastTick;
	
	// For fast path.
	UPROPERTY(BlueprintReadOnly)
	float mAG_StandingStillLeanDistanceAlpha;
	
	UPROPERTY(BlueprintReadOnly)
	float mAG_InvertedAimPitch;
	
	UPROPERTY(BlueprintReadOnly)
	float mAG_SlidePlayRate;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_HasNoAcceleration;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_RunToSprintTransition;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_RunToChangeDirectionTransition;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_SprintToRunTransition;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_IsJumping;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_IsFalling;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_IdleToRunTransition;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_IsSwimming;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_TurnInPlaceArms;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_JumpLoopToFallingTransition;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_FallingToJumpLoopTransition;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_UseArmBaseRotation;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_UseFootIK;
	
	UPROPERTY(BlueprintReadOnly)
	bool AG_UseHandIK;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_NothingEquipped;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_SwimToIdle;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_SprintToRun_02;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_RunToSprint_02;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_HasPositiveVectorLength;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_IsWalking;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_IsOnLadder;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_MovingOnLadder;
	
	UPROPERTY(BlueprintReadOnly)
	bool mAG_NoAOBlend;

	UPROPERTY(BlueprintReadOnly)
	FRotator mAG_CrouchArmRotator;
	
	UPROPERTY(BlueprintReadOnly)
	FRotator mAG_InvertedAimYawRotator;
	
	UPROPERTY(BlueprintReadOnly)
	FRotator mAG_InvertedAimPitchRotator;
	
	UPROPERTY(BlueprintReadOnly)
	FRotator mAG_AimPitchRotatorParachute;
	
	UPROPERTY(BlueprintReadOnly)
	FRotator mAG_AimPitchRotatorSwimClamped;

	UPROPERTY(BlueprintReadOnly)
	FVector mAG_MinIkFootOffsetVector;

	UPROPERTY(BlueprintReadOnly)
	FVector mAG_IkFootLOffsetVector;

	UPROPERTY(BlueprintReadOnly)
	FVector mAG_IkFootROffsetVector;

	UPROPERTY(BlueprintReadOnly)
	FRotator m1pLadderAimPitch;
	
	UPROPERTY(BlueprintReadOnly)
	FRotator m1pLadderMeshRotator;

	UPROPERTY(BlueprintReadOnly)
	bool m1pLadderIsClimbing;
};

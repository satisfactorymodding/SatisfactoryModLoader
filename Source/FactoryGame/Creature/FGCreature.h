// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "../FGCharacterBase.h"
#include "../FGUseableInterface.h"
#include "FGCreature.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FRotationDoneDelegate, APawn*, PawnRotated );

// @todo: We should probably change this to EUndefinedBool
UENUM()
enum EEnabled
{
	E_Enabled,
	E_Disabled,
	E_Unknown
};

UENUM( BlueprintType )
enum class EMoveSpeed :uint8
{
	MS_Undefined,
	MS_Walk			UMETA( DisplayName = "Slow speed" ),
	MS_Run			UMETA( DisplayName = "Normal" ),
	MS_Sprint		UMETA( DisplayName = "Extra fast" )
};

USTRUCT( BlueprintType ) 
struct FMoveSpeedPair
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	EMoveSpeed MoveSpeedType; 

	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	float Speed;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGCreature : public AFGCharacterBase
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** ctor */
	AFGCreature( const FObjectInitializer& ObjectInitializer );

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;
	virtual void Tick( float deltaTime ) override;
	// End AActor Interface

	// Begin FGCharacterBase
	virtual void Died( AActor* died ) override;
	// End FGCharacterBase

	/** @return	Pawn's eye location */
	virtual FVector GetPawnViewLocation() const;

	/** Gets the spline we are set to follow */
	UFUNCTION( BlueprintPure, Category = "Creature" )
	FORCEINLINE class AFGSplinePath* GetSplinePath() { return mSpline; }

	/** Getter for spawn variables */
	FORCEINLINE bool CanSpawnDuringDay() { return mCanSpawnDuringDay; }
	FORCEINLINE bool CanSpawnDuringNight() { return mCanSpawnDuringNight; }

	/** Gets the spline we are set to follow */
	UFUNCTION( BlueprintPure, Category = "Creature" )
	FORCEINLINE bool GetIsEnabled() { return mIsEnabled == E_Enabled ? true : false; }

	/** Indicates if we are persistent ( not removed after a distance specified in AISystem )  */
	UFUNCTION( BlueprintPure, Category = "Creature" )
	FORCEINLINE bool IsPersistent() { return mIsPersistent; }

	/** Sets if we should persist or not */
	UFUNCTION( BlueprintCallable, Category = "Creature" )
	void SetPersistent( bool persist ) { mIsPersistent = persist; }

	/** Starts the rotation movement */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Movement" )
	void StartRotationMovement( FRotator targetRotation );

	/** Cancels the rotation movement */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Movement" )
	void CancelRotationMovement();

	/**Gets the target rotation */
	UFUNCTION( BlueprintPure, Category = "Movement" )
	FORCEINLINE FRotator GetTargetRotation() { return mTargetRotation; }

	/** Is this creature an arachnid? */
	UFUNCTION( BlueprintPure, Category = "Arachnophobia" )
	FORCEINLINE bool GetIsArachnid() { return mIsArachnid; }

	/** Gets the array of sprites that may be used for arachnophobia mode */
	UFUNCTION( BlueprintPure, Category = "Arachnophobia" )
	FORCEINLINE TArray< UMaterialInstance* > GetArachnophobiaModeMaterials() { return mArachnophobiaModeMaterials; }

	/** Sets up the Arachnophobia mode */
	UFUNCTION( BlueprintNativeEvent, Category = "Arachnophobia" )
	void ConfigureArachnophobiaMode( bool isArachnophobiaMode );

	/** How much of day time percentage ( 0.0 - 1.0 ) should count towards night time  */
	UFUNCTION( BlueprintPure, Category = "Spawning" )
	FORCEINLINE float GetDayTimePctAsNight( ) { return mDayTimePctCountAsNight; }

	/** Called when the Arachnophobia mode setting is changed */
	UFUNCTION()
	void OnArachnophobiaModeChanged( bool isArachnophobiaMode );

	/** Checks when we are done rotating and calls the complete delegate */
	UFUNCTION()
	void CheckRotationMovement();

	/** Notify when creature consumes a item*/
	UFUNCTION( NetMulticast, BlueprintCallable, Unreliable, Category = "Consume" )
	void Multicast_ConsumeItem( TSubclassOf< class UFGItemDescriptor > itemDescriptor, int32 amount = 1 );

	/** Play effects when creature consumes a item*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Consume" )
	void PlayConsumeItemEffect( TSubclassOf< class UFGItemDescriptor > itemDescriptor, int32 amount );

	/** Updates the movement speed ( server side ) */
	UFUNCTION( BlueprintCallable, Category = "Movement" )
	void SetMoveSpeed( EMoveSpeed newMoveSpeedType );

	/* * Calculate a trajectory to lead a target with a set interceptor speed (aka, bullet speed/charge speed), finding the earliest interception if multiple are possible
	@targetPos Position of the target you are trying to intercept
	@targetVelocity The movement velocity of the target you are truing to intercept
	@fromPos The interceptors current position (aka the shooters position)
	@interceptorSpeed the speed of the interception (aka, bullet speed/charge speed)
	@isPosibleToLead indicated if the lead is possible (if you are moving too slow and your target is moving away, the lead might be impossible)
	@leadScaling If set to 1, the lead will get an exact interception. If above 1 it will move a bit in front of the target, and below one it will come up a bit short. 0 = no lead, and all these calculations will be a waste, probably a lead of under 0.5 will also be a toooootal waste unless the target is likely to turn/slow down, but that should instead be reprecented in the velocity)
	
	@InterceptPoint Position of interception if possible, otherwise an approximate logical position is set, so it looks like it at least tries to predict/hit*/
	UFUNCTION( BlueprintPure, Category = "AI" )
	static void AiCalculateLeadTrajectory( const FVector& targetPos, const FVector& targetVelocity, const FVector& fromPos, float interceptorSpeed, bool &isPosibleToLead , FVector& interceptPoint, float leadScaling = 1.0f);


	/** Called when creature died to spawn death item */
	UFUNCTION( BlueprintNativeEvent, Category = "Creature" )
	void SpawnDeathItem();
private:
	UFUNCTION()
	void OnRep_TargetRotation();

protected:
	// We want the AI system to be able to optimize our actor without exposing that functionality
	friend class UFGAISystem;

	UFUNCTION()
	void OnRep_IsEnabled();

	/** Set our enabled state */
	void SetEnabled( EEnabled enabled );
protected:
	/** How big navmesh do we want to generate */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mNavigationGenerationRadius;

	/** Navigation outside this radius will be removed */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mNavigationRemovalRadius;

	/** Materials that may be used on arachnids */
	UPROPERTY( EditDefaultsOnly, Category = "Arachnophobia" )
	TArray< UMaterialInstance* > mArachnophobiaModeMaterials;

	/** Is creature considered an arachnid */
	UPROPERTY( EditDefaultsOnly, Category = "Arachnophobia" )
	bool mIsArachnid;

	/** True if optimized by the AI system */
	UPROPERTY( ReplicatedUsing = OnRep_IsEnabled )
	TEnumAsByte< EEnabled > mIsEnabled;

	/** Class of item to drop when dead */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	TSubclassOf< class AFGItemPickup > mItemToDrop;
public:
	/** Spline we are set to follow */
	UPROPERTY( SaveGame, EditInstanceOnly, Category = "Creature" )
	class AFGSplinePath* mSpline;

	/** Called when we are done with rotation movement */
	UPROPERTY( BlueprintAssignable, Category = "Movement", DisplayName = "OnRotationDone" )
	FRotationDoneDelegate mRotationDoneDelegate;

	/** Array with information about different speeds that this creature can use */
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	TArray< FMoveSpeedPair > mMoveSpeedData;

	/** Indicates if we should optimize this creatures mesh ( disable ticking ) when looking at it from a distance ( not good on large creatures ) */
	UPROPERTY( EditDefaultsOnly, Category = "Creature" )
	bool mShouldOptimizeMeshWhenVisible;
private: 
	/** Should this creature be able to persist in the world */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Creature" )
	bool mIsPersistent;

	/** We specify our own controller class because we need to delay the spawning. Set this instead of "AIControllerClass */
	UPROPERTY( EditDefaultsOnly, meta = (DisplayName = "Actual AI Controller Class"), Category = "Pawn" )
	TSubclassOf< AController > mActualAIControllerClass;

	/** Timer handle used when rotating the pawn with our custom rotate movement */
	UPROPERTY()
	FTimerHandle mRotationTimerHandle;

	/** Target rotation for custom rotate movement */
	UPROPERTY( ReplicatedUsing = OnRep_TargetRotation )
	FRotator mTargetRotation; 

	/** How long time we can take on rotation at max */
	float mMaxRotationTime;

	/** The timestep we use when rotating */
	float mRotationDt;

	/** How long we have been rotating for */
	float mTimeSpentRotating;

	/** Can creatures spawn during day? */
	UPROPERTY( EditDefaultsOnly, Category = "Spawning" )
	bool mCanSpawnDuringDay;

	/** Can creatures spawn during night? */
	UPROPERTY( EditDefaultsOnly, Category = "Spawning" )
	bool mCanSpawnDuringNight;

	/** Used in combination with BTT_RotateToTarget if we need the creature to move while rotating */
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	bool mMoveDuringRotation;

	/** Scale value for input vector when rotating and moving */
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	float mRotationSpeedMultiplier;

	/** Component used to determine eye location for a creature */
	UPROPERTY( EditAnywhere )
	USceneComponent* mEyeLocationComponent;

	/**Sprite for the arachnophobia mode */
	UPROPERTY( EditAnywhere )
	class UBillboardComponent* mArachnophobia_Sprite;

	/** Material for the arachnophobia mode */
	UPROPERTY( EditAnywhere )
	class UMaterialBillboardComponent* mArachnophobia_Material;

	/** Particle for the arachnophobia mode */
	UPROPERTY( EditAnywhere )
	class UParticleSystemComponent* mArachnophobia_Particle;

	/** How much of day time percentage ( 0.0 - 1.0 ) should count towards night time  */
	UPROPERTY( EditDefaultsOnly, Category = "Spawning" )
	float mDayTimePctCountAsNight;
};
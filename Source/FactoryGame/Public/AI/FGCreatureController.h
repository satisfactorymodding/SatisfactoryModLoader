// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AIController.h"

#include "Creature/FGCreature.h"
#include "FGCreatureSubsystem.h"

#include "FGStimulusAccumulator.h"
#include "FGDamageTypeAccumulator.h"

#include "AI/Navigation/NavQueryFilter.h"

#include "FGCreatureController.generated.h"

namespace FGBBKeys
{
	const FName Spawner = TEXT("Spawner");
	const FName Spline = TEXT("Spline");
	const FName TargetActor = TEXT("TargetActor");

	const FName MinRoamingDistance = TEXT("MinRoamingDistance");
	const FName MaxRoamingDistance = TEXT("MaxRoamingDistance");
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnCreatureStateChanged, class AFGCreatureController*, creatureController, ECreatureState, previousState, ECreatureState, newState );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnCreatureTargetChanged, class AFGCreatureController*, creatureController, AActor*, newTarget );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnCreatureTargetVisibilityChanged, class AFGCreatureController*, creatureController, AActor*, newTarget, bool, isVisible );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCreatureCurrentActionChanged, class UFGCreatureAction*, action );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnNoisePerceived, AActor*, actor, const FAIStimulus&, stimulus, TSubclassOf< class UFGNoise >, noiseClass );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnActionSelectionComplete, class UFGAction*, selectedAction );

UENUM( BlueprintType )
enum class ETargetVisibilityRequirement : uint8
{
	TVR_None				UMETA( DisplayName = "None" ),
	TVR_Visible				UMETA( DisplayName = "Visible" ),
	TVR_RecentlyVisible		UMETA( DisplayName = "Recently Visible" )
};

USTRUCT( BlueprintType )
struct FFGCreatureAggroData
{
	GENERATED_BODY()

	/** The target this data belongs to. */
	UPROPERTY( BlueprintReadOnly )
	AActor* Target = nullptr;

	/** The aggro level of this target. */
	UPROPERTY( BlueprintReadOnly )
	float Aggro = 0.f;

	/** Whether or not this aggro target is visible to us. */
	UPROPERTY( BlueprintReadOnly )
	bool IsVisible = false;
};

USTRUCT( BlueprintType )
struct FFGCreatureVisibilityData
{
	GENERATED_BODY()
	
	/** The target this data belongs to. */
	UPROPERTY( BlueprintReadOnly )
	AActor* Target = nullptr;

	/** 0-1 value describing how visible the target is. */
	UPROPERTY( BlueprintReadOnly )
	float VisibilityLevel = 0.f;

	/** Whether or not the target is currently perceived, this does not mean they are fully seen yet. */
	UPROPERTY( BlueprintReadOnly )
	bool IsPerceived = false;

	/** Whether or not the target is actively visible. Meaning they are fully seen. */
	UPROPERTY( BlueprintReadOnly )
	bool IsActivelyVisible = false;
};

USTRUCT( BlueprintType )
struct FFGCreaturePathToTarget
{
	GENERATED_BODY()

	FFGCreaturePathToTarget() {}

	FFGCreaturePathToTarget( AActor* target, float timeStamp, UNavigationPath* path, TSubclassOf< UNavigationQueryFilter > queryFilter )
		: Target( target )
		, TimeCached( timeStamp )
		, PathObject( path )
		, QueryFilter( queryFilter )
	{}

	UPROPERTY( BlueprintReadOnly )
	AActor* Target = nullptr;

	UPROPERTY( BlueprintReadOnly )
	float TimeCached = 0.f;

	UPROPERTY( BlueprintReadOnly )
	UNavigationPath* PathObject = nullptr;

	UPROPERTY( BlueprintReadOnly )
	TSubclassOf< UNavigationQueryFilter > QueryFilter = nullptr;
};

USTRUCT( BlueprintType )
struct FFGRecentDamageTaken
{
	GENERATED_BODY()

	/** What kind of damage that was received. */
	UPROPERTY( BlueprintReadOnly )
	const class UFGDamageType* DamageType = nullptr;

	/** When the damage was received. */
	UPROPERTY( BlueprintReadOnly )
	float Timestamp = 0.f;

	/** How much damage was received. */
	UPROPERTY( BlueprintReadOnly )
	float Amount = 0.f;

	/** What dealt damage to us. */
	UPROPERTY( BlueprintReadOnly )
	AActor* DamageCauser = nullptr;

	/** Who instigated the damage dealt to us. */
	UPROPERTY( BlueprintReadOnly )
	AController* DamageInstigator = nullptr;

	/** The location we were at when we were damaged. */
	UPROPERTY( BlueprintReadOnly )
	FVector DamageLocation = FVector::ZeroVector;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGCreatureController : public AAIController
{
	GENERATED_BODY()
public:	
	AFGCreatureController( const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get() );

	// Begin AIController Interface
	virtual void OnPossess( APawn* InPawn ) override;
	virtual void OnUnPossess() override;
	virtual FPathFollowingRequestResult MoveTo( const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath = nullptr ) override;
	virtual void UpdateControlRotation( float DeltaTime, bool bUpdatePawn = true ) override;
	// End AIController Interface

	// Begin AActor Interface
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Tick( float DeltaSeconds ) override;
	// End AActor Interface

	/** Toggles whether or not the AI should be enabled or disabled.  */
	UFUNCTION( BlueprintCallable, Category = "AI" )
	void SetEnabled( bool enabled );

	/** Whether or not the creature is ready to despawn. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	bool IsReadyToDespawn() const;

	/* Called from AFGCreature::Died() */
	virtual void CreatureDied();

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE class AFGCreature* GetControlledCreature() const { return mControlledCreature; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE ECreatureState GetCurrentCreatureState() const { return mCurrentBehaviorState; }

	/** Whether or not the creature is in any state specified by the state mask. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	bool CheckCurrentState( int32 stateMask ) const;
	
	UFUNCTION( BlueprintPure, Category = "AI" )
	virtual ECreatureState GetDesiredCreatureState() const;

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE float GetStressLevel() const { return mStressLevel; }

	/** Whether or not we should be hostile towards the specified actor. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	virtual bool CanBeHostileTowards( const AActor* actor ) const;

	/** Whether or not the specified actor should be considered a threat. */
	UFUNCTION( BlueprintNativeEvent, BlueprintPure, Category = "AI" )
	bool IsActorConsideredThreat( const AActor* actor ) const;

	/** Whether or not the specified actor is a valid target. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	virtual bool IsValidTarget( const AActor* actor ) const;

	/** Gets the current target of the creature. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE AActor* GetCurrentTarget() const { return mCurrentTarget; }

	/** Sets the current target and focus of the creature. */
	UFUNCTION( BlueprintCallable, Category = "AI" )
	void SetCurrentTarget( AActor* newTarget );
	
	/** Gets a list of all current aggro target data. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	const TArray< FFGCreatureAggroData >& GetAggroTargets() const { return mAggroTargets; }

	/** Gets a list of all visible target data. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	const TArray< FFGCreatureVisibilityData >& GetVisibleTargets() const { return mVisibleTargets; }

	/** Creates a list of locations which we consider threatening. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	TArray< FVector > GetKnownThreatLocations() const;

	/** Gets all targets. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	TArray< AActor* > GetAllTargets( ETargetVisibilityRequirement visibilityRequirement, float minimumAggro ) const;
	
	/** Gets the target with the highest amount of aggro, if one exists. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	AActor* GetHighestAggroTarget( ETargetVisibilityRequirement visibilityRequirement, float minimumAggro ) const;

	/** Gets the target which is closest to us, if one exists. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	AActor* GetClosestTarget( ETargetVisibilityRequirement visibilityRequirement, float minimumAggro ) const;

	/** Gets a random target weighted by their aggro. Higher aggro targets are more likely chosen. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	AActor* GetRandomWeightedTarget( ETargetVisibilityRequirement visibilityRequirement, float minimumAggro ) const;

	/** Gets a random target above a certain aggro. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	AActor* GetRandomTarget( ETargetVisibilityRequirement visibilityRequirement, float minimumAggro ) const;

	/** Gets the nearest target we are alerted by. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	AActor* GetNearestAlertTarget() const;

	/** Gets the nearest location of something we are alerted by. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	bool GetNearestAlertLocation( FVector& out_location ) const;

	UFUNCTION( BlueprintCallable, Category = "AI" )
	UNavigationPath* GetCachedPathToTarget( AActor* target, float cacheLifetime = 0.2f, TSubclassOf< UNavigationQueryFilter > queryFilter = nullptr );

	/** Gets the aggro of the specified target actor. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	float GetAggroForTarget( const AActor* target ) const;

	/** Gets the visibility level of the specified target actor. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	float GetVisibilityLevelForTarget( const AActor* target ) const;
	
	/** Whether or not the specified target is considered fully visible, meaning their visibility level is 1.0. */
    UFUNCTION( BlueprintPure, Category = "AI" )
    bool IsTargetFullyVisible( const AActor* target ) const;
	
	/** Used to trigger a state update for the creature. Called from events which can influence the creature's behaviour. */
	void TriggerStateUpdate( bool bImmediate = false );

	UFUNCTION( BlueprintCallable, Category= "AI")
	void SetAggroForTarget( AActor* target, float newAggro, bool bImmediateStateUpdate = false );

	/** Adds a aggro modification to a target. */
	UFUNCTION( BlueprintCallable, Category = "AI" )
	void ModifyAggroForTarget( AActor* target, float aggroModification, bool bImmediateStateUpdate = false );

	UFUNCTION( BlueprintCallable, Category = "AI" )
	void NullifyAllAggro( bool bImmediateStateUpdate = false );

	UFUNCTION( BlueprintCallable, Category= "AI")
	void SetStressLevel( float newStress, bool bImmediateStateUpdate = false );

	UFUNCTION( BlueprintCallable, Category= "AI")
	void SetStressLevelToMax( bool bImmediateStateUpdate = false );

	UFUNCTION( BlueprintCallable, Category = "AI" )
	void ModifyStressLevel( float stressModification, bool bImmediateStateUpdate = false );

	/** Goes through all known stimuli and returns the most desirable one to investigate. Returns true if it successfully found one. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	bool GetStimulusLocationToInvestigate( FVector& outLocation ) const;

	/** Use this function to try to free the creature if it's stuck outside of the navmesh. Will try to move it to a nearby position on the nav mesh if possible. */
	UFUNCTION( BlueprintCallable, Category = "AI" )
	bool TryUnstuckCreature();

	void OnCreatureStuckInGeometry();

	/** Whether or not the creature is currently stuck and can't move. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	bool IsStuck() const { return mIsStuck; }

	/** Whether or not the creature is currently fleeing. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	bool IsFleeing() const { return mIsFleeing; }

	UFUNCTION( BlueprintNativeEvent, Category = "AI" )
	void OnInterruptActionFinished(bool success);

	/** Gets the current action being performed by the creature. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE class UFGCreatureAction* GetCurrentAction() const { return mCurrentAction; }
	
	/** Sets the current action being performed by the creature. */
	void SetCurrentAction( class UFGCreatureAction* action );

	/** Called by the action selection task when we successfully select an action. */
	UFUNCTION( BlueprintCallable, Category = "AI" )
	void OnActionSelectionComplete( class UFGAction* selectedAction );

	/** Called when the creature changes movement mode. */
    UFUNCTION()
    void OnCreatureMovementModeChanged( EMovementMode PrevMovementMode, uint8 PreviousCustomMode );

	bool GetAlignRotationToFloor() const { return mAlignRotationToFloor; }
protected:
	/** Used to update the state of the creature. */
	void UpdateCreatureState();

	/** Called whenever the behavior state of the creature changes. */
	UFUNCTION( BlueprintNativeEvent, Category="AI" )
	void OnCreatureStateChanged( ECreatureState previousState, ECreatureState newState );

	/** Updates the fleeing state of the creature. */
	void UpdateFleeingState( float DeltaSeconds );
	
	/** Listen for damage to our pawn */
	void SubscribeToPawnDamage();

	/** Stop listening for damage to our pawn */
	void UnSubscribeToPawnDamage();
	
	UFUNCTION( BlueprintCallable, Category = "AI" )
	bool SetCurrentCreatureState( ECreatureState NewState );

	// Begin AIController Interface
	virtual bool InitializeBlackboard( UBlackboardComponent& BlackboardComp, UBlackboardData& BlackboardAsset ) override;
	// End AIController Interface

	/** Returns an amount of stress to add based on a perceived stimulus. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	float GetStressAccumulationFromStimulus( AActor* inActor, const FAIStimulus& Stimulus ) const;

	/** Returns an amount of stress to add based on damage taken. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	float GetStressAccumulationFromDamage( AActor* inActor, float damageAmount, const UFGDamageType* damageType ) const;

	/** Whether or not we would want to investigate a given stimulus. */
	virtual bool ShouldInvestigateStimulus( AActor* stimulusActor, const FAIStimulus& stimulus ) const;

	/** Checks if the specified stimulus is a noise we want to investigate. */
	bool ShouldInvestigateNoise( AActor* stimulusActor, const FAIStimulus& stimulus ) const;

	/** Called whenever a noise is perceived by the creature. */
	UFUNCTION( BlueprintImplementableEvent, Category = "AI" )
	void OnNoisePerceived( AActor* actor, const FAIStimulus& stimulus, TSubclassOf< class UFGNoise > noiseType );
	
	UFUNCTION()
	virtual void OnTargetPerceptionUpdated( AActor* inActor, struct FAIStimulus Stimulus );

	/** Called when our controlled pawn takes damage. */
	UFUNCTION()
	virtual void OnPawnTakeDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );

	/** Called when our creature takes damage from anything other than itself. */
	UFUNCTION( BlueprintImplementableEvent, Category = "AI" )
	void OnCreatureTakeAnyDamage( float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );

	/** Called whenever we gain / lose sight of a target. */
	UFUNCTION( BlueprintNativeEvent, Category = "AI" )
	void OnTargetVisibilityChanged( AActor* target, bool isVisible );

	/** Whether or not we want to be alerted by this target when they are visible to us. Runs CanBeHostileTowards by default. */
	UFUNCTION( BlueprintNativeEvent, Category = "AI" )
	bool CanBeAlertedByTarget( const AActor* target ) const;

	/** Whether or not the specified aggro target fulfills the specified visibility requirement. */
	UFUNCTION( BlueprintCallable, Category = "AI" )
	bool IsAggroTargetVisible( const FFGCreatureAggroData& AggroData, ETargetVisibilityRequirement VisibilityRequirement ) const;

	void TryCreatureActionInterrupt();

private:
#if !UE_BUILD_SHIPPING
	void DisplayDebugInformation();
#endif

	UFUNCTION()
	void TickCreatureHealthRegen();
	
	/** Register an actor as an aggro target. */
	FFGCreatureAggroData* GetOrRegisterAggroTarget( AActor* target );

	/** Used to update whether or not a target is currently being perceived by sight, this does not mean the creature considers it visible yet. */
	void SetVisibilityPerceivedForTarget( AActor* target, bool isPerceived );

	/** Wrapper for updating our visibility data. */
	void UpdateVisibilityData( float DeltaSeconds );

	/** Wrapper for updating our aggro data. */
	void UpdateAggroData( float DeltaSeconds );

	/** Used to filter out irrelevant targets for all the "Get X Target" functions. */
	bool FilterAggroTarget( const FFGCreatureAggroData& target ) const;
	
	/** Wrapper for setting the flee state of the creature. */
	void SetCreatureFleeState( bool shouldFlee );
	
	/** Called once the stun damage cooldown has expired. */
	UFUNCTION()
	void OnStunDamageCooldownFinished();

	/** Called when the creature goes from stunned to unstunned or vice versa. */
	UFUNCTION()
	void OnCreatureStunChanged( bool isStunned );

	UFUNCTION()
	void ClearOutdatedRecentDamageTaken();

	/** Called when we successfully sense an actor. */
	void SenseActor( AActor* perceivedActor, const FAIStimulus& stimulus );

	/** Sometimes a stimulus might come from an actor which belongs to another, such as a weapon which belongs to the player. This function would in that case return the player. */
	AActor* GetActualPerceivedActor( AActor* inActor ) const;

	bool CanBeHostileAgainstPlayer( const class AFGCharacterPlayer* player ) const;

public:
	/** Called whenever the creature state changes. */
	UPROPERTY( BlueprintAssignable, Category = "AI" )
	FOnCreatureStateChanged mOnCreatureStateChanged;

	/** Called whenever the creature's target changes. */
	UPROPERTY( BlueprintAssignable, Category = "AI" )
	FOnCreatureTargetChanged mOnCreatureTargetChanged;

	/** Called whenever a creature's target visibility changes. */
	UPROPERTY( BlueprintAssignable, Category = "AI" )
	FOnCreatureTargetVisibilityChanged mOnCreatureTargetVisibilityChanged;

	/** Called whenever the creature's target changes. */
	UPROPERTY( BlueprintAssignable, Category = "AI" )
	FOnCreatureCurrentActionChanged mOnCreatureCurrentActionChanged;

	/** Called whenever the creature perceives a noise. */
	UPROPERTY( BlueprintAssignable, Category = "AI" )
	FOnNoisePerceived mOnNoisePerceived;

	/** Called whenever the creature perceives a noise. */
	UPROPERTY( BlueprintAssignable, Category = "AI" )
	FOnActionSelectionComplete mOnActionSelectionComplete;

protected:
	/** Current action being performed by the creature. */
	UPROPERTY( BlueprintReadOnly, Category = "AI" )
	class UFGCreatureAction* mCurrentAction;
	
	/** Will be alerted by noise which is within this distance. */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mNoiseAlertDistance;

	/** Tilt controller rotation toward the floor normal. Don't forget to set rotation rates in movement component to use this vales! Only pitch is supported for now */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	bool mAlignRotationToFloor;
	
	UPROPERTY()
	TArray< FFGCreatureAggroData > mAggroTargets;

	/** Controllers who have been responsible for damaging us recently. */
	UPROPERTY()
	TArray< AController* > mAggressors;

	UPROPERTY()
	TArray< FFGCreatureVisibilityData > mVisibleTargets;

	UPROPERTY()
	AActor* mCurrentTarget;

	UPROPERTY()
	TArray< FFGCreaturePathToTarget > mCachedPathToTargets;

	UPROPERTY( BlueprintReadOnly, Category = "AI" )
	TArray< FFGRecentDamageTaken > mRecentDamageTaken;

	/** For how long we will remember recent damage taken. */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mRecentDamageMaxAge;

	UPROPERTY()
	FTimerHandle mClearRecentDamageTimerHandle;

	/** The current stress level of the creature. */
	UPROPERTY()
	float mStressLevel;

	/** Whether or not the creature is fleeing. */
	bool mIsFleeing;

	/** Keeps track of the amount of damage the creature has taken, once it exceeds the stun threshold the creature will be stunned. */
	float mStunDamageAccumulation;

	bool mShouldUpdateCreatureState;

	UPROPERTY()
	FCreatureActionInterrupt mRunningInterrupt;

	bool mInterruptRunning;

private:
	UPROPERTY()
	class AFGCreature* mControlledCreature;

	UPROPERTY()
	FTimerHandle mHealthRegenHandle;
	
	/** Current behavior state of the creature. Don't set directly, call SetCurrentCreatureState. */
	UPROPERTY()
	ECreatureState mCurrentBehaviorState;

	/** Timer responsible for preventing the creature from being stunned by damage while the cooldown is active. */
	FTimerHandle mStunDamageCooldownTimerHandle;

	/** Will be true if the creature fails to unstuck and cant move. */
	bool mIsStuck;
};

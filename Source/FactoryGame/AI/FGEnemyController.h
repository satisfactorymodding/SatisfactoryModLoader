// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGCreatureController.h"
#include "FGAggroTargetInterface.h"
#include "Curves/CurveFloat.h"
#include "FGEnemyController.generated.h"

UENUM( BlueprintType )
enum class EIgnore : uint8
{
	I_NONE = 0				UMETA( DisplayName = "Invalid status." ),
	I_FALSE	= 1				UMETA( DisplayName = "Target is not ignored." ),
	I_NOT_VALID	= 2			UMETA( DisplayName = "Target ignored cause not valid" ),
	I_NO_PATH = 3			UMETA( DisplayName = "Target ignored cause could not find path." ),
	I_LastEnum	= 4			UMETA( Hidden )
};

/**
* Contains information about how desirable a aggro
* target is for our Pawn
*/
USTRUCT( BlueprintType )
struct FAggroEntry
{
	GENERATED_BODY();

	/** Set good default values. */
	FAggroEntry() :
		AggroTarget( nullptr ),
		BaseDesirability( 0.0f ),
		Aggro( 0.0f ),
		AggroDesirability( 0.0f ),
		Distance( 0.0f ),
		DistanceDesirability( 0.0f ),
		LastHurtTime( -1.0f ),
		Ignore( EIgnore::I_FALSE ),
		LastIgnoreTime( -1.0f )
	{
	}

	/** Set good default values. */
	FAggroEntry( const TScriptInterface< IFGAggroTargetInterface > fromAggroTarget ) :
		FAggroEntry()
	{
		AggroTarget = fromAggroTarget;
	}

	bool operator ==( const TScriptInterface< IFGAggroTargetInterface > otherAggroTarget ) const
	{
		return AggroTarget == otherAggroTarget;
	}

	UPROPERTY( BlueprintReadWrite, Category = "Aggro" )
	TScriptInterface< IFGAggroTargetInterface >	AggroTarget;
	float						BaseDesirability;
	UPROPERTY( BlueprintReadWrite, Category = "Aggro" )
	float						Aggro;
	float						AggroDesirability;
	float						Distance;
	float						DistanceDesirability;
	UPROPERTY( BlueprintReadWrite, Category = "Aggro" )
	float						LastHurtTime;
	UPROPERTY( BlueprintReadWrite, Category = "Aggro" )
	EIgnore						Ignore;
	float						LastIgnoreTime;
};

struct FFindByAggroTarget
{
	TScriptInterface< IFGAggroTargetInterface >	AggroTarget;

	FFindByAggroTarget( TScriptInterface< IFGAggroTargetInterface > InAggroTarget ) : AggroTarget( InAggroTarget ) { }

	bool operator() ( const FAggroEntry Element ) const
	{
		return ( AggroTarget == Element.AggroTarget );
	}

};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGEnemyController : public AFGCreatureController
{
	GENERATED_BODY()

public:
	/** ctor */
	AFGEnemyController( const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get() );

	//~ Begin AController Interface
	virtual void Possess( APawn* InPawn ) override;
	virtual void UnPossess() override;
	//~ End AController Interface

	/** Override the startpanic */
	virtual void StartPanic_Implementation();

	/**
	 * Removes specified target from Aggro list                                                                    
	 */
	void RemoveAggroEntryByTarget( TScriptInterface< IFGAggroTargetInterface > target );

	/**
	* Called when gathering aggro targets and cleaning up invalid aggro targets.
	* Used to filter out ignored aggro targets.
	*
	* @return - If we should ignore this target altogether.
	*/
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	bool IsOnIgnoreList( const TScriptInterface< IFGAggroTargetInterface > aggroTargetInterface ) const;

	/**
	* Called when gathering aggro targets and cleaning up invalid aggro targets.
	* Use this if you want to filter away aggro targets.
	*
	* @return - If we should aggro against this target.
	*/
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	bool ShouldAddAggroTarget( const TScriptInterface< IFGAggroTargetInterface > aggroTargetInterface ) const;

	/**
	* Updates the list of all aggrotargets.
	*
	* @param deltaTime - time since last update.
	* @param full -	if a full update should be done. (expensive)
	*					Extended checks every target if it should still be in the aggro list.
	*/
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	void UpdateAggroTargets( float dt, bool fullCheck = false );

	/**
	 * Sweeps through all aggro entries and removes the invalid ones
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	void RemoveInvalidAggroTargets();

	/**
	 * Finds an appropriate target from the list of aggro targets that exist                                                                    
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	void FindAndAssignTarget();

	/**
	 * Assigns a new aggrotarget                                                                    
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	void SetCurrentAggroTarget( TScriptInterface< IFGAggroTargetInterface > newAggroTargetInterface );

	/** Called if we change aggro target */
	void UpdateAggroTarget( TScriptInterface< IFGAggroTargetInterface > oldTarget, TScriptInterface< IFGAggroTargetInterface > newTarget );

	/** Do stuff when we found a new target */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|AI|Aggro" )
	void OnAggroTargetUpdated();

	/** Do stuff when clearing the target */
	void OnAggroTargetRemoved( const TScriptInterface< IFGAggroTargetInterface > oldTarget  );

	/** Called when we lose an aggro target and have no other target set */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|AI|Aggro" )
	void OnAggroTargetLost( AActor* lostActor );

	/** Add a new aggro target to our aggro target list, can't be in the list before */
	void AddNewAggroTarget( const TScriptInterface< IFGAggroTargetInterface > target );

	/**
	* Adds aggro to the specified target
	*
	* @param aggroTarget - The target to add aggro to.
	* @param aggroToAdd - How much aggro do we want to add to the target.
	*/
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	void AddToAggroByTarget( const TScriptInterface< IFGAggroTargetInterface > target, float damage );

	/** aggro thresholds for setting a target and releasing a target may be different */
	UFUNCTION()
	float GetAggroThreshold();

	/**
	 * @returns true if we should switch from our current aggro target to the new target
	 */
	bool ShouldSwitchTarget( TScriptInterface< IFGAggroTargetInterface > newTarget );
	
	/**
	* Checks wether or not the target is valid to move towards
	*
	* @param target - the target to check.
	* @return - Can we have this entry as a traget.
	*/
	bool IsValidTarget( TScriptInterface< IFGAggroTargetInterface > target );

	/**
	* Do we care if we can see an actor or not.
	*
	* @param target - the actor we're interested in.
	*
	* @return - true if we care about can see target; otherwise false.
	*/
	bool CareIfCanSeeActor( AActor* target );

	/**
	 * Checks to see if we see an actor or not.
	 *
	 * @param target - the actor we want to trace against
	 */
	UFUNCTION(BlueprintPure,Category="FactoryGame|AI")
	bool CanSeeActor( AActor* target );

	/** Returns the aggro target that currently has the most aggro */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|AI" )
	FORCEINLINE TScriptInterface< IFGAggroTargetInterface > GetMostDesirableAggroTarget() { return mMostDesirableAggroTarget; }

	/** Gets targeting desire from a aggro target */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI" )
	float GetTargetingDesire( TScriptInterface< IFGAggroTargetInterface > aggroTarget );

	/** function for sorting our array of aggrotargets */
	void SortMostDesirableAggroTargets();

	/**
	* Get targeting desire from an AggroEntry.
	*
	* @param target - entry to calculate desire for.
	*
	* @return - the targeting desire.
	*/
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	float GetTargetingDesireFromAggroEntry( FAggroEntry outTarget );

	/** Updates the aggro */
	void UpdateAggroTargetsAggro( float dt ); 

	/**
	* Update all ignored aggro-targets and see if the ignore status can be removed.
	*/
	void UpdateAggroTargetsIgnored( float dt );

	/**
	* Update desirability based on distance
	*/
	void UpdateAggroTargetsDistance();

	/**
	* Update all aggro entries desirabilities.
	*/
	void UpdateAggroTargetsDesirabilities();

	/**
	* Gets the base desirability a VALID target is for this pawn (if it hasn't attacked us at all)
	* @param aggroTargetIndex - the target we want to check how desirable is for us
	* @return - the base disirability
	*/
	float GetBaseTargetingDesire( int32 aggroTargetIndex );

	/**
	* Caluclates the desire of the aggro target based on the distance to the target
	*
	* @param aggroTargetIndex - The target we want to know how desirable it is to attack
	* @return -1 if something is wrong, else the desirability multiplier
	*/
	float GetDistanceTargetingDesire( int32 aggroTargetIndex ); 

	/**
	* Caluclates the desire of the aggro target based on the aggro to the target
	*
	* @param aggroTargetIndex - The target we want to know how desirable it is to attack
	* @return -1 if something is wrong, else the desirability multiplier
	*/
	float GetAggroTargetingDesire( int32 aggroTargetIndex );

	/**
	 * Finds the most desirable target based on the combination of desirabilities                                                                    
	 */
	TScriptInterface< IFGAggroTargetInterface > FindMostDesirableAggroTarget();

	/**
	* Is the target ignored
	*
	* @return - true if it is ignored.
	*/
	bool IsIgnored( TScriptInterface< IFGAggroTargetInterface > target );

	/**
	* This function sets a targets ignore status as well as for how long.
	* When the time runs out the status is returned to I_FALSE.
	*
	* @param target - the aggro target to ignore.
	* @param ignore - to set ignore to true or false.
	* @param seconds - how long the target should be ignored.
	* @param force - should the status update be forced.
	*/
	void SetIgnore( TScriptInterface< IFGAggroTargetInterface > target, EIgnore ignoreType, float seconds, bool force = false );

	/**
	* This function sets a targets ignore status as well as for how long.
	* When the time runs out the status is returned to I_FALSE.
	*
	* @param index - the aggro target index to ignore
	* @param ignore - to set ignore to true or false.
	* @param seconds - how long the target should be ignored.
	* @param force - should the status update be forced.
	*/
	void SetIgnoreByIndex( int32 index, EIgnore ignoreType, float seconds, bool force = false );

	/**
	* Get the targets ignore status
	*
	* @param targetIndex - if set, we will use this since it's cheaper
	* @return - true if it is ignored.
	*/
	EIgnore GetIgnoreStatus( TScriptInterface< IFGAggroTargetInterface > target, int32 targetIndex = -1 );

	/** 
	 * Gathers initial aggro targets, goes through the global list of aggro targets and filters out interesting aggro targets
	 * Also, hookups ourself on delegates when new aggrotargets is spawned
	 **/
	void StartInitialAggroCollection();

	/** Updates our current aggro, and then makes sure we assign a new target */
	UFUNCTION()
	void UpdateAggroAndFindAndAssignTarget();

	/** Gathers all aggro targets into the current list. Note, this doesn't clear the current aggro list */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	void GatherAggroTargets();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	void ClearAllAggroTargetsAndUpdate();

	/** Returns index of current pattern */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|AI" )
	FORCEINLINE int32 GetAttackPatternIndex() { return mAttackPatternIndex; }

	/** Returns the attack class found in the attack pattern */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI" )
	TSubclassOf< UFGAttack > GetCurrentAttackFromPattern(){ return mAttackPattern[ mAttackPatternIndex ]; }

	/** Updates the attack from attackpattern to the next in line ( will loop ) */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI" )
	void UpdateAttackPattern();

	/** Returns the last valid location for target */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|AI" )
	FORCEINLINE FVector GetTargetLastValidLocation() { return mLastValidLocation; }

	/** Resets the variable mLastValidLocation to an invalid location */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI" ) 
	void ResetLastValidTargetLocation() { mLastValidLocation = FAISystem::InvalidLocation; } 
public:
	/** Handle that cares about how often we update the aggro for our AI */
	FTimerHandle mUpdateAggroHandle;

	/** Specifies how often we need to update all aggro */
	UPROPERTY( EditDefaultsOnly, Category = "Aggro" )
	float mUpdateAggroInterval;
	
	/** How long time should it take to lose all aggro from damage */
	UPROPERTY( EditDefaultsOnly, Category = "Aggro" )
	float mTimeToLoseAllAggro;
	
	/** The highest aggro for all aggro targets */
	UPROPERTY( BlueprintReadWrite, Category = "Aggro" )
	float mAggroTargetsAggroMax;

	/** Aggro weigths */
	UPROPERTY( EditDefaultsOnly, Category = "Aggro" )
	float mAggroBaseWeight; 
	
	UPROPERTY( EditDefaultsOnly, Category = "Aggro" )
	float mAggroAggroWeight; 
	
	UPROPERTY( EditDefaultsOnly, Category = "Aggro" )
	float mAggroDistanceWeight;

	/** All actors that this actor can aggro to */
	UPROPERTY( BlueprintReadWrite, Category = "Aggro" )
	TArray< FAggroEntry > mAggroEntries;

	/** All actors that this actor can aggro to sorted by desirability in DESC ( index 0 is most desirable) */
	UPROPERTY( BlueprintReadOnly, Category = "Aggro" )
	TArray< FAggroEntry > mSortedAggroEntries;

	/** We only switch mCurrentTarget if the new targets desirablility is this factor larger than the old one. */
	UPROPERTY( EditDefaultsOnly, Category = "Aggro" )
	float mTargetSwitchFactor;

	/** How long should the targets be on the ignore list */
	UPROPERTY( EditDefaultsOnly, Category = "Aggro" )
	float mDefaultIgnoreCooldown; 

	/** We want static actors to be ignored a long time */
	UPROPERTY( EditDefaultsOnly, Category = "Aggro" )
	float mStaticIgnoreCooldown;

	/** Curve for determining the distance aggro added */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Aggro" )
	UCurveFloat* mAggroDistanceCurve;

	/** Minimum aggro the enemy needs to add a target to its aggro list */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Aggro" )
	float mGainAggroThreshold;

	/** if aggro goes below this value the target is invalid */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Aggro" )
	float mLoseAggroThreshold;

	/**
	* This is the aggro target that at the last check was the most desirable.
	* NOTE: Only set this variable through SetCurrentAggroTarget().
	*/
	UPROPERTY( BlueprintReadOnly, Category = "Aggro" )
	TScriptInterface< IFGAggroTargetInterface > mCurrentAggroTarget;

	/** The top potential aggro target */
	TScriptInterface< IFGAggroTargetInterface > mMostDesirableAggroTarget;

	/** Array with attacks that determine order of attacks */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	TArray< TSubclassOf< class UFGAttack > > mAttackPattern;

	/** Current attack in attack pattern */
	int32 mAttackPatternIndex;
protected:
	/** Called whenever a new aggro target is added */
	UFUNCTION()
	void AggroTargetAdded( TScriptInterface< IFGAggroTargetInterface > aggroTarget );

	UFUNCTION()
	void AggroTargetRemoved( TScriptInterface< IFGAggroTargetInterface > aggroTarget );

	/** Listen for damage to our pawn */
	void SubscribeToPawnDamage();

	/** Stop listening for damage to our pawn */
	void UnSubscribeToPawnDamage();

	/** Called when our controlled pawn takes damage */
	UFUNCTION()
	void OnPawnTakeDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );

	/** Is this target allowed for aggro */
	bool IsTargetAllowed( AActor* targetActor );
private:
	/** List of aggro target classes that we should not aggro against */
	UPROPERTY( EditDefaultsOnly, Category = "Aggro", meta = ( MustImplement = "FGAggroTargetInterface") )
	TArray< TSoftClassPtr< AActor > > mIgnoredAggroTargetClasses;
	
	/** Last location target was seen on */
	FVector mLastValidLocation;

	/** Time we should ignore targets when panicking */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mPanicIgnoreTime;
};

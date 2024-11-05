// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGCharacterBase.h"
#include "FGAction.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NavMesh/RecastNavMesh.h"
#include "FGCreature.generated.h"

class AFGCreature;
class AFGCreatureController;

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogCreature, Log, All );

extern TAutoConsoleVariable< int32 > CVarCreatureDebug;
extern TAutoConsoleVariable< int32 > CVarCreatureVisionDebug;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnCreaturePersistenceChanged, class AFGCreature*, creature, bool, newPersistence );

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

USTRUCT( BlueprintType ) 
struct FNoiseToInvestigate
{
	GENERATED_BODY()
	
	/** The type of noise to investigate. */
	UPROPERTY( EditDefaultsOnly, Category = "Noise" )
	TSubclassOf< UFGNoise > NoiseType;

	/** Only consider noise made from these kinds of actors. */
	UPROPERTY( EditDefaultsOnly, Category = "Noise" )
	TArray< TSubclassOf< AActor > > SourceActorFilter;
	
	/** The noise will be ignored if it's not within this distance range. If Min > Max then Max is ignored. */
	UPROPERTY( EditDefaultsOnly, Category = "Noise" )
	FFloatInterval MinMaxRange;

	/** The noise will be ignored if it's not within this loudness range. If Min > Max then Max is ignored. */
	UPROPERTY( EditDefaultsOnly, Category = "Noise" )
	FFloatInterval MinMaxLoudness;
};

USTRUCT( BlueprintType ) 
struct FFGCreaturePerceptionSettings
{
	GENERATED_BODY()

	FFGCreaturePerceptionSettings()
		: SightConfig( nullptr )
		, ImmediateVisibilityRadius( 500.0f )
		, HearingConfig( nullptr )
	{
	}
	
	/** The sight configuration for this creature. */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Perception" )
	class UAISenseConfig_Sight* SightConfig;

	/** If something is within this radius, it will immediately be fully visible instead of slowly building up. */
	UPROPERTY( EditDefaultsOnly, Category = "Perception" )
	float ImmediateVisibilityRadius;
	
	/** The hearing configuration for this creature. */
    UPROPERTY( EditDefaultsOnly, Instanced, Category = "Perception" )
    class UAISenseConfig_Hearing* HearingConfig;
};

UENUM( BlueprintType, Meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class ECreatureState : uint8
{
	CS_Default			= 0			UMETA( DisplayName = "Default" ),

	CS_Roam				= 1 << 0	UMETA( DisplayName = "Roam" ),
	CS_Alert			= 1 << 1	UMETA( DisplayName = "Alert" ),
	CS_Fight			= 1 << 2	UMETA( DisplayName = "Fight" ),
	CS_Flee				= 1 << 3	UMETA( DisplayName = "Flee" ),
	CS_Investigate		= 1 << 4	UMETA( DisplayName = "Investige" ),
};

inline FString CreatureStateEnumToString( ECreatureState state )
{
	const UEnum* EnumPtr = FindObject< UEnum >( nullptr, TEXT( "/Script/FactoryGame.ECreatureState" ), true );

	if( !EnumPtr )
	{
		return FString( "Invalid" );
	}

	return EnumPtr->GetNameStringByValue( ( int32 )state );
}

UCLASS( BlueprintType, Blueprintable, EditInlineNew )
class FACTORYGAME_API UFGCreatureInterruptTest : public UFGActionTest
{
	GENERATED_BODY()

public:
	virtual void Initialize( APawn* pawn, AController* controller, UFGAction* ownerAction ) override;
	
	void Initialize(AFGCreature* creature, AFGCreatureController* controller);

	UFUNCTION(BlueprintPure)
	AFGCreature* GetCreature() const { return mCreature; }

	UFUNCTION(BlueprintPure)
	AFGCreatureController* GetCreatureController() const { return mCreatureController; }

private:
	UPROPERTY()
	AFGCreature* mCreature = nullptr;
	UPROPERTY()
	AFGCreatureController* mCreatureController = nullptr;

};

/** Used to create, track and organize Actions for creatures */
USTRUCT( BlueprintType )
struct FCreatureAction
{
	GENERATED_BODY()

	/** States for which the action will be enabled for: Default = none */
	UPROPERTY( EditAnywhere, meta=(Bitmask,BitmaskEnum="ECreatureState") )
	uint8 RequiredStates;

	/** Whether or not the action should start on cooldown when it enters a state where it can be used. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General Settings")
	bool StartsWithCooldown;

	/** Action Name. Only used for display purpose in arrays. */
	UPROPERTY(VisibleAnywhere, AdvancedDisplay)
	FString ActionName;
	
	/** Action to use */
	UPROPERTY( EditAnywhere, Instanced )
	UFGAction* Action;

	FCreatureAction()
	{
		RequiredStates = (uint8)ECreatureState::CS_Default;
		Action = nullptr;
		ActionName = Action ? Action->GetName() : "ActionName";
		StartsWithCooldown = false;
	}
};

USTRUCT( BlueprintType )
struct FCreatureActionInterrupt
{
	GENERATED_BODY()

	/** States for which the interrupt can take place for: Default = none */
	UPROPERTY( EditAnywhere, meta=(Bitmask,BitmaskEnum="ECreatureState") )
	uint8 StateInterrupt;

	/** Action Name. Only used for display purpose in arrays. */
	UPROPERTY(VisibleAnywhere, AdvancedDisplay)
	FString ActionName;

	/** Checks to pass to trigger interrupt */
	UPROPERTY( EditAnywhere, Instanced )
	TArray<UFGCreatureInterruptTest*> Interrupts;

	/** Action to play on Interrupt */
	UPROPERTY( EditAnywhere, Instanced )
	UFGAction* Action;

	FCreatureActionInterrupt()
	{
		StateInterrupt = (uint8)ECreatureState::CS_Default;
		Action = nullptr;
		ActionName = Action ? Action->GetName() : "ActionName";
		Interrupts = TArray<UFGCreatureInterruptTest*>();
	}
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FCreatureBehaviorOverride
{
	GENERATED_BODY()
	
	/** The behavior tree will only be executed for the following states. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, meta=(Bitmask,BitmaskEnum="ECreatureState") )
	uint8 OverriddenStates;

	/** The custom behavior tree to run. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	UBehaviorTree* BehaviorTree;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCreatureStunnedChanged, bool, isStunned );

/**
 * Base class for passive creatures in the game, see AFGEnemy for aggressive creatures.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGCreature : public AFGCharacterBase
{
	GENERATED_BODY()
public:
	AFGCreature( const FObjectInitializer& ObjectInitializer );
	
	// Begin AActor Interface
	// Required for Actions/UObject replication
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void OnConstruction( const FTransform& Transform ) override;
	virtual void PostLoad() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
	virtual bool IsSelectedInEditor() const override;
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const;
#endif
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void BeginDestroy() override;
	virtual void GetActorEyesViewPoint( FVector& OutLocation, FRotator& OutRotation ) const override;
	// End AActor Interface

	void RenameActionArrayEntries();
	void UpdateCreatureNavAgentProps();

	bool IsReadyToDespawn() const;
	
	// Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin FGCharacterBase
	virtual void Died( AActor* died ) override;
	virtual void DoRagdoll_Internal() override;
	// End FGCharacterBase

	/** @return	Pawn's eye location */
	virtual FVector GetPawnViewLocation() const;

	UFUNCTION( BlueprintPure, Category = "Creature" )
	class UFGCreatureMovementComponent* GetCreatureCharacterMovement() const;

	UFUNCTION( BlueprintPure, Category = "AI" )
	class AFGCreatureController* GetCreatureController() const { return mCreatureController; }

	bool GetAdjustedNavAgentProps( FNavAgentProperties& out_navAgentProps, UWorld* worldContext = nullptr ) const;

	UFUNCTION(BlueprintPure, Category = "AI" )
	FName GetNavAgentName() const { return mNavAgentName; }
	
	/** Gets the spline we are set to follow */
	UFUNCTION( BlueprintPure, Category = "Creature" )
	FORCEINLINE class AFGSplinePath* GetSplinePath() { return mSpline; }

	UFUNCTION( BlueprintCallable, Category = "Creature" )
	void SetSplinePath(AFGSplinePath* spline) { mSpline = spline; }

	/** Gets the spline we are set to follow */
	UFUNCTION( BlueprintPure, Category = "Creature" )
	FORCEINLINE bool GetIsEnabled() const { return mIsEnabled == E_Enabled ? true : false; }

	/** Indicates if we are persistent ( not removed after a distance specified in AISystem )  */
	UFUNCTION( BlueprintPure, Category = "Creature" )
	FORCEINLINE bool IsPersistent() const { return mIsPersistent; }

	UFUNCTION( BlueprintPure, Category= "Damage" )
	FORCEINLINE float GetPassiveHealthRegenAmount() const { return mPassiveHealthRegen; }

	/** Whether or not this is a passive creature. Which means it can't aggro on anything. */
	UFUNCTION( BlueprintPure, Category = "Creature" )
	FORCEINLINE bool IsPassiveCreature() const { return mIsPassiveCreature; }

	/** Is this creature an arachnid? */
	UFUNCTION( BlueprintPure, Category = "Arachnophobia" )
	FORCEINLINE bool GetIsArachnid() const { return mIsArachnid; }

	/** Gets the array of sprites that may be used for arachnophobia mode */
	UFUNCTION( BlueprintPure, Category = "Arachnophobia" )
	FORCEINLINE TArray< UMaterialInstance* > GetArachnophobiaModeMaterials() { return mArachnophobiaModeMaterials; }

	/** Sets up the Arachnophobia mode */
	UFUNCTION( BlueprintNativeEvent, Category = "Arachnophobia" )
	void ConfigureArachnophobiaMode( bool isArachnophobiaMode );

	/** How much of day time percentage ( 0.0 - 1.0 ) should count towards night time  */
	UFUNCTION( BlueprintPure, Category = "Spawning" )
	FORCEINLINE float GetDayTimePctAsNight( ) { return mDayTimePctCountAsNight; }

	UFUNCTION( BlueprintPure, Category= "Damage" )
	FORCEINLINE float GetNavigationGenerationRadius() const { return mNavigationGenerationRadius; }

	UFUNCTION( BlueprintPure, Category= "Damage" )
	FORCEINLINE float GetNavigationRemovalRadius() const { return mNavigationRemovalRadius; }

	/** Called when the Arachnophobia mode setting is changed */
	UFUNCTION()
	void OnArachnophobiaModeChanged( bool isArachnophobiaMode );

	/** Notify when creature consumes a item*/
	UFUNCTION( NetMulticast, BlueprintCallable, Reliable, Category = "Consume" )
	void Multicast_ConsumeItem( TSubclassOf< class UFGItemDescriptor > itemDescriptor, const class AFGPlayerController* playerController );

	/** Play effects when creature consumes a item*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Consume" )
	void PlayConsumeItemEffect( TSubclassOf< UFGItemDescriptor > itemDescriptor, const AFGPlayerController* playerController );

	/** Updates the movement speed ( server side ) */
	UFUNCTION( BlueprintCallable, Category = "Movement" )
	void SetMoveSpeed( EMoveSpeed newMoveSpeedType );
	
	/** Called when creature died to spawn death item */
	UFUNCTION( BlueprintNativeEvent, Category = "Creature" )
	void SpawnDeathItem();

	/** Returns the spawner that created this creature. Can be null */
	UFUNCTION( BlueprintPure, Category = "Creature" )
	class AFGCreatureSpawner* GetSpawner() const { return mOwningSpawner; }

	/** Sets the spawner for this creature */
	void SetSpawner( class AFGCreatureSpawner* inSpawner ) { mOwningSpawner = inSpawner; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE class UBehaviorTree* GetBehaviorTreeAsset() const { return mBehaviorTree; }

	FORCEINLINE TArray< FNoiseToInvestigate > GetNoiseTypesToInvestigate() const { return mNoiseTypesToInvestigate; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	UBehaviorTree* GetOverrideBehaviorTreeForState( ECreatureState state ) const;

	UFUNCTION( BlueprintPure, Category = "AI" )
	bool HasOverriddenBehaviorState( ECreatureState State ) const;

	UFUNCTION( BlueprintPure, Category = "AI" )
	bool IsCreatureStateEnabled( ECreatureState State ) const;

	FORCEINLINE ECreatureState GetCurrentBehaviorState() const { return mCurrentBehaviorState; }

	FORCEINLINE const FFGCreaturePerceptionSettings& GetPerceptionSettings() const { return mPerceptionSettings; }

	FORCEINLINE const FFloatInterval& GetRoamingDistance() const { return mRoamingDistance; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	float GetRandomRoamingWaitTime() const;

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE float GetSpawnDistance() const { return mSpawnDistance; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE float GetDespawnDistance() const { return mDespawnDistance; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE float GetFleeStressThreshold() const { return mFleeStressThreshold; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE float GetStressReductionRate() const { return mStressReductionRate; }
	
	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE float GetUnreachableTargetDamageStressMultiplier() const { return mUnreachableTargetDamageStressMultiplier; }
	
	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE float GetMaximumAggroLevel() const { return mMaximumAggroLevel; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE float GetAggroFightThreshold() const { return mAggroFightThreshold; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE float GetAggroGainRate() const { return mAggroGainRate; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE float GetAggroReductionRate() const { return mAggroReductionRate; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE UCurveFloat* GetAggroGainRateCurve() const { return mAggroGainRateCurve; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE UCurveFloat* GetVisibilityGainCurve() const { return mVisibilityGainRateCurve; }
	
	UFUNCTION( BlueprintPure, Category = "AI" )
	TArray<UFGAction*> GetAvailableActionsForState( ECreatureState state );

	UFUNCTION( BlueprintPure, Category = "AI" )
	TArray<UFGAction*> GetAllCreatureActions() const;

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE TArray<FCreatureAction> GetCreatureActionsSetup() const { return mCreatureActionsSetup; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	FORCEINLINE TArray<FCreatureActionInterrupt> GetCreatureActionInterrupts() const { return mCreatureActionInterrupts; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	const TArray< class UFGStimulusAccumulator* >& GetStimuliAccumulatorsStress() const { return mStimuliStressAccumulators; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	const TArray< class UFGDamageTypeAccumulator* >& GetDamageTypeAccumulatorsStress() const { return mDamageTypeStressAccumulators; }
	
	UFUNCTION( BlueprintPure, Category = "AI" )
	TSubclassOf< class UFGCreatureFamily > GetCreatureFamily() const { return mCreatureFamily; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	ANavigationData* GetCreatureNavData() const;
	
	UFUNCTION( BlueprintPure, Category = "Creature" )
	TArray< TSubclassOf<UFGItemDescriptor> > GetCreatureFood() const { return mCreatureFood; }

	/** Called if the spawner has successfully recoupled itself with this creature */
	void ClearKillOrphanTimer();

	/** Whether or not this creature can be stunned. */
	UFUNCTION( BlueprintPure, Category = "Stun" )
	bool CanBeStunned() const;

	UFUNCTION( BlueprintPure, Category = "Stun" )
	bool CanBeStunnedByDamage() const;

	/** How much damage needs to be dealt in order to stun the creature. */
	UFUNCTION( BlueprintPure, Category = "Stun" )
	float GetStunDamageThreshold() const { return mStunDamageThreshold; }

	/** How long the creature should be stunned when the damage buildup exceeds the stun damage threshold. . */
	UFUNCTION( BlueprintPure, Category = "Stun" )
	float GetStunDamageDuration() const { return mStunDamageDuration; }

	/** How much time must pass before the creature can be stunned again by damage. */
	UFUNCTION( BlueprintPure, Category = "Stun" )
	float GetStunDamageCooldownDuration() const { return mStunDamageCooldownDuration; }

	/** How much to reduce the stun damage buildup per second. */
	UFUNCTION( BlueprintPure, Category = "Stun" )
	float GetStunDamageReductionRate() const { return mStunDamageReductionRate; }

	/** Whether or not this creature is stunned. */
	UFUNCTION( BlueprintPure, Category = "Stun" )
	bool IsStunned() const { return mIsStunned; }

	/** Stuns the creature. */
	UFUNCTION( BlueprintCallable, Category = "Stun" )
	void BeginStun( float stunDuration );

	/** Clears the stun from a creature. */
	UFUNCTION( BlueprintCallable, Category = "Stun" )
	void EndStun();

	/** Sets the creature as persistent. */
	UFUNCTION( BlueprintCallable, Category = "Creature" )
	void SetIsPersistent( bool persistent );

	/** Set our enabled state */
	void SetEnabled( EEnabled enabled );

	/** Returns if the creature is tamed or not */
	UFUNCTION( BlueprintImplementableEvent, Category = "Creature" )
	bool IsTamed();

	UFUNCTION( BlueprintCallable, BlueprintPure )
	int GetAmountToEatWhenTamed() const { return mAmountToEatWhenTamed; }
	
protected:
	UFUNCTION()
    void OnRep_IsEnabled();

private:
	UFUNCTION()
	void OnRep_IsStunned();

	/** Called when creature state changes. */
	UFUNCTION()
	void OnCreatureStateChanged( class AFGCreatureController* creatureController, ECreatureState previousState, ECreatureState newState );
	
public:
	/** Spline we are set to follow */
	UPROPERTY( SaveGame, EditInstanceOnly, Category = "Creature" )
	class AFGSplinePath* mSpline;

	/** Indicates if we should optimize this creatures mesh ( disable ticking ) when looking at it from a distance ( not good on large creatures ) */
	UPROPERTY( EditDefaultsOnly, Category = "Creature" )
	bool mShouldOptimizeMeshWhenVisible;

	/** Called whenever the creature gets stunned / unstunned. */
	UPROPERTY( BlueprintAssignable, Category = "Stun" )
	FOnCreatureStunnedChanged mOnCreatureStunnedChanged;

	/** Called whenever the creature changes its persistence. */
	UPROPERTY( BlueprintAssignable, Category = "Creature" )
	FOnCreaturePersistenceChanged mOnCreaturePersistenceChanged;

protected:
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "AI" )
	FName mNavAgentName = "Default";

	/** Takes the calculated nav bounds of the creature and multiplies it by this number to determine its agent size. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	float mNavBoundsScale = 1.0f;
	
	/** If checked, the system will use the character capsule radius to compute what the nav agent size is instead of the actor's bounds */
	UPROPERTY( EditAnywhere, Category = "AI" )
	bool mUseCapsuleRadiusInsteadOfBoundsForNavRadius = false;
	
	/** How big navmesh do we want to generate */
	UPROPERTY( EditAnywhere, Category = "AI" )
	float mNavigationGenerationRadius;

	/** Navigation outside this radius will be removed */
	UPROPERTY( EditAnywhere, Category = "AI" )
	float mNavigationRemovalRadius;

	/** The min and max distance to move when the creature is roaming around. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	FFloatInterval mRoamingDistance;

	/** How long the creature should wait before moving again when roaming to random locations. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	FFloatInterval mRoamingWaitTime;

	/** What behavior to use for this creature. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	UBehaviorTree* mBehaviorTree;

	/** Noises that we want to investigate. Usually creatures just investigate whatever they can be hostile against, but exceptions can be made with this. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	TArray< FNoiseToInvestigate > mNoiseTypesToInvestigate;

	/** Custom trees to override default behavior for certain states. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "AI" )
	TArray< FCreatureBehaviorOverride > mOverrideBehaviorTrees;

	/** Perception settings for this creature. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "AI" )
	FFGCreaturePerceptionSettings mPerceptionSettings;

	/** Once the creature's stress level exceeds this threshold, it will flee. Negative threshold will cause it to never flee. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	float mFleeStressThreshold;

	/** How much stress the creature loses per second. */
	UPROPERTY( EditAnywhere, Category = "AI", meta = ( UIMin = "0.0", ClampMin = "0.0" ) )
	float mStressReductionRate;
	
	/** When taking damage from an unreachable target, we will add stress based on the damage multiplied by this value. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	float mUnreachableTargetDamageStressMultiplier;
	
	/** Which behavior states are disabled for this creature. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "AI", meta=(Bitmask,BitmaskEnum="ECreatureState") )
	uint8 mDisabledBehaviorStates;

	/** The current behavior state of the creature. Replicated to clients. */
	UPROPERTY( Replicated, BlueprintReadOnly, Category = "AI" )
	ECreatureState mCurrentBehaviorState;

	/** Array of actions the creature can execute in its various states. */
	UPROPERTY( EditAnywhere, Category = "AI", meta=(FullyExpand=false, TitleProperty="ActionName") )
	TArray<FCreatureAction> mCreatureActionsSetup;

	UPROPERTY( EditAnywhere, Category = "AI", meta=(FullyExpand=false, TitleProperty="ActionName") )
	TArray<FCreatureActionInterrupt> mCreatureActionInterrupts;

	/** Used to accumulate stress for the creature based on perception. */
	UPROPERTY( EditAnywhere, Instanced, Category = "AI" )
	TArray< class UFGStimulusAccumulator* > mStimuliStressAccumulators;

	/** Maximum amount of aggro a target can have. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	float mMaximumAggroLevel;

	/** How much aggro a target needs to have in order for the creature to transition to fighting state. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	float mAggroFightThreshold;

	/** Used to accumulate stress for the creature based on damage taken. */
	UPROPERTY( EditAnywhere, Instanced, Category = "AI" )
	TArray< class UFGDamageTypeAccumulator* > mDamageTypeStressAccumulators;

	/** Curve used to increase aggro per second for a visible target based on distance towards it. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	UCurveFloat* mAggroGainRateCurve;
	
	/** Curve used to describe the rate of how fast a creature sees something based on distance. The thing is considered visible once its visibility value reaches 1.0. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	UCurveFloat* mVisibilityGainRateCurve;

	/** How much aggro per second the creature builds up for a target when they're visible. Gets multiplied with AggroGainRateCurve. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	float mAggroGainRate;

	/** Amount of aggro to reduce per second when a target is not visible. */
	UPROPERTY( EditAnywhere, Category = "AI", meta = ( UIMin = "0.0", ClampMin = "0.0" ) )
	float mAggroReductionRate;
	
	/** What family / species this creature belongs to. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	TSubclassOf< class UFGCreatureFamily > mCreatureFamily;
	
	/** Materials that may be used on arachnids */
	UPROPERTY( EditAnywhere, Category = "Arachnophobia" )
	TArray< UMaterialInstance* > mArachnophobiaModeMaterials;

	/** Is creature considered an arachnid */
	UPROPERTY( EditAnywhere, Category = "Arachnophobia" )
	bool mIsArachnid;

	/** True if optimized by the AI system */
	UPROPERTY( ReplicatedUsing = OnRep_IsEnabled )
	TEnumAsByte< EEnabled > mIsEnabled;

	/** Class of item to drop when dead */
	UPROPERTY( EditAnywhere, Category = "AI" )
	TSubclassOf< class AFGItemPickup > mItemToDrop;

	/** Array with information about different speeds that this creature can use */
	UPROPERTY( EditAnywhere, Category = "Movement" )
	TArray< FMoveSpeedPair > mMoveSpeedData;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Creature" )
	TArray< TSubclassOf<UFGItemDescriptor> > mCreatureFood;
	
private:
	/** Our controller. */
	UPROPERTY()
	class AFGCreatureController* mCreatureController;
	
	/** Should this creature be able to persist in the world */
	UPROPERTY( SaveGame, EditAnywhere, Category = "Creature" )
	bool mIsPersistent;
	
	/** Whether or not this is a passive creature. Which means it can't aggro on anything. */
	UPROPERTY( EditAnywhere, Category = "Creature" )
	bool mIsPassiveCreature;

	/** Timer handle used for killing orphan creatures ( orphan = missing a reference to a spawner ) */
	UPROPERTY()
	FTimerHandle mKillOrphanHandle;

	/** Creature health regen when in roaming or default state */
	UPROPERTY( EditAnywhere, Category="Damage")
	float mPassiveHealthRegen;

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
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	float mDayTimePctCountAsNight;

	/** The distance this creature wants to spawn at. */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	float mSpawnDistance;

	/** The distance this creature wants to despawn at. */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	float mDespawnDistance;

	/** Reference to the spawner that handles this creature */
	UPROPERTY( SaveGame )
	class AFGCreatureSpawner* mOwningSpawner;
	
	/** Whether or not this creature can be stunned at all. */
	UPROPERTY( EditAnywhere, Category = "Stun" )
	bool mCanBeStunned;
	
	/** Whether or not this creature can be stunned by damage buildup. */
	UPROPERTY( EditAnywhere, Category = "Stun" )
	bool mCanBeStunnedByDamage;

	/** How much damage needs to be dealt in order to stun the creature. */
	UPROPERTY( EditAnywhere, Category = "Stun" )
	float mStunDamageThreshold;
	
	/** How long the creature should be stunned for after receiving enough damage buildup. */
	UPROPERTY( EditAnywhere, Category = "Stun" )
	float mStunDamageDuration;

	/** How much time must pass before the creature can be stunned again. */
	UPROPERTY( EditAnywhere, Category = "Stun" )
	float mStunDamageCooldownDuration;

	/** How much to reduce the stun damage buildup per second. */
	UPROPERTY( EditAnywhere, Category = "Stun" )
	float mStunDamageReductionRate;

	/** Whether or not the creature is currently stunned. */
	UPROPERTY( ReplicatedUsing = OnRep_IsStunned )
	bool mIsStunned;

	/** Timer responsible for ending the stun. */
	FTimerHandle mStunTimerHandle;
	
	UPROPERTY( EditDefaultsOnly )
	int mAmountToEatWhenTamed = 0;
	
	UPROPERTY( EditDefaultsOnly )
	float mDefaultRotationRate = 90;

	UPROPERTY( EditDefaultsOnly )
	float mCombatRotationRate = 360;
	
#ifdef WITH_EDITOR
	mutable bool mPreviousSelected;
#endif
	int32 mCachedAgentIndex;
};

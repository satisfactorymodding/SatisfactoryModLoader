// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "ItemAmount.h"
#include "FGGamePhaseManager.generated.h"

/**
 * The old enum that defined the phases of the game. Replaced by UFGGamePhase.
 * DEPRECATED Only kept for save compatibility
 */
UENUM( BlueprintType )
enum EGamePhase : uint8
{
	EGP_EarlyGame		= 0 UMETA( DisplayName = "Establishing Phase" ),
	EGP_MidGame			= 1 UMETA( DisplayName = "Development Phase" ),
	EGP_LateGame		= 2 UMETA( DisplayName = "Expansion Phase" ),
	EGP_EndGame			= 3 UMETA( DisplayName = "Retention Phase" ),
	EGP_FoodCourt		= 4 UMETA( DisplayName = "Food Court" ),
	EGP_Victory			= 5 UMETA( DisplayName = "Victory!" ),
	// Added N/A to have a state that indicates we have migrated the save
	EGP_NA				= 6 UMETA( DisplayName = "Non Applicable" ) 
};

/**
 * Used for specifying what tiers are included in what game phase. DEPRECATED only kept while migrating the system
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FPhaseTierInfo
{
	GENERATED_BODY()

	FPhaseTierInfo() :
		GamePhase( EGP_EarlyGame ),
		LastTierOfPhase( 0 ),
		Name( FText::FromString( TEXT( "GAME_PHASE_NAME" ) ) ),
		PhaseUnlockedMessage( nullptr )
	{
	}

	/** The phase to specify tier for */
	UPROPERTY( EditDefaultsOnly )
	TEnumAsByte< EGamePhase > GamePhase;

	/** What is the last tier of the phase specified previously. */
	UPROPERTY( EditDefaultsOnly )
	int32 LastTierOfPhase;

	/** Name of this phase. */
	UPROPERTY( EditDefaultsOnly )
	FText Name;

	/** Message sent when this phase is unlocked */
	UPROPERTY( EditDefaultsOnly, Category = "Message" )
	TSubclassOf< class UFGMessageBase > PhaseUnlockedMessage;
};

/**
* This is used to specify the cost for the different phases of the game.
* DEPRECATED Only kept for save compatibility
*/
USTRUCT( BlueprintType )
struct FACTORYGAME_API FPhaseCost
{
	GENERATED_BODY()

	FPhaseCost() :
		GamePhase( EGP_EarlyGame )
	{

	}

	/** The phase to specify the cost for */
	UPROPERTY( EditDefaultsOnly, SaveGame )
	TEnumAsByte< EGamePhase > GamePhase;

	/** Cost of this tier */
	UPROPERTY( EditDefaultsOnly, SaveGame )
	TArray< FItemAmount > Cost;
};

/** Struct used to store values for the project assembly launch sequence. */
USTRUCT( BlueprintType )
struct FProjectAssemblyLaunchSequenceValue
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, SaveGame )
	uint8 Key;
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, SaveGame )
	int32 Value;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, SaveGame )
	bool IsCompleted;
};

/**
 * Represents the remaining cost information for a specific phase in the Space Elevator.
 *
 * This struct contains the item class involved, the total cost required for that item, 
 * and the remaining cost left to be fulfilled.
 */
USTRUCT(BlueprintType)
struct FRemainingPhaseCost
{
	GENERATED_BODY()

	FRemainingPhaseCost(){}

	FRemainingPhaseCost( TSubclassOf< class UFGItemDescriptor > inItemClass, int32 inTotalCost, int32 inRemainingCost ) :
		ItemClass( inItemClass ),
		TotalCost( inTotalCost ),
		RemainingCost( inRemainingCost )
	{}

	/** The class of the item that this phase cost handles. */
	UPROPERTY( Transient, BlueprintReadOnly, Category="Space Elevator|Item" )
	TSubclassOf< class UFGItemDescriptor > ItemClass = nullptr;

	/** The total cost required for this phase. */
	UPROPERTY( Transient, BlueprintReadOnly, Category="Space Elevator|Item" )
	int32 TotalCost = 0;

	/** The amount of cost left to be paid off for this phase */
	UPROPERTY( Transient, BlueprintReadOnly, Category="Space Elevator|Item" )
	int32 RemainingCost = 0;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnGamePhaseChanged, EGamePhase, gamePhase );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCurrentGamePhaseUpdated, UFGGamePhase*, currentGamePhase );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnTargetGamePhaseUpdated, UFGGamePhase*, targetGamePhase );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPayOffOnGamePhase, FRemainingPhaseCost, remainingPhaseCost );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnProjectAssemblyLaunchSequenceValuesUpdated, const TArray< FProjectAssemblyLaunchSequenceValue >&, newValues );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnGameCompleted );

UCLASS( Blueprintable, abstract, HideCategories = ( "Actor Tick", Rendering, Replication, Input, Actor ) )
class FACTORYGAME_API AFGGamePhaseManager : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:	
	/** Get the game phase manager, this should always return something unless you call it really early. */
	static AFGGamePhaseManager* Get( UWorld* world );

	/** Get the game phase manager from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "GamePhase", DisplayName = "GetGamePhaseManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGGamePhaseManager* Get( UObject* worldContext );
	
	AFGGamePhaseManager();

	// Begin Actor
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End Actor
	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
	
	/** Sets the game phase based on the index of the game phase. This is not an ideal solution but this is so we can use the
	 *  advanced game setting (FG.GameRules.SetGamePhase) which is based on an integer. Ideally settings would support objects as entries
	 *  but for now we have to do it like this.
	 *  @return true if we could set the game phase from the index
	 */
	bool SetGamePhaseFromGamePhaseIndex( int32 inGamePhaseIndex );
	/** Gets the given game phase as an index for use with the advanced game settings */
	int32 GetGamePhaseIndexFromGamePhase( class UFGGamePhase* inPhase ) const;

	/** Advances the game to the next phase if the target phase is valid. */
	void GoToNextGamePhase();

	/**
	 * Updates and broadcasts the current and target game phases.
	 * Executes if we have authority and either no current phase exists or the incoming phase is newer.
	 * If no next phase is available after updating current phase, sets mTargetGamePhase to nullptr.
	 *
	 * @param inPhase The incoming phase to consider.
	 * @return True if we could update the current game phase
	 */
	bool UpdateCurrentGamePhase( class UFGGamePhase* inPhase );

	bool IsLastGamePhaseReached() const;
	bool ReadyToGoToNextGamePhase() const;

	/** Set the game phase corresponding to the given tier */
	void SetGamePhaseForTier( int32 tier );

	/** Gives the last relevant game phase */
	void UnlockAllGamePhases();
	
	UE_DEPRECATED( 5.2, "Use GetCurrentGamePhase instead" )
	UFUNCTION( BlueprintPure, Category = "Progression" )
	EGamePhase GetGamePhase() const;
	UFUNCTION( BlueprintPure, Category = "Progression" )
	FORCEINLINE class UFGGamePhase* GetCurrentGamePhase() const { return mCurrentGamePhase; }
	/** Returns the next game phase that we are upgrading towards. Can be a nullptr if we reached the end of the game */
	UFUNCTION( BlueprintPure, Category = "Progression" )
	FORCEINLINE class UFGGamePhase* GetTargetGamePhase() const { return mTargetGamePhase; }
	UFUNCTION( BlueprintPure, Category = "Progression|Conversions", meta=(DisplayName = "ToGamePhase (EGamePhase)", CompactNodeTitle = "->", Keywords="cast convert game phase enum", BlueprintAutocast) )
	class UFGGamePhase* GetGamePhaseFromGamePhaseEnum( EGamePhase gamePhase ) const;

	/** gets the game phase name */
	UFUNCTION( BlueprintPure, Category = "Progression" )
	FText GetGamePhaseName( EGamePhase gamePhase ) const;

	/** gets the game phase number */
	UFUNCTION( BlueprintPure, Category = "Progression" )
	EGamePhase GetGamePhaseForSchematic( TSubclassOf< UFGSchematic > inSchematic );
	UFUNCTION( BlueprintPure, Category = "Progression" )
	class UFGGamePhase* GetGamePhaseFromSchematic( TSubclassOf< UFGSchematic > inSchematic );

	/**
	 * Retrieves the game phase corresponding to a given tech tier.
	 * 
	 * @param techTier The tech tier for which to find the corresponding game phase.
	 * @return A pointer to the matching UFGGamePhase object, or nullptr if not found.
	 */
	UFUNCTION( BlueprintPure, Category = "Progression" )
	UFGGamePhase* GetGamePhaseFromTechTier( int32 techTier ) const;
	UFUNCTION( BlueprintPure, Category = "Progression" )
	EGamePhase GetGamePhaseForTechTier( int32 techTier ) const;
	
	/** Returns the cost for the passed game phase */
	UFUNCTION( BlueprintCallable, Category = "Progression" )
	void GetBaseCostForGamePhase( EGamePhase gamePhase, UPARAM( ref )TArray< FItemAmount >& out_cost );

	/** Returns the cost for the passed game phase */
	UFUNCTION( BlueprintCallable, Category = "Progression" )
	void GetCostForGamePhase( EGamePhase gamePhase, UPARAM( ref )TArray< FItemAmount >& out_cost );

	/**
	 * Pays off a given amount of items in a specific game phase.
	 * If a payoff occurs, triggers the mOnPayOffOnGamePhase delegate on game thread and returns the amount paid off.
	 *
	 * @param payOff The item amount to be paid off.
	 * @param gamePhase The game phase in which the payoff occurs.
	 * @return Returns the amount successfully paid off; returns 0 if no payoff was possible.
	 */
	UFUNCTION( BlueprintCallable, Category = "Progression" )
	int32 PayOffOnTargetGamePhase( FItemAmount payOff );

	/**
	 * Gathers current and upcoming game phases based on the provided world context.
	 * If a game phase manager is found, it filters through cached phases to find relevant ones.
	 * Otherwise it returns all game phases.
	 * 
	 * @param worldContext The context from which to derive the game phase manager.
	 * @return TArray<UFGGamePhase*> List of current and remaining game phases.
	 */
	UFUNCTION( BlueprintCallable, Category = "Progression", Meta = ( DefaultToSelf = "worldContext" ) )
	static TArray<UFGGamePhase*> GetCurrentAndRemainingGamePhases( UObject* worldContext );

	/** Returns last tech tier of the given game phase */
	UFUNCTION( BlueprintPure, Category = "Progression" )
	int32 GetLastTechTierForGamePhase( EGamePhase phase ) const;
	
	UFUNCTION( BlueprintCallable, Category = "Progression" )
	void GetRemainingPhaseCosts( TArray<FRemainingPhaseCost>& out_remainingPhaseCosts );

	/** Stores a value for the project assembly launch sequence. Will override existing value if key already exists. */
	void StoreProjectAssemblyLaunchSequenceValue( const FProjectAssemblyLaunchSequenceValue& ValueToStore );

	/** Gets the current value for a key in the project assembly launch sequence. Will return -1 if no value is stored.
	 * @returns whether or not a stored value was found for the specified key.
	 */
	UFUNCTION( BlueprintPure, Category = "Progression" )
	bool GetProjectAssemblyLaunchSequenceValue( uint8 Key, FProjectAssemblyLaunchSequenceValue& PAValue ) const;
	
	UFUNCTION()
	void OnRep_CurrentGamePhase();
	UFUNCTION()
	void OnRep_TargetGamePhase();
	UFUNCTION()
	void OnRep_TargetGamePhasePaidOffCosts( TArray<FItemAmount>& previousTargetGamePhasePaidOffCosts );
	UFUNCTION()
	void OnRep_IsGameCompleted();
	UFUNCTION()
	void OnRep_ProjectAssemblyLaunchSequenceValues();

	/** Debug */
	void Debug_DumpStateToLog();

	/** Resets the game phases to the defaults. Used for resetting progression for testing. */
	void ResetGamePhase();

	/** Marks the game as completed. This means we have completed the game and launched project assembly. i.e the outro sequence has played  */
	UFUNCTION( BlueprintCallable, Category = "Progression" )
	void SetGameIsCompleted();
	/** Return true if we have completed the game and launched project assembly. i.e the outro sequence has played */
	UFUNCTION( BlueprintPure, Category = "Progression" )
	FORCEINLINE bool GetGameIsCompleted() const { return mIsGameCompleted; }

private:
	UFUNCTION()
	void SubmitGamePhaseTelemetry( UFGGamePhase* currentGamePhase );
	
public:
	/** Broadcast a notification when we pay something of on a game phase*/
	UPROPERTY( BlueprintAssignable, Category = "Progression" )
	FOnPayOffOnGamePhase mOnPayOffOnGamePhase;
	
	/** Called when the game phase is updated */
	UPROPERTY( BlueprintAssignable, Category = "Progression" )
	FOnGamePhaseChanged mOnGamePhaseChanged;

	/** Called when the current game phase is updated */
	UPROPERTY( BlueprintAssignable, Category = "Progression" )
	FOnCurrentGamePhaseUpdated mOnCurrentGamePhaseUpdated;

	/** Called when the current game phase is updated */
	UPROPERTY( BlueprintAssignable, Category = "Progression" )
	FOnTargetGamePhaseUpdated mOnTargetGamePhaseUpdated;

	/** Called when the game is completed */
	UPROPERTY( BlueprintAssignable, Category = "Progression" )
	FOnGameCompleted mOnGameCompleted;
	
	/** Called whenever the stored values for the project assembly launch sequence changes. */
	UPROPERTY( BlueprintAssignable, Category = "Progression" )
	FOnProjectAssemblyLaunchSequenceValuesUpdated mOnProjectAssemblyLaunchSequenceValuesUpdated;
	
protected:
// BEGIN DEPRECATED
	/** DEPRECATED use mCurrentGamePhase instead, Only kept for save compatibility  */
	UPROPERTY( SaveGame )
	TEnumAsByte< EGamePhase > mGamePhase = EGP_NA;

	/** DEPRECATED Only kept for save compatibility */
	UPROPERTY( SaveGame )
	TArray< FPhaseCost > mGamePhaseCosts;
// END DEPRECATED

private:
	/** All game phase assets that the we found from the asset manager.
	 * We rely on this being sorted firstly by mLastTierOfPhase and secondly by mPriority
	 */
	UPROPERTY( Transient )
	TArray<class UFGGamePhase*> mCachedGamePhases;
	
	/** The current GamePhase that is applied */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_CurrentGamePhase )
	TObjectPtr<class UFGGamePhase> mCurrentGamePhase = nullptr;

	/** The next game phase that we are upgrading towards. Can be a nullptr if we reached the end of the game */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_TargetGamePhase )
	TObjectPtr<class UFGGamePhase> mTargetGamePhase = nullptr;

	/** The amounts we paid off for the current game phase */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_TargetGamePhasePaidOffCosts )
	TArray<FItemAmount> mTargetGamePhasePaidOffCosts;

	/** Array containing stored information about the project assembly launch sequence. (Values for the buttons and levers in the UI)
	 */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_ProjectAssemblyLaunchSequenceValues )
	TArray< FProjectAssemblyLaunchSequenceValue > mPALaunchSequenceValues;

	/** True if we have completed the game and launched project assembly. i.e the outro sequence has played */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsGameCompleted )
	bool mIsGameCompleted = false;
};


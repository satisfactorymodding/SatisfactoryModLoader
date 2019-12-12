// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "ItemAmount.h"
#include "FGGamePhaseManager.generated.h"

/**
 * The three phases of the game.
 *
 * @todounlock  As I see this is not necessary, and it's not particularly modder friendly,
 *              This could be replaced by an index into the array, then we don't need to do reverse look ups and stuff. -G2, 6 mars 19
 */
UENUM( BlueprintType )
enum EGamePhase
{
	EGP_EarlyGame		= 0 UMETA( DisplayName = "Establishing Phase" ),
	EGP_MidGame			= 1 UMETA( DisplayName = "Development Phase" ),
	EGP_LateGame		= 2 UMETA( DisplayName = "Expansion Phase" ),
	EGP_EndGame			= 3 UMETA( DisplayName = "Retention Phase" ),
	EGP_FoodCourt		= 4 UMETA( DisplayName = "Food Court" ),
	EGP_Victory			= 5 UMETA( DisplayName = "Victory!" )
};

/**
 * Used for specifying what tiers are included in what game phase.
 */
USTRUCT( BlueprintType )
struct FPhaseTierInfo
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
*/
USTRUCT( BlueprintType )
struct FPhaseCost
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnGamePhaseUpdated, EGamePhase, gamePhase );

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

public:
	AFGGamePhaseManager();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	//@todoupdate Many things in here that are not const that should be.

	/** Updates the game phase number. Must be called from authority to take effect. */
	UFUNCTION( BlueprintCallable, Category = "Progression" )
	void SetGamePhase( EGamePhase newPhase );

	/** gets the game phase number */
	UFUNCTION( BlueprintPure, Category = "Progression" )
	FORCEINLINE EGamePhase GetGamePhase() { return mGamePhase; }

	/** gets the game phase name */
	UFUNCTION( BlueprintPure, Category = "Progression" )
	FText GetGamePhaseName( EGamePhase gamePhase ) const;

	/** gets the game phase number */
	UFUNCTION( BlueprintPure, Category = "Progression" )
	EGamePhase GetGamePhaseForSchematic( TSubclassOf< UFGSchematic > inSchematic );

	/** gets the game phase number */
	UFUNCTION( BlueprintPure, Category = "Progression" )
	EGamePhase GetGamePhaseForTechTier( int32 techTier );
	
	/** Returns the cost for the passed game phase */
	UFUNCTION( BlueprintCallable, Category = "Progression" )
	void GetBaseCostForGamePhase( EGamePhase gamePhase, UPARAM( ref )TArray< FItemAmount >& out_cost );

	/** Returns the cost for the passed game phase */
	UFUNCTION( BlueprintCallable, Category = "Progression" )
	void GetCostForGamePhase( EGamePhase gamePhase, UPARAM( ref )TArray< FItemAmount >& out_cost );

	/** Pays off on a game phase */
	UFUNCTION( BlueprintCallable, Category = "Progression" )
	int32 PayOffOnGamePhase( FItemAmount payOff, EGamePhase gamePhase );

	/** Rep notify for mGamePhase */
	UFUNCTION()
	void OnRep_GamePhase();

	/** Resets the game phases to the defaults. Used for resetting progression for testing. */
	void ResetGamePhase();

protected:
	/** Current GamePhase */
	UPROPERTY( EditDefaultsOnly, SaveGame, ReplicatedUsing = OnRep_GamePhase, Category = "Progression" )
	TEnumAsByte< EGamePhase > mGamePhase;

	/** Specifies what game phases are connected to what tiers */
	UPROPERTY( EditDefaultsOnly, Category = "Progression" )
	TArray< FPhaseTierInfo > mGamePhaseTierInfo;

	/** Speciefies what the different tiers cost */
	UPROPERTY( EditDefaultsOnly, SaveGame, Replicated, Category = "Progression" )
	TArray< FPhaseCost > mGamePhaseCosts;	
public: 
	/** Called when the game phase is updated */
	UPROPERTY( BlueprintAssignable, Category = "Recipe" )
	FOnGamePhaseUpdated mOnGamePhaseChanged;
};

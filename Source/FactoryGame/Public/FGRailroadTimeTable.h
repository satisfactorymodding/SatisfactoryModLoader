// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/Info.h"
#include "FGSaveInterface.h"
#include "FGTrainDockingRules.h"
#include "FGRailroadTimeTable.generated.h"

/**
 * A stop entry in the time table.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FTimeTableStop
{
	GENERATED_BODY()
public:
	/** Where to stop. */
	UPROPERTY( SaveGame, BlueprintReadWrite, VisibleAnywhere )
	class AFGTrainStationIdentifier* Station = nullptr;

	/** Station Rules */
	UPROPERTY( SaveGame, BlueprintReadWrite, VisibleAnywhere )
	FTrainDockingRuleSet DockingRuleSet;
};

/**
 * Object containing a trains time table and where it is right now.
 */
UCLASS( BlueprintType )
class FACTORYGAME_API AFGRailroadTimeTable : public AInfo, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGRailroadTimeTable();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor Interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Add a stop to the time table. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|TimeTable" )
	bool AddStop( int32 index, const FTimeTableStop& stop );

	/** Remove a stop from the time table. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|TimeTable" )
	void RemoveStop( int32 index );

	/** Get the number of stops. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|TimeTable" )
	FORCEINLINE int32 GetNumStops() const { return mStops.Num(); }

	/** Get the number of stops. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|TimeTable" )
	FORCEINLINE int32 GetMaxNumStops() const { return MAX_STOPS; }

	/** Get all stops in the time table. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Railroad|TimeTable" )
	void GetStops( TArray< FTimeTableStop >& out_stops ) const;

	/** Set all stops in the time table. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|TimeTable" )
	bool SetStops( const TArray< FTimeTableStop >& stops );

	/**
	 * Is the index a valid stop.
	 * Checks if the index is valid and the 'Stop' actor is valid. 
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|TimeTable" )
	bool IsValidStop( int32 index ) const;

	/**
	 * Get the given stop.
	 * @return The stop at index, valid or invalid. If the index is invalid it returns an empty stop.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|TimeTable" )
	FTimeTableStop GetStop( int32 index ) const;

	/** @return Current stop the train is at or heading to. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|TimeTable" )
	FORCEINLINE int32 GetCurrentStop() const { return mCurrentStop; }

	/** @param index Set the stop the train is heading to. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|TimeTable" )
	void SetCurrentStop( int32 index );

	/** Increment the current stop to the next one in order. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|TimeTable" )
	void IncrementCurrentStop();

	/** Purge the list of any invalid stops. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|TimeTable" )
	void PurgeInvalidStops();
	
	/** Get the docking rules for a given stop */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|RailRoad|TimeTable" )
	void GetDockingRuleSetForStop( int32 index, FTrainDockingRuleSet& out_ruleSet ) const;

private:
	const int32 MAX_STOPS = 100;

	/** Array of destinations this train will visit. */
	UPROPERTY( SaveGame, Replicated, VisibleAnywhere, Category = "Time Table" )
	TArray< FTimeTableStop > mStops;

	/** Current stop the train is at or heading to. */
	UPROPERTY( SaveGame, Replicated, VisibleAnywhere, Category = "Time Table" )
	int32 mCurrentStop;
};

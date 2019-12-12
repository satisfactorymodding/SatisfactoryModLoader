// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "GameFramework/Info.h"
#include "FGSaveInterface.h"
#include "FGRailroadTimeTable.generated.h"

/**
 * A stop entry in the time table.
 */
USTRUCT( BlueprintType )
struct FTimeTableStop
{
	GENERATED_BODY()
public:
	/** Where to stop. */
	UPROPERTY( SaveGame, BlueprintReadWrite )
	class AFGTrainStationIdentifier* Station = nullptr;

	/** Time to stay. */
	UPROPERTY( SaveGame, BlueprintReadWrite )
	float Duration = 0.0f;
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
	void SetCurrentStop( int32 index ) { mCurrentStop = index; }

	/**
	 * @param index Which stop to modify, this function does nothing if invalid.
	 * @param Duration How long the train will stay at the station (seconds)
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|TimeTable" )
	void SetStopDuration( int32 index, float duration ); //@todotrains remove if unused after pontus is finished.

private:
	const int32 MAX_STOPS = 100;

	/** Array of destinations this train will visit. */
	UPROPERTY( SaveGame, Replicated )
	TArray< FTimeTableStop > mStops;

	/** Current stop the train is at or heading to. */
	UPROPERTY( SaveGame )
	int32 mCurrentStop;
};

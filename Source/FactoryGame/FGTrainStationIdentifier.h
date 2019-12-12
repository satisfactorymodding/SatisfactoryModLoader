// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"
#include "TextProperty.h"
#include "GameFramework/Info.h"
#include "FGSaveInterface.h"
#include "FGTrainStationIdentifier.generated.h"

/**
 * Identifier for a train station that is always available on server and clients.
 */
UCLASS()
class FACTORYGAME_API AFGTrainStationIdentifier : public AInfo, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGTrainStationIdentifier();

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

	/** Get the station actor, only valid on server. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|StationIdentifier" )
	class AFGBuildableRailroadStation* GetStation() const { return mStation; }

	/** Get the name of this station. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|StationIdentifier" )
	FText GetStationName() const { return mStationName; }

	/** Set the name of this station, must be called on server. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|StationIdentifier" )
	void SetStationName( const FText& text );

	/** Get the track this station belongs to. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|StationIdentifier" )
	int32 GetTrackGraphID() const { return mTrackGraphID; }

private:
	UFUNCTION()
	void OnRep_StationName();

public:
	/** The station this info represents. */
	UPROPERTY( SaveGame, Replicated )
	class AFGBuildableRailroadStation* mStation;

	/** The track this station is on. */
	UPROPERTY( Replicated )
	int32 mTrackGraphID;

	/** Cached here for clients. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_StationName )
	FText mStationName;
};

#pragma once
#include "UObject/Interface.h"
#include "UObject/Class.h"

#include "Buildables/FGBuildableRailroadTrack.h"
#include "FGRailroadInterface.generated.h"

/**
* For blueprint support of the interface, we will never add anything to it, just use it to have a UCLASS to be able to access.
*/
UINTERFACE( Blueprintable )
class UFGRailroadInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGRailroadInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 
};

/**
* @brief Interface for all buildables that can be placed on the railroad track.
*/
class IFGRailroadInterface
{
	GENERATED_IINTERFACE_BODY()

	/** When this is registered on a track. */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Railroad|Interface" )
	void RegisteredOnTrack( const FRailroadTrackPosition& position );

	/** When this is unregistered from a track, e.g. the track is dismantled. */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Railroad|Interface" )
	void UnregisteredFromTrack();

	/** Get the track location. */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "FactoryGame|Railroad|Interface" )
	FRailroadTrackPosition GetTrackPosition() const;

	/** Get the track id we're on. */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "FactoryGame|Railroad|Interface" )
	int32 GetTrackGraphID() const;
};

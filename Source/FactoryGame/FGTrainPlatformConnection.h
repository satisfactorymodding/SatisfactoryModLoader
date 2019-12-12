// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGRailroadTrackConnectionComponent.h"
#include "FGConnectionComponent.h"
#include "FGTrainPlatformConnection.generated.h"

/**
*	Enum indicating the direction to or from a station. Stations should specify their tail direct via the ETPC_Out type
*/
UENUM(BlueprintType)
enum class ETrainPlatformConnectionType : uint8
{
	ETPC_Out				UMETA( DisplayName = "Output" ),
	ETPC_In					UMETA( DisplayName = "Input" ),
	ETPC_Neutral			UMETA( DisplayName = "Neutral" )
};

/**
 *	Component for detecting overlap and direction of platforms for snapping and connection referencing
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGTrainPlatformConnection : public UFGConnectionComponent
{
	GENERATED_BODY()
	
public:
	
	// Specify a connection for this platform connection to connect to and adjust its direction to match the connection
	void AttachToConnection( UFGTrainPlatformConnection* connectTo );

	// Sets the platform this component is connecting to. Does not modify connection direction
	void SetConnectedTo( UFGTrainPlatformConnection* connectedBy );

	// Detach this connection from another (when another platform is dismantled tx.)
	void DetachFromConnection();

	// Get the connection that this is connected to
	UFGTrainPlatformConnection* GetConnectedTo() const { return mConnectedTo; }

	/** Specify the status of this connection ( is it an incoming, outgoing, or pending ) 
	*	@note This function is also called when SetConnectedPlatform is called. Possibly a move out of public space if it is not needed explicitly.
	*/
	void SetConnectionType( ETrainPlatformConnectionType connectionStatus );

	/** Get The current status of this connection */
	ETrainPlatformConnectionType GetConnectionType() const { return mPlatformConnectionStatus; }

	/** Force the component into the reverse direction */
	void ReverseComponentDirection();

	/** Set the component direction explicity */
	void SetComponentDirection( uint8 componentDirection );

	/** Get the direction of the connection */
	uint8 GetComponentDirection() const { return mComponentDirection; }

	/** Get owning FGBuildableTrainPlatform */
	class AFGBuildableTrainPlatform* GetPlatformOwner();

	/** Assign the railroad connection pointed to by this platform connection 
	*	@note Each platform connection should have exactly one RailroadTrackConnection they link to.
	*/
	void SetRailroadConnectionReference( UFGRailroadTrackConnectionComponent* railroadConnection ) { mRailroadTrackConnection = railroadConnection; }

	/** Return a reference to the train platform interface this connection is a part of */
	UFGRailroadTrackConnectionComponent* GetRailroadConnectionReference() const { return mRailroadTrackConnection; } 
	
	/** Is this platform connected to another one? */
	FORCEINLINE bool IsConnected() const { return !(mConnectedTo == nullptr); }

	/** TEMP: Will remove (TM) */
	void DrawDebugDirection();
	FTimerHandle mDrawDebugTimerHandle;

protected:
	/** This bool indicates an arbitrary direction of this platform. It is used for stepping through platforms 
	*	Platforms that connect must have mismatched values for their snapped components ( ie: 1 -> 0 || 0 -> 1 && !(1 -> 1) etc. )
	*/
	UPROPERTY( SaveGame )
	uint8 mComponentDirection : 1;

	/** Enum indicating the status of this connection */
	UPROPERTY( EditDefaultsOnly, Category = "Platform Connection" )
	ETrainPlatformConnectionType mPlatformConnectionStatus;

	/** store a reference to the owner of this connection as a FGBuildableTrainPlatform, not a UProperty as this is our Owning actor cached so we don't need to keep casting */
	UPROPERTY( SaveGame )
	class AFGBuildableTrainPlatform* platformOwner;

private:
	/** Stores a reference to the track connection (Not a Uproperty because the reference exists in the railroad track) */
	UPROPERTY( SaveGame )
	UFGRailroadTrackConnectionComponent* mRailroadTrackConnection;

	/** Stores a reference to the connected platform component, if there is one (Not a UProperty as this is just a reference to an external component) */
	UPROPERTY( SaveGame )
	UFGTrainPlatformConnection* mConnectedTo;

};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGSignTypes.h"
#include "FGRemoteCallObject.h"
#include "Buildables/FGBuildableWidgetSign.h"
#include "Buildables/FGBuildablePixelSign.h"
#include "FGSignSubsystem.generated.h"

class UTextureRenderTarget2D;

/**
*	This Struct handles serializing net requests from clients for X number of signs and their data as well
*	as the Server's response to those requests. Clients send an array of SignBuildables that their subsystem
*	has determined to be the highest priority. When the Server receives the request, it in turn serializes 
*	the corresponding sign data and sends the payload back to the client.
*	In this way we can optimize out some data ( notably the alpha channel for colors ) and send many signs
*	in a single RPC request. While a request is active (client has not received a response) the client will 
*	not send further requests to ensure we don't overflow our reliable buffer.
*/
USTRUCT()
struct FSignRPC_Data
{
	GENERATED_BODY()

	FSignRPC_Data() = default;
	FSignRPC_Data( bool isServer ) : IsServer( isServer ) {}

	bool NetSerialize( FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess );
	void AddPendingSign( AFGBuildableWidgetSign* sign );

	// When receiving on Server this array will be filled by NetSerialize
	UPROPERTY()
	TArray< AFGBuildableWidgetSign* > Signs;

	// When receiving on client this map will be generated by NetSerialize
	UPROPERTY( NotReplicated )
	TMap< AFGBuildableWidgetSign*, FPrefabSignData > SignToDataMap;

	bool IsServer{false};
};

template<>
struct TStructOpsTypeTraits< FSignRPC_Data > : public TStructOpsTypeTraitsBase2< FSignRPC_Data >
{
	enum
	{
		WithNetSerializer = true,
	};
};

/*
* Passed to server from client to remotely set a signs data. This struct is very similar to the above bulk request RPC_data and one could
* theoretically reuse / modify that RPC_data struct to work for clients to send data. However, that would make the logic a fair bit more messy
* and more difficult to debug and understand. This is cleaner even though the code is very similar
*/
USTRUCT()
struct FClientSetSignData
{
	GENERATED_BODY()

public:
	bool NetSerialize( FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess );

	UPROPERTY()
	AFGBuildableWidgetSign* Sign;

	UPROPERTY()
	FPrefabSignData SignData;
};

template<>
struct TStructOpsTypeTraits< FClientSetSignData > : public TStructOpsTypeTraitsBase2< FClientSetSignData >
{
	enum
	{
		WithNetSerializer = true,
	};
};


UCLASS()
class FACTORYGAME_API UFGSignDataRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGSignDataRemoteCallObject = false;

	// Request Block of sign data's for X number of signs from the server
	UFUNCTION( Server, Reliable )
	void Server_RequestSignData( FSignRPC_Data signRPCData );

	// Respond to client with block of sign data and their buildable sign
	UFUNCTION( Client, Reliable )
	void Client_RequestSignDataResponse( FSignRPC_Data signRPCData );
	
	// Called by client to set the sign data on server
	UFUNCTION( Server, Reliable )
	void Server_SetSignData( FClientSetSignData clientData );

};

USTRUCT()
struct FACTORYGAME_API FSortedPendingSign
{
	GENERATED_BODY()

public:
	FSortedPendingSign() { Sign = nullptr; SqDistanceToPlayer = FLT_MAX; }
	FSortedPendingSign( AFGBuildableWidgetSign* pendingSign ) { Sign = pendingSign; SqDistanceToPlayer = FLT_MAX; }

	bool operator<( const FSortedPendingSign& other ) const { return SqDistanceToPlayer < other.SqDistanceToPlayer; }

	UPROPERTY()
	AFGBuildableWidgetSign* Sign;

	// Distance to the player. Will be updated during tick / before requesting data
	float SqDistanceToPlayer = FLT_MAX;
};

USTRUCT()
struct FACTORYGAME_API FMappedSignData
{
	GENERATED_BODY()

	bool bIsRelevant = true;
	
	uint32 PresetGUID = 0;
	
	UPROPERTY()
	UMaterialInstanceDynamic* mMaterialInstance = nullptr;
	
	UPROPERTY()
	class UWidgetComponent* mRootWidgetComponent = nullptr;
	
	FMappedSignData(UMaterialInstanceDynamic* InMaterial, UWidgetComponent* InWidget)
	{
		mMaterialInstance = InMaterial;
		mRootWidgetComponent = InWidget;
	}
	FMappedSignData()
	{
		mMaterialInstance = nullptr;
		mRootWidgetComponent = nullptr;
	}

	void AddOwner( AFGBuildableWidgetSign* NewSign )
	{
		Owners.Add( NewSign );
	}

	void RemoveOwner( AFGBuildableWidgetSign* RemovedSign )
	{
		const int32 Index = Owners.IndexOfByKey( RemovedSign );
		if(Index != INDEX_NONE)
		{
			Owners.RemoveAt( Index,1,true );
		}
	}

	int32 GetNumOwners() const { return Owners.Num(); }
	AFGBuildableWidgetSign* GetWidgetOwner() const					{ return Owners.IsValidIndex( 0 ) ? Owners[0] : nullptr; }
	bool DoesContainSign(const AFGBuildableWidgetSign* Sign) const	{ return Owners.Contains( Sign); }
	const TArray<AFGBuildableWidgetSign*>& GetOwnersConst()			{ return Owners; }
private:
	/* First buildable will own the widget, must be modified through Add and Remove Owner. */
	UPROPERTY()
	TArray<AFGBuildableWidgetSign*> Owners;


};

/**
 * Subsystem to sign management and client replication
 */
UCLASS()
class FACTORYGAME_API AFGSignSubsystem : public AFGSubsystem
{
	GENERATED_BODY()

public:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Get the circuit subsystem. */
	static AFGSignSubsystem* Get( UWorld* world );

	/** Get the circuit subsystem */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGSignSubsystem* GetSignSubsystem( UObject* worldContext );

	AFGSignSubsystem();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	// End AActor interface

	/** Updates all signs and their relative distance to the player */
	void UpdateAndSortPendingSigns();

	/** Called on BeginPlay of sign actors to add themselves to the tracking list */
	void AddWidgetSign( AFGBuildableWidgetSign* widgetSign );

	/** Called on EndPlay of sign actors to remove themselves from the tracking list */
	void RemoveWidgetSign( AFGBuildableWidgetSign* widgetSign );

	/** Called from the buildable signs themselves when their data version flag is incremented */
	void NotifySignDataDirty( AFGBuildableWidgetSign* widgetSign );

	/** Called from the remote call object on client to notify that a payload was received */
	void OnClientDataReceived() { mHasPendingClientRequest = false; }

	/** Called in Begin play of pixel sign actors to add themselves to the tracking list */
	void AddPixelSign( AFGBuildablePixelSign* pixelSign );

	/** Called on EndPlay of pixel sign actors to remove themselves from the tracking list */
	void RemovePixelSign( AFGBuildablePixelSign* pixelSign );

	/* When we do have this preset pooled we can fetch that data.*/
	bool DoesSamePresetExists(uint32 GUID, FMappedSignData*& OutData);

	/* Add a new preset to the managed pool.*/
	void RegisterNewPreset(AFGBuildableWidgetSign* Sign, uint32 GUID, UWidgetComponent* Widget, UMaterialInstanceDynamic* InMaterial);

	void UpdatePresetMaterialInstance(uint32 GUID, const TFunctionRef<void(class UWidgetComponent* InWidgetComponent, UMaterialInstanceDynamic* InMaterialInstance ) >& UpdateFunction);

	void ResolveRemoved(AFGBuildableWidgetSign* Sign, uint32 GUID);

 	void UpdateRelevancy();

	UWidgetComponent* GetWidgetByGUID(uint32 GUID);

	//<FL>[KonradA]
	FORCEINLINE bool HasQueriedBlockedUsers() { return bHasQueriedBlockedUsers; };
	//</FL>
private:
	/** Tracks whether the subsystem is waiting for a sign data request is pending from the server. If so, no new requests will be issued */
	bool mHasPendingClientRequest;
	double mLastClientRequestTime;
	double mPendingClientRequestTimeout = 5.0;

	/** Array of every buildable. These are added from the signs begin play */
	UPROPERTY()
	TArray< AFGBuildableWidgetSign* > mAllWidgetSigns;

	/** The current list of signs that the player does not have the data for. These are sorted by distance to player so we always request those closest to us */
	UPROPERTY()
	TArray< FSortedPendingSign > mPendingSortedSigns;

	/* Map of GUID for unique sign setup and ptr to the render target.
	 * The material instances in FMappedSignData have the subsystem as outer to avoid GC. */
	//UPROPERTY()
	//TMap<uint32,FMappedSignData> mUniqueSignToRenderTargetSetup;

	UPROPERTY()
	TArray<FMappedSignData> mUniqueSignToRenderTargetData; 

	//////////////////////////////////////////////////////
	/// Pixel Sign Members
	UPROPERTY()
	AActor* mSignPixelInstanceActor;

	UPROPERTY()
	TMap< int32, UFGSignPixelInstanceManager* > mPixelInstanceManagerMap;

	TArray< AFGBuildablePixelSign* > mAllPixelSigns;

	// <FL>[KonradA]
	bool bHasQueriedBlockedUsers;
	FDelegateHandle hOnQueryAllBlockedComplete;
	// </FL>
};

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

public:
	FSignRPC_Data() {}
	FSignRPC_Data( bool isServer ) : 
	IsServer( isServer ) {}

	static const int32 REP_NUM_MAX = 2048;

	bool NetSerialize( FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess )
	{
		bOutSuccess = true;
		if( Ar.IsSaving() )
		{
			// If this is coming from the server to client?
			Ar << IsServer;
			// The number of Signs included in this payload
			uint32 numSigns = (uint32)Signs.Num();
			Ar << numSigns;

			if( IsServer )
			{
				/**
				* Per Sign ->
				*	NETGUID : Used to identify the Sign Buildable across the network
				*	TSubclass< UUserWidget > : The prefab layout to use
				*	FString TextKey
				*		FString TextData ... ( Num Keys / Num Elements)
				*	FString IconKey
				*		int32 IconData ... ( Num Keys / Num Elements)
				*	Int32 Foreground_R
				*	Int32 Foregroudn_G
				*	Int32 Foreground_B
				*	Int32 Background_R
				*	Int32 Background_G
				*	Int32 Background_B	
				*	float Emissive
				*	float Glossiness
				*/
				for( uint32 i = 0; i < numSigns; ++i )
				{
					// NET Guid that defines this sign buildable
					FNetworkGUID netGuid( Map->GetNetGUIDFromObject( Signs[ i ] ) );
					Ar << netGuid;

					FPrefabSignData data; 
					Signs[i]->GetSignPrefabData( data );
					
					// Send the prefab layout class
					Ar << data.PrefabLayout;

					// All Text Elements
					TArray< FString > textElementKeys;
					data.TextElementData.GetKeys( textElementKeys );
					uint32 numTextElements = (uint32)textElementKeys.Num();

					Ar << numTextElements;

					for( FString key : textElementKeys )
					{
						FString textData = data.TextElementData[ key ];
						Ar << key;
						Ar << textData;
					}

					// All Icon Elements
					TArray< FString > iconElementKeys;
					data.IconElementData.GetKeys( iconElementKeys );
					uint32 numIconElements = (uint32)iconElementKeys.Num();

					Ar << numIconElements;

					for( FString key: iconElementKeys )
					{
						int32 iconData = data.IconElementData[ key ];
						Ar << key;
						Ar << iconData;
					}

					// Foreground 
					FLinearColor color = data.ForegroundColor;
					Ar << color.R;
					Ar << color.G;
					Ar << color.B;
					// Background
					color = data.BackgroundColor;
					Ar << color.R;
					Ar << color.G;
					Ar << color.B;
					// Auxilary
					color = data.AuxiliaryColor;
					Ar << color.R;
					Ar << color.G;
					Ar << color.B;

					// Emissive
					Ar << data.Emissive;
					// Glossiness
					Ar << data.Glossiness;
				}
			}
			else
			{
				// On Client we only ever send an array of NET GUIDS representing the Sign Buildables we are seeking the data to
				for( uint32 i = 0; i < numSigns; ++i )
				{
					FNetworkGUID netGuid = Map->GetNetGUIDFromObject( Signs[ i ] );
					Ar << netGuid;
				}
			}
		}
		else
		{
			// LOADING (Reading)
			Ar << IsServer;

			uint32 numSigns = 0;
			Ar << numSigns;

			if( IsServer == false )
			{
				// On server we want to take the array of NETGUIDS passed from the client and resolve them so this data payload has a valid array of sign buildables

				// Safety make sure its empty
				Signs.Empty();
				for( uint32 i = 0; i < numSigns; ++i )
				{
					FNetworkGUID netGuid;
					Ar << netGuid;
					AFGBuildableWidgetSign* sign = Cast< AFGBuildableWidgetSign >( Map->GetObjectFromNetGUID( netGuid, true ) );

					if( sign )
					{
						Signs.Add( sign );
					}
				}
			}
			else
			{
				// On client we want to turn the payload into a TMap with resolved netGuids pointing to their PrefabSignData

				// Safety to make sure theres no stale data
				SignToDataMap.Empty();
				for( uint32 i = 0; i < numSigns; ++i )
				{
					// Filled as we deserialize the incoming payload
					FPrefabSignData data;
					
					FNetworkGUID netGuid;
					Ar << netGuid;
					AFGBuildableWidgetSign* sign = Cast< AFGBuildableWidgetSign >( Map->GetObjectFromNetGUID( netGuid, true ) );

					TSubclassOf< UUserWidget > prefabClass;
					Ar << prefabClass;

					data.PrefabLayout = prefabClass;

					uint32 numTextElements = 0;
					Ar << numTextElements;

					for( uint32 count = 0; count < numTextElements; ++count )
					{
						FString textName;
						FString textData;

						Ar << textName;
						Ar << textData;

						data.TextElementData.Add( TTuple< FString, FString >( textName, textData ) );
					}

					uint32 numIconElements = 0;
					Ar << numIconElements;

					for( uint32 count = 0; count < numIconElements; ++count )
					{
						FString iconName;
						int32 iconData;

						Ar << iconName;
						Ar << iconData;

						data.IconElementData.Add( TTuple< FString, int32 >( iconName, iconData ) );
					}

					float R,G,B;
					Ar << R;
					Ar << G;
					Ar << B;
					data.ForegroundColor = FLinearColor( R, G, B, 1.f );

					Ar << R;
					Ar << G;
					Ar << B;
					data.BackgroundColor = FLinearColor( R, G, B, 1.f);

					Ar << R;
					Ar << G;
					Ar << B;
					data.AuxiliaryColor = FLinearColor( R, G, B, 1.f );

					float val = 0.f;
					// Emissive
					Ar << val;
					data.Emissive = val;

					// Glossiness
					Ar << val;
					data.Glossiness = val;

					// Flag this as coming from replication so the client doesn't trigger a SetSignData RPC on the server
					data.IsFromReplication = true;

					SignToDataMap.Add( TTuple< AFGBuildableWidgetSign*, FPrefabSignData >( sign, data ) );

				}

			}
		}

		return bOutSuccess;
	}

	void AddPendingSign( AFGBuildableWidgetSign* sign ) 
	{
		Signs.AddUnique( sign );
	}

public:

	// When receiving on Server this array will be filled by NetSerialize
	UPROPERTY()
	TArray< AFGBuildableWidgetSign* > Signs;

	// When receiving on client this map will be generated by NetSerialize
	UPROPERTY()
	TMap< AFGBuildableWidgetSign*, FPrefabSignData > SignToDataMap;

	bool IsServer;
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

	bool NetSerialize( FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess )
	{
		bOutSuccess = true;

		if( Ar.IsSaving() )
		{
			FNetworkGUID netGuid = Map->GetNetGUIDFromObject( Sign );
			Ar << netGuid;
			Ar << SignData.PrefabLayout;

			// All Text Elements
			TArray< FString > textElementKeys;
			SignData.TextElementData.GetKeys( textElementKeys );
			uint32 numTextElements = (uint32)textElementKeys.Num();

			Ar << numTextElements;

			for( FString key: textElementKeys )
			{
				FString textData = SignData.TextElementData[ key ];
				Ar << key;
				Ar << textData;
			}

			// All Icon Elements
			TArray< FString > iconElementKeys;
			SignData.IconElementData.GetKeys( iconElementKeys );
			uint32 numIconElements = (uint32)iconElementKeys.Num();

			Ar << numIconElements;

			for( FString key: iconElementKeys )
			{
				int32 iconData = SignData.IconElementData[ key ];
				Ar << key;
				Ar << iconData;
			}

			// Foreground
			FLinearColor color = SignData.ForegroundColor;
			Ar << color.R;
			Ar << color.G;
			Ar << color.B;
			// Background
			color = SignData.BackgroundColor;
			Ar << color.R;
			Ar << color.G;
			Ar << color.B;
			// Auxilary
			color = SignData.AuxiliaryColor;
			Ar << color.R;
			Ar << color.G;
			Ar << color.B;

			// Emissive
			Ar << SignData.Emissive;
			// Glossiness
			Ar << SignData.Glossiness;
		}
		else
		{
			FNetworkGUID netGuid;
			Ar << netGuid;
			Sign = Cast< AFGBuildableWidgetSign >( Map->GetObjectFromNetGUID( netGuid, true ) );

			TSubclassOf< UUserWidget > prefabClass;
			Ar << prefabClass;

			SignData.PrefabLayout = prefabClass;

			uint32 numTextElements = 0;
			Ar << numTextElements;

			for( uint32 count = 0; count < numTextElements; ++count )
			{
				FString textName;
				FString textData;

				Ar << textName;
				Ar << textData;

				SignData.TextElementData.Add( TTuple< FString, FString >( textName, textData ) );
			}

			uint32 numIconElements = 0;
			Ar << numIconElements;

			for( uint32 count = 0; count < numIconElements; ++count )
			{
				FString iconName;
				int32 iconData;

				Ar << iconName;
				Ar << iconData;

				SignData.IconElementData.Add( TTuple< FString, int32 >( iconName, iconData ) );
			}

			float R, G, B;
			Ar << R;
			Ar << G;
			Ar << B;
			SignData.ForegroundColor = FLinearColor( R, G, B, 1.f );

			Ar << R;
			Ar << G;
			Ar << B;
			SignData.BackgroundColor = FLinearColor( R, G, B, 1.f );

			Ar << R;
			Ar << G;
			Ar << B;
			SignData.AuxiliaryColor = FLinearColor( R, G, B, 1.f );

			float val = 0.f;
			// Emissive
			Ar << val;
			SignData.Emissive = val;

			// Glossiness
			Ar << val;
			SignData.Glossiness = val;
			
		}

		return bOutSuccess;
	};

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


private:
	

	/** Tracks whether the subsystem is waiting for a sign data request is pending from the server. If so, no new requests will be issued */
	bool mHasPendingClientRequest;

	/** Array of every buildable. These are added from the signs begin play */
	UPROPERTY()
	TArray< AFGBuildableWidgetSign* > mAllWidgetSigns;

	/** The current list of signs that the player does not have the data for. These are sorted by distance to player so we always request those closest to us */
	UPROPERTY()
	TArray< FSortedPendingSign > mPendingSortedSigns;

	//////////////////////////////////////////////////////
	/// Pixel Sign Members
	UPROPERTY()
	AActor* mSignPixelInstanceActor;

	UPROPERTY()
	TMap< int32, UFGSignPixelInstanceManager* > mPixelInstanceManagerMap;

	TArray< AFGBuildablePixelSign* > mAllPixelSigns;


};

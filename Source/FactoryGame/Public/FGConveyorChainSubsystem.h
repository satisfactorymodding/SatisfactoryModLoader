// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "FGConveyorChainActor.h"
#include "FGSubsystem.h"
#include "FGRemoteCallObject.h"

#include "FGConveyorChainSubsystem.generated.h"

class AFGConveyorChainActor;

USTRUCT()
struct FConveyorItemSpacingRange
{
	GENERATED_BODY()

	FConveyorItemSpacingRange() {}
	FConveyorItemSpacingRange( int32 startIndex, int32 endIndex, float firstItemPosition ) :
		StartIndex( startIndex ),
		EndIndex( endIndex ),
		FirstItemPosition( firstItemPosition )
	{}
	
	friend FArchive& operator<< ( FArchive& ar, FConveyorItemSpacingRange& spacingRange );
	
	int32 StartIndex = INDEX_NONE; //Inclusive
	int32 EndIndex = INDEX_NONE; // Exclusive
	float FirstItemPosition = 0.f;
	float DistanceSpacing = 0.f;
	
	static constexpr int32 NetSizeBits = (sizeof( StartIndex ) + sizeof( EndIndex ) + sizeof( FirstItemPosition ) + sizeof( DistanceSpacing )) * 8;
};

USTRUCT()
struct FConveyorItemDescRange
{
	GENERATED_BODY()

	FConveyorItemDescRange() {}
	FConveyorItemDescRange( int32 startIndex, int32 endIndex, TSubclassOf< UFGItemDescriptor > itemDesc ) :
		StartIndex( startIndex ),
		EndIndex( endIndex ),
		ItemDesc( itemDesc )
	{}
	
	friend FArchive& operator<< ( FArchive& ar, FConveyorItemDescRange& spacingRange );
	
	int32 StartIndex = INDEX_NONE; //Inclusive
	int32 EndIndex = INDEX_NONE; // Exclusive
	TSubclassOf< UFGItemDescriptor > ItemDesc = nullptr;

	static constexpr int32 NetSizeBits = (sizeof( StartIndex ) + sizeof( EndIndex ) + sizeof( ItemDesc )) * 8;
};

USTRUCT()
struct FConveyorChainItemRPCData
{
	GENERATED_BODY()

	bool NetSerialize( FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess );

	
	UPROPERTY()
	TArray< AFGConveyorChainActor* > ChainActors;

	// The Remote call object that sent this RPC data request
	UPROPERTY()
	UFGConveyorChainRemoteCallObject* ChainRCO;

	// The chain subsystem (for looking up item class indices)
	UPROPERTY()
	AFGConveyorChainSubsystem* ChainSubsystem;

	UPROPERTY()
	class APlayerController* PlayerController;

	// True if data originates from server. This is used because both client and server save and load the data
	bool IsServerData = false;
};

template<>
struct TStructOpsTypeTraits< FConveyorChainItemRPCData > : public TStructOpsTypeTraitsBase2< FConveyorChainItemRPCData >
{
	enum
	{
		WithNetSerializer = true,
	};
};

USTRUCT()
struct FConveyorChainSegmentRPCData
{
	GENERATED_BODY()

	bool NetSerialize( FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess );
	
	UPROPERTY()
	TArray< AFGConveyorChainActor* > ChainActors;

	UPROPERTY()
	UFGConveyorChainRemoteCallObject* ChainRCO;

	bool IsServerData = false;
};

template<>
struct TStructOpsTypeTraits< FConveyorChainSegmentRPCData > : public TStructOpsTypeTraitsBase2< FConveyorChainSegmentRPCData >
{
	enum
	{
		WithNetSerializer = true,
	};
};

UCLASS()
class FACTORYGAME_API UFGConveyorChainRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }
	
	// Client requests from server an update on the items for the given conveyor chains
	UFUNCTION( Server, Reliable )
	void Server_RequestChainItemUpdate( const FConveyorChainItemRPCData& chainData );
	
	UFUNCTION( Client, Reliable )
	void Client_RespondChainItemUpdate( const FConveyorChainItemRPCData& chainData );

	UFUNCTION( Server, Reliable )
	void Server_RequestChainSegmentData( const FConveyorChainSegmentRPCData& segmentData );

	UFUNCTION( Client, Reliable )
	void Client_RespondChainSegmentData( const FConveyorChainSegmentRPCData& segmentData );

	void SetPendingItemTransferData( AFGConveyorChainActor* pendingChain, const TArray< FConveyorItemDescRange >& pendingDescRanges, int32 numDescProcessed,
		const TArray< FConveyorItemSpacingRange >& pendingSpacingRanges, int32 numSpacingProcessed, int32 currentRemovalIndex, int32 currentAdditionIndex  )
	{
		PendingItemChainActor = pendingChain;
		PendingDescRanges.Append( pendingDescRanges );
		PendingDescSendIndex = PendingDescSendIndex + numDescProcessed;
		
		PendingSpacingRanges.Append( pendingSpacingRanges );
		PendingSpacingSendIndex = PendingSpacingSendIndex + numSpacingProcessed;

		PendingRemovalIndex = currentRemovalIndex;
		PendingAdditionIndex = currentAdditionIndex;
	}
	
	void ClearPendingItemTransferData()
	{
		PendingItemChainActor = nullptr;
		PendingDescRanges.Empty();
		PendingDescSendIndex = 0;

		PendingSpacingRanges.Empty();
		PendingSpacingSendIndex = 0;

		PendingRemovalIndex = INDEX_NONE;
		PendingAdditionIndex = INDEX_NONE;
	}

	void SetPendingSegmentTransferData( AFGConveyorChainActor* pendingChain, int32 segmentIndex )
	{
		PendingSegmentChainActor = pendingChain;
		PendingSegmentIndex = segmentIndex;
	}

	void ClearPendingSegmentTransferData()
	{
		PendingSegmentChainActor = nullptr;
		PendingSegmentIndex = INDEX_NONE;
	}
	
public:
	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGConveyorChainRemoteCallObject = false;

	// --- Begin Partial ITEM Transfer Tracking
	UPROPERTY()
	AFGConveyorChainActor* PendingItemChainActor = nullptr;
	
	UPROPERTY()
	TArray< FConveyorItemDescRange > PendingDescRanges;

	UPROPERTY()
	int32 PendingDescSendIndex = 0;

	UPROPERTY()
	TArray< FConveyorItemSpacingRange > PendingSpacingRanges;
	
	UPROPERTY()
	int32 PendingSpacingSendIndex = 0;

	UPROPERTY()
	int32 PendingRemovalIndex = INDEX_NONE;

	UPROPERTY()
	int32 PendingAdditionIndex = INDEX_NONE;
	// --- Emd Partial ITEM Transfer Tracking

	// --- Begin Partial Segment Transfer Tracking
	UPROPERTY()
	AFGConveyorChainActor* PendingSegmentChainActor = nullptr;

	UPROPERTY()
	int32 PendingSegmentIndex = INDEX_NONE;
	
	// --- End Partial Sesgment Transfer Tracking

	UPROPERTY()
	TArray< AFGConveyorChainActor* > RequestedItemChainActors;

	UPROPERTY()
	TArray< AFGConveyorChainActor* > RequestedSegmentChainActors;

	UPROPERTY()
	bool HasPendingItemClientRequest = false;

	UPROPERTY()
	bool HasPendingSegmentClientRequest = false;
};


UCLASS()
class FACTORYGAME_API AFGConveyorChainSubsystem : public AFGSubsystem
{
	GENERATED_BODY()

public:
	AFGConveyorChainSubsystem();
	
	/** Get the ConveyorChain Subsystem */
	static AFGConveyorChainSubsystem* Get( UWorld* world );
	static AFGConveyorChainSubsystem* Get( UObject* worldContext );

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// Called when the Belt Movement Quality user setting is changed so we can reparam and update all belt chains
	UFUNCTION()
	void OnConveyorItemMovementQualityUpdated( FString cvar );
	
	void AddConveyorChain( AFGConveyorChainActor* chainActor );
	void RemoveConveyorChain( AFGConveyorChainActor* chainActor );

	/** Builds an array of all Item Descriptors. The class index in this array becomes its Network Identifier (we assume < 65k items so we can rep item classes with only 2 bytes) */
	void BuildItemDescriptorRepArray();
	
	UFUNCTION()
	void OnRep_ConveyorItemDescAndID();

	void NotifyChainReceivedItemUpdate( AFGConveyorChainActor* chainActor );
	void NotifyChainNeedsSegmentUpdate( AFGConveyorChainActor* ChainActor );
	void NotifyChainReceiveSegmentUpdate( AFGConveyorChainActor* chainActor );
	void NotifyChainNeedsItemUpdate( AFGConveyorChainActor* ChainActor );


	/**
	 *	Each time the server time is updated an entry is added to the delta array so we can track time between updates (we track up to 256)
	 *	This is used to calculate the clients time debt (or how far we've run ahead of the server) in the buildable subsystem which controls
	 *	how much deltaTime the client updates the chains with.
	 */
	UFUNCTION()
	void OnRep_ServerFactoryTickTime( float oldValue );


	/** Tracks how much time the server has used updating conveyor chains */
	void AddServerTickTime( float dt ) { mServerFactoryTickTime += dt; }
	/** Tracks how much time the client has used updating conveyor chains */
	void AddClientTickTime( float dt ) { mClientFactoryTickTime += dt; }

	/** This is called during tick by the client to consume portions of its debt in an effort to catch up to the servers current time (if we're far behind we use more time to update) */
	float GetAndConsumeClientTimeDebt( float updateDelta );

	/** Returns the current server tick time */
	FORCEINLINE float GetServerFactoryTickTime() const { return mServerFactoryTickTime; }
	/** Returns the current client tick time */
	FORCEINLINE float GetClientFactoryTickTime() const { return mClientFactoryTickTime; }

	FORCEINLINE void SetClientFactoryTickTime( float time ) { mClientFactoryTickTime = time; }
	
	/** Gets the average delta time between net updates (how much time is the server using to update chain belts between netupdates) */
	float GetAverageServerTickDeltaTime();

	/**
	 *	Before ticking the belts, the client subsystem checks if too much time has past since our last update. If so we don't tick the belts
	 *	This can happen for a variety of reason. Noteably spikes from Saving or really any issue that causes the server to become unresponsive
	 */
	bool IsUnusuallyLargeTickDelta();
	
	TSubclassOf< UFGItemDescriptor > GetItemDescFromIndex( int32 index )
	{
		if( mAllItemDescriptors.IsValidIndex( index ) )
		{
			return mAllItemDescriptors[index];
		}

		return nullptr;
	}
	
	int32 GetIndexOfItemDescClass( TSubclassOf< UFGItemDescriptor > itemDesc )
	{
		return mAllItemDescriptors.IndexOfByKey( itemDesc );
	}

	FORCEINLINE int32 GetReparamStepsForSplineSegments()
	{
		return mReparamStepsPerSegment;
	}

private:
	FORCEINLINE int32 GetReparamStepForQualitySetting( int32 qualitySetting )
	{
		// Just a safety although this should never be an issue
		qualitySetting = FMath::Clamp( qualitySetting, 0, mReparamStepQualitySettings.Num() );
		
		if( mReparamStepQualitySettings.IsValidIndex( qualitySetting ) )
		{
			return mReparamStepQualitySettings[qualitySetting];
		}

		// This is the default value in spline components in general and is what it would use if we didn't change it via settings
		return 10;
	}
	
	
private:
	// The number or settings that correspond to a quality setting in the GameUserSettings
	static const inline TArray<int32> mReparamStepQualitySettings = { 5, 10, 20, 50 };

	// Just a copy of how the setting is known in the user settings
	static const inline FString CONVEYOR_VISUAL_QUALITY = "FG.ConveyorVisualQuality";
	
	UPROPERTY()
	int32 mReparamStepsPerSegment = 10;
	
	UPROPERTY()
	uint16 RepIDIncrement = 0;
	
	UPROPERTY()
	TArray< AFGConveyorChainActor* > mConveyorChains;

	/** When a chain is first replicated it will not have its spline segments replicated so its placed here until its spline data is requested then it is built */
	UPROPERTY()
	TArray< AFGConveyorChainActor* > mChainsNeedingSegmentUpdate;

	/** When a chain needs an update it is added here. If there are no pending requests the client will move from here into the pending update request pool after issueing a request*/
	UPROPERTY()
	TArray< AFGConveyorChainActor* > mChainsNeedingItemUpdate;

	/** When the client issues a server RPC for an item update, the requesting actor is placed here. Only when this array is empty will we issue another request */
	UPROPERTY()
	TArray< AFGConveyorChainActor* > mPendingItemUpdateRequest;

	/** When the client issues a server RPC for an segment update, the requesting actor is placed here. Only when this array is empty will we issue another request */
	UPROPERTY()
	TArray< AFGConveyorChainActor* > mPendingSegmentUpdateRequest;

	UPROPERTY()
	TArray< AFGConveyorChainActor* > mSegmentUpdatedReceived;

	// The total amount of time this subsystem has been accumulating from FactoryTick time.
	UPROPERTY( ReplicatedUsing=OnRep_ServerFactoryTickTime )
	float mServerFactoryTickTime;

	// The total amount of time this subsystem as accumalted tick time on client
	UPROPERTY()
	float mClientFactoryTickTime = 0.f;

	// This is the amount of the time that is in disparity between client and server. This can be negative or positive
	UPROPERTY()
	float mClientTickDebt;
	
	UPROPERTY()
	TArray< float > mServerFactoryTickDeltas;
	
	UPROPERTY( ReplicatedUsing=OnRep_ConveyorItemDescAndID )
	TArray< TSubclassOf< UFGItemDescriptor > > mAllItemDescriptors;

};


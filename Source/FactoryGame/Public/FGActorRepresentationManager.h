// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGSubsystem.h"
#include "FGActorRepresentation.h"
#include "FGRemoteCallObject.h"
#include "Engine/Texture2D.h"
#include "FGActorRepresentationManager.generated.h"

class AFGActorRepresentationManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnActorRepresentationAdded, UFGActorRepresentation*, newRepresentation );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnActorRepresentationRemoved, UFGActorRepresentation*, removedRepresentation );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnActorRepresentationUpdated, UFGActorRepresentation*, updatedRepresentation );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorRepresentationUpdatedCompassShow, UFGActorRepresentation*, updatedRepresentation, bool, newShouldShowInCompass );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorRepresentationUpdatedMapShow, UFGActorRepresentation*, updatedRepresentation, bool, newShouldShowOnMap );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorRepresentationTypeFilteredOnMap, ERepresentationType, representationType, bool, visible );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorRepresentationTypeFilteredOnCompass, ERepresentationType, representationType, bool, visible );

/** Custom INetDeltaBaseState used by representation manager replication */
class FFGActorRepresentationReplicatorDeltaState : public INetDeltaBaseState
{
public:
	virtual bool IsStateEqual(INetDeltaBaseState* OtherState) override;
	virtual void CountBytes(FArchive& Ar) const override;

	/** Updates the representation list from the representation manager */
	void UpdateReplicatedRepresentationList( const AFGActorRepresentationManager* representationManager );
	void UpdateReplicatedMovementData();
	/** True if we have any data pending replication */
	bool HasPendingReplicationData() const;
	
	/** Changelist of the representation array that was replicated to the client last time. This number changes when the representations are added, removed or updated */
	uint64 RepresentationManagerChangelist{0};
	/** A set of representations that have been already replicated to the client */
	TSet<FGuid> ReplicatedRepresentationSet;
	/** A list of representation updates that have not been replicated to the client yet */
	TArray<FGuid> PendingRepresentationUpdates;
	/** A list of representation removals that have not been replicated to the client yet */
	TArray<FGuid> PendingRepresentationRemovals;
	/** Mappings of replicated representation ID to the last changelist it was replicated in */
	TMap<FGuid, uint64> ReplicatedRepresentations;
	/** A list of non-static (e.g. moving) representations position/rotation of which need to be updated regularly */
	TArray<FGuid> MovingRepresentationList;
	/** Changelist for moving representations */
	uint64 MovingRepresentationChangelist{0};
	/** Index of the moving representation that we should replicate next */
	int32 CurrentMovingRepresentationIndex{0};
	/** Offset into the moving representation array. Used to evenly spread updates out in case we cannot update all of the representations immediately */
	int32 CurrentMovingRepresentationOffset{0};
};

/** Struct used for replication of representation manager data */
USTRUCT()
struct FACTORYGAME_API FFGActorRepresentationReplicator
{
	GENERATED_BODY()

	bool NetDeltaSerialize( FNetDeltaSerializeInfo& DeltaParams );
private:
	bool NetDeltaSerialize_Write( const AFGActorRepresentationManager* representationManager, FNetDeltaSerializeInfo& deltaParams ) const;
	bool NetDeltaSerialize_Read( AFGActorRepresentationManager* representationManager, FNetDeltaSerializeInfo& deltaParams );

	static void NetSerializeProperty_Write( FBitWriter& Ar, FProperty* Property, void* PropertyValuePtr, UPackageMap* PackageMap, INetSerializeCB& Callbacks );
	static void NetSerializeProperty_Read( FBitReader& Ar, FProperty* Property, void* PropertyValuePtr, UPackageMap* PackageMap, INetSerializeCB& Callbacks, TDoubleLinkedList<FProperty*>& PropertyChain, UFGActorRepresentation* rootRepresentation );
};

template<>
struct TStructOpsTypeTraits<FFGActorRepresentationReplicator> : TStructOpsTypeTraitsBase2<FFGActorRepresentationReplicator>
{
	enum { WithNetDeltaSerializer = true };
};

/**
 * This class manages all the representations of actors that are used in the compass and on the map.
 */
UCLASS()
class FACTORYGAME_API AFGActorRepresentationManager : public AFGSubsystem
{
	GENERATED_BODY()
public:
	/** Get the representation manager, this should always return something unless you call it really early. */
	static AFGActorRepresentationManager* Get( UWorld* world );

	/** Get the representation manager from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Representation", DisplayName = "GetActorRepresentationManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGActorRepresentationManager* Get( UObject* worldContext );

public:
	AFGActorRepresentationManager();
	
	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	// End AActor interface

	/** Creates a new actor representation. Must be called on server for representation that aren't local to appear for all players. */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	UFGActorRepresentation* CreateAndAddNewRepresentation( AActor* realActor, const bool isLocal = false, TSubclassOf<UFGActorRepresentation> representationClass = nullptr );

	/** Creates a new representation for something that doesn't have an actor. Must be called on server for representations that aren't local to appear for all players. */
	UFGActorRepresentation* CreateNewRepresentationNoActor( FVector location, class UTexture2D* compassTexture, FLinearColor compassColor, float lifeSpan, bool shouldShowInCompass, bool shouldShowOnMap, ERepresentationType representationType = ERepresentationType::RT_Default, TSubclassOf<UFGActorRepresentation> representationClass = nullptr );
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	UFGActorRepresentation* CreateAndAddNewRepresentationNoActor( FVector location, class UTexture2D* compassTexture, FLinearColor compassColor, float lifeSpan, bool shouldShowInCompass, bool shouldShowOnMap, ERepresentationType representationType = ERepresentationType::RT_Default, TSubclassOf<UFGActorRepresentation> representationClass = nullptr );

	void AddRepresentation( class UFGActorRepresentation* actorRepresentation );
	
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	bool UpdateRepresentationOfActor( AActor* realActor );
	bool UpdateRepresentation( UFGActorRepresentation* actorRepresentation );
	
	/** Removes the representation of an actor */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Representation" )
	bool RemoveRepresentationOfActor( AActor* realActor );

	void RemoveRepresentation( class UFGActorRepresentation* actorRepresentation );

	/** Finds the representation of the given real actor */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	UFGActorRepresentation* FindActorRepresentation(const AActor* realActor);
	
	class UFGResourceNodeRepresentation* FindResourceNodeRepresentation( class AFGResourceNodeBase* resourceNode );
	
	/** Gathers all representations and returns them */
	UFUNCTION( BlueprintCallable, Category = "Representation" )
	void GetAllActorRepresentations( UPARAM( ref ) TArray< class UFGActorRepresentation* >& out_AllRepresentations );
	
	/** Debug */
	void DumpActorRepresentations();

	/** Set if representation type should be visible on map */
	UFUNCTION( BlueprintCallable, Category = "Filtering" )
	void SetMapRepresentationTypeFilter( class APawn* owningPlayerPawn, ERepresentationType type, bool visible );

	/** Set if representation type should be visible on compass */
	UFUNCTION( BlueprintCallable, Category = "Filtering" )
	void SetCompassRepresentationTypeFilter( class APawn* owningPlayerPawn, ERepresentationType type, bool visible );

	/** Returns true if representation type is visible on map */
	UFUNCTION( BlueprintCallable, Category = "Filtering" )
	bool GetMapRepresentationTypeFilter( class APawn* owningPlayerPawn, ERepresentationType type );

	/** Returns true if representation type is visible on compass */
	UFUNCTION( BlueprintCallable, Category = "Filtering" )
	bool GetCompassRepresentationTypeFilter( class APawn* owningPlayerPawn, ERepresentationType type );

	/** Sets the actor representations view distance on compass */
	UFUNCTION( BlueprintCallable, Category = "Filtering" )
	void SetCompassViewDistanceForActorRepresentation( UFGActorRepresentation* actorRepresentation, ECompassViewDistance viewDistance );

	AActor* GetRealActorFromActorRepresentation( UFGActorRepresentation* actorRepresentation );

	UFUNCTION( BlueprintPure, Category = "Filtering" )
	float GetDistanceValueFromCompassViewDistance( ECompassViewDistance compassViewDistance );

public:
	/** Called whenever a new representation is added */
	UPROPERTY( BlueprintAssignable, Category = "Representation" )
	FOnActorRepresentationAdded mOnActorRepresentationAdded;

	/** Called whenever a new representation is removed, not sure how long it will be valid after a remove. */
	UPROPERTY( BlueprintAssignable, Category = "Representation" )
	FOnActorRepresentationRemoved mOnActorRepresentationRemoved;

	/** Called whenever a representation is updated */
	UPROPERTY( BlueprintAssignable, Category = "Representation" )
	FOnActorRepresentationUpdated mOnActorRepresentationUpdated;

	/** Called whenever a new representation changes it's show value for the compass */
	UPROPERTY( BlueprintAssignable, Category = "Representation" )
	FOnActorRepresentationUpdatedCompassShow mOnActorRepresentationUpdatedCompassShow;

	/** Called whenever a new representation changes it's show value for the maps */
	UPROPERTY( BlueprintAssignable, Category = "Representation" )
	FOnActorRepresentationUpdatedMapShow mOnActorRepresentationUpdatedMapShow;
	
	/** Called whenever a representation type changes it's filter status on the map */
	UPROPERTY( BlueprintAssignable, Category = "Representation" )
	FOnActorRepresentationTypeFilteredOnMap mOnActorRepresentationTypeFilteredOnMap;

	/** Called whenever a representation type changes it's filter status on the compass */
	UPROPERTY( BlueprintAssignable, Category = "Representation" )
	FOnActorRepresentationTypeFilteredOnCompass mOnActorRepresentationTypeFilteredOnCompass;

private:
	friend struct FFGActorRepresentationReplicator;
	friend class FFGActorRepresentationReplicatorDeltaState;

	void AddReplicatedRepresentation( UFGActorRepresentation* representation );
	void RemoveReplicatedRepresentation( UFGActorRepresentation* representation );
	void UpdateReplicatedRepresentation( UFGActorRepresentation* representation );
	UFGActorRepresentation* CreateReplicatedRepresentation( const UClass* representationClass, const FGuid& representationId );
	FNetworkGUID FindNetworkGUIDForActor( const AActor* actor) const;

	/** All actor representations. Parts of it are synced over network and other parts is added locally. Used to get all relevant representations for the current instance */
	UPROPERTY()
	TArray<class UFGActorRepresentation*> mAllRepresentations;

	/** Representations of moving objects. These need to be updated regularly to keep their position in sync with the representation */
	UPROPERTY()
	TArray<class UFGActorRepresentation*> mMovingRepresentations;
	
	/** These are all the representations of actors that should replicate from server to clients */
	UPROPERTY()
	TArray<class UFGActorRepresentation* > mReplicatedRepresentations;

	/** A map of replicated representation ID to the representation object. Used for fast lookups */
	UPROPERTY()
	TMap<FGuid, UFGActorRepresentation*> mReplicatedRepresentationMap;

	UPROPERTY( Replicated )
	FFGActorRepresentationReplicator mActorRepresentationReplicator;

	/** Changelist of the master state of the representation manager. Updated every time the representation is added, removed or updated */
	uint64 mRepresentationManagerChangelist{0};
	/** Changelist that is updated every time we update location data on moving representations on server */
	uint64 mMovingRepresentationChangelist{0};
};

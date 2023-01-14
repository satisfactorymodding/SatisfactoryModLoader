// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGSubsystem.h"
#include "FGActorRepresentation.h"
#include "FGRemoteCallObject.h"
#include "FGActorRepresentationManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnActorRepresentationAdded, UFGActorRepresentation*, newRepresentation );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnActorRepresentationRemoved, UFGActorRepresentation*, removedRepresentation );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnActorRepresentationUpdated, UFGActorRepresentation*, updatedRepresentation );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorRepresentationUpdatedCompassShow, UFGActorRepresentation*, updatedRepresentation, bool, newShouldShowInCompass );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorRepresentationUpdatedMapShow, UFGActorRepresentation*, updatedRepresentation, bool, newShouldShowOnMap );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorRepresentationTypeFilteredOnMap, ERepresentationType, representationType, bool, visible );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActorRepresentationTypeFilteredOnCompass, ERepresentationType, representationType, bool, visible );

USTRUCT()
struct FResourceNodeRepresentationPair
{
	GENERATED_BODY()
	
	FResourceNodeRepresentationPair():
		ResourceNode( nullptr ),
		ScanCount( 0 )
	{}

	FResourceNodeRepresentationPair( class AFGResourceNodeBase* resourceNode, int32 scanCount ) :
		ResourceNode( resourceNode ),
		ScanCount( scanCount )
	{}

	UPROPERTY()
	class AFGResourceNodeBase* ResourceNode;
	UPROPERTY()
	int32 ScanCount;
};

UCLASS()
class FACTORYGAME_API UFGActorRepresentationRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGActorRepresentationRemoteCallObject = false;

	// UFUNCTION( Client, Reliable )
	// void Client_AddResourceNodeRepresentations( const TArray< class AFGResourceNodeBase* >& resourceNodes );
	//
	// UFUNCTION( Client, Reliable )
	// void Client_RemoveResourceNodeRepresentations( const TArray< class AFGResourceNodeBase* >& resourceNodes );

	// UFUNCTION( Server, Reliable )
	// void Server_RequestResourceNodeRepresentations();
	//
	// UFUNCTION( Client, Reliable )
	// void Client_SyncResourceNodeRepresentations( const TArray< FResourceNodeRepresentationPair >& resourceNodeRepresentationPairs );

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
	virtual void PreReplication( IRepChangedPropertyTracker& changedPropertyTracker ) override;
	virtual bool ReplicateSubobjects( class UActorChannel* channel, class FOutBunch* bunch, FReplicationFlags* repFlags ) override;
	virtual void OnSubobjectCreatedFromReplication(UObject* newSubobject) override;
	virtual void OnSubobjectDestroyFromReplication(UObject* subobject) override;
	virtual void BeginPlay() override;
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
	bool UpdateRepresentationOfActor( AActor* realActor ); // const
	bool UpdateRepresentation( UFGActorRepresentation* actorRepresentation ) const; // const
	
	/** Removes the representation of an actor */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Representation" )
	bool RemoveRepresentationOfActor( AActor* realActor );

	void RemoveRepresentation( class UFGActorRepresentation* actorRepresentation );
	
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

private:
	UFUNCTION()
	void OnRep_ReplicatedRepresentations( TArray< class UFGActorRepresentation* > previousReplicatedRepresentations );

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
	friend class UFGActorRepresentationRemoteCallObject;

	/** All actor representations. Parts of it are synced over network and other parts is added locally. Used to get all relevant representations for the current instance */
	UPROPERTY()
	TArray< class UFGActorRepresentation* > mAllRepresentations;
	
	/** These are all the representations of actors that should replicate from server to clients */
	UPROPERTY( ReplicatedUsing = OnRep_ReplicatedRepresentations )
	TArray< class UFGActorRepresentation* > mReplicatedRepresentations;
	
};

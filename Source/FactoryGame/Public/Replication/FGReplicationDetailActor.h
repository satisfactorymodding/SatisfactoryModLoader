// Copyright 2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGReplicationDependencyActorInterface.h"
#include "../FGInventoryComponent.h"
#include "FGReplicationDetailActor.generated.h"

/**
* The replication detail actor is an extendable class for handling special cases of replication for buildables.
* This class is mostly needed becase it is not possible to dynamically change the replication state of components 
* without having them replicate at least once. With this structure, replication data can be moved to a separate actor
* so that the main actor can still be dynamic while the replicated components and values can be dormant until needed.
*
* E.g. inventory stacks don't need to be replicated until a player interacts with the building.
*/
UCLASS( abstract )
class FACTORYGAME_API AFGReplicationDetailActor : public AActor, public IFGReplicationDependencyActorInterface
{
	GENERATED_BODY()

public:
	AFGReplicationDetailActor();

	/** Creates a ReplicationDetailActor and attaches it to the owner character if one doesn't already exist */
	static AFGReplicationDetailActor* CreateReplicationDetailActor( UClass* childClass, class IFGReplicationDetailActorOwnerInterface* owner );

	/** Run initialization on this object. */
	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor );
	
	/** Refreshes the replicated data values based on their corresponding values in the owning actor */
	virtual void UpdateInternalReplicatedValues();

	/** Run any logic needed prior to saving. If pointers have been moved this is the spot to copy over actor representation data. */
	virtual void OnPreSaveGame();

	/** Run any logic needed in order to get the correct dismantle refunds. */
	virtual void OnDismantleRefund();

	/** Flushes the state of the replication detail actor over to its owner. E.g. Inventory components copy their state. */
	virtual void FlushReplicationActorStateToOwner();

	/** Validation function to check whether initial replication has occurred. Only works on client and overriden implementations. */
	virtual bool HasCompletedInitialReplication() const;

protected:

	/** Owning AFGBuildable to this replication detail actor object. Should never be null. */
	UPROPERTY(Transient)
	class AFGBuildable* mOwningBuildable;

	/** Checks whether this actor is relevant to a connection. */
	virtual bool IsNetRelevantFor( const AActor* realViewer, const AActor* viewTarget, const FVector& srcLocation ) const override;

public:
	FORCEINLINE ~AFGReplicationDetailActor() = default;
};
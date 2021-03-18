// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Replication/FGReplicationDetailActor.h"
#include "FGReplicationDetailActorOwnerInterface.generated.h"

/**
 * @todo Please comment me
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGReplicationDetailActorOwnerInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FACTORYGAME_API IFGReplicationDetailActorOwnerInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	/** Returns the replication details actor for the owner. This must always return a value so lazy load if it doesn't exist. */
	virtual class AFGReplicationDetailActor* GetReplicationDetailActor( bool tryCreate = false ) = 0;

	/** Called when the replication detail actor changes state (i.e. is being interacted with or not). */
	virtual void OnBuildableReplicationDetailStateChange( bool newStateIsActive ) = 0;

	/** 
	* Function called when a replication detail actor was created for the owner. 
	* On host this is called when the actor is created, on client it is called 
	* when the replication detail actor has been fully replicated. 
	**/
	virtual void OnReplicationDetailActorCreated() = 0;

	/**
	 * Function called when a replication detail actor is removed. This is called from the replication actor manually
	 * This will not trigger from Destroy() calls on the detail actor
	 */
	virtual void OnReplicationDetailActorRemoved() = 0;

	/** Returns the relevant class type for the replication detail actor. Must inherit from AFGReplicationDetailActor. */
	virtual UClass* GetReplicationDetailActorClass() const = 0;
};

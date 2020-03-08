#pragma once
#include "UObject/Interface.h"

#include "FGReplicationDetailActor.h"
#include "FGReplicationDetailActorOwnerInterface.generated.h"

UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGReplicationDetailActorOwnerInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGReplicationDetailActorOwnerInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 

public:
	FORCEINLINE ~UFGReplicationDetailActorOwnerInterface() = default;
};

class FACTORYGAME_API IFGReplicationDetailActorOwnerInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	/** Returns the replication details actor for the owner. This must always return a value so lazy load if it doesn't exist. */
	virtual class AFGReplicationDetailActor* GetReplicationDetailActor() = 0;

	/** Called when the replication detail actor changes state (i.e. is being interacted with or not). */
	virtual void OnBuildableReplicationDetailStateChange( bool newStateIsActive ) = 0;

	/** 
	* Function called when a replication detail actor was created for the owner. 
	* On host this is called when the actor is created, on client it is called 
	* when the replication detail actor has been fully replicated. 
	**/
	virtual void OnReplicationDetailActorCreated() = 0;

	/** Returns the relevant class type for the replication detail actor. Must inherit from AFGReplicationDetailActor. */
	virtual UClass* GetReplicationDetailActorClass() const = 0;

public:
	FORCEINLINE IFGReplicationDetailActorOwnerInterface() = default;
};
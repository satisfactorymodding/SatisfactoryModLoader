// Copyright 2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "Components/ActorComponent.h"
#include "FGReplicationDetailInventoryComponent.generated.h"

/**
* A wrapper that acts as a getter and setter for dynamic pointers to InventoryComponents that are 
* swapped and managed by the ReplicationDetailActor system. If anything uses a pointed to a InventoryComponent that is
* swapped by the ReplicationDetail system then that InventoryComponent needs to be access via this object and the GetActiveInventoryComponent() function.
**/
UCLASS()
class FACTORYGAME_API UFGReplicationDetailInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFGReplicationDetailInventoryComponent();

	/** Only called on server to set the original InventoryComponent. */
	void SetMainInventoryComponent( class UFGInventoryComponent* inventoryComponent );
	
	/** Called when the InventoryComponent is being switched on server. Called on client when the initial InventoryComponent has been replicated. */
	void SetReplicationInventoryComponent( class UFGInventoryComponent* inventoryComponent );

	/** Returns the active inventory component */
	FORCEINLINE class UFGInventoryComponent* GetActiveInventoryComponent() const { return mActiveInventoryComponent; }

protected:
	// The active InventoryComponent returned
	class UFGInventoryComponent* mActiveInventoryComponent;

	class UFGInventoryComponent* mMainInventoryComponent; // Original InventoryComponent
	class UFGInventoryComponent* mReplicationInventoryComponent; // The dynamically replicated InventoryComponent that is created on demand

	class AFGReplicationDetailActor* mReplicationDetailActor; // Replication Detail Actor owning the replication InventoryComponent

public:
	FORCEINLINE ~UFGReplicationDetailInventoryComponent() = default;
};

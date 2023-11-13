// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Components/ActorComponent.h"
#include "FGInventoryComponent.h"
#include "FGReplicationDetailInventoryComponent.generated.h"


USTRUCT()
struct FReplicationDetailData
{
	GENERATED_BODY()

	FReplicationDetailData()
	{
		mActiveInventoryComponent = nullptr;
		mMainInventoryComponent = nullptr;
		mReplicationInventoryComponent = nullptr;
		mReplicationDetailActor = nullptr;
	}

public:
	/** Only called on server to set the original InventoryComponent. */
	void SetMainInventoryComponent( UFGInventoryComponent* inventoryComponent );
	
	/** Called when the InventoryComponent is being switched on server. Called on client when the initial InventoryComponent has been replicated. */
	void SetReplicationInventoryComponent( UFGInventoryComponent* inventoryComponent );

	/** When the a detail actor is destroyed, this is called to null out the replication inventory component (so that it can be reinitialized when a new one is created) */
	void ClearReplicationInventoryComponent();

	/** Returns the active inventory component */
	FORCEINLINE UFGInventoryComponent* GetActiveInventoryComponent() const { return mActiveInventoryComponent; }

	/** Returns whether or not a MainInventoryComponent has been set */
	FORCEINLINE bool HasMainInventoryComponent() const { return IsValid(mMainInventoryComponent); }

protected:
	UPROPERTY()
	AActor* mOwningActor;
	
	UPROPERTY()
	UFGInventoryComponent* mActiveInventoryComponent;
	
	UPROPERTY()
	UFGInventoryComponent* mMainInventoryComponent; // Original InventoryComponent
	
	UPROPERTY()
	UFGInventoryComponent* mReplicationInventoryComponent; // The dynamically replicated InventoryComponent that is created on demand
	
	UPROPERTY()
	class AFGReplicationDetailActor* mReplicationDetailActor; // Replication Detail Actor owning the replication InventoryComponent
};

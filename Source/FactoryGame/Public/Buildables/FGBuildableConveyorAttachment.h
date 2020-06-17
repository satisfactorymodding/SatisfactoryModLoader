// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "../Replication/FGReplicationDetailInventoryComponent.h"
#include "../Replication/FGReplicationDetailActor_Storage.h"
#include "FGBuildableFactory.h"
#include "FGBuildableConveyorAttachment.generated.h"

/**
* This is a struct that will assign an item to a certain connection. Used by splitters to cycle outputs so all items dont always go to one output
*/
USTRUCT()
struct FACTORYGAME_API FConnectionItemStruct
{
	GENERATED_BODY()

	FConnectionItemStruct() :
		Connection( nullptr ),
		Item( FInventoryItem() ),
		IndexInInventory( 0 ),
		OffsetBeyond( 0.0f ),
		Grabbed( false )
	{
	}

	FConnectionItemStruct( UFGFactoryConnectionComponent* inConnection, FInventoryItem inItem, float inOffsetBeyond, int32 indexInInventory ) :
		Connection( inConnection ),
		Item( inItem ),
		IndexInInventory( indexInInventory ),
		OffsetBeyond( inOffsetBeyond ),
		Grabbed( false )
	{
	}

	/** The connection to put the item on */
	UPROPERTY()
	class UFGFactoryConnectionComponent* Connection;

	/** The item to put on the connection */
	UPROPERTY()
	FInventoryItem Item;

	/** What is our index in the inventory component */
	int32 IndexInInventory;

	/** How far past the conveyor belt length this item is */
	float OffsetBeyond;

	/** To allow this to be thread safe, this bool marks if a table element has been consumed, to remove the need to delete from the table array */
	bool Grabbed;

public:
	FORCEINLINE ~FConnectionItemStruct() = default;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableConveyorAttachment : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AFGBuildableConveyorAttachment();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	//~ Begin Factory Interface
	//virtual void Factory_Tick( float deltaTime ) override;
	//~ End Factory Interface

	//~ Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	//~ End IFGDismantleInferface

	FORCEINLINE class UFGInventoryComponent* GetBufferInventory() const { return mBufferInventory; }
protected:
	friend class AFGReplicationDetailActor_Storage;

	// Begin Factory_ interface
	virtual void Factory_CollectInput_Implementation() override;
	// End Factory_ interface

	// Begin IFGReplicationDetailActorOwnerInterface
	virtual void OnRep_ReplicationDetailActor() override;
	virtual void OnBuildableReplicationDetailStateChange( bool newStateIsActive ) override;
	virtual class AFGReplicationDetailActor* GetOrCreateReplicationDetailActor() override;
	// End IFGReplicationDetailActorOwnerInterface
public:
	/** The size of the inventory for this attachment. Used to hold a buffer of incoming items */
	int32 mInventorySizeX;

	/** The size of the inventory for this storage. Used to hold a buffer of incoming items*/
	int32 mInventorySizeY;

protected:

	/** The inventory to store everything in. Don't use this directly, use mStorageInventoryHandler->GetActiveInventoryComponent() */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mBufferInventory;

	/** Cached input connections for faster lookup. */
	TArray< UFGFactoryConnectionComponent* > mInputs;

	/** Cached output connections for faster lookup. */
	TArray< UFGFactoryConnectionComponent* > mOutputs;

	/** Cached linear size of the inventory component*/
	int32 mCachedInventorySize;


public:
	FORCEINLINE ~AFGBuildableConveyorAttachment() = default;
};

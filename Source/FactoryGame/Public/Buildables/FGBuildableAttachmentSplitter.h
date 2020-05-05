// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableConveyorAttachment.h"
#include "FGBuildableAttachmentSplitter.generated.h"

USTRUCT()
struct FACTORYGAME_API FConveyorSpaceData
{
	GENERATED_BODY()
public:
	FConveyorSpaceData() :
		AvailableSpace( 0.f ),
		HasNewItem( false )
	{}

	FConveyorSpaceData( float availableSpace ) :
		AvailableSpace( availableSpace ),
		HasNewItem( false )
	{}

	// The last cached available space on the belt
	float AvailableSpace;

	// if the conveyor has a new item on it.
	bool HasNewItem;

public:
	FORCEINLINE ~FConveyorSpaceData() = default;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableAttachmentSplitter : public AFGBuildableConveyorAttachment
{
	GENERATED_BODY()
public:
	/** Ctor */
	AFGBuildableAttachmentSplitter();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGBuildable interface
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	// End AFGBuildable interface

	//~ Begin IFGDismantleInterface
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund ) const override;
	// End IFGDismantleInterface

protected:
	// Begin Factory_ interface
	virtual void Factory_Tick( float deltaTime ) override;
	virtual bool Factory_GrabOutput_Implementation( UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type ) override;
	// End Factory_ interface

	// Populate the elements of the distribution table. The algorithm vaires between normal splitters and smart splitters. 
	// The goal is to get all possible items assigned to an output while maintaining throughput and evenly splitting items between belts
	virtual void FillDistributionTable(float deltaTime);
	
	/** Returns an estimate of how many items the conveyor connected to the given component can grab. If no conveyor is connected it returns 0  */
	uint8 EstimatedMaxNumGrabFromConveyor( UFGFactoryConnectionComponent* factoryConnection, float dt ) const;

protected:

	/** Cycles through the outputs, stores the output we want to put mItem on. Index is for the mOutputs array. */
	UPROPERTY( SaveGame, Meta = (NoAutoJson) )
	int32 mCurrentOutputIndex;

	UPROPERTY( SaveGame, Meta = ( NoAutoJson ) )
	int32 mCurrentInventoryIndex;

	/** Table of all items in the inventory mapped to a desired output. The array is filled from a call to FillDistributionTable which runs in factory tick */
	UPROPERTY()
	TArray< FConnectionItemStruct > mDistributionTable;

private:
	friend class AFGAttachmentSplitterHologram;

	/** Store last cached available space and if an item have been grabbed by the connected components  */
	UPROPERTY( Transient )
	TMap<UFGFactoryConnectionComponent*, FConveyorSpaceData> mConveyorSpaceData;


public:
	FORCEINLINE ~AFGBuildableAttachmentSplitter() = default;
};

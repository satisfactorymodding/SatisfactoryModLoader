// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableConveyorAttachment.h"
#include "FGBuildableAttachmentSplitter.generated.h"

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

	virtual void FillDistributionTable();

protected:

	/** Cycles through the outputs, stores the output we want to put mItem on. Index is for the mOutputs array. */
	UPROPERTY( SaveGame, Meta = (NoAutoJson) )
	int32 mCurrentOutputIndex;

	UPROPERTY( SaveGame, Meta = ( NoAutoJson ) )
	int32 mCurrentInventoryIndex;

	UPROPERTY()
	TArray< FConnectionItemStruct > mDistributionTable;

private:
	friend class AFGAttachmentSplitterHologram;

};

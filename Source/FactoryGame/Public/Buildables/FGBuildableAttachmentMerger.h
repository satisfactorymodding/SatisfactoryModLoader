// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildableConveyorAttachment.h"
#include "FGBuildableAttachmentMerger.generated.h"

/**
 * Base class for mergers, it can have multiple inputs, but only one output.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableAttachmentMerger : public AFGBuildableConveyorAttachment
{
	GENERATED_BODY()
public:
	AFGBuildableAttachmentMerger();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface
	
	// Begin Factory_ interface
	virtual void Factory_Tick( float deltaTime ) override;
	// End Factory_ interface

protected:
	// Begin Factory_ interface
	virtual bool Factory_GrabOutput_Implementation( class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type ) override;
	// End Factory_ interface
private:
	/** Cycles through the inputs, stores the input we want to check next. Index is for the mInputs array. */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson ) )
	int32 mCurrentInputIndex;

	UPROPERTY( SaveGame, Meta = ( NoAutoJson ) )
	int32 mCurrentInventoryIndex;
};

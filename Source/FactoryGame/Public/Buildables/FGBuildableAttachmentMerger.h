// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableConveyorAttachment.h"
#include "FGBuildableAttachmentMerger.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableAttachmentMerger : public AFGBuildableConveyorAttachment
{
	GENERATED_BODY()
public:
	/** Ctor */
	AFGBuildableAttachmentMerger();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

protected:
	// Begin Factory_ interface
	virtual void Factory_Tick( float deltaTime ) override;
	virtual void Factory_CollectInput_Implementation() override;
	virtual bool Factory_GrabOutput_Implementation( class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type ) override;
	// End Factory_ interface
private:
	/** Cycles through the inputs, stores the input we want to check next. Index is for the mInputs array. */
	UPROPERTY( SaveGame, Meta = (NoAutoJson) )
	int32 mCurrentInputIndex;

	UPROPERTY( SaveGame, Meta = (NoAutoJson) )
	int32 mCurrentInventoryIndex;
};

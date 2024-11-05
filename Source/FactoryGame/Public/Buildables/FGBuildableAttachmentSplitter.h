// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableConveyorAttachment.h"
#include "FGBuildableAttachmentSplitter.generated.h"

/**
 * Base class for splitters, one input and multiple outputs.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableAttachmentSplitter : public AFGBuildableConveyorAttachment
{
	GENERATED_BODY()
public:
	AFGBuildableAttachmentSplitter();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

protected:
	// Begin Factory_ interface
	virtual void Factory_Tick( float deltaTime ) override;
	// End Factory_ interface

protected:
	/** Cycles through the outputs, stores the output we want to put mItem on. Index is for the mOutputs array. */
	UPROPERTY( SaveGame, Meta = (NoAutoJson) )
	int32 mCurrentOutputIndex;

private:
	friend class AFGAttachmentSplitterHologram;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableConveyorAttachment.h"
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

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface
	
	// Begin Factory_ interface
	virtual void Factory_Tick( float deltaTime ) override;
	// End Factory_ interface
	
private:
	/** Cycles through the inputs, stores the input we want to check next. Index is for the mInputs array. */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson ) )
	int32 mCurrentInputIndex;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGPipeAttachmentSnapTargetInterface.generated.h"

UINTERFACE( BlueprintType, Blueprintable )
class FACTORYGAME_API UFGPipeAttachmentSnapTargetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for actors to implement to be a valid snap target for Pipeline attachments. Eg. PipelineSupports can implement this to allow pumps to snap directly to themselves
 */
class FACTORYGAME_API IFGPipeAttachmentSnapTargetInterface
{
	GENERATED_BODY()
public:
	/** Returns true if the passed in attachment class should snap to this target actor */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "PipeSnapTarget" )
	bool IsValidSnapTargetForAttachment( TSubclassOf< class AFGBuildablePipelineAttachment > attachmentClass );
};

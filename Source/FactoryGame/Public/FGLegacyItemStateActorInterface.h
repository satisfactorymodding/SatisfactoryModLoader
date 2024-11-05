// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Templates/SubclassOf.h"
#include "FGDynamicStruct.h"
#include "FGLegacyItemStateActorInterface.generated.h"

class UFGItemDescriptor;

/**
 * Implements this on the actor that was used as the item state actor previously to be able to convert the data contained in it
 * The actor in question will be called right after it has been converted to the item state.
 */
UINTERFACE()
class FACTORYGAME_API UFGLegacyItemStateActorInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGLegacyItemStateActorInterface
{
	GENERATED_BODY()
public:
	virtual FFGDynamicStruct ConvertToItemState( TSubclassOf<UFGItemDescriptor> itemDescriptor ) const = 0;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGMusicPlayerInterface.h"
#include "Equipment/FGEquipmentAttachment.h"
#include "FGBoomBoxAttachment.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBoomBoxAttachment : public AFGEquipmentAttachment, public IFGMusicPlayerInterface
{
	GENERATED_BODY()
};

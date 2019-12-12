// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGEquipment.h"
#include "FGToolBelt.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGToolBelt : public AFGEquipment
{
	GENERATED_BODY()
	
	
public:
	/** How many arm slots are added by this belt  */
	UPROPERTY( EditDefaultsOnly, Category = "Belt" )
	int32 mNumArmSlotsToUnlock;
};

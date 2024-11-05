// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Creature/FGCreature.h"
#include "FGEnemy.generated.h"

/**
 * 
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGEnemy : public AFGCreature
{
	GENERATED_BODY()
public:
	/** ctor */
	AFGEnemy( const FObjectInitializer& ObjectInitializer );
};


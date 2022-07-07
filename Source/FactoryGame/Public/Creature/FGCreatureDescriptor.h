// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "../Resources/FGItemDescriptor.h"
#include "FGCreatureDescriptor.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCreatureDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()

	virtual UTexture2D* Internal_GetSmallIcon() const override;
	virtual UTexture2D* Internal_GetBigIcon() const override;

	/** The creature this descriptor stores information about */
	UPROPERTY( EditDefaultsOnly, Category = "Creature", meta = ( AddAutoJSON = true ) )
	TSubclassOf< class AFGCreature > mCreatureClass;

	/** Small icon of the creature when arachnophobia mode is active, always in memory */
	UPROPERTY( EditDefaultsOnly, Category="UI", meta = ( AddAutoJSON = true ) )
	UTexture2D* mSmallIconArachnophobiaMode;
	
	/** Big icon of the creature when arachnophobia mode is active, always in memory */
	UPROPERTY( EditDefaultsOnly, Category="UI", meta = ( AddAutoJSON = true ) )
	UTexture2D* mBigIconArachnophobiaMode;
};

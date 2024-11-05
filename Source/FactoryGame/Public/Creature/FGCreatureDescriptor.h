// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "../Resources/FGItemDescriptor.h"
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
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

protected:
	FORCEINLINE virtual bool Internal_CanItemBePickedup() const override { return false; }

public:
	/** The creature this descriptor stores information about */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Creature", meta = ( AddAutoJSON = true ) )
	TSubclassOf< class AFGCreature > mCreatureClass;

protected:
	/** Small icon of the creature when arachnophobia mode is active, always in memory */
	UPROPERTY( EditDefaultsOnly, Category="UI", meta = ( AddAutoJSON = true ) )
	UTexture2D* mSmallIconArachnophobiaMode;
	
	/** Big icon of the creature when arachnophobia mode is active, always in memory */
	UPROPERTY( EditDefaultsOnly, Category="UI", meta = ( AddAutoJSON = true ) )
	UTexture2D* mBigIconArachnophobiaMode;
};

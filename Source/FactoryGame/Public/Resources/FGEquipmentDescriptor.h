// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGItemDescriptor.h"
#include "Equipment/FGEquipment.h" // I really want to get rid of this include, but removing it adds compile errors
#include "FGEquipmentDescriptor.generated.h"

/**
*
*/
UCLASS( Abstract )
class FACTORYGAME_API UFGEquipmentDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	/** Get the equipment that is linked to this descriptor. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Equipment" )
	static TSubclassOf< class AFGEquipment > GetEquipmentClass( TSubclassOf< class UFGItemDescriptor > inClass );

public:
	/** The equipment that is linked to this descriptor. */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	TSubclassOf< class AFGEquipment > mEquipmentClass;
};

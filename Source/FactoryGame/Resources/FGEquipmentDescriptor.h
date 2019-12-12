// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGItemDescriptor.h"
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
	static TSubclassOf< class AFGEquipment > GetEquipmentClass( TSubclassOf< UFGItemDescriptor > inClass );

public:
	/** The equipment that is linked to this descriptor. */
	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	TSubclassOf< class AFGEquipment > mEquipmentClass;
};

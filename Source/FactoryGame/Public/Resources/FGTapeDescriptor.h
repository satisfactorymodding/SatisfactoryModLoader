// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
#include "FGTapeDescriptor.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGTapeDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	/** Get songs in this tape */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Tape" )
    static TSoftClassPtr< class UFGTapeData > GetTapeData( TSubclassOf< class UFGItemDescriptor > inClass );
public:
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TSoftClassPtr< class UFGTapeData > mTapeData;
};

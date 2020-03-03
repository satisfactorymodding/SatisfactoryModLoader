// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGItemCategory.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGItemCategory : public UObject
{
	GENERATED_BODY()
	
public:
	/** Used to get the mDisplayName in blueprint. */
	UFUNCTION( BlueprintPure, Category = "Build Category" )
	static FText GetCategoryName( TSubclassOf< UFGItemCategory > inClass );

private:
	/** Name of this item category*/
	UPROPERTY( EditDefaultsOnly, Category = "Build Category" )
	FText mDisplayName;

public:
	FORCEINLINE ~UFGItemCategory() = default;
};

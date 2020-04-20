// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Styling/SlateBrush.h"
#include "FGSchematicCategory.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGSchematicCategory : public UObject
{
	GENERATED_BODY()

public:
	/** Used to get the mDisplayName in blueprint. */
	UFUNCTION( BlueprintPure, Category = "Schematic Category" )
	static FText GetCategoryName( TSubclassOf< UFGSchematicCategory > inClass );

	/** Get the icon for a category */
	UFUNCTION( BlueprintPure, Category = "Schematic Category" )
	static FSlateBrush GetCategoryIcon( TSubclassOf< UFGSchematicCategory > inClass );

private:
	/** Name of this build category*/
	UPROPERTY( EditDefaultsOnly, Category = "Schematic Category" )
	FText mDisplayName;

	/** Icon for the category */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic Category" )
	FSlateBrush mCategoryIcon;


public:
	FORCEINLINE ~UFGSchematicCategory() = default;
};

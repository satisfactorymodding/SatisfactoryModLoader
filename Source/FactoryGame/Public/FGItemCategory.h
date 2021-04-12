// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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

	/** The order we want item categories in menus, lower is earlier */
	UFUNCTION( BlueprintPure, Category = "Build Category" )
    static float GetMenuPriority( TSubclassOf< UFGItemCategory > inClass );

	/** Sort an array dependent on their menu priority. */
	UFUNCTION( BlueprintCallable, Category = "Build Category" )
    static void SortByMenuPriority( UPARAM( ref ) TArray< TSubclassOf< UFGItemCategory > >& itemCategories );

private:
	/** Name of this item category*/
	UPROPERTY( EditDefaultsOnly, Category = "Build Category" )
	FText mDisplayName;

	/** The order in menus is decided by this value. Lower values means earlier in menu. Negative values are allowed. [-N..0..N]*/
	UPROPERTY( EditDefaultsOnly, Category = "Build Category" )
	float mMenuPriority;
};

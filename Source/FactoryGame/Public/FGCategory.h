// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGCategory.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGCategory : public UObject
{
	GENERATED_BODY()

public:
	/** Used to get the mDisplayName in blueprint. */
	UFUNCTION( BlueprintPure, Category = "Organization" )
	static FText GetCategoryName( TSubclassOf< UFGCategory > inClass );

	/** The order we want item categories in menus, lower is earlier */
	UFUNCTION( BlueprintPure, Category = "Organization" )
	static float GetMenuPriority( TSubclassOf< UFGCategory > inClass );

	/** Sort an array dependent on their menu priority. */
	UFUNCTION( BlueprintCallable, Category = "Organization" )
	static void SortByMenuPriority( UPARAM( ref ) TArray< TSubclassOf< UFGCategory > >& itemCategories );

	/** Get the icon for a category */
	UFUNCTION( BlueprintPure, Category = "Organization" )
	static FSlateBrush GetCategoryIcon( TSubclassOf< UFGCategory > inClass );

private:
	/** Name of this item category*/
	UPROPERTY( EditDefaultsOnly, Category = "Organization" )
	FText mDisplayName;

	/** The order in menus is decided by this value. Lower values means earlier in menu. Negative values are allowed. [-N..0..N]*/
	UPROPERTY( EditDefaultsOnly, Category = "Organization" )
	float mMenuPriority;

	/** Icon for the category */
	UPROPERTY( EditDefaultsOnly, Category = "Organization" )
	FSlateBrush mCategoryIcon;
	
};

// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "UObject/NoExportTypes.h"
#include "FGBuildCategory.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGBuildCategory : public UObject
{
	GENERATED_BODY()
	
public:
	/** Used to get the mDisplayName in blueprint. */
	UFUNCTION( BlueprintPure, Category = "Build Category" )
	static FText GetCategoryName( TSubclassOf< UFGBuildCategory > inClass );

	/** Get the icon for a category */
	UFUNCTION( BlueprintPure, Category = "Build Category" )
	static FSlateBrush GetCategoryIcon( TSubclassOf< UFGBuildCategory > inClass );

private:
	/** Name of this build category*/
	UPROPERTY( EditDefaultsOnly, Category = "Build Category" )
	FText mDisplayName;

	/** Icon for the category */
	UPROPERTY( EditDefaultsOnly, Category = "Build Category" )
	FSlateBrush mCategoryIcon;
	

public:
	FORCEINLINE ~UFGBuildCategory() = default;
};

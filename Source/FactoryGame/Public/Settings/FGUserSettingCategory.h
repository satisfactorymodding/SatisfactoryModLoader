// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCategory.h"
#include "FGUserSettingCategory.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FUserSettingSubCategoryMapping
{
	GENERATED_BODY()
	
	UPROPERTY( BlueprintReadWrite )
	TSubclassOf< class UFGUserSettingCategory > SubCategory;
	
	UPROPERTY( BlueprintReadWrite )
	TArray< class UUserWidget* > SettingWidgets;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FUserSettingCategoryMapping
{
	GENERATED_BODY()
	
	UPROPERTY( BlueprintReadWrite )
	TSubclassOf< class UFGUserSettingCategory > Category;
	
	UPROPERTY( BlueprintReadWrite )
	TArray<FUserSettingSubCategoryMapping> SubCategories;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGUserSettingCategory : public UFGCategory
{
	GENERATED_BODY()

	/** Sort an array of FUserSettingCategoryMapping dependent on their category priority. Only sorts by category and not subcategories */
	UFUNCTION( BlueprintCallable, Category = "Organization" )
	static void SortByCategoryPriority( UPARAM( ref ) TArray< FUserSettingCategoryMapping >& userSettingCategoryMapping );
	
};

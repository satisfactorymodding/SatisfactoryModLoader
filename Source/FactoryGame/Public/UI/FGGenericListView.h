// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGListView.h"
#include "FGGenericListView.generated.h"

/**
 * Custom list view that allows the user to override the widget type per list item by using @UFGGenericListItemDescriptor as an item type
 */
UCLASS()
class FACTORYGAME_API UFGGenericListView : public UFGListView
{
	GENERATED_BODY()
public:

protected:
	virtual TSubclassOf<UUserWidget> GetDesiredEntryClassForItem(UObject* Item) const override;
};

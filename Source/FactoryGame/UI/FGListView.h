// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Widgets/SWidget.h"
#include "Widgets/SBoxPanel.h"
#include "Components/PanelWidget.h"
#include "Views/ITypedTableView.h"
#include "FGListView.generated.h"

class UFGListViewSlot;

/**
 * A vertical box widget is a view panel allowing child widgets to be automatically laid out vertically from an array.
 * Supports selection and dynamic data binding to an array through delegates.
 *
 * * Many Children
 * * Flows Vertical
 * * Selection Functionality
 */
UCLASS()
class UFGListView : public UPanelWidget
{
	// MODDING EDIT
	GENERATED_BODY()
	UFGListView(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	
	/** Delegate for constructing a UWidget for an item to display. */
	DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam( UWidget*, FOnGenerateRow, int32, item );

	/** Delegate for getting the number of items to display. */
	DECLARE_DYNAMIC_DELEGATE_RetVal( int32, FGetNumRows );

public:
	/** Tells the list view to refresh the items in the list. */
	UFUNCTION( BlueprintCallable, Category = "ListView" )
	void Refresh();

#if WITH_EDITOR
	// UWidget interface
	virtual const FText GetPaletteCategory() override;
	// End UWidget interface
#endif

protected:
	// UPanelWidget
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded( UPanelSlot* slot ) override;
	virtual void OnSlotRemoved( UPanelSlot* slot ) override;
	// End UPanelWidget

	// UVisual
	virtual void ReleaseSlateResources( bool releaseChildren ) override;
	// End UVisual

public:
	/** Delegate for constructing a UWidget for an item to display. */
	UPROPERTY( EditAnywhere, Category = "Events", DisplayName = "OnGenerateRowEvent", meta = ( IsBindableEvent = "True" ) )
	FOnGenerateRow mOnGenerateRowEvent;

	/** Delegate for getting the number of items to display. */
	UPROPERTY( EditAnywhere, Category = "Events", DisplayName = "GetNumRowsEvent", meta = ( IsBindableEvent = "True" ) )
	FGetNumRows mGetNumRowsEvent;

protected:
	/** Internal slate vertical box. */
	TSharedPtr< class SVerticalBox > mMyVerticalBox;

	// Begin @todo Implement selection logic
	/** Which index in the array maps to which widget. */
	TArray< UFGListViewSlot* > mItemToWidgetMap;
	/** Which widget maps to which index in the array. */
	TMap< UFGListViewSlot*, int32 > mWidgetToItemMap;
	/** The selection method for the list */
	UPROPERTY( /*Edit*/ VisibleAnywhere, Category = "ListView" )
	TEnumAsByte< ESelectionMode::Type > mSelectionMode;
	/** A set of selected items */
	TSet< int32 > mSelectedItems;
	// End @todo

protected:
	// UWidget interface
	virtual TSharedRef< SWidget > RebuildWidget() override;
	// End of UWidget interface
};

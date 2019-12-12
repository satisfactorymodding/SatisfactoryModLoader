// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGSignElementWidget.generated.h"

struct FSignElementWidgetData
{
	class UFGSignCanvasWidget* CanvasParent;
	class UFGSignElementData* ElementData;
	class UCanvasPanelSlot* PanelSlot;
};

/**
 * UserWidget that represents an item that can be added to a FGSignCanvasWidget
 */
UCLASS()
class FACTORYGAME_API UFGSignElementWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void InitSignElement( const FSignElementWidgetData& elementWidgetData );
	virtual void SetElementData( class UFGSignElementData* data );

	UFUNCTION( BlueprintCallable, Category = "Sign Widget" )
	virtual void RefreshElement(bool isInitialization = false  );

	UFUNCTION( BlueprintCallable, Category = "Sign Widget" )
	class UFGSignElementData* GetElementData() const;

	class UCanvasPanelSlot* GetPanelSlot() const;
	
	void SetPanelSlot( class UCanvasPanelSlot* panelSlot );
	
	FORCEINLINE TSubclassOf<UUserWidget> GetDragWidgetClass() const { return mDragWidgetClass; }
	FORCEINLINE FVector2D GetDragOffset() const { return mDragOffset; }

	UFUNCTION( BlueprintImplementableEvent, Category = "Sign Widget" )
	void OnElementSelected();

	UFUNCTION( BlueprintImplementableEvent, Category = "Sign Widget" )
	void OnElementDeselected();

	// Called from canvas to notify that this element has focus
	void NativeNotifyElementSelected();
	void NativeNotifyElementDeselected();


	class TSubclassOf<class UFGSignElementSettingsWidget> GetSettingsWidgetClass();

protected:

	// Begin Widget Event Implementation
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InAnalogEvent ) override;
	virtual FReply NativeOnMouseButtonUp( const FGeometry& InGeometry, const FPointerEvent& InAnalogEvent ) override;
	virtual void NativeOnDragDetected( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation ) override;
	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	// End Widget Event Implementation

protected:
	/************************************************************************/
	/*						Begin Widget Bindings
	/************************************************************************/
	// Border widget to indicate object selection
	UPROPERTY( meta=(BindWidget ) )
	class UBorder* mSelectionBorder;
	/************************************************************************/
	/*						Begin Widget Bindings
	/************************************************************************/
	
	// Specify the widget to virually represent being dragged
	UPROPERTY( EditDefaultsOnly, Category = "Sign Widget" )
	TSubclassOf<UUserWidget> mDragWidgetClass;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Widget" )
	TSubclassOf<class UFGSignElementSettingsWidget> mSignElementSettingsWidget;

	// Reference to the sign element being dragged
	UPROPERTY()
	class UFGSignElementDragWidget* mDragElement;

	// Reference to the parent SignCanvasWidget
	UPROPERTY()
	class UFGSignCanvasWidget* mCanvasParent;

	// Reference to the element data represented by this widget
	UPROPERTY()
	class UFGSignElementData* mElementData;

	// Keep a reference to the panel slot this is stored in the FGSignCanvasWidget
	UPROPERTY()
	class UCanvasPanelSlot* mPanelSlot;

	// Tracks mouse cursor offset on a drag operation
	FVector2D mDragOffset;

};

// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Components/CanvasPanel.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateBrush.h"
#include "FGSignCanvasWidget.generated.h"

/**
 *	Custom widget that contains a canvas panel widget for holding sign design elements
 */
UCLASS()
class FACTORYGAME_API UFGSignCanvasWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init( class UFGSignInteractWidget* interactWidget, TArray<UFGSignElementData*> elementData );

	UFUNCTION( BlueprintCallable, Category = "Sign Widget" )
	void AddSignCanvasElement( UFGSignElementData* elementData );

	UFUNCTION( BlueprintCallable, Category = "Sign Widget" )
	void OnElementSelected( class UFGSignElementData* elementData );

	/** Returns the correct local component location of a canvas element */
	UFUNCTION( BlueprintCallable, Category = "Sign Widget" )
	FVector2D GetCanvasToComponentLocation( FVector2D locationInCanvas );
	
	UFUNCTION( BlueprintCallable, Category = "Sign Widget" )
	FVector2D GetComponentToCanvasLocation( FVector2D locationInComponent );
	
	/** Get Border brush to apply to selected canvas elements */
	FORCEINLINE FSlateBrush& GetBorderSelectionBrush() { return mSelectionBrushTemplate; }

	// Called to apply sign data back to the world sign
	void ApplySignData();

	// Called by the dragged element, spawns the drag widget
	void OnElementBeginDrag( class UFGSignElementDragWidget* dragElement );

	// Called by the element being dragged from its NativeOnDrop
	void OnElementDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, class UFGSignElementDragDrop* InOperation );

	// Called to set the size of the canvas size box to match the world size of the sign
	void SetCanvasSize( FVector2D size );

protected:
	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual void NativeOnDragEnter( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual void NativeOnDragLeave( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;

protected:
	/************************************************************************/
	/*						Begin Widget Bindings
	/************************************************************************/ 
	// Size Box that holds our Canvas, its size is set to absolute and the canvas fills that space
	UPROPERTY( meta = ( BindWidget ) )
	class USizeBox* mCanvasSizeBox;
	
	// The canvas panel where actual sign elements will be added
	UPROPERTY( meta=( BindWidget ))
	UCanvasPanel* mCanvasPanel;
	/************************************************************************/
	/*                     End Widget Bindings
	/************************************************************************/

	UPROPERTY( EditDefaultsOnly, Category = "Sign Widget" )
	FSlateBrush mSelectionBrushTemplate;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Widget" )
	TSubclassOf<class UFGSignElementWidget> mDefaultElementClass;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Widget" )
	TSubclassOf<class UFGSignElementWidget> mTextElementClass;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Widget" )
	TSubclassOf<class UFGSignElementWidget> mIconElementClass;

	UPROPERTY()
	class UFGSignElementDragDrop* mDragAndDrop;

	UPROPERTY()
	class UFGSignElementDragWidget* mDragElement;

	UPROPERTY()
	TArray<class UFGSignElementWidget*> mElementWidgets;

	// Reference to the currently selected widget
	UPROPERTY()
	class UFGSignElementWidget* mSelectedElement;

	UPROPERTY()
	class UFGSignInteractWidget* mInteractWidget;

private:
	void InitializeSlot( class UCanvasPanelSlot* slot );

	class UFGSignElementWidget* GetElementWidgetById( int32 id );


public:
	FORCEINLINE ~UFGSignCanvasWidget() = default;
};

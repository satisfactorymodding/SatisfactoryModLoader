// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Text/TextLayout.h"
#include "FGSignElementWidget.generated.h"


// Helper Data struct to consolidate all the info each element needs
USTRUCT( )
struct FACTORYGAME_API FInteractElementWidgetData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	int32 ElementID;
	UPROPERTY()
	class UFGSignCanvasWidget* CanvasParent;
	UPROPERTY()
	class UCanvasPanelSlot* PanelSlot;
};

// Helper Data struct to consolidate all the info each element needs
USTRUCT()
struct FACTORYGAME_API FBuildableElementWidgetData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	int32 ElementID;
	UPROPERTY()
	class UFGSignBuildingWidget* BuildableCanvas;
	UPROPERTY()
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
	
	// Initialize this element to exist in the context of the interact (designer) widget
	virtual void InitSignElementForInteract( const FInteractElementWidgetData& elementWidgetData );

	// Initialize this element to exist on a buildable widget
	virtual void InitSignElementForBuildable( FBuildableElementWidgetData& buildableWidgetData );

	UFUNCTION( BlueprintCallable, Category = "Sign Widget" )
	virtual void RefreshElement(bool isInitialization = false  );

	UFUNCTION( BlueprintPure, Category = "Sign Widget" )
	FORCEINLINE int32 GetElementID() const { return mElementID; }


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

	//////////////////////////////////////////////////////////////////////////
	/// Blueprint Accessors

	/** Returns the Text string data attr of this element (can be empty) */
	UFUNCTION( BlueprintPure, Category = "Sign Widget" )
	FString GetTextStringAttr() const;

	/** Returns the Icon Id attr of this element (can be invalid) */
	UFUNCTION( BlueprintPure, Category = "Sign Widget" )
	int32 GetIconIDAttr() const;

	/** Returns the position attr of this element */
	UFUNCTION( BlueprintPure, Category = "Sign Widget" )
	FVector2D GetPositionAttr() const;

	/** Returns the Size Specifier attribute of this element. This is a generic "size" value. Can mean different things whether this is an icon or a text type */
	UFUNCTION( BlueprintPure, Category = "Sign Widget" )
	int32 GetSizeSpecifierAttr() const;

	/** Returns the Size of the Canvas slot on the canvas for this element */
	UFUNCTION( BlueprintPure, Category = "Sign Widget" )
	FVector2D GetSizeAttr() const;

	/** Returns the Size Specifier attribute of this element. This is a generic "size" value. Can mean different things whether this is an icon or a text type */
	UFUNCTION( BlueprintPure, Category = "Sign Widget" )
	ETextJustify::Type GetAlignmentAttr() const;

	/// End Blueprint Accessors
	//////////////////////////////////////////////////////////////////////////


protected:

	// Begin Widget Event Implementation
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InAnalogEvent ) override;
	virtual FReply NativeOnMouseButtonUp( const FGeometry& InGeometry, const FPointerEvent& InAnalogEvent ) override;
	virtual void NativeOnDragDetected( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation ) override;
	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	// End Widget Event Implementation

protected:
	/************************************************************************/
	/*						Begin Widget Bindings */
	/************************************************************************/
	// Border widget to indicate object selection
	UPROPERTY( meta=(BindWidget ) )
	class UBorder* mSelectionBorder;
	/************************************************************************/
	/*						Begin Widget Bindings */
	/************************************************************************/
	
	
	/************************************************************************/
	/*						Begin Interact Properties */
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

	UPROPERTY()
	FInteractElementWidgetData mWidgetData;


	// Keep a reference to the panel slot this is stored in the FGSignCanvasWidget
	UPROPERTY()
	class UCanvasPanelSlot* mPanelSlot;

	// Tracks mouse cursor offset on a drag operation
	FVector2D mDragOffset;

	/************************************************************************/
	/*						End Interact Properties */
	/************************************************************************/

	UPROPERTY()
	int32 mElementID;

	// Reference to the parent Buildable canvas (only if this element exist on a building and not on the sign designer)
	UPROPERTY()
	class UFGSignBuildingWidget* mBuildableCanvas;

};

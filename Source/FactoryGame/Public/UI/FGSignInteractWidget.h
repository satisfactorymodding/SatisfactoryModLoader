// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSignInterface.h"
#include "UI/FGInteractWidget.h"
#include "FGSignTypes.h"
#include "Framework/Text/TextLayout.h"
#include "FGSignInteractWidget.generated.h"


/**
 *	General purpose Sign Designer Interact Widget. Intended to be used across all customizable signs
 */
UCLASS()
class FACTORYGAME_API UFGSignInteractWidget : public UFGInteractWidget
{
	GENERATED_BODY()
	
	
public:
	// Widget Construct
	void NativeConstruct() override;

	// Called after the interact widget is assigned to pull data and establish interface
	void NativeInitSignData();

	// Called one frame after init to build all sign elements
	void NativePostInit();

	UFUNCTION( BlueprintCallable, Category = "Sign Widget" )
	void ApplySignData();

	/** Returns a scalar to scale all UI elements by (to set absolute positions correctly) */
	FVector2D GetViewportScaledVector( FVector2D inVect );
	/** Returns a scalar to scale UI elements back to world space */
	FVector2D GetWorldScaledVector( FVector2D inVect );

	// Get the dimensions of the world sign
	FVector2D GetWorldSignSize();

	// Called by either the canvas or the layout list to inform that a new element was selected
	void NotifyElementSelected( UObject* sender, class UFGSignElementWidget* elementData );

	/** Begin Add Element Bindings */
	UFUNCTION()
	void AddNewTextElement();
	UFUNCTION()
	void AddNewIconElement();
	UFUNCTION()
	void AddNewPanelElement();
	/** End Add Element Bindings */


	// Delete an element
	UFUNCTION()
	void DeleteElement( int32 elementID );

	// Get the element string data by given ID
	FSignStringElement& GetElementDataRefFromID( int32 elementID )
	{
		return mSignStringData.GetStringElementRefFromID( elementID );
	}

	// Gets a copy of an elements string data
	bool GetElementDataCopyFromID( int32 elementID, FSignStringElement& out_elementData )
	{
		return mSignStringData.GetStringElementCopyFromID( elementID, out_elementData );
	}

	/////////////////////////////////////////////////////////////////////
	/// Element Property Setters

	UFUNCTION( BlueprintCallable, Category = "Signs|InteractWidget" )
	void SetElementPosition( int32 id, FVector2D newPosition );

	UFUNCTION( BlueprintCallable, Category = "Signs|InteractWidget" )
	void SetElementText( int32 id, FString newText );

	UFUNCTION( BlueprintCallable, Category = "Signs|InteractWidget" )
	void SetElementSize( int32 id, FVector2D newSize );

	UFUNCTION( BlueprintCallable, Category = "Signs|InteractWidget" )
	void SetElementIconID( int32 id, int32 iconID );

	UFUNCTION( BlueprintCallable, Category = "Signs|InteractWidget" )
	void SetElementSizeSpecifier( int32 id, ESignSizeDefinition sizeSpecification );

	UFUNCTION( BlueprintCallable, Category = "Signs|InteractWidget" )
	void SetElementTextJustification( int32 id, ETextJustify::Type newJustification );



protected:
	// Begin UFGInteractWidget interface
	virtual bool NativeCanCallInit() override;
	// End UFGInteractWidget interface

	// Initialize the viewport DPI matrix for furture vector transforms
	void CalculateDPIMatrix();

	// Calculates the maximum size possible for our canvas object while maintaining aspect of world sign
	void CalculateScaledCanvasDimensions( FVector2D worldSize );

protected:

	/************************************************************************/
	/*					Begin Widget Bindings */
	/************************************************************************/
	// Widget reference that holds a list of all active elements and allows for creation / deletion of sign elements
	UPROPERTY( meta = ( BindWidget ) )
	class UFGSignElementListWidget* mElementListWidget;


	// Container (Canvas Panel) to add the appropriate settings widget to when an element is selected
	UPROPERTY( meta = ( BindWidget ) )
	class UOverlay* mElementSettingsContainer;

	// Size box from where we determine the drawing canvases maximum size constraints
	UPROPERTY( meta=( BindWidget ) )
	class USizeBox* mCanvasSizeBox;

	// Panel to hold the FGSignCanvas ( dimensions will never be skewed )
	UPROPERTY( meta=( BindWidget) )
	class UCanvasPanel* mCanvasContainer;

	// Custom widget that holds the panel for which actual sign elements are added
	UPROPERTY( meta=( BindWidget) )
	class UFGSignCanvasWidget* mSignCanvasWidget;
	/************************************************************************/
	/*					End Widget Bindings */
	/************************************************************************/

	UPROPERTY()
	TMap< int32, class UFGSignElementListItemWidget* > mElementToListItem;

	// Created at runtime, can be null if no element is selected
	UPROPERTY()
	class UFGSignElementSettingsWidget* mElementSettingsWidget;

	// Pointer to the interact objects sign interface
	IFGSignInterface* mSignInterface;

	UPROPERTY( BlueprintReadWrite, Category = "Sign Widget" )
	FSignStringData mSignStringData;

private:
	friend class UFGSignElementListWidget;
	friend class UFGSignCanvasWidget;

	// Matrix of DPI scale to apply to get absolute screen position
	FMatrix2x2 mDPIScaleMatrix;

	// Matrix to reverse DPI scale when going from screen to world
	FMatrix2x2 mInverseDPIScaleMatrix;

	// Scale from World Size of sign to our Canvas UI Element
	float mCanvasToComponentScale;

};

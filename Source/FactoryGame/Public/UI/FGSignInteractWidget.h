// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "../FGSignInterface.h"
#include "FGInteractWidget.h"
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
	void AddNewSignElement( UFGSignElementData* elementData );

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
	/** End Add Element Bindings */

protected:
	virtual bool NativeCanCallInit() override;

	// Initialize the viewport DPI matrix for furture vector transforms
	void CalculateDPIMatrix();

	// Calculates the maximum size possible for our canvas object while maintaining aspect of world sign
	void CalculateScaledCanvasDimensions( FVector2D worldSize );

protected:

	/************************************************************************/
	/*					Begin Widget Bindings
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
	/*					End Widget Bindings
	/************************************************************************/

	// Created at runtime, can be null if no element is selected
	UPROPERTY()
	class UFGSignElementSettingsWidget* mElementSettingsWidget;

	// Pointer to the interact objects sign interface
	IFGSignInterface* mSignInterface;

	UPROPERTY( BlueprintReadWrite, Category = "Sign Widget" )
	FSignData mSignData;

private:
	// Matrix of DPI scale to apply to get absolute screen position
	FMatrix2x2 mDPIScaleMatrix;

	// Matrix to reverse DPI scale when going from screen to world
	FMatrix2x2 mInverseDPIScaleMatrix;

	// Scale from World Size of sign to our Canvas UI Element
	float mCanvasToComponentScale;

public:
	FORCEINLINE ~UFGSignInteractWidget() = default;
};

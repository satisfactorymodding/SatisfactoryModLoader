// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSignInterface.h"
#include "FGSignTypes.h"
#include "Blueprint/UserWidget.h"
#include "FGSignElementListItemWidget.generated.h"

/**
 *	List item widget to display sign hierarchy of elements. One is added to the SignElementList Widget for each layer and every child ElementData
 *	As of now, it doesn't know what type it is. So it can hold either a layer or element type. I kinda hate this but want to get this working so I'm leaving it in this fashion for now
 */
UCLASS()
class FACTORYGAME_API UFGSignElementListItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Initialization functions, one for each different type of list representation ( rather than creating unique classes for each )
	void NativeInit( class UFGSignElementListWidget* listWidget, const FSignStringElement& elementData );

	// Called when this element is selected, UFUNCTION because its bound to a button delegate
	UFUNCTION()
	void OnSelected();

	// When delete is selected on this layer this is called
	UFUNCTION()
	void DeleteSelect();

	// Return the element data this list widget represents
	int32 GetElementID() { return mElementID; }

protected:
	/************************************************************************/
	/*						Begin Widget Bindings */
	/************************************************************************/
	// Text to display the name of the list element
	UPROPERTY( meta = ( BindWidget ) )
	class UTextBlock* mNameTextBlock;

	// Icon to display the layer type in the list
	UPROPERTY( meta = ( BindWidget ) )
	class UImage* mIconImage;

	// Button to allow binding of selection to select the element on the canvas ( and set it as the selected element for the interact widget)
	UPROPERTY( meta = ( BindWidget ) )
	class UButton* mSelectionButton;

	// Button to delete the element
	UPROPERTY( meta = ( BindWidget ) )
	class UButton* mDeleteButton;

	/************************************************************************/
	/*						End Widget Bindings */
	/************************************************************************/

	// ID of the element
	int32 mElementID;

	// Holds a refernce to the layer data for this list element ( can be null, for example if this is an element type and not a layer )
	class UFGSignLayer* mLayerRef;

	// Holds a reference to the parent (owning) ElementListWidget. Used for bindinds on element selection
	class UFGSignElementListWidget* mListWidget;
};



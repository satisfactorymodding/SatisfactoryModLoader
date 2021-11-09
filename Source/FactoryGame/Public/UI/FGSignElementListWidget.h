// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSignInterface.h"
#include "Blueprint/UserWidget.h"
#include "FGSignElementListWidget.generated.h"

/**
 * Overview widget for adding an removing elements from the sign interact widget
 */
UCLASS()
class FACTORYGAME_API UFGSignElementListWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Call to build widget element list and assign callbacks for adding new elements
	void Init( class UFGSignInteractWidget* interactWidget, FSignStringData& stringData );

	// Called to add a list item for an existing element. The SignInteractWidget handles the creation of the data object. Not this list widget
	void AddListElement( const FSignStringElement& stringElement  );

	// Called when a layer element is selected
	void OnLayerSelected( class UFGSignLayer* layer );

	// Called when a data element is selected
	void OnElementSelected( int32 elementID );
	
	// Called when deletion is selected for a given layer
	void DeleteLayer( class UFGSignLayer* layer );

	// Called when deletion is selected for a given element 
	void RemoveListElement( int32 mElementID );

protected:
	/************************************************************************/
	/*						Begin Widget Bindings */
	/************************************************************************/
	// Button to add a new Text Element
	UPROPERTY( meta = ( BindWidget ) )
	class UButton* mAddTextElementButton;

	// Button to add a new Icon Element
	UPROPERTY( meta = ( BindWidget ) )
	class UButton* mAddIconElementButton;

	// The verticle box where added elements will be listed
	UPROPERTY( meta = ( BindWidget ) )
	class UVerticalBox* mElementListBox;
	/************************************************************************/
	/*                     End Widget Bindings */
	/************************************************************************/

	// Holds a reference to all widgets in this list
	TArray< class UFGSignElementListItemWidget* > mAllListElements;

	// Reference to the parent interact widget, NOT a UProperty as this is not the owning class
	class UFGSignInteractWidget* mInteractWidget;

	// Template for the list layer widget ( used to create widgets for layer elements )
	UPROPERTY( EditDefaultsOnly, Category = "SignListItem" )
	TSubclassOf< class UUserWidget > mLayerItemTemplate;

	// Default template for all non-layer list elements ( used to create widgets for SignElementData )
	UPROPERTY( EditDefaultsOnly, Category = "SignListItem" )
	TSubclassOf< class UUserWidget > mDefaultItemTemplate;

};

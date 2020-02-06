// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
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

	void Init( class UFGSignInteractWidget* interactWidget, TArray<class UFGSignElementData*> elementData );

	void AddElement( class UFGSignElementData* elementData );

	void OnElementSelected( class UFGSignElementData* elementData );

protected:
	/************************************************************************/
	/*						Begin Widget Bindings
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
	/*                     End Widget Bindings
	/************************************************************************/

	// Reference to the parent interact widget
	class UFGSignInteractWidget* mInteractWidget;

};

// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "Blueprint/UserWidget.h"
#include "FGSignElementDragWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGSignElementDragWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Sets the size and border style of the widget. Calls the blueprint event Init() for further customization
	void NativeInit( FVector2D size, class UFGSignElementWidget* elementWidget );

	UFUNCTION( BlueprintImplementableEvent, Category = "Sign Widget" )
	void Init( class UFGSignElementData* elementData );

	FORCEINLINE void SetElementReference( class UFGSignElementWidget* elementWidget );
	FORCEINLINE class UFGSignElementWidget* GetElementReference() const;

	void NotifyExitCanvasBounds();
	void NotifyEnterCanvasBounds();

	UFUNCTION( BlueprintImplementableEvent, Category = "Sign Widget" )
	void OnExitCanavasBounds();

	UFUNCTION( BlueprintImplementableEvent, Category = "Sign Widget" )
	void OnEnterCanvasBounds();


protected:

	
	// Hold a reference to the widget we are representing
	UPROPERTY()
	class UFGSignElementWidget* mElementReference;

	/************************************************************************/
	/*					Begin Widget Bindings
	/************************************************************************/
	UPROPERTY( meta = (BindWidget ))
	class USizeBox* mSizeBox;

	UPROPERTY( meta = (BindWidget ))
	class UImage* mBackground;
	/************************************************************************/
	/*					End Widget Bindings
	/************************************************************************/

};

void UFGSignElementDragWidget::SetElementReference( UFGSignElementWidget* elementWidget )
{
	mElementReference = elementWidget;
}

UFGSignElementWidget* UFGSignElementDragWidget::GetElementReference() const
{
	return mElementReference;
}

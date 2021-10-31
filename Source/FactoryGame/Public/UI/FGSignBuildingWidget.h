// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateBrush.h"
#include "FGSignTypes.h"
#include "Buildables/FGBuildableWidgetSign.h"
#include "FGSignBuildingWidget.generated.h"

/**
 *	Custom widget that contains a canvas panel widget for holding sign elements (exists on the buildable itself)
 */
UCLASS()
class UFGSignBuildingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init( class AFGBuildableWidgetSign* widgetSign );

	UFUNCTION( BlueprintCallable, Category = "Sign Widget" )
	void AddSignCanvasElement( const FSignStringElement& stringData );

	UFUNCTION( BlueprintCallable, Category = "Sign Widget" )
	void RemoveSignCanvasElement( int32 elementID );

	// Call to Remove all children from the canvas
	void RemoveAllSignElements();

	/************************************************************************/
	/*						Begin Widget Bindings */
	/************************************************************************/ 
	// Size Box that holds our Canvas, its size is set to absolute and the canvas fills that space
	UPROPERTY( meta = ( BindWidget ) )
	class USizeBox* mCanvasSizeBox;
	
	// The canvas panel where actual sign elements will be added
	UPROPERTY( meta=( BindWidget ))
	UCanvasPanel* mRootCanvasPanel;
	/************************************************************************/
	/*                     End Widget Bindings */
	/************************************************************************/
protected:

	UPROPERTY( EditDefaultsOnly, Category = "Sign Widget" )
	FSlateBrush mSelectionBrushTemplate;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Widget" )
	TSubclassOf<class UFGSignElementWidget> mDefaultElementClass;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Widget" )
	TSubclassOf<class UFGSignElementWidget> mTextElementClass;

	UPROPERTY( EditDefaultsOnly, Category = "Sign Widget" )
	TSubclassOf<class UFGSignElementWidget> mIconElementClass;

	UPROPERTY()
	TArray<class UFGSignElementWidget*> mElementWidgets;

private:
	void InitializeSlot( class UCanvasPanelSlot* slot, FVector2D pos, FVector2D size );

	class UFGSignElementWidget* GetElementWidgetById( int32 id );

	UPROPERTY()
	AFGBuildableWidgetSign* mWidgetSign;

};

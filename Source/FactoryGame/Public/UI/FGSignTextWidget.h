// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UI/FGSignElementWidget.h"
#include "FGSignTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGSignTextWidget : public UFGSignElementWidget
{
	GENERATED_BODY()
	
	
public:
	virtual void InitSignElementForInteract( const FInteractElementWidgetData& elementWidgetData ) override;
	virtual void InitSignElementForBuildable( FBuildableElementWidgetData& buildableWidgetData ) override;
	virtual void RefreshElement(bool isInitialization = false  ) override;

	UFUNCTION( BlueprintPure, Category = "Sign Widget" )
	class UTextBlock* GetTextBlock();

protected:

	/************************************************************************/
	/*						Begin Widget Bindings */
	/************************************************************************/
	UPROPERTY( meta=(BindWidget) )
	class UTextBlock* mTextBlock;
	/************************************************************************/
	/*						End Widget Bindings */
	/************************************************************************/

};

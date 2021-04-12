// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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
	virtual void InitSignElement( const FSignElementWidgetData& elementWidgetData ) override;
	virtual void SetElementData( class UFGSignElementData* data ) override;
	virtual void RefreshElement(bool isInitialization = false  ) override;

	UFUNCTION( BlueprintPure, Category = "Sign Widget" )
	class UTextBlock* GetTextBlock();

protected:

	/************************************************************************/
	/*						Begin Widget Bindings
	/************************************************************************/
	UPROPERTY( meta=(BindWidget) )
	class UTextBlock* mTextBlock;
	/************************************************************************/
	/*						End Widget Bindings
	/************************************************************************/

};

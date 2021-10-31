// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UI/FGSignElementWidget.h"
#include "FGSignIconWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGSignIconWidget: public UFGSignElementWidget
{
	GENERATED_BODY()
	
	
public:
	virtual void InitSignElementForInteract( const FInteractElementWidgetData& elementWidgetData ) override;
	virtual void InitSignElementForBuildable( FBuildableElementWidgetData& buildableWidgetData ) override;

	virtual void RefreshElement(bool isInitialization = false  ) override;

	UFUNCTION( BlueprintPure, Category = "Sign Widget" )
	class UImage* GetImage();

protected:

	/************************************************************************/
	/*						Begin Widget Bindings */
	/************************************************************************/
	UPROPERTY( meta=(BindWidget) )
	class UImage* mImage;
	/************************************************************************/
	/*						End Widget Bindings */
	/************************************************************************/

};

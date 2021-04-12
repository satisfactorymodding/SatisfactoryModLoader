// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGPopupInstigatorInterface.generated.h"

/**
 * @todo Please comment me
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGPopupInstigatorInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGPopupInstigatorInterface
{
	GENERATED_BODY()
public:
	/** Called from FGPopupWidgetContent to fill its contents */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Popup" )
	void WidgetFactory( TSubclassOf<class UUserWidget> popupClass, TArray<class UUserWidget*>& out_widgets );

	/** Called when the popup is closed and returns an int that can be used to interpret selection */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Popup" )
	void NotifyPopupClosed( TSubclassOf<class UUserWidget> popupClass, int32 exitCode );
};

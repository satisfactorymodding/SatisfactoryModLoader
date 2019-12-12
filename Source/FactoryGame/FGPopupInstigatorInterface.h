// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGPopupInstigatorInterface.generated.h"


// This class does not need to be modified.
UINTERFACE( Blueprintable )
class UFGPopupInstigatorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FACTORYGAME_API IFGPopupInstigatorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/** Called from FGPopupWidgetContent to fill its contents */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Popup" )
		void WidgetFactory( TSubclassOf<class UUserWidget> popupClass, TArray<class UUserWidget*>& out_widgets );

	/** Called when the popup is closed and returns an int that can be used to interpret selection */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Popup" )
		void NotifyPopupClosed( TSubclassOf<class UUserWidget> popupClass, int32 exitCode );


};

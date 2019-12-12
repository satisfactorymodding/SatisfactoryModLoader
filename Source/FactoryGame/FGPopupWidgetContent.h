// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGPopupWidgetContent.generated.h"



/**
 *
 */
UCLASS()
class FACTORYGAME_API UFGPopupWidgetContent : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Called by the popup widget to determine if its buttons should be enabled */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "PopupContent" )
	bool GetShouldOkayBeEnabled();

	/** Assigns the UObject which is meant to implement the FGPopupInstigatorInterface */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "PopupContent" )
	void SetInstigatorAndInitialize( UObject* instigator );

	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "PopupContent" )
	void SetOptionalTextElements( const FText& title, const FText& desc );

	/** Called when the containing popup is confirmed */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "PopupContent" )
	void NotifyPopupConfirmed();

	/** Called when the containing popup is closed without confirmation */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "PopupContent" )
	void NotifyPopupCanceled();


public:
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "PopupContent" )
	UObject* mInstigator;

	UPROPERTY( BlueprintReadWrite, Category = "PopupContent" )
	class UFGPopupWidget* mPopupWidget;

};

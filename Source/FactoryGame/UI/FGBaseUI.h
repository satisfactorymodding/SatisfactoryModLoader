// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UMG.h"
#include "Blueprint/UserWidget.h"
#include "FGPopupWidget.h"
#include "FGBaseUI.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGBaseUI : public UUserWidget
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGBaseUI( const FObjectInitializer& ObjectInitializer );

	virtual void NativeConstruct();

	/** Tick tock */
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime );

	/** Creates a popup */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI" )
	class UFGPopupWidget* CreatePopupWidget( FPopupData popupData );
	
	/** Adds a popup to the queue */
	void AddPopupToQueue( FPopupData inPopupData );

	/** Adds a popup to the qu� */
	UFUNCTION( BlueprintCallable, Category = "UI", meta = ( AutoCreateRefTerm = "ConfirmClickDelegate", DeprecatedFunction, DeprecationMessage="Use AddPopupWithCloseDelegate instead" ) )
	void AddPopup( FText Title, FText Body, const FPopupConfirmClicked& ConfirmClickDelegate, EPopupId PopupID = PID_OK, TSubclassOf< UUserWidget > popupClass = nullptr );
	
	/** Removes a pending popup */
	UFUNCTION( BlueprintCallable, Category="UI")
	void PopPopupQueue();

	/** Getter for popup */
	UFUNCTION( BlueprintPure, Category = "UI" )
	class UFGPopupWidget* GetPopup() { return mActivePopup; }

	/** Sets the popup variable  */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void SetPopup( class UFGPopupWidget* inPopup ) { mActivePopup = inPopup; }

	/** Starts the creation of popup */
	void ShowPopup();

	/** Closes a popup */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI" )
	void ClosePopup();
protected:
	/** Can a popup be displayed at this moment? */
	bool mCanDisplayPopup;

	/** Current active popup */
	UPROPERTY()
	class UFGPopupWidget* mActivePopup;

	/** Queue with popups to show */
	TArray< FPopupData > mPopupDataQueue;
};

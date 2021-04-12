// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMG.h"
#include "Blueprint/UserWidget.h"
#include "UI/FGPopupWidget.h"
#include "FGBaseUI.generated.h"

/**
 * @todo Please comment me
 */
UCLASS()
class FACTORYGAME_API UFGBaseUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFGBaseUI( const FObjectInitializer& ObjectInitializer );

	// Begin UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime ) override;
	// End UUserWidget interface

	/** Creates a popup */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI" )
	class UFGPopupWidget* CreatePopupWidget( FPopupData popupData );
	
	/** Adds a popup to the queue */
	void AddPopupToQueue( FPopupData inPopupData );

	/** Adds a popup to the queue */
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

	/** Clear the popup queue of all popups of the given class */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void ClearPopupQueueOfClass( TSubclassOf< UUserWidget > widgetClass );

protected:
	/** Can a popup be displayed at this moment? */
	bool mCanDisplayPopup;

	/** Current active popup */
	UPROPERTY()
	class UFGPopupWidget* mActivePopup;

	/** Queue with popups to show */
	TArray< FPopupData > mPopupDataQueue;
};

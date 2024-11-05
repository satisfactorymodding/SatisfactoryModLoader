// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGInteractWidget.h"
#include "FGPopupInstigatorInterface.h"
#include "FGPopupWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE( FPopupConfirmClicked );

DECLARE_DYNAMIC_DELEGATE_OneParam( FPopupClosed, bool, ConfirmClicked );

UENUM( BlueprintType )
enum EPopupId
{
	PID_OK,
	PID_OK_CANCEL,
	PID_NONE
};

USTRUCT( BlueprintType )
struct FPopupData
{
	GENERATED_BODY();
public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Popup" )
	FText Title = {};

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Popup" )
	FText Body = {};

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Popup" )
	TEnumAsByte< EPopupId > ID = EPopupId::PID_NONE;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Popup" )
	TSubclassOf< class UUserWidget > PopupClass = {};

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Popup" )
	UObject* Instigator = nullptr;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Popup" )
	class UFGPopupWidgetContent* PopupContent = nullptr;
		
	UPROPERTY()
	FPopupConfirmClicked PopupConfirmClickedDelegate_DEPRECATED = {};

	UPROPERTY()
	FPopupClosed PopupClosedDelegate = {};

	TWeakPtr<SWidget> FocusOnClose; // <FL> [WuttkeP] Allow restoring focused widget when a popup is closed.

};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGPopupWidget : public UFGInteractWidget
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintCallable, Category = "Popup", meta=(DeprecatedFunction, DeprecationMessage="Use CallPopupClosedClicked instead") )
	void CallPopupConfirmClicked();

	UFUNCTION( BlueprintCallable, Category = "Popup" )
	void CallPopupClosedClicked( bool confirm );
public:
	int32 mPriority;

	/** Delegate for when pressing the confirm button in popup */
	UPROPERTY()
	FPopupConfirmClicked mPopupConfirmClickedDelegate_DEPRECATED;

	/** Delegate for when pressing the confirm button in popup */
	UPROPERTY()
	FPopupClosed mPopupClosedDelegate;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Popup" )
	UObject* mInstigator;

	/** The popup widget content if the popup was created with an instance of this type. So this may be null for simple popups */
	UPROPERTY(Transient)
	TObjectPtr<UFGPopupWidgetContent> mContent;

	TWeakPtr<SWidget> mFocusOnClose; // <FL> [WuttkeP] Allow restoring focused widget when a popup is closed.

};

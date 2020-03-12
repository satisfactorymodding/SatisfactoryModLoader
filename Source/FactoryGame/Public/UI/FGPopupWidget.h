// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "../FGPopupInstigatorInterface.h"
#include "FGInteractWidget.h"
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
struct FACTORYGAME_API FPopupData
{
	GENERATED_BODY();
public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Popup" )
	FText Title;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Popup" )
	FText Body;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Popup" )
	TEnumAsByte< EPopupId > ID;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Popup" )
	TSubclassOf< class UUserWidget > PopupClass;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Popup" )
	UObject* Instigator;
		
	UPROPERTY()
	FPopupConfirmClicked PopupConfirmClickedDelegate_DEPRECATED;

	UPROPERTY()
	FPopupClosed PopupClosedDelegate;


public:
	FORCEINLINE ~FPopupData() = default;
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


public:
	FORCEINLINE ~UFGPopupWidget() = default;
};

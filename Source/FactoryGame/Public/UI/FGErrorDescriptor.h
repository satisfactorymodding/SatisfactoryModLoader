// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "MVVMViewModelBase.h"
#include "FGErrorDescriptor.generated.h"

class UFGPopupWidgetContent;
USTRUCT()
struct FErrorDescriptor: public FTableRowBase
{
	GENERATED_BODY()

	/**
	 * Collection of error tags mapping to this error. 
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FGameplayTagContainer ErrorTags;

	/**
	 * If specified, this popup class will be used to display error information.
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr< UFGPopupWidgetContent > PopupClass;

	/**
	 * An error code that will be presented to the user for this error.
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName ErrorCode;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FText ErrorDescription;

	/**
	 * Whether we should show a popup for this error or not 
	 */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	bool bShowPopup = true;
};

UCLASS()
class UFGErrorDescriptor : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:

	UPROPERTY(FieldNotify, BlueprintReadOnly)
	FName ErrorCode;

	UPROPERTY(FieldNotify, BlueprintReadOnly)
	FText ErrorDescription;

	UPROPERTY(FieldNotify, BlueprintReadOnly)
	FString ErrorDetails;
};
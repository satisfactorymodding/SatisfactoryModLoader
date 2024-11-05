// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Blueprint/IUserObjectListEntry.h"
#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Templates/SubclassOf.h"
#include "FGGenericListItemDescriptor.generated.h"

class UUserWidget;
/**
 *
 */
UCLASS()
class FACTORYGAME_API UFGGenericListItemDescriptor : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> mWidgetClass;

	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<UObject> mObject;

	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType="ToClass"))
	static UObject* CastGenericListItemDescriptor(UObject* InObject, TSubclassOf<UObject> ToClass);
};

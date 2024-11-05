// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "MVVMViewModelBase.h"
#include "FGGenericListModel.generated.h"

class UFGGenericListItemDescriptor;
/**
 *
 */
UCLASS()
class FACTORYGAME_API UFGGenericListModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:

protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Category=ListModel)
	TArray<TObjectPtr<UFGGenericListItemDescriptor>> mListEntries;
};

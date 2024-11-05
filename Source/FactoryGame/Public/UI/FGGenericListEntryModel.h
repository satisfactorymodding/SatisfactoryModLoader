// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "MVVMViewModelBase.h"
#include "FGGenericListEntryModel.generated.h"

struct FCommonSessionCreationSettings;
/**
 * Describes a generic metadata entry which could be an entry in a list.
 */
UCLASS()
class FACTORYGAME_API UFGGenericListEntryModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetTitle(const FText& InTitle);

	UFUNCTION(BlueprintCallable)
	void SetBody(const FText& InBody);

	UFUNCTION(BlueprintCallable)
	void SetIcon(const TSoftObjectPtr<UTexture2D>& InIcon);

	UFUNCTION(BlueprintCallable)
	void SetInnerInfo(UFGGenericListEntryModel* InInner);

	UFUNCTION(BlueprintCallable)
	void SetIsVisible(bool bInIsVisible);
	
protected:
	UPROPERTY(EditAnywhere, FieldNotify, BlueprintReadWrite, Setter)
	FText Title;

	UPROPERTY(EditAnywhere, FieldNotify, BlueprintReadWrite, Setter)
	FText Body;

	UPROPERTY(EditAnywhere, FieldNotify, BlueprintReadWrite, Setter)
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, FieldNotify, BlueprintReadWrite, Setter)
	TObjectPtr<UFGGenericListEntryModel> InnerInfo;

	UPROPERTY(EditAnywhere, FieldNotify, BlueprintReadWrite, BlueprintSetter=SetIsVisible)
	bool bIsVisible = true;
};

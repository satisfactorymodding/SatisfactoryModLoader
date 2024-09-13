// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MVVMViewModelBase.h"

#include "GameplayTagContainerViewModel.generated.h"

/**
 *
 */
UCLASS()
class ONLINEINTEGRATION_API UGameplayTagContainerViewModel final: public UMVVMViewModelBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category=TagContainer)
	void AddTag(FGameplayTag InTag);

	UFUNCTION(BlueprintCallable, Category=TagContainer)
	void RemoveTag(FGameplayTag InTag);
	
	UFUNCTION(BlueprintCallable, Category=TagContainer)
	void SetTag(FGameplayTag InTag, bool bSet);

	UFUNCTION(BlueprintCallable, Category=TagContainer)
	void ResetTags(const FGameplayTagContainer& State);

	UFUNCTION(BlueprintCallable, Category=TagContainer)
	bool HasTagExact(FGameplayTag InTag) const;

	UFUNCTION(BlueprintCallable, Category=TagContainer)
	bool HasAllExact(const FGameplayTagContainer& InTags) const;

	UFUNCTION(BlueprintCallable, Category=TagContainer)
	bool HasTag(FGameplayTag InTag) const;
protected:
	UPROPERTY(FieldNotify, BlueprintReadOnly)
	FGameplayTagContainer Tags;
};

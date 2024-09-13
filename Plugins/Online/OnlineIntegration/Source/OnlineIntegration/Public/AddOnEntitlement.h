// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "AddOnEntitlement.generated.h"

class UTexture2D;
class ULocalUserInfo;

/**
 * Data asset like object that can be used to reference a single entitlement, as defined by the ICommerce interface.
 * Can be used to display entitlement information in the UI or to check if a player has a specific entitlement.
 */
UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UAddOnEntitlement final : public UMVVMViewModelBase
{
	GENERATED_BODY()
	friend class UCommonUserSubsystem;
public:
	UFUNCTION(BlueprintCallable)
	bool DoesPlayerHaveEntitlement(const ULocalUserInfo* User) const;
	
protected:
	/**
	 * A human-readable name for the entitlement.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, FieldNotify, Category=UserInterface)
	FText DisplayName;

	/**
	 *
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, FieldNotify, Category=UserInterface)
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, FieldNotify, Category=UserInterface)
	TMap<FName, FString> PerPlatformIds;

	/**
	 * An array of all the local users that have this entitlement.
	 * */
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TSet<TObjectPtr<ULocalUserInfo>> UsersWithEntitlement;
};

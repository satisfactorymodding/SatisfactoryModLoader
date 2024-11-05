// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "FGOnlineIntegrationSettings.generated.h"

class UAddOnEntitlement;
class UTexture2D;
class UDataTable;
class UFGSessionCreationSummaryItemModel;
class UUserWidget;

USTRUCT()
struct FACTORYGAME_API FSessionValidationInfoRowDescriptor: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UFGSessionCreationSummaryItemModel> ModelClass;
};

USTRUCT()
struct FACTORYGAME_API FUserProfileRowDesc: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer RequiredUserTags;

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer RequiredPlatformTraits;
};

USTRUCT()
struct FACTORYGAME_API FReadOnlySessionInfoRowDesc: public FTableRowBase
{
	GENERATED_BODY()

	/**
	 * The widget class used for this row.
	 */
	UPROPERTY( EditAnywhere)
	TSoftClassPtr<UUserWidget> WidgetClass;

	/**
	 * If the session is read only (not hosted or joined by this client) then the row will only be created if this session attribute exists
	 */
	UPROPERTY( EditAnywhere)
	FGameplayTag SessionAttribute;
};

/**
 *
 */
UCLASS( config = Game, DefaultConfig, meta = ( DisplayName = "Online Integration Settings" ) )
class FACTORYGAME_API UFGOnlineIntegrationSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UFGOnlineIntegrationSettings();

	static const UFGOnlineIntegrationSettings* Get();
	UDataTable* GetOnlineStatDataTable() const;
	UDataTable* GetOnlineAggregatedStatDataTable() const;
	UDataTable* GetSessionValidationRowDescTable() const;
	UDataTable* GetReadOnlySessionInfoRowDescTable() const;
	TArray<UAddOnEntitlement*> LoadAddonEntitlements() const;
	
protected:
	UPROPERTY( EditAnywhere, Config, Category = "Online Stats",
			   meta = ( RequiredAssetDataTags = "RowStructure=/Script/OnlineIntegration.OnlineStatData" ) )
	TSoftObjectPtr< UDataTable > mOnlineStatDataTable;

	UPROPERTY( EditAnywhere, Config, Category = "Online Stats",
			   meta = ( RequiredAssetDataTags = "RowStructure=/Script/OnlineIntegration.OnlineStatDataAggregated" ) )
	TSoftObjectPtr< UDataTable > mOnlineAggregatedStatDataTable;

	UPROPERTY( EditAnywhere, Config, Category = "UI Settings",
			   meta = ( RequiredAssetDataTags = "RowStructure=/Script/FactoryGame.SessionValidationInfoRowDescriptor" ) )
	TSoftObjectPtr< UDataTable > mSessionValidationRowDescTable;
	
	UPROPERTY( EditAnywhere, Config, Category = "UI Settings",
		   meta = ( RequiredAssetDataTags = "RowStructure=/Script/FactoryGame.ReadOnlySessionInfoRowDesc" ) )
	TSoftObjectPtr< UDataTable > mSessionInformationRowDescTable;

	UPROPERTY( EditAnywhere, Config, Category=DLC)
	TArray<TSoftObjectPtr<UAddOnEntitlement>> mAddonEntitlements;
};

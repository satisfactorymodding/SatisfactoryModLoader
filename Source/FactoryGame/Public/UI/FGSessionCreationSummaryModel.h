// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGGenericListEntryModel.h"
#include "FGGenericListModel.h"
#include "SessionCreationSettings.h"
#include "FGSessionCreationSummaryModel.generated.h"

UCLASS(Abstract, Blueprintable)
class FACTORYGAME_API UFGSessionCreationSummaryItemModel: public UFGGenericListEntryModel
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintNativeEvent )
	void SetSessionCreationSettings( const FCommonSessionCreationSettings& inCommonSessionCreationSettings );
};


/**
 * 
 */
UCLASS(BlueprintType)
class FACTORYGAME_API UFGSessionCreationSummaryModel: public UFGGenericListModel
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetSessionCreationSettings(const FCommonSessionCreationSettings& InSessionCreationSettings);
	
protected:
	void CreateModelFields();
	virtual void PostInitProperties() override;
	
	UPROPERTY(FieldNotify, BlueprintSetter=SetSessionCreationSettings)
	FCommonSessionCreationSettings mSessionCreationSettings;
};
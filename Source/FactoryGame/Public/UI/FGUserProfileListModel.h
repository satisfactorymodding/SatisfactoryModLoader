// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGGenericListModel.h"
#include "FGUserProfileListModel.generated.h"

class ULocalUserInfo;
/**
 *
 */
UCLASS()
class FACTORYGAME_API UFGUserProfileListModel : public UFGGenericListModel
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintCallable )
	void SetLocalUserInfo( ULocalUserInfo* inLocalUserInfo );

	UFUNCTION( BlueprintCallable )
	void SetRowDescriptorTable( UPARAM(meta = ( RequiredAssetDataTags = "RowStructure=/Script/FactoryGame.ReadOnlySessionInfoRowDesc" )) UDataTable* inDataTable );

	UFUNCTION( BlueprintCallable )
	void RebuildList();

protected:
	
	UPROPERTY( FieldNotify, BlueprintSetter=SetLocalUserInfo )
	TObjectPtr< ULocalUserInfo > mUserInfo;

	UPROPERTY( EditAnywhere, BlueprintSetter=SetRowDescriptorTable,
		   meta = ( RequiredAssetDataTags = "RowStructure=/Script/FactoryGame.ReadOnlySessionInfoRowDesc" ) )
	TObjectPtr< UDataTable > mRowDescTable;
};

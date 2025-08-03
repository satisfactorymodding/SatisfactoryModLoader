#pragma once

#include "CoreMinimal.h"
#include "AssetDefinition.h"
#include "AssetDefinitionHookBlueprint.generated.h"

UCLASS()
class SMLEDITOR_API UAssetDefinition_HookBlueprint : public UAssetDefinition {
	GENERATED_BODY()
public:
	// Begin UAssetDefinition interface
	virtual FText GetAssetDisplayName() const override;
	virtual FText GetAssetDisplayName(const FAssetData& AssetData) const override;
	virtual FText GetAssetDescription(const FAssetData& AssetData) const override;
	virtual FLinearColor GetAssetColor() const override { return FLinearColor(FColor( 63, 126, 255 )); }
	virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;
	virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
	// End UAssetDefinition interface
};

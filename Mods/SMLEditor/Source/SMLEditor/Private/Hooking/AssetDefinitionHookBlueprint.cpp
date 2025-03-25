#include "Hooking/AssetDefinitionHookBlueprint.h"
#include "Hooking/HookBlueprintEditor.h"
#include "Patching/BlueprintHookBlueprint.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

FText UAssetDefinition_HookBlueprint::GetAssetDisplayName() const {
	return LOCTEXT("HookBlueprint_AssetDisplayName", "Blueprint Hook");
}

FText UAssetDefinition_HookBlueprint::GetAssetDescription(const FAssetData& AssetData) const {
	FString Description = AssetData.GetTagValueRef<FString>(GET_MEMBER_NAME_CHECKED(UBlueprint, BlueprintDescription));
	if (!Description.IsEmpty()) {
		Description.ReplaceInline(TEXT("\\n"), TEXT("\n"));
		return FText::FromString(MoveTemp(Description));
	}
	return FText::GetEmpty();
}

EAssetCommandResult UAssetDefinition_HookBlueprint::OpenAssets(const FAssetOpenArgs& OpenArgs) const {
	TArray<FAssetData> OutAssetsThatFailedToLoad;
	for (UHookBlueprint* Blueprint : OpenArgs.LoadObjects<UHookBlueprint>({}, &OutAssetsThatFailedToLoad)) {
		const TSharedRef<FHookBlueprintEditor> NewBlueprintEditor(new FHookBlueprintEditor());
		NewBlueprintEditor->InitHookBlueprintEditor(OpenArgs.GetToolkitMode(), OpenArgs.ToolkitHost, Blueprint);
	}
	return EAssetCommandResult::Handled;
}

TSoftClassPtr<UObject> UAssetDefinition_HookBlueprint::GetAssetClass() const {
	return UHookBlueprint::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UAssetDefinition_HookBlueprint::GetAssetCategories() const {
	static const auto Categories = { EAssetCategoryPaths::Blueprint };
	return Categories;
}

#undef LOCTEXT_NAMESPACE

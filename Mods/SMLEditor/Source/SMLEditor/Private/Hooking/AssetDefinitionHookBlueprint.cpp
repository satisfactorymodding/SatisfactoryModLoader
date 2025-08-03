#include "Hooking/AssetDefinitionHookBlueprint.h"
#include "Hooking/HookBlueprintEditor.h"
#include "Patching/BlueprintHookBlueprint.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

FText UAssetDefinition_HookBlueprint::GetAssetDisplayName() const {
	// Blueprint hook is the generic asset name when no context is available to differentiate it from blueprint mixins
	return LOCTEXT("HookBlueprint_AssetDisplayName", "Blueprint Hook");
}

FText UAssetDefinition_HookBlueprint::GetAssetDisplayName(const FAssetData& AssetData) const {
	// Show a different name for blueprint mixin assets
	const FString TargetClassExportObjectPath = AssetData.GetTagValueRef<FString>(GET_MEMBER_NAME_CHECKED(UHookBlueprint, MixinTargetClass));
	if (!TargetClassExportObjectPath.IsEmpty() && TargetClassExportObjectPath != TEXT("None")) {
		const FString TargetClassObjectPath = FPackageName::ExportTextPathToObjectPath(TargetClassExportObjectPath);
		FString TargetClassName = FPackageName::ObjectPathToObjectName(TargetClassObjectPath);
		TargetClassName.RemoveFromEnd(TEXT("_C"), ESearchCase::CaseSensitive);

		// If we have a valid mixin class name, show the full display name with the mixin target class, otherwise show a generic name
		if (!TargetClassName.IsEmpty()) {
			return FText::Format(LOCTEXT("HookBlueprint_MixinAssetFullDisplayName", "Blueprint Mixin ({0})"), FText::AsCultureInvariant(TargetClassName));
		}
		return LOCTEXT("HookBlueprint_MixinAssetDisplayName", "Blueprint Mixin");
	}
	// Assume this is a static blueprint hook asset otherwise
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

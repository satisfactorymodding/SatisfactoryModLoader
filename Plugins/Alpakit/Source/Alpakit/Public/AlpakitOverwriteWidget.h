#pragma once
#include "Slate.h"
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AlpakitSettings.h"
#include "AssetData.h"

struct FSelectedModInfo {
	FString ModReference;
	FString ModDisplayName;
};

class ALPAKIT_API SAlpakitOverwriteWidget : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SAlpakitOverwriteWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void SetPathsToOverwrite(TArray<FAssetIdentifier> SelectedIdentifiers);
	void SaveSettings() const;
private:
	UAlpakitSettings* AlpakitSettings;
	TArray<FAssetIdentifier> SelectedPaths;
	TSharedPtr<SListView<TSharedPtr<FSelectedModInfo>>> ListViewWidget;
	TArray<TSharedPtr<FSelectedModInfo>> Items;

	ECheckBoxState DoesModHaveAllOverwrites(const FSelectedModInfo& ModInfo);
	void ToggleOverwritesForMod(const FSelectedModInfo& ModInfo, bool bRemoveOverwrites);
	
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FSelectedModInfo> Item, const TSharedRef<STableViewBase>& OwnerTable);
};
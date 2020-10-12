#include "AlpakitOverwriteWidget.h"

void SAlpakitOverwriteWidget::Construct(const FArguments& InArgs) {
	AlpakitSettings = UAlpakitSettings::Get();
	
	for (const FAlpakitMod& AlpakitMod : AlpakitSettings->Mods) {
		TSharedPtr<FSelectedModInfo> Item = MakeShareable(new FSelectedModInfo());
		Item->ModReference = AlpakitMod.Name;
		Item->ModDisplayName = AlpakitMod.DisplayName;
		Items.Add(Item);
	}
	ChildSlot [
		SNew(SScrollBox)
		+SScrollBox::Slot() [
			SAssignNew(ListViewWidget, SListView<TSharedPtr<FSelectedModInfo>>)
			.ItemHeight(24)
			.SelectionMode(ESelectionMode::None)
			.ListItemsSource(&Items)
			.OnGenerateRow(this, &SAlpakitOverwriteWidget::OnGenerateRowForList)
		]
	];
}

void SAlpakitOverwriteWidget::SetPathsToOverwrite(TArray<FAssetIdentifier> SelectedIdentifiers) {
	SelectedPaths = SelectedIdentifiers;
}

void SAlpakitOverwriteWidget::SaveSettings() const {
	AlpakitSettings->SaveSettings();
}

ECheckBoxState SAlpakitOverwriteWidget::DoesModHaveAllOverwrites(const FSelectedModInfo& ModInfo) {
	const int32 ModIndex = AlpakitSettings->FindModIndexByModReference(ModInfo.ModReference);
	if (ModIndex != INDEX_NONE) {
		const FAlpakitMod& AlpakitMod = AlpakitSettings->Mods[ModIndex];
		int32 AssetsOverwritten = 0;
		for (const FAssetIdentifier& AssetIdentifier : SelectedPaths) {
			const FString AssetIdentifierString = AssetIdentifier.ToString();
			if (AlpakitMod.OverwritePaths.Contains(AssetIdentifierString)) {
				AssetsOverwritten++;
			}
		}
		if (AssetsOverwritten == 0) {
			return ECheckBoxState::Unchecked;
		}
		if (AssetsOverwritten == SelectedPaths.Num()) {
			return ECheckBoxState::Checked;
		}
	}
	return ECheckBoxState::Undetermined;
}

void SAlpakitOverwriteWidget::ToggleOverwritesForMod(const FSelectedModInfo& ModInfo, bool bRemoveOverwrites) {
	const int32 ModIndex = AlpakitSettings->FindModIndexByModReference(ModInfo.ModReference);
	if (ModIndex != INDEX_NONE) {
		FAlpakitMod& AlpakitMod = AlpakitSettings->Mods[ModIndex];
		for (const FAssetIdentifier& AssetIdentifier : SelectedPaths) {
			const FString AssetIdentifierString = AssetIdentifier.ToString();
			if (bRemoveOverwrites) {
				//Remove override from alpakit mod object
				AlpakitMod.OverwritePaths.Remove(AssetIdentifierString);
			} else {
				//Add override into alpakit mod object, but only if it's unique
				AlpakitMod.OverwritePaths.AddUnique(AssetIdentifierString);
			}
		}
	}
	//Automatically save alpakit settings when we toggle overwrites
	SaveSettings();
}

TSharedRef<ITableRow> SAlpakitOverwriteWidget::OnGenerateRowForList(TSharedPtr<FSelectedModInfo> Item, const TSharedRef<STableViewBase>& OwnerTable) {
	return
		SNew(STableRow<TSharedPtr<FSelectedModInfo>>, OwnerTable)
		.Padding(2.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.AutoWidth()
			.Padding(2.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
					.Padding(3.0f)
					.AutoWidth()
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Fill)
					[
						SNew(STextBlock)
						.Text(FText::FromString(Item->ModDisplayName))
					]
				+ SHorizontalBox::Slot()
					.Padding(3.0f)
					.FillWidth(1.0f)
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Fill)
					[
						SNew(SCheckBox)
						.IsChecked_Lambda([this, Item]() { 
							return DoesModHaveAllOverwrites(*Item);
						})
						.OnCheckStateChanged_Lambda([this, Item](ECheckBoxState NewState) {
							if (NewState != ECheckBoxState::Undetermined) {
								const bool bRemoveOverwrites = NewState == ECheckBoxState::Unchecked;
								ToggleOverwritesForMod(*Item, bRemoveOverwrites);
							}
						})
					]
			]
		];
}


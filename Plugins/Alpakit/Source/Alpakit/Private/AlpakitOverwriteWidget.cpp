// Fill out your copyright notice in the Description page of Project Settings.

#include "AlpakitOverwriteWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SAlpakitOverwriteWidget::Construct(const FArguments& InArgs)
{
	Settings = GetMutableDefault<UAlpakitSettings>();

	for (int i = 0; i < Settings->Mods.Num(); i++)
	{
		TSharedPtr<FModIndex> item = MakeShareable(new FModIndex());
		item.Get()->idx = i;
		Items.Add(item);
	}
	ChildSlot
	[
		SNew(SScrollBox)
		//The actual list view creation
		+ SScrollBox::Slot()
		[
			SAssignNew(ListViewWidget, SListView<TSharedPtr<FModIndex>>)
			.ItemHeight(24)
			.SelectionMode(ESelectionMode::None)
			.ListItemsSource(&Items) //The Items array is the source of this listview
			.OnGenerateRow(this, &SAlpakitOverwriteWidget::OnGenerateRowForList)
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SAlpakitOverwriteWidget::SetPathsToOverwrite(TArray<FAssetIdentifier> SelectedIdentifiers)
{
	SelectedPaths = SelectedIdentifiers;
}

TSharedRef<ITableRow> SAlpakitOverwriteWidget::OnGenerateRowForList(TSharedPtr<FModIndex> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	//Create the row
	return
		SNew(STableRow< TSharedPtr<FModIndex> >, OwnerTable)
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
						.Text(FText::FromString(Settings->Mods[Item->idx].Name))
					]
				+ SHorizontalBox::Slot()
					.Padding(3.0f)
					.FillWidth(1.0f)
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Fill)
					[
						SNew(SCheckBox)
						.IsChecked_Lambda([this, Item]() { 
							int matchCount = 0;
							for (FAssetIdentifier asset : this->SelectedPaths)
								if (this->Settings->Mods[Item->idx].OverwritePaths.Contains(asset.ToString()))
									matchCount++;
							if (matchCount == 0)
								return ECheckBoxState::Unchecked;
							if (matchCount == this->SelectedPaths.Num())
								return ECheckBoxState::Checked;
							return ECheckBoxState::Undetermined;
						})
						.OnCheckStateChanged_Lambda([this, Item](ECheckBoxState state) {
							if (state == ECheckBoxState::Checked)
							{
								for (FAssetIdentifier asset : this->SelectedPaths)
									if (!this->Settings->Mods[Item->idx].OverwritePaths.Contains(asset.ToString()))
										this->Settings->Mods[Item->idx].OverwritePaths.Add(asset.ToString());
							}
							else if(state == ECheckBoxState::Unchecked)
							{
								for (FAssetIdentifier asset : this->SelectedPaths)
									if (this->Settings->Mods[Item->idx].OverwritePaths.Contains(asset.ToString()))
										this->Settings->Mods[Item->idx].OverwritePaths.Remove(asset.ToString());
							}
							Settings->SaveConfig();
						})
					]
			]
		];
}


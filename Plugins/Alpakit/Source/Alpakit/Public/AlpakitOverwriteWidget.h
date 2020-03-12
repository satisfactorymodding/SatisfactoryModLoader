// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Slate.h"
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "AlpakitSettings.h"
#include "AssetData.h"

class FModIndex
{
public:
	int idx;
};

class ALPAKIT_API SAlpakitOverwriteWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAlpakitOverwriteWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void SetPathsToOverwrite(TArray<FAssetIdentifier> SelectedIdentifiers);

private:
	UAlpakitSettings* Settings;

	TArray<FAssetIdentifier> SelectedPaths;

	TSharedPtr<SListView<TSharedPtr<FModIndex>>> ListViewWidget;
	
	TArray<TSharedPtr<FModIndex>> Items;
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FModIndex> Item, const TSharedRef<STableViewBase>& OwnerTable);
};
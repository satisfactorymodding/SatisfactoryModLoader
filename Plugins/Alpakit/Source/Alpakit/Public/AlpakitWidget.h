#pragma once

#include "AlpakitSettings.h"
#include "Slate.h"
#include "IDetailsView.h"
#include "Components/Widget.h"

class SAlpakitWidget : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SAlpakitWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void SaveSettings() const;
private:
	UAlpakitSettings* AlpakitSettings;
	TSharedPtr<SButton> AlpakitButton;
	TSharedPtr<SButton> SaveSettingsButton;
	TSharedPtr<IDetailsView> DetailsView;

	FReply SavedSettingsTriggered() const;
	FReply PackButtonTriggered();
};

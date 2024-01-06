#pragma once

#include "AlpakitModEntryList.h"
#include "Slate.h"

class SAlpakitWidget : public SCompoundWidget {
public:
    SLATE_BEGIN_ARGS(SAlpakitWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedPtr<IDetailsView> DetailsView;
    TSharedPtr<SAlpakitModEntryList> ModList;
    TSharedPtr<STextBlock> QueueText;
    TSharedPtr<SButton> AlpakitAllDevButton;
    TSharedPtr<SButton> AlpakitAllReleaseButton;

    FReply PackageAllMods(bool ReleaseBuild);
	FReply CreateMod();

	bool IsPackageButtonEnabled() const;
};

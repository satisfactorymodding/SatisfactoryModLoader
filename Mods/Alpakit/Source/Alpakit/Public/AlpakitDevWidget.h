#pragma once

#include "AlpakitModEntryList.h"

class SAlpakitDevWidget : public SCompoundWidget {
public:
    SLATE_BEGIN_ARGS(SAlpakitDevWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedPtr<IDetailsView> DetailsView;
    TSharedPtr<SAlpakitModEntryList> ModList;

    FReply PackageAllMods();
	FReply CreateMod();

	bool IsPackageButtonEnabled() const;
};

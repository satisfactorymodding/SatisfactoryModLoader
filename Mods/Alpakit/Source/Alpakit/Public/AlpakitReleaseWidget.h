#pragma once

#include "AlpakitModEntryList.h"
#include "ModTargetsConfig.h"
#include "Slate.h"

class SAlpakitReleaseWidget : public SCompoundWidget {
public:
    SLATE_BEGIN_ARGS(SAlpakitReleaseWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedPtr<SAlpakitModEntryList> ModList;
    TMap<FString, TSharedRef<FModTargetsConfig>> ModTargetsConfigs;

    FReply PackageAllMods();

	bool IsPackageButtonEnabled() const;
};

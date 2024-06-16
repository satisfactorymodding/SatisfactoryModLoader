#pragma once

#include "AlpakitModEntryList.h"
#include "ModTargetsConfig.h"
#include "Slate.h"

class SAlpakitReleaseWidget : public SCompoundWidget {
public:
    SLATE_BEGIN_ARGS(SAlpakitReleaseWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

    static FString GetModSMLDependencyVersion(TSharedRef<IPlugin> Mod);
    static void SetModSMLDependencyVersion(TSharedRef<IPlugin> Mod, FString Version);
    static FString GetModGameVersion(TSharedRef<IPlugin> Mod);
    static void SetModGameVersion(TSharedRef<IPlugin> Mod, FString Version);
private:
    TSharedPtr<SAlpakitModEntryList> ModList;
    TMap<FString, TSharedRef<FModTargetsConfig>> ModTargetsConfigs;

    FReply PackageAllMods();

	bool IsPackageButtonEnabled() const;
};

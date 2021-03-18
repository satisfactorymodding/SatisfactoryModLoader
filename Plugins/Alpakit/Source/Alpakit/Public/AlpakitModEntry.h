#pragma once
#include "AlpakitModEntryList.h"
#include "Interfaces/IPluginManager.h"

/**
 * Entry of a mod within the mod list of the alpakit window
 */
class SAlpakitModEntry : public SCompoundWidget {
	SLATE_BEGIN_ARGS(SAlpakitModEntry) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args, TSharedRef<IPlugin> InMod, TSharedRef<SAlpakitModEntryList> InOwner);
	
	void PackageMod() const;

private:
	TSharedPtr<IPlugin> Mod;
	TSharedPtr<SAlpakitModEntryList> Owner;
};

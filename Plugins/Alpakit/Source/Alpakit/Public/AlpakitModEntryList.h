#pragma once
#include "Interfaces/IPluginManager.h"

/**
 * Widget that lists all plugins that might be able to get packed as mods
 */
class SAlpakitModEntryList : public SCompoundWidget {
	SLATE_BEGIN_ARGS(SAlpakitModEntryList) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

	/**
	 * Updates the mod list.
	 */
	void LoadMods();
	
private:
	TSharedPtr<SListView<TSharedRef<IPlugin>>> ModList;
	TArray<TSharedRef<IPlugin>> Mods;
};

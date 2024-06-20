#pragma once
#include "Interfaces/IPluginManager.h"

/**
 * Widget that lists all plugins that might be able to get packed as mods
 */
class SAlpakitModEntryList : public SCompoundWidget {
	DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnModEntryLead, const TSharedRef<IPlugin>&);
	DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnModEntryTail, const TSharedRef<IPlugin>&);
	
	SLATE_BEGIN_ARGS(SAlpakitModEntryList) {}
	    SLATE_NAMED_SLOT(FArguments, BarSlot)
		SLATE_NAMED_SLOT(FArguments, SearchTrail)
		SLATE_EVENT(FOnModEntryLead, ModEntryLead)
		SLATE_EVENT(FOnModEntryTail, ModEntryTrail)
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

	/**
	 * Updates the mod list.
	 */
	void LoadMods();

	/**
	 * Filters the mods for the given string
	 */
	void Filter(const FString& InFilter);

	/**
	 * Returns the string which was use previously to filter
	 */
	FString GetLastFilter() const;

	/**
	 * True if engine plugins are considered being mods
	 */
	void SetShowEngine(bool bInShowEngine);
	void SetShowProject(bool bInShowProject);

	TArray<TSharedRef<IPlugin>> GetFilteredMods() const { return FilteredMods; }

	void OnCheckboxChanged(TSharedRef<IPlugin> Mod, ECheckBoxState NewState);
	void UpdateAllCheckbox();

	void OnNewPluginCreated(IPlugin& Plugin);
	void SetAllMods(bool Checked);
private:
	TSharedPtr<SListView<TSharedRef<IPlugin>>> ModList;
	TSharedPtr<SCheckBox> AllModsCheckbox;
	TArray<TSharedRef<IPlugin>> Mods;
	TArray<TSharedRef<IPlugin>> FilteredMods;
	FString LastFilter;
	bool bShowEngine = false;
	bool bShowProject = false;
};

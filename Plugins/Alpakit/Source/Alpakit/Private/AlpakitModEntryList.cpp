#include "AlpakitModEntryList.h"


#include "AlpakitModEntry.h"
#include "Interfaces/IPluginManager.h"

void SAlpakitModEntryList::Construct(const FArguments& Args) {
	ModList = SNew(SListView<TSharedRef<IPlugin>>)
        .SelectionMode(ESelectionMode::None)
        .ListItemsSource(&Mods)
        .OnGenerateRow_Lambda([](TSharedRef<IPlugin> Mod, const TSharedRef<STableViewBase>& List) {
        	return SNew( STableRow<TSharedRef<IPlugin>>, List)[
				SNew( SAlpakitModEntry, Mod)
			];
        });
	
	ChildSlot.AttachWidget(ModList.ToSharedRef());
    
    LoadMods();
}

bool DoesPluginHaveRuntime(const IPlugin& Plugin) {
	//Content plugins always have runtime component
	if (Plugin.GetDescriptor().bCanContainContent) {
		return true;
	}
	//C++ plugins have runtime component as long as one of their modules does
	for (const FModuleDescriptor& Module : Plugin.GetDescriptor().Modules) {
		if (Module.Type == EHostType::Runtime ||
			Module.Type == EHostType::RuntimeNoCommandlet ||
			Module.Type == EHostType::RuntimeAndProgram ||
			Module.Type == EHostType::ClientOnly ||
			Module.Type == EHostType::ClientOnlyNoCommandlet ||
			Module.Type == EHostType::ServerOnly ||
			Module.Type == EHostType::CookedOnly) {
			return true;
		}
	}
	return false;
}

void SAlpakitModEntryList::LoadMods() {
	Mods.Empty();
	const TArray<TSharedRef<IPlugin>> EnabledPlugins = IPluginManager::Get().GetEnabledPlugins();
	for (TSharedRef<IPlugin> Plugin : EnabledPlugins) {
		//Skip WWise, it is already shipped with the game
		if (Plugin->GetName() == TEXT("WWise")) {
			continue;
		}
		//Only include project plugins for now
		//TODO allow building engine plugins, make sure UAT task supports that as well
		if (Plugin->GetType() == EPluginType::Project) {
			const bool bHasRuntime = DoesPluginHaveRuntime(Plugin.Get());
			if (bHasRuntime) {
				Mods.Add(Plugin);
			}
		}
	}
	Mods.Sort([](const TSharedRef<IPlugin> Plugin1, const TSharedRef<IPlugin> Plugin2) {
		return Plugin1->GetName() < Plugin2->GetName();
	});
	ModList->RequestListRefresh();
}

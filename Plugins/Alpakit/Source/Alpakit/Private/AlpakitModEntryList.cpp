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

void SAlpakitModEntryList::LoadMods() {
	Mods.Empty();
	for (TSharedRef<IPlugin> Plugin : IPluginManager::Get().GetDiscoveredPlugins()) {
		if (Plugin->GetType() != EPluginType::Mod && Plugin->GetType() != EPluginType::Project) continue;
		if (!Plugin->IsEnabled()) continue;
		bool bHasRuntime = Plugin->GetDescriptor().Modules.Num() < 1;
		if (!bHasRuntime) for (auto Module : Plugin->GetDescriptor().Modules) {
			if (Module.Type == EHostType::Runtime) {
				bHasRuntime = true;
				break;
			}
		}
		if (!bHasRuntime) continue;
		if (Plugin->GetName() == "Wwise") continue;
		Mods.Add(Plugin);
	}
	Mods.Sort([](TSharedRef<IPlugin> Plugin1, TSharedRef<IPlugin> Plugin2) {
		return Plugin1->GetName() < Plugin2->GetName();
	});
	ModList->RequestListRefresh();
}

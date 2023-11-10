#pragma once
#include "AlpakitModEntryList.h"
#include "AlpakitProfile.h"
#include "Interfaces/IPluginManager.h"

/**
 * Entry of a mod within the mod list of the alpakit window
 */
class SAlpakitModEntry : public SCompoundWidget {
    SLATE_BEGIN_ARGS(SAlpakitModEntry) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& Args, TSharedRef<IPlugin> InMod, TSharedRef<SAlpakitModEntryList> InOwner);

    void OnEnableCheckboxChanged(ECheckBoxState NewState);
    bool IsPackageButtonEnabled() const;

    void OnEditMod();
    FReply OnEditModFinished(class UModMetadataObject* Metadata);

    FORCEINLINE bool IsSelected() {
        return Checkbox && Checkbox->IsChecked();
    }

    FORCEINLINE void SetSelected(bool bInSelected) {
        if (Checkbox) {
            Checkbox->SetIsChecked(bInSelected);
        }
    }
private:
    void PackageMod();
    
    TSharedPtr<IPlugin> Mod;
    TSharedPtr<SAlpakitModEntryList> Owner;
    TSharedPtr<class SCheckBox> Checkbox;
    
    /** Dialog for editing mod properties */
    TSharedPtr<SWindow> PropertiesWindow;
};

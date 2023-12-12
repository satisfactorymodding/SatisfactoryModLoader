#pragma once
#include "AlpakitModEntryList.h"
#include "AlpakitProfile.h"
#include "ModTargetsConfig.h"
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
    TSharedPtr<SCheckBox> Checkbox;
    TSharedPtr<SButton> EditButton;
    TSharedPtr<SButton> ConfigureReleaseButton;
    
    /** Dialog for editing mod properties */
    TSharedPtr<SWindow> PropertiesWindow;

    FModTargetsConfig ModTargetsConfig;

    void QueueStarted();
    void QueueComplete();
};

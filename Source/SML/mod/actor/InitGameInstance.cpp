#include "InitGameInstance.h"

#include "FileManagerGeneric.h"
#include "SubclassOf.h"
#include "keybind/ModKeyBindRegistry.h"
#include "mod/ModSubsystems.h"

void UInitGameInstance::Init_Implementation() {
}

void UInitGameInstance::LoadModContent() {
    //Subsystems holders
    for (UClass* SubsystemHolderClass : ModSubsystems) {
        FSubsystemInfoHolder::RegisterSubsystemHolder(SubsystemHolderClass);
    }
    //Key Bindings and Axis Bindings
    for (const FModKeyBindingInfo& KeyBindingInfo : ModKeyBindings) {
        UModKeyBindRegistry::RegisterModKeyBind(KeyBindingInfo.ModReference, KeyBindingInfo.KeyMapping, KeyBindingInfo.DisplayName);
    }
    for (const FModAxisBindingInfo& AxisBindingInfo : ModAxisBindings) {
        UModKeyBindRegistry::RegisterModAxisBind(AxisBindingInfo.ModReference, AxisBindingInfo.PositiveAxisMapping, AxisBindingInfo.NegativeAxisMapping, AxisBindingInfo.PositiveAxisDisplayName, AxisBindingInfo.NegativeAxisDisplayName);
    }
}

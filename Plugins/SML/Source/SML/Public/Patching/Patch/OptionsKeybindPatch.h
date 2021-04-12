#pragma once
#include "CoreMinimal.h"

class FScriptArrayHelper;

class SML_API FOptionsKeybindPatch {
public:
    /** Groups key binding structs array by owner mod reference */
    static void CategorizeKeyBindingsByModReference(FScriptArrayHelper& InKeyBindings, UScriptStruct* KeyBindStructClass, TMap<FString, TArray<int32>>& OutCategorizedNames);

    /** Sorts provided mod reference array according to their display names */
    static void SortModReferencesByDisplayName(TArray<FString>& InModReferences, TMap<FString, FString>& OutDisplayNames);

    /** Populates keybind button list in options widget */
    static void PopulateKeyBindButtonList(class UUserWidget* ContextWidget, FScriptArrayHelper& KeyBindingsArray, const TArray<FString>& SortedModReferences, const TMap<FString, FString> DisplayNames, const TMap<FString, TArray<int32>>& CategorizedKeyBinds);

private:
    friend class FSatisfactoryModLoader;

    /** Processes hook replacing key bindings options screen */
    static void HandleRefreshKeyBindingsHook(class FBlueprintHookHelper& HookHelper);

    static void RegisterPatch();
};

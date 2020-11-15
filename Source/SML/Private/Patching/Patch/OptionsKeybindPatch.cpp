#pragma once
#include "Patching/Patch/OptionsKeybindPatch.h"
#include "BlueprintHookHelper.h"
#include "BlueprintHookManager.h"
#include "ModHandler.h"
#include "ReflectionHelper.h"
#include "SatisfactoryModLoader.h"
#include "TextBlock.h"
#include "UserWidget.h"
#include "VerticalBox.h"
#include "WidgetBlueprintLibrary.h"
#include "Engine/UserDefinedStruct.h"

void* GetArrayElementPtr(const FScriptArray& ScriptArray, int32 Index, int32 BytesPerElement) {
    return (uint8*)ScriptArray.GetData() + Index * BytesPerElement;
}

void FOptionsKeybindPatch::CategorizeKeyBindingsByModReference(const FScriptArray& InKeyBindings, UScriptStruct* KeyBindStructClass, TMap<FString, FScriptArray>& OutCategorizedNames) {
    UNameProperty* ActionNameProperty = FReflectionHelper::FindPropertyByShortName<UNameProperty>(KeyBindStructClass, TEXT("ActionName"));
    check(ActionNameProperty);
    
    for (int32 i = 0; i < InKeyBindings.Num(); i++) {
        //Retrieve action name from script struct
        void* KeyBindData = GetArrayElementPtr(InKeyBindings, i, KeyBindStructClass->GetStructureSize());
        const FString ActionName = ActionNameProperty->GetPropertyValue_InContainer(KeyBindData).ToString();
        int32 FirstDotIndex;
        ActionName.FindChar(TEXT('.'), FirstDotIndex);
        FString ResultModReference;
        
        //If dot is not found in key binding action name, it should be native FactoryGame key binding
        if (FirstDotIndex == INDEX_NONE) {
            ResultModReference = TEXT("FactoryGame");
        } else {
            ResultModReference = ActionName.Mid(0, FirstDotIndex);
        }
        //Add resulting key binding into array
        FScriptArray& ResultArray = OutCategorizedNames.FindOrAdd(ResultModReference);
        const int32 ElementIndex = ResultArray.AddZeroed(1, KeyBindStructClass->GetStructureSize());
        void* NewElementPointer = GetArrayElementPtr(ResultArray, ElementIndex, KeyBindStructClass->GetStructureSize());
        KeyBindStructClass->CopyScriptStruct(NewElementPointer, KeyBindData);
    }
}

void FOptionsKeybindPatch::SortModReferencesByDisplayName(TArray<FString>& InModReferences, TMap<FString, FString>& OutDisplayNames) {
    FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
    for (const FString& ModReference : InModReferences) {
        const FModContainer* ModContainer = ModHandler->GetLoadedMod(ModReference);
        check(ModContainer);
        OutDisplayNames.Add(ModReference, ModContainer->ModInfo.Name);
    }
    InModReferences.StableSort([&](const FString& A, const FString& B){
        const FString& ModNameA = OutDisplayNames.FindChecked(A);
        const FString& ModNameB = OutDisplayNames.FindChecked(B);
        return ModNameA < ModNameB;
    });
}

void FOptionsKeybindPatch::PopulateKeyBindButtonList(UUserWidget* ContextWidget, UScriptStruct* KeyBindStructClass, const TArray<FString>& SortedModReferences, const TMap<FString, FString> DisplayNames, const TMap<FString, FScriptArray>& CategorizedKeyBinds) {
    UClass* KeyBindButtonWidgetClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/Widget_KeybindButton.Widget_KeybindButton_C"));
    check(KeyBindButtonWidgetClass);
    
    //Now we have sorted out key bindings array. Add them in given order to the vertical box.
    UVerticalBox* ButtonBox = FReflectionHelper::GetObjectPropertyValue<UVerticalBox>(ContextWidget, TEXT("mButtonBox"));
    
    for (const FString& ModReference : SortedModReferences) {
        const FScriptArray& KeyBindingsArray = CategorizedKeyBinds.FindChecked(ModReference);
        APlayerController* OwningController = ContextWidget->GetOwningPlayer();
        //Add display name on top of key bindings
        UTextBlock* TitleTextBlock = NewObject<UTextBlock>(OwningController);
        TitleTextBlock->Font.Size = 18;
        const FString ModDisplayName = DisplayNames.FindChecked(ModReference);
        TitleTextBlock->SetText(FText::FromString(ModDisplayName));
        ButtonBox->AddChildToVerticalBox(TitleTextBlock);

        //Construct widget, set relevant properties and add it into the box directly
        for (int32 i = 0; i < KeyBindingsArray.Num(); i++) {
            void* KeyBindDataPtr = GetArrayElementPtr(KeyBindingsArray, i, KeyBindStructClass->GetStructureSize());
            
            UUserWidget* ButtonWidget = UWidgetBlueprintLibrary::Create(ContextWidget, KeyBindButtonWidgetClass, OwningController);
            FReflectionHelper::SetStructPropertyValue(ButtonWidget, TEXT("mKeyBindData"), KeyBindDataPtr);
            FReflectionHelper::SetPropertyValue<UObjectProperty>(ButtonWidget, TEXT("mKeyBindParent"), ContextWidget);
            ButtonBox->AddChildToVerticalBox(ButtonWidget);
        }
    }
}

void FOptionsKeybindPatch::HandleRefreshKeyBindingsHook(FBlueprintHookHelper& HookHelper) {
    //Retrieve information about struct and properties first
    UUserWidget* ContextWidget = CastChecked<UUserWidget>(HookHelper.GetContext());
    UUserDefinedStruct* KeyBindStructClass = LoadObject<UUserDefinedStruct>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/KeyBindData"));
    check(KeyBindStructClass);
    
    //Retrieve key bindings by calling blueprint method
    FScriptArray OutKeyBindDataArray;
    FReflectionHelper::CallScriptFunction(HookHelper.GetContext(), TEXT("GetKeybindData"), OutKeyBindDataArray);
    
    //KeyBind data is returned in the array, process each element and divide them by mod display name
    TMap<FString, FScriptArray> OutCategorizedKeyBinds;
    CategorizeKeyBindingsByModReference(OutKeyBindDataArray, KeyBindStructClass, OutCategorizedKeyBinds);
    
    //Generate ModReference array and sort it by display name
    TMap<FString, FString> OutDisplayNameByModReference;
    TArray<FString> SortedModReferences;
    OutCategorizedKeyBinds.GetKeys(SortedModReferences);
    SortModReferencesByDisplayName(SortedModReferences, OutDisplayNameByModReference);

    //Now we have sorted out key bindings array. Add them in given order to the vertical box.
    PopulateKeyBindButtonList(ContextWidget, KeyBindStructClass, SortedModReferences, OutDisplayNameByModReference, OutCategorizedKeyBinds);
    
    //Skip normal function code because it is unnecessary to run
    HookHelper.JumpToFunctionReturn();
}

void FOptionsKeybindPatch::RegisterPatch() {
    UClass* WidgetKeyBindClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/PauseMenu/Widget_KeyBind.Widget_KeyBind_C"));
    check(WidgetKeyBindClass);
    UFunction* RefreshKeyBindingsFunction = WidgetKeyBindClass->FindFunctionByName(TEXT("RefreshKeyBindings"));
    UBlueprintHookManager::HookBlueprintFunction(RefreshKeyBindingsFunction, HandleRefreshKeyBindingsHook, EPredefinedHookOffset::Start);
}


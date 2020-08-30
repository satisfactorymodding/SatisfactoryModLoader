#include "ModKeyBindRegistry.h"
#include "FGOptionsSettings.h"
#include "SatisfactoryModLoader.h"
#include "VerticalBox.h"
#include "WidgetBlueprintLibrary.h"
#include "Engine/UserDefinedStruct.h"
#include "GameFramework/InputSettings.h"
#include "mod/blueprint_hooking.h"
#include "mod/ModHandler.h"
#include "util/ReflectionHelper.h"

void HandleRefreshKeyBindingsHook(FBlueprintHookHelper& HookHelper);

void UModKeyBindRegistry::RegisterHooking() {
    UClass* WidgetKeyBindClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/PauseMenu/Widget_KeyBind.Widget_KeyBind_C"));
    check(WidgetKeyBindClass);
    UFunction* RefreshKeyBindingsFunction = WidgetKeyBindClass->FindFunctionByName(TEXT("RefreshKeyBindings"));
    HookBlueprintFunction(RefreshKeyBindingsFunction, HandleRefreshKeyBindingsHook, EPredefinedHookOffset::Start);
}

void* GetArrayElementPtr(FScriptArray& ScriptArray, int32 Index, int32 BytesPerElement) {
    return (uint8*)ScriptArray.GetData() + Index * BytesPerElement;
}

void HandleRefreshKeyBindingsHook(FBlueprintHookHelper& HookHelper) {
    //Retrieve information about struct and properties first
    UUserWidget* ContextWidget = CastChecked<UUserWidget>(HookHelper.GetContext());
    UClass* KeyBindButtonWidgetClass = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/Widget_KeybindButton.Widget_KeybindButton_C"));
    check(KeyBindButtonWidgetClass);
    UUserDefinedStruct* KeyBindStructClass = LoadObject<UUserDefinedStruct>(NULL, TEXT("/Game/FactoryGame/Interface/UI/Menu/KeyBindData"));
    check(KeyBindStructClass);
    
    UNameProperty* ActionNameProperty = FReflectionHelper::FindPropertyByShortName<UNameProperty>(KeyBindStructClass, TEXT("ActionName"));
    const int32 ArrayElementSize = KeyBindStructClass->GetStructureSize();
    
    //Retrieve key bindings by calling blueprint method
    FScriptArray OutKeyBindDataArray;
    FReflectionHelper::CallScriptFunction(HookHelper.GetContext(), TEXT("GetKeybindData"), OutKeyBindDataArray);
    
    //KeyBind data is returned in the array, process each element and divide them by mod display name
    TMap<FString, FScriptArray> KeyBindByDisplayName;
    TArray<FString> SortedDisplayNames;
    const FModHandler* ModHandler = SML::GetModHandler();
    
    for (int32 i = 0; i < OutKeyBindDataArray.Num(); i++) {
        //Retrieve action name from script struct
        void* KeyBindData = GetArrayElementPtr(OutKeyBindDataArray, i, ArrayElementSize);
        const FString ActionName = ActionNameProperty->GetPropertyValue_InContainer(KeyBindData).ToString();
        int32 FirstDotIndex;
        ActionName.FindChar(TEXT('.'), FirstDotIndex);
        FString ResultDisplayName;
        
        //If dot is not found in key binding action name, it should be native FactoryGame key binding
        //Use Satisfactory as display name for FactoryGame key bindings
        if (FirstDotIndex == INDEX_NONE) {
            ResultDisplayName = TEXT("Satisfactory");
        } else {
            //Query mod handler for mod display name by mod reference
            FString ModReference = ActionName.Mid(0, FirstDotIndex);
            if (ModHandler->IsModLoaded(ModReference)) {
                const FModContainer& ModContainer = ModHandler->GetLoadedMod(ModReference);
                ResultDisplayName = ModContainer.ModInfo.Name;
            } else {
                //Otherwise fallback to using mod reference
                ResultDisplayName = ModReference;
            }
        }
        
        //Add resulting key binding into array
        FScriptArray& ResultArray = KeyBindByDisplayName.FindOrAdd(ResultDisplayName);
        SortedDisplayNames.AddUnique(ResultDisplayName);
        const int32 ElementIndex = ResultArray.AddZeroed(1, ArrayElementSize);
        void* NewElementPointer = GetArrayElementPtr(ResultArray, ElementIndex, ArrayElementSize);
        KeyBindStructClass->CopyScriptStruct(NewElementPointer, KeyBindData);
    }
    SortedDisplayNames.StableSort();

    //Now we have sorted out key bindings array. Add them in given order to the vertical box.
    UVerticalBox* ButtonBox = FReflectionHelper::GetObjectPropertyValue<UVerticalBox>(HookHelper.GetContext(), TEXT("mButtonBox"));
    for (const FString& ModDisplayName : SortedDisplayNames) {
        FScriptArray& KeyBindingsArray = KeyBindByDisplayName.FindChecked(ModDisplayName);
        APlayerController* OwningController = ContextWidget->GetOwningPlayer();
        //Add display name on top of key bindings
        UTextBlock* TitleTextBlock = NewObject<UTextBlock>(OwningController);
        TitleTextBlock->Font.Size = 18;
        TitleTextBlock->SetText(FText::FromString(ModDisplayName));
        ButtonBox->AddChildToVerticalBox(TitleTextBlock);

        //Construct widget, set relevant properties and add it into the box directly
        for (int32 i = 0; i < KeyBindingsArray.Num(); i++) {
            void* KeyBindDataPtr = GetArrayElementPtr(KeyBindingsArray, i, ArrayElementSize);
            
            UUserWidget* ButtonWidget = UWidgetBlueprintLibrary::Create(ContextWidget, KeyBindButtonWidgetClass, OwningController);
            FReflectionHelper::SetStructPropertyValue(ButtonWidget, TEXT("mKeyBindData"), KeyBindDataPtr);
            FReflectionHelper::SetPropertyValue<UObjectProperty>(ButtonWidget, TEXT("mKeyBindParent"), ContextWidget);
            ButtonBox->AddChildToVerticalBox(ButtonWidget);
        }
    }
    //Skip normal function code because it is unnecessary to run
    HookHelper.JumpToFunctionReturn();
}

void UModKeyBindRegistry::RegisterModKeyBind(const FString& ModReference, const FInputActionKeyMapping& KeyMapping, const FText& DisplayName) {
    UInputSettings* InputSettings = UInputSettings::GetInputSettings();
    UFGOptionsSettings* OptionsSettings = GetMutableDefault<UFGOptionsSettings>();
    const FString ModPrefix = FString::Printf(TEXT("%s."), *ModReference);

    //Ensure that we are prefixed by ModReference to allow unique identification
    const FString ActionName = KeyMapping.ActionName.ToString();
    checkf(ActionName.StartsWith(ModPrefix), TEXT("RegisterModKeyBind called with ActionName not being prefixed by ModReference"));
    
    //Check for uniqueness. We want mapping registered only one time
    TArray<FInputActionKeyMapping> MappingsAlreadyRegistered;
    InputSettings->GetActionMappingByName(KeyMapping.ActionName, MappingsAlreadyRegistered);
    if (MappingsAlreadyRegistered.Contains(KeyMapping)) {
        return;
    }
    
    //If we already have non-gamepad/gamepad mapping registered, don't register this one
    //This is because FactoryGame currently can only differentiate 2 mappings with same action name currently:
    //One should be bound to gamepad (and be not editable in controls), and other should be not-gamepad,
    //but editable in control options. So we only allow 2 mappings at most, and they should have different types
    const bool bIsGamePadKey = KeyMapping.Key.IsGamepadKey();
    for (const FInputActionKeyMapping& OtherMapping : MappingsAlreadyRegistered) {
        const bool bIsOtherGamePadKey = OtherMapping.Key.IsGamepadKey();
        if (bIsGamePadKey == bIsOtherGamePadKey)
            return; //Disallow registering 2 mappings with same type
    }
    
    //Either we don't have registered mapping, or it is of different type at this point
    //We can add it now, and calling AddActionMapping will also update all active PlayerInput objects
    InputSettings->AddActionMapping(KeyMapping);
    
    //Only register display name for non-gamepad mappings, because
    //FactoryGame option slider currently only supports 1 key per 1 action, and it
    //should be non-gamepad action key mapping
    if (!bIsGamePadKey) {
        FActionMappingDisplayName DisplayNameMapping;
        DisplayNameMapping.ActionMappingName = KeyMapping.ActionName;
        DisplayNameMapping.DisplayName = DisplayName;
        OptionsSettings->mActionBindingsDisplayNames.Add(DisplayNameMapping);
    }
}

void PerformChecksForModAxisBindings(const FInputAxisKeyMapping& PositiveAxisMapping, const FInputAxisKeyMapping& NegativeAxisMapping) {
    const FString PositiveAxisName = PositiveAxisMapping.AxisName.ToString();
    const FString NegativeAxisName = NegativeAxisMapping.AxisName.ToString();
    checkf(PositiveAxisName == NegativeAxisName, TEXT("RegisterModAxisBind called with different axis names for positive and negative mappings"));
    checkf(PositiveAxisMapping.Scale > 0, TEXT("PositiveAxisMapping should have positive scale"));
    checkf(NegativeAxisMapping.Scale < 0, TEXT("NegativeAxisMapping should have negative scale"));
    checkf(PositiveAxisMapping.Key.IsGamepadKey() == NegativeAxisMapping.Key.IsGamepadKey(), TEXT("Negative and Positive mappings should be same type"));
}

void UModKeyBindRegistry::RegisterModAxisBind(const FString& ModReference, const FInputAxisKeyMapping& PositiveAxisMapping, const FInputAxisKeyMapping& NegativeAxisMapping, const FText& PositiveDisplayName, const FText& NegativeDisplayName) {
    UInputSettings* InputSettings = UInputSettings::GetInputSettings();
    UFGOptionsSettings* OptionsSettings = GetMutableDefault<UFGOptionsSettings>();
    const FString ModPrefix = FString::Printf(TEXT("%s."), *ModReference);

    //Just like with action mapping, check that both axis names start with mod prefix
    const FString AxisName = PositiveAxisMapping.AxisName.ToString();
    checkf(AxisName.StartsWith(ModPrefix), TEXT("RegisterModAxisBind called with AxisName not being prefixed by ModReference"));
    PerformChecksForModAxisBindings(PositiveAxisMapping, NegativeAxisMapping);

    //Ensure we don't have duplicate axis mappings already registered
    TArray<FInputAxisKeyMapping> MappingsAlreadyRegistered;
    InputSettings->GetAxisMappingByName(PositiveAxisMapping.AxisName, MappingsAlreadyRegistered);
    if (MappingsAlreadyRegistered.Contains(PositiveAxisMapping) ||
        MappingsAlreadyRegistered.Contains(NegativeAxisMapping)) {
        return;
    }

    //Ensure we don't have same type of axis mappings registered
    const bool bIsGamePadKey = PositiveAxisMapping.Key.IsGamepadKey();
    for (const FInputAxisKeyMapping& OtherMapping : MappingsAlreadyRegistered) {
        const bool bIsOtherGamePadKey = OtherMapping.Key.IsGamepadKey();
        if (bIsGamePadKey == bIsOtherGamePadKey)
            return; //Disallow registering 2 mappings with same type
    }

    //Register both axis bindings
    InputSettings->AddAxisMapping(PositiveAxisMapping);
    InputSettings->AddAxisMapping(NegativeAxisMapping);

    //Only register display name for non-gamepad mappings, same reason as for keys
    if (!bIsGamePadKey) {
        FAxisMappingDisplayName DisplayName;
        DisplayName.AxisMappingName = PositiveAxisMapping.AxisName;
        DisplayName.DisplayNamePositiveScale = PositiveDisplayName;
        DisplayName.DisplayNameNegativeScale = NegativeDisplayName;
        OptionsSettings->mAxisBindingsDisplayNames.Add(DisplayName);
    }
}


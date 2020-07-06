#include "ItemTooltipHandler.h"


#include "TextBlock.h"
#include "WidgetBlueprintLibrary.h"
#include "mod/blueprint_hooking.h"
#include "util/Logging.h"

//Overwrites delegates bound to title & description widgets to use FTooltipHookHelper, add custom item widget
void ApplyItemOverridesToTooltip(UWidget* TooltipWidget, APlayerController* OwningPlayer, const FInventoryStack& InventoryStack) {
    //Gather UProperty exposed by tooltip widget
    UClass* TooltipWidgetClass = TooltipWidget->GetClass();
    UObjectProperty* TitleWidgetProperty = Cast<UObjectProperty>(TooltipWidgetClass->FindPropertyByName(TEXT("mTitle")));
    UObjectProperty* DescriptionWidgetProperty = Cast<UObjectProperty>(TooltipWidgetClass->FindPropertyByName(TEXT("mDescription")));
    check(TitleWidgetProperty && DescriptionWidgetProperty);
    
    //Retrieve references to some stuff
    UTextBlock* NameBlock = Cast<UTextBlock>(TitleWidgetProperty->GetObjectPropertyValue_InContainer(TooltipWidget));
    UTextBlock* DescriptionBlock = Cast<UTextBlock>(DescriptionWidgetProperty->GetObjectPropertyValue_InContainer(TooltipWidget));
    //Retrieve parent panel, it will hold name, description and recipe blocks
    UPanelWidget* ParentPanel = NameBlock->GetParent();
    
    //Spawn custom widget in parent panel and add it
    UItemStackContextWidget* ContextWidget = NewObject<UItemStackContextWidget>(ParentPanel);
    ContextWidget->InventoryStack = InventoryStack;
    ContextWidget->PlayerController = OwningPlayer;
    ContextWidget->Visibility = ESlateVisibility::Collapsed;
    ParentPanel->AddChild(ContextWidget);
    //Rebind text delegates to custom widget
    NameBlock->TextDelegate.BindUFunction(ContextWidget, TEXT("GetItemName"));
    DescriptionBlock->TextDelegate.BindUFunction(ContextWidget, TEXT("GetItemDescription"));
    
    //Append custom widgets to description
    TArray<UWidget*> Widgets = UItemTooltipHandler::CreateDescriptionWidgets(OwningPlayer, InventoryStack);
    for (UWidget* Widget : Widgets) {
        ParentPanel->AddChild(Widget);
    }
}

FText UItemStackContextWidget::GetItemName() const {
    return UItemTooltipHandler::GetItemName(PlayerController, InventoryStack);
}

FText UItemStackContextWidget::GetItemDescription() const {
    return UItemTooltipHandler::GetItemDescription(PlayerController, InventoryStack);
}

FInventoryStack GetStackFromSlot(UObject* SlotWidget) {
    //Retrieve fields relevant to owner inventory
    UObjectProperty* InventoryProperty = Cast<UObjectProperty>(SlotWidget->GetClass()->FindPropertyByName(TEXT("mCachedInventoryComponent")));
    UIntProperty* SlotIndexProperty = Cast<UIntProperty>(SlotWidget->GetClass()->FindPropertyByName(TEXT("mSlotIdx")));
    check(InventoryProperty && SlotIndexProperty);
    
    FInventoryStack ResultStack{};
    //Access inventory if it's not a null pointer
    UFGInventoryComponent* InventoryComponent = Cast<UFGInventoryComponent>(InventoryProperty->GetObjectPropertyValue_InContainer(SlotWidget));
    if (InventoryComponent) {
        const int32 SlotIndex = SlotIndexProperty->GetPropertyValue_InContainer(SlotWidget);
        InventoryComponent->GetStackFromIndex(SlotIndex, ResultStack);
    }
    return ResultStack;
}

static TArray<ISMLItemTooltipProvider*> GlobalTooltipProviders;

void UItemTooltipHandler::RegisterHooking() {
    //Hook into InventorySlot widget to apply tooltip overrides
    UClass* InventorySlot = LoadObject<UClass>(NULL, TEXT("/Game/FactoryGame/Interface/UI/InGame/InventorySlots/Widget_InventorySlot.Widget_InventorySlot_C"));
    check(InventorySlot);
    UFunction* Function = InventorySlot->FindFunctionByName(TEXT("GetTooltipWidget"));
    HookBlueprintFunction(Function, [](FBlueprintHookHelper& HookHelper) {
        UUserWidget* TooltipWidget = Cast<UUserWidget>(*HookHelper.GetOutVariablePtr<UObjectProperty>());
        UUserWidget* SlotWidget = Cast<UUserWidget>(HookHelper.GetContext());
        if (TooltipWidget != nullptr) {
            APlayerController* OwningPlayer = SlotWidget->GetOwningPlayer();
            const FInventoryStack InventoryStack = GetStackFromSlot(SlotWidget);
            if (InventoryStack.Item.IsValid()) {
                ApplyItemOverridesToTooltip(TooltipWidget, OwningPlayer, InventoryStack);
            }
        }
    }, EPredefinedHookOffset::Return);
}

void UItemTooltipHandler::RegisterGlobalTooltipProvider(UObject* TooltipProvider) {
    void* InterfaceAddress = TooltipProvider->GetInterfaceAddress(USMLItemTooltipProvider::StaticClass());
    if (InterfaceAddress) {
        //Pin UObject implementing interface so it won't be garbage collected
        TooltipProvider->AddToRoot();
        ISMLItemTooltipProvider* Provider = static_cast<ISMLItemTooltipProvider*>(InterfaceAddress);
        GlobalTooltipProviders.Add(Provider);
    }
}

FText UItemTooltipHandler::GetItemName(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack) {
    UClass* ItemClass = InventoryStack.Item.ItemClass;
    UClass* InterfaceClass = USMLItemDisplayInterface::StaticClass();
    if (ItemClass->ImplementsInterface(InterfaceClass)) {
        UObject* ItemObject = ItemClass->GetDefaultObject();
        return ISMLItemDisplayInterface::Execute_GetOverridenItemName(ItemObject, OwningPlayer, InventoryStack);
    }
    return UFGItemDescriptor::GetItemName(ItemClass);
}

#define APPEND_IF_NOT_EMPTY(expr) { FString _Result = expr; if (!_Result.IsEmpty()) DescriptionText.Add(_Result); }

FText UItemTooltipHandler::GetItemDescription(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack) {
    UClass* ItemClass = InventoryStack.Item.ItemClass;
    UClass* InterfaceClass = USMLItemDisplayInterface::StaticClass();
    TArray<FString> DescriptionText;
    APPEND_IF_NOT_EMPTY(UFGItemDescriptor::GetItemDescription(ItemClass).ToString());
    if (ItemClass->ImplementsInterface(InterfaceClass)) {
        UObject* ItemObject = ItemClass->GetDefaultObject();
        APPEND_IF_NOT_EMPTY(ISMLItemDisplayInterface::Execute_GetOverridenItemDescription(ItemObject, OwningPlayer, InventoryStack).ToString());
    }
    for (ISMLItemTooltipProvider* Provider : GlobalTooltipProviders) {
        APPEND_IF_NOT_EMPTY(Provider->GetItemDescription(OwningPlayer, InventoryStack).ToString());
    }
    return FText::FromString(FString::Join(DescriptionText, TEXT("\n")));
}

TArray<UWidget*> UItemTooltipHandler::CreateDescriptionWidgets(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack) {
    TArray<UWidget*> ResultWidgets;
    UClass* ItemClass = InventoryStack.Item.ItemClass;
    UClass* InterfaceClass = USMLItemDisplayInterface::StaticClass();
    if (ItemClass->ImplementsInterface(InterfaceClass)) {
        UObject* ItemObject = ItemClass->GetDefaultObject();
        UWidget* NewWidget = ISMLItemDisplayInterface::Execute_CreateDescriptionWidget(ItemObject, OwningPlayer, InventoryStack);
        if (NewWidget) {
            ResultWidgets.Add(NewWidget);
        }
    }
    for (ISMLItemTooltipProvider* Provider : GlobalTooltipProviders) {
        UWidget* ProviderWidget = Provider->CreateDescriptionWidget(OwningPlayer, InventoryStack);
        if (ProviderWidget) {
            ResultWidgets.Add(ProviderWidget);
        }
    }
    return ResultWidgets;
}


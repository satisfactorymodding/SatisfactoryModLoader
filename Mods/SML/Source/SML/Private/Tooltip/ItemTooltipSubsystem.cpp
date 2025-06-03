#include "Tooltip/ItemTooltipSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/PanelWidget.h"
#include "Components/RichTextBlock.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Tooltip/ItemStackContextWidget.h"
#include "Tooltip/SMLItemDisplayInterface.h"
#include "Tooltip/SMLItemTooltipProvider.h"

//Overwrites delegates bound to title & description widgets to use FTooltipHookHelper, add custom item widget
void UItemTooltipSubsystem::ApplyItemOverridesToTooltip(UTextBlock* TitleTextBlock, URichTextBlock* DescriptionTextBlock, APlayerController* OwningPlayer, const FInventoryStack& InventoryStack) {

    //Retrieve parent panel, it will hold name, description and recipe blocks
    UPanelWidget* ParentPanel = TitleTextBlock->GetParent();
    UVerticalBox* VerticalBoxPanel = CastChecked<UVerticalBox>(DescriptionTextBlock->GetParent());
    
    //Spawn custom widget in parent panel and add it
    UItemStackContextWidget* ContextWidget = NewObject<UItemStackContextWidget>(ParentPanel);
    ContextWidget->ItemTooltipSubsystem = this;
    ContextWidget->InventoryStack = InventoryStack;
    ContextWidget->PlayerController = OwningPlayer;
    ContextWidget->SetVisibility(ESlateVisibility::Collapsed);
    ParentPanel->AddChild(ContextWidget);
    
    //Append custom widgets to description
    TArray<UWidget*> Widgets = CreateDescriptionWidgets(OwningPlayer, InventoryStack);
    for (UWidget* Widget : Widgets) {
        VerticalBoxPanel->AddChild(Widget);
    }
}

FInventoryStack GetStackFromSlot(UObject* SlotWidget) {
    //Retrieve fields relevant to owner inventory
    FObjectProperty* InventoryProperty = CastField<FObjectProperty>(SlotWidget->GetClass()->FindPropertyByName(TEXT("mCachedInventoryComponent")));
    FIntProperty* SlotIndexProperty = CastField<FIntProperty>(SlotWidget->GetClass()->FindPropertyByName(TEXT("mSlotIdx")));
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

void UItemTooltipSubsystem::RegisterGlobalTooltipProvider(const FString& ModReference, UObject* ItemTooltipProvider) {
    if (ItemTooltipProvider->Implements<USMLItemTooltipProvider>()) {
        GlobalTooltipProviders.AddUnique(ItemTooltipProvider);
    }
}

FText UItemTooltipSubsystem::GetItemName(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack) {
    UClass* ItemClass = InventoryStack.Item.GetItemClass();
    if (ItemClass != NULL) {
        UObject* ItemObject = ItemClass->GetDefaultObject();
        if (ItemObject->Implements<USMLItemDisplayInterface>()) {
            return ISMLItemDisplayInterface::Execute_GetOverridenItemName(ItemObject, OwningPlayer, InventoryStack);
        }
    }
    return UFGItemDescriptor::GetItemName(ItemClass);
}

FText UItemTooltipSubsystem::GetItemDescription(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack) {
    UClass* ItemClass = InventoryStack.Item.GetItemClass();
    TArray<FString> DescriptionText;

    const FString VanillaDescription = UFGItemDescriptor::GetItemDescription(ItemClass).ToString();
    if (!VanillaDescription.IsEmpty()) {
        DescriptionText.Add(VanillaDescription);
    }
    
    if (ItemClass != NULL) {
        UObject* ItemObject = ItemClass->GetDefaultObject();
        if (ItemObject->Implements<USMLItemDisplayInterface>()) {
            const FString ItemModdedDescription = ISMLItemDisplayInterface::Execute_GetOverridenItemDescription(ItemObject, OwningPlayer, InventoryStack).ToString();
            if (!ItemModdedDescription.IsEmpty()) {
                DescriptionText.Add(ItemModdedDescription);
            }
        }
    }
    
    for (UObject* GlobalTooltipProvider : GlobalTooltipProviders) {
        const FString GlobalItemDescription = ISMLItemTooltipProvider::Execute_GetItemDescription(GlobalTooltipProvider, OwningPlayer, InventoryStack).ToString();
        if (!GlobalItemDescription.IsEmpty()) {
            DescriptionText.Add(GlobalItemDescription);
        }
    }
    
    return FText::FromString(FString::Join(DescriptionText, TEXT("\n")));
}

TArray<UWidget*> UItemTooltipSubsystem::CreateDescriptionWidgets(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack) {
    TArray<UWidget*> ResultWidgets;
    UClass* ItemClass = InventoryStack.Item.GetItemClass();
    
    if (ItemClass != NULL) {
        UObject* ItemObject = ItemClass->GetDefaultObject();
        if (ItemObject->Implements<USMLItemDisplayInterface>()) {
            UWidget* NewWidget = ISMLItemDisplayInterface::Execute_CreateDescriptionWidget(ItemObject, OwningPlayer, InventoryStack);
            if (NewWidget) {
                ResultWidgets.Add(NewWidget);
            }
        }
    }
    
    for (UObject* GlobalTooltipProvider : GlobalTooltipProviders) {
        UWidget* ProviderWidget = ISMLItemTooltipProvider::Execute_CreateDescriptionWidget(GlobalTooltipProvider, OwningPlayer, InventoryStack);
        if (ProviderWidget) {
            ResultWidgets.Add(ProviderWidget);
        }
    }
    
    return ResultWidgets;
}

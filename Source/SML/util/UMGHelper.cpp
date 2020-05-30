#include "UMGHelper.h"
#include "PanelWidget.h"

void FUMGHelper::InsertChildAtIndex(UPanelWidget* PanelWidget, int32 Index, UWidget* Widget) {
    //First, add our widget to create new slot
    checkf(PanelWidget->AddChild(Widget), TEXT("Failed to AddChild to panel widget"));
    checkf(PanelWidget->GetChildrenCount() > Index, TEXT("InsertChildAtIndex: Invalid Index: %d"), Index);
    //Then move all widgets from given index one slot down
    const TArray<UPanelSlot*>& Slots = PanelWidget->GetSlots();
    for (int32 i = Slots.Num() - 1; i > Index; i--) {
        UPanelSlot* CurrentSlot = Slots[Index];
        UPanelSlot* PreviousSlot = Slots[Index - 1];
        //Copy previous slot content to this slot, so all slots before index will be moved down by 1
        CurrentSlot->Content = PreviousSlot->Content;
        CurrentSlot->Content->Slot = CurrentSlot;
    }
    //Replace index slot finally
    UPanelSlot* TargetSlot = Slots[Index];
    TargetSlot->Content = Widget;
    TargetSlot->Content->Slot = TargetSlot;
    //Invalidate caches
    PanelWidget->InvalidateLayoutAndVolatility();
}

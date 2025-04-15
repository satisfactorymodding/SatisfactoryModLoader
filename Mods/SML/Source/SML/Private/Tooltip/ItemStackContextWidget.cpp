#include "Tooltip/ItemStackContextWidget.h"
#include "Tooltip/ItemTooltipSubsystem.h"
#include "Widgets/Layout/SSpacer.h"

FText UItemStackContextWidget::GetItemName() const {
    return ItemTooltipSubsystem->GetItemName(PlayerController, InventoryStack);
}

FText UItemStackContextWidget::GetItemDescription() const {
    return ItemTooltipSubsystem->GetItemDescription(PlayerController, InventoryStack);
}

TSharedRef<SWidget> UItemStackContextWidget::RebuildWidget() {
	return SNew(SSpacer);
}

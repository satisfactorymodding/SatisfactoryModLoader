#include "Tooltip/ItemStackContextWidget.h"
#include "ItemTooltipHandler.h"

FText UItemStackContextWidget::GetItemName() const {
    return UItemTooltipHandler::GetItemName(PlayerController, InventoryStack);
}

FText UItemStackContextWidget::GetItemDescription() const {
    return UItemTooltipHandler::GetItemDescription(PlayerController, InventoryStack);
}

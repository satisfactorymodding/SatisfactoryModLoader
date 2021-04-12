#pragma once
#include "CoreMinimal.h"
#include "Inventory.h"
#include "Components/Widget.h"
#include "SMLItemTooltipProvider.generated.h"

UINTERFACE(Blueprintable)
class SML_API USMLItemTooltipProvider : public UInterface {
    GENERATED_BODY()
};

/**
* Register Object implementing this interface in UItemTooltipHandler to be able
* to add description text/widgets to any item in the game
* 
* Attention! White it is possible to implement it in Blueprints, it will
* be called very often, so please avoid doing heavy logic here
*/
class SML_API ISMLItemTooltipProvider {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent)
    FText GetItemDescription(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);

    UFUNCTION(BlueprintNativeEvent)
    UWidget* CreateDescriptionWidget(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);
};

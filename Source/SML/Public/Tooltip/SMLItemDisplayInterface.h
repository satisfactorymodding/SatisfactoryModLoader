#pragma once
#include "CoreMinimal.h"
#include "Inventory.h"
#include "Components/Widget.h"
#include "SMLItemDisplayInterface.generated.h"

UINTERFACE(Blueprintable)
class SML_API USMLItemDisplayInterface : public UInterface {
    GENERATED_BODY()
};

/**
* Implement this on your item to be able to override it's display name,
* description text, and add custom description widget
* in the item stack and player-aware manner
*/
class SML_API ISMLItemDisplayInterface {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent)
    FText GetOverridenItemName(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);

    UFUNCTION(BlueprintNativeEvent)
    FText GetOverridenItemDescription(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);

    UFUNCTION(BlueprintNativeEvent)
    UWidget* CreateDescriptionWidget(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);
};

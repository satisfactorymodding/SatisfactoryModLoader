#pragma once
#include "CoreMinimal.h"
#include "Widget.h"
#include "Inventory.h"
#include "ItemStackContextWidget.generated.h"

UCLASS()
class UItemStackContextWidget : public UWidget {
    GENERATED_BODY()
public:
    UPROPERTY()
    FInventoryStack InventoryStack;
    UPROPERTY()
    APlayerController* PlayerController;
public:
    UFUNCTION()
    FText GetItemName() const;
    UFUNCTION()
    FText GetItemDescription() const;
};
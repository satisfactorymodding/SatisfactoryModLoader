#pragma once
#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Inventory.h"
#include "Tooltip/ItemTooltipSubsystem.h"

#include "ItemStackContextWidget.generated.h"

UCLASS()
class UItemStackContextWidget : public UWidget {
    GENERATED_BODY()
public:
    UPROPERTY()
    FInventoryStack InventoryStack;
    UPROPERTY()
    APlayerController* PlayerController;
    UPROPERTY()
    UItemTooltipSubsystem* ItemTooltipSubsystem;
public:
    UFUNCTION()
    FText GetItemName() const;
    UFUNCTION()
    FText GetItemDescription() const;
};

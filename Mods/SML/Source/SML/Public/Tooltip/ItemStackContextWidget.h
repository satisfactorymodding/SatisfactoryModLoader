#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Tooltip/ItemTooltipSubsystem.h"
#include "ItemStackContextWidget.generated.h"

UCLASS()
class SML_API UItemStackContextWidget : public UWidget {
    GENERATED_BODY()
public:
    UPROPERTY()
    FInventoryStack InventoryStack;
    UPROPERTY()
    TObjectPtr<APlayerController> PlayerController;
    UPROPERTY()
    TObjectPtr<UItemTooltipSubsystem> ItemTooltipSubsystem;

    UFUNCTION(BlueprintPure)
    FText GetItemName() const;
    UFUNCTION(BlueprintPure)
    FText GetItemDescription() const;

	// Begin UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End UWidget interface
};

#pragma once
#include "FGInventoryComponent.h"
#include "Text.h"
#include "VerticalBox.h"
#include "Widget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemTooltipHandler.generated.h"

UCLASS()
class SML_API UItemTooltipHandler: public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    /**
     * Register tooltip provider that will be called for all items registered
     * Please be careful with implementation as it will be called very often
     * Object should implement ISMLItemTooltipProvider
     */
    UFUNCTION(BlueprintCallable)
    static void RegisterGlobalTooltipProvider(const FString& ModReference, UObject* ItemTooltipProvider);
    
    /**
     * Returns formatted item name obtained from InventoryStack
     * For normal items it just returns UFGItemDescriptor::GetItemDescription
     * For items implementing ISMLItemDisplayInterface, this is routed to GetItemName
     */
    UFUNCTION(BlueprintPure)
    static FText GetItemName(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);

    /**
     * Retrieves correct item description for given inventory stack
     * Call semantics are similar to GetItemName()
     */
    UFUNCTION(BlueprintPure)
    static FText GetItemDescription(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);

    static TArray<UWidget*> CreateDescriptionWidgets(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);
private:
    friend class FSatisfactoryModLoader;

    static void Initialize();
    
    /** Array of registered tooltip providers, UPROPERTY to avoid garbage collection */
    UPROPERTY()
    TArray<UObject*> GlobalTooltipProviders;
};

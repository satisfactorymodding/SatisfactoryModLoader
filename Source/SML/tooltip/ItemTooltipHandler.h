#pragma once
#include "FGInventoryComponent.h"
#include "Text.h"
#include "VerticalBox.h"
#include "Widget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemTooltipHandler.generated.h"
class ISMLItemTooltipProvider;
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

UCLASS()
class SML_API UItemTooltipHandler: public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    //Internal usage only, called by SML on startup
    NO_API static void RegisterHooking();

    /**
     * Register tooltip provider that will be called for all items registered
     * Please be careful with implementation as it will be called very often
     * Object should implement ISMLItemTooltipProvider
     */
    UFUNCTION(BlueprintCallable)
    static void RegisterGlobalTooltipProvider(UObject* TooltipProvider);
    
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
};

UINTERFACE( Blueprintable )
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
    UFUNCTION( BlueprintNativeEvent )
    FText GetItemDescription(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);

    UFUNCTION( BlueprintNativeEvent )
    UWidget* CreateDescriptionWidget(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);
};

UINTERFACE( Blueprintable )
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
    UFUNCTION( BlueprintNativeEvent )
    FText GetOverridenItemName(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);

    UFUNCTION( BlueprintNativeEvent )
    FText GetOverridenItemDescription(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);

    UFUNCTION( BlueprintNativeEvent )
    UWidget* CreateDescriptionWidget(APlayerController* OwningPlayer, const FInventoryStack& InventoryStack);
};

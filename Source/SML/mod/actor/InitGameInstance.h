#pragma once
#include "Object.h"
#include "GameFramework/PlayerInput.h"

#include "InitGameInstance.generated.h"

class UModSubsystemHolder;

/* Holds information about individual key binding registration */
USTRUCT(BlueprintType)
struct FModKeyBindingInfo {
    GENERATED_BODY()
    
    /** Mod reference of the mod this key binding belongs to */
    UPROPERTY(EditAnywhere)
    FString ModReference;
    
    /* Information about key binding being registered. ActionName should be prefixed with ModReference. */
    UPROPERTY(EditAnywhere)
    FInputActionKeyMapping KeyMapping;
    
    /* Display name of Key Binding in Options|Controls menu */
    UPROPERTY(EditAnywhere)
    FText DisplayName;
};

/* Holds information about individual axis binding registration */
USTRUCT(BlueprintType)
struct FModAxisBindingInfo {
    GENERATED_BODY()
    
    /** Mod reference of the mod this key binding belongs to */
    UPROPERTY(EditAnywhere)
    FString ModReference;
    
    /* Information about Positive (Scale > 0) axis mapping. AxisNames should be the same and prefixed with ModReference. */
    UPROPERTY(EditAnywhere)
    FInputAxisKeyMapping PositiveAxisMapping;
    /* Information about Negative (Scale < 0) axis mapping. AxisNames should be the same and prefixed with ModReference. */
    UPROPERTY(EditAnywhere)
    FInputAxisKeyMapping NegativeAxisMapping;
    
    /* Display name of *Positive* Axis Binding in Options|Controls menu */
    UPROPERTY(EditAnywhere)
    FText PositiveAxisDisplayName;
    /* Display name of *Negative* Axis Binding in Options|Controls menu */
    UPROPERTY(EditAnywhere)
    FText NegativeAxisDisplayName;
};

UCLASS(Abstract, Blueprintable, HideCategories = ("Actor Tick", Rendering, Replication, Input, Actor, Collision, LOD, Cooking))
class SML_API UInitGameInstance : public UObject {
    GENERATED_BODY()
public:
    /**
     * Called after game instance is initialized
     * This has nothing to do with UWorld objects and they may be not created yet
     * at this point, so this is UObject and not an Actor, so
     * subset of functions you can call here is pretty limited
     * Notice that it will be called once per game startup, unlike InitGame/MenuWorld
     */
    UFUNCTION(BlueprintNativeEvent)
    void Init();

    /* Called along with Init at the same time, used to register stuff in fields below automatically */
    void LoadModContent();
public:
    /** Key Bindings for this mod to be registered */
    UPROPERTY(EditDefaultsOnly, Category = "Key Bindings")
    TArray<FModKeyBindingInfo> ModKeyBindings;

    /**
     * Axis Bindings for this mod to be registered
     * They are very similar to key bindings in behavior, but there are some differences:
     *  - Axis Bindings provide /degrees of input/ and not discrete 0/1 values
     *  - Axis Bindings are continuously polled and not triggered on action (so they are good for movement)
     *  So use them for movement basically
     */
    UPROPERTY(EditDefaultsOnly, Category = "Key Bindings")
    TArray<FModAxisBindingInfo> ModAxisBindings;
    
    /**
    * List of subsystem holders to register
    * Subsystem holders are created for each game world initialized
    * and hold references to custom mod subsystems
    */
    UPROPERTY(EditDefaultsOnly, Category = Advanced)
    TArray<TSubclassOf<UModSubsystemHolder>> ModSubsystems;

    /**
    * List of classes for objects implementing ISMLItemTooltipProvider
    * These will be registered on startup and used to obtain additional description
    * text/widget for all items
    */
    UPROPERTY(EditDefaultsOnly, Category = Advanced)
    TArray<UClass*> GlobalItemTooltipProviders;
};

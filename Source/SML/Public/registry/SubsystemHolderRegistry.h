#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Subsystem/ModSubsystemHolder.h"
#include "SubsystemHolderRegistry.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSubsystemHolderRegistry, Log, Log);

/** Structure holding information about subsystem holder entry registered */
USTRUCT()
struct FSubsystemHolderRegistrarEntry {
    GENERATED_BODY()
public:
    FString OwnerModReference;
    UPROPERTY()
    TSubclassOf<UModSubsystemHolder> SubsystemHolderClass;
};

UCLASS()
class SML_API USubsystemHolderRegistry : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    USubsystemHolderRegistry();

    /**
    * Registers subsystem holder to be attached to game state and initialized on world load
    * You can only register subsystem holders before initial world load, e.g only in InitGameInstance methods
    * If registration is attempted after that, registry will throw an exception instead
    */
    UFUNCTION(BlueprintCallable)
    static void RegisterSubsystemHolder(const FString& ModReference, TSubclassOf<UModSubsystemHolder> SubsystemHolderClass);
private:
    friend class FSatisfactoryModLoader;

    /** Setups hooking required for registry functionality */
    static void InitializeRegistry();

    /** Freezes registry so it no longer accepts further registrations */
    static void FreezeRegistry();

    /** Initializes and attaches all mod subsystems */
    static void InitializeSubsystems(class AFGGameState* GameState);
    
    /** True if registry is frozen and no longer accepts registrations */
    static bool bIsRegistryFrozen;
    
    /** Array with all registered holders, need to be property to avoid garbage collection of UClasses */
    UPROPERTY()
    TArray<FSubsystemHolderRegistrarEntry> RegisteredSubsystemHolders;
};
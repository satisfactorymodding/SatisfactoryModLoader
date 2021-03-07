#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
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
class SML_API USubsystemHolderRegistry : public UGameInstanceSubsystem {
    GENERATED_BODY()
public:
    USubsystemHolderRegistry();

    /**
    * Registers subsystem holder to be attached to game state and initialized on world load
    * You can only register subsystem holders before initial world load, e.g only in InitGameInstance methods
    * If registration is attempted after that, registry will throw an exception instead
    */
    UFUNCTION(BlueprintCallable)
    void RegisterSubsystemHolder(const FString& ModReference, TSubclassOf<UModSubsystemHolder> SubsystemHolderClass);

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
private:
    friend class FSatisfactoryModLoader;

    /** True if registry is frozen and no longer accepts registrations */
    bool bRegistryFrozen;

    /** Freezes registry so it no longer accepts further registrations */
    void FreezeRegistry();

    /** Initializes and attaches all mod subsystems */
    static void InitializeSubsystems(class AFGGameState* GameState);

    /** Setups hooking required for registry functionality */
    static void InitializePatches();
    
    
    /** Array with all registered holders, need to be property to avoid garbage collection of UClasses */
    UPROPERTY()
    TArray<FSubsystemHolderRegistrarEntry> RegisteredSubsystemHolders;
};

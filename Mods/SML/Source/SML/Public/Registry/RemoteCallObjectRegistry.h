#pragma once
#include "CoreMinimal.h"
#include "FGRemoteCallObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RemoteCallObjectRegistry.generated.h"

UCLASS()
class SML_API URemoteCallObjectRegistry : public UGameInstanceSubsystem {
    GENERATED_BODY()
public:
    /**
     * Manually register a remote call object (RCO).
     * In most cases you should add the RCO to the RemoteCallObjects array of a Game Instance Subsystem instead
     */
    UFUNCTION(BlueprintCallable)
    void RegisterRemoteCallObject(TSubclassOf<UFGRemoteCallObject> RemoteCallObject);

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
private:
    friend class FSatisfactoryModLoader;
    
    UPROPERTY()
    TArray<TSubclassOf<UFGRemoteCallObject>> RegisteredRCOs;

    static void RegisterRCOsOnGameMode(class AGameModeBase* GameMode);
    
    /** Registers this registry related hooks */
    static void InitializePatches();
};

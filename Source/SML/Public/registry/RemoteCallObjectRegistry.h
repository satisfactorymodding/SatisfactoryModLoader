#pragma once
#include "CoreMinimal.h"
#include "FGRemoteCallObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RemoteCallObjectRegistry.generated.h"

UCLASS()
class SML_API URemoteCallObjectRegistry : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    static void RegisterRemoteCallObject(TSubclassOf<UFGRemoteCallObject> RemoteCallObject);
private:
    friend class FSatisfactoryModLoader;
    
    UPROPERTY()
    TArray<TSubclassOf<UFGRemoteCallObject>> RegisteredRCOs;

    static void RegisterRCOsOnGameMode(class AGameModeBase* GameMode);
    
    /** Registers this registry related hooks */
    static void InitializeRegistry();
};
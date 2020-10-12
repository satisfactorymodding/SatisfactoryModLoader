#pragma once
#include "GameInstanceSubsystem.h"
#include "actor/InitGameInstance.h"

#include "GameInstanceInitSubsystem.generated.h"

UCLASS()
class SML_API UGameInstanceInitSubsystem : public UGameInstanceSubsystem {
    GENERATED_BODY()
public:
    /** Retrieves list of all InitGameInstance objects registered */
    UFUNCTION(BlueprintPure)
    TArray<UInitGameInstance*> GetInitGameInstanceList() const;

    /** Retrieves InitGameInstance for specific ModReference. Returns NULL if not found */
    UFUNCTION(BlueprintPure)
    UInitGameInstance* GetInitGameInstanceByModReference(const FString& ModReference) const;
private:
    UPROPERTY()
    TArray<UInitGameInstance*> GameInstanceInitList;
    UPROPERTY()
    TMap<FString, UInitGameInstance*> GameInstanceInitByModRef;
private:
    friend class FModHandler;
    
    /** Creates Init object instance for given mod and registers it */
    void CreateInitObjectForMod(const FString& ModReference, TSubclassOf<UInitGameInstance> ObjectClass);

    /** Initialize all registered Init objects in their registration order */
    void InitializeInitObjects();
};

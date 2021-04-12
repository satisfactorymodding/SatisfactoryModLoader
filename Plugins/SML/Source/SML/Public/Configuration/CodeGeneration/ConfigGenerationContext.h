#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Configuration/CodeGeneration/ConfigGeneratedStruct.h"
#include "ConfigGenerationContext.generated.h"

UCLASS(BlueprintType)
class SML_API UConfigGenerationContext : public UObject {
    GENERATED_BODY()
public:
    /** Creates new config struct object that you can populate with variables or reference */
    UFUNCTION(BlueprintCallable)
    UConfigGeneratedStruct* CreateNewConfigStruct(const FString& StructName);

    UFUNCTION(BlueprintPure)
    TArray<UConfigGeneratedStruct*> GetAllGeneratedStructs() const;
private:
    UPROPERTY()
    TMap<FString, UConfigGeneratedStruct*> GeneratedStructs;
};

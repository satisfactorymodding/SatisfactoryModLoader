#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "ConfigGeneratedStruct.generated.h"

UCLASS(BlueprintType)
class SML_API UConfigGeneratedStruct : public UObject {
    GENERATED_BODY()
public:
    /** Adds new config variable into this generated struct */
    UFUNCTION(BlueprintCallable)
    void AddConfigVariable(const FConfigVariableDescriptor& Descriptor, const FString& VariableName);

    UFUNCTION(BlueprintPure)
    FORCEINLINE FString GetStructName() const { return StructName; }

    FORCEINLINE const TMap<FString, FConfigVariableDescriptor>& GetVariables() const { return Variables; }
protected:
    friend class UConfigGenerationContext;
    FString StructName;
    UPROPERTY()
    TMap<FString, FConfigVariableDescriptor> Variables;
};

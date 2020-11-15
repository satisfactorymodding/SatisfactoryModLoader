#include "Configuration/CodeGeneration/ConfigGenerationContext.h"

UConfigGeneratedStruct* UConfigGenerationContext::CreateNewConfigStruct(const FString& StructName) {
    checkf(!GeneratedStructs.Contains(StructName), TEXT("Attempt to add struct with duplicate name: %s"), *StructName);
    UConfigGeneratedStruct* GeneratedStruct = NewObject<UConfigGeneratedStruct>();
    GeneratedStruct->StructName = StructName;
    GeneratedStructs.Add(StructName, GeneratedStruct);
    return GeneratedStruct;
}

TArray<UConfigGeneratedStruct*> UConfigGenerationContext::GetAllGeneratedStructs() const {
    TArray<UConfigGeneratedStruct*> OutStructArray;
    GeneratedStructs.GenerateValueArray(OutStructArray);
    return OutStructArray;
}

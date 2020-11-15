#include "Configuration/CodeGeneration/ConfigGeneratedStruct.h"

void UConfigGeneratedStruct::AddConfigVariable(const FConfigVariableDescriptor& Descriptor, const FString& VariableName) {
    checkf(!Variables.Contains(VariableName), TEXT("Attempt to add duplicate variable %s"), *VariableName);
    Variables.Add(VariableName, Descriptor);
}

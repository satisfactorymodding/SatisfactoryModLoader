#include "Configuration/Properties/ConfigPropertyArray.h"
#include "CodeGeneration/ConfigVariableDescriptor.h"
#include "CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/Values/ConfigValueArray.h"

TSubclassOf<UConfigValue> UConfigPropertyArray::GetValueClass_Implementation() const {
    return UConfigValueArray::StaticClass();
}

FConfigVariableDescriptor UConfigPropertyArray::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariableArray(ElementValue->CreatePropertyDescriptor(Context, OuterPath));
}

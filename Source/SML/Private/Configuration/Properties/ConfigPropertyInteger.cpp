#include "Configuration/Properties/ConfigPropertyInteger.h"
#include "CodeGeneration/ConfigVariableDescriptor.h"
#include "CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/Values/ConfigValueInteger.h"

UConfigPropertyInteger::UConfigPropertyInteger() {
    DefaultValue = 0;
}

TSubclassOf<UConfigValue> UConfigPropertyInteger::GetValueClass_Implementation() const {
    return UConfigValueInteger::StaticClass();
}

void UConfigPropertyInteger::ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const {
    UConfigValueInteger* IntegerValue = Cast<UConfigValueInteger>(Value);
    if (IntegerValue != NULL) {
        IntegerValue->Value = DefaultValue;
    }
}

FConfigVariableDescriptor UConfigPropertyInteger::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_Float);
}

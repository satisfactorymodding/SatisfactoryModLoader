#include "Configuration/Properties/ConfigPropertyFloat.h"
#include "CodeGeneration/ConfigVariableDescriptor.h"
#include "CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/Values/ConfigValueFloat.h"

UConfigPropertyFloat::UConfigPropertyFloat() {
    DefaultValue = 0.0f;
}

TSubclassOf<UConfigValue> UConfigPropertyFloat::GetValueClass_Implementation() const {
    return UConfigValueFloat::StaticClass();
}

void UConfigPropertyFloat::ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const {
    UConfigValueFloat* FloatValue = Cast<UConfigValueFloat>(Value);
    if (FloatValue != NULL) {
        FloatValue->Value = DefaultValue;
    }
}

FConfigVariableDescriptor UConfigPropertyFloat::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_Float);
}

#include "Configuration/Properties/ConfigPropertyString.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/Values/ConfigValueString.h"

UConfigPropertyString::UConfigPropertyString() {
    DefaultValue = TEXT("");
}

TSubclassOf<UConfigValue> UConfigPropertyString::GetValueClass_Implementation() const {
    return UConfigValueString::StaticClass();
}

void UConfigPropertyString::ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const {
    UConfigValueString* StringValue = Cast<UConfigValueString>(Value);
    if (StringValue != NULL) {
        StringValue->Value = DefaultValue;
    }
}

FConfigVariableDescriptor UConfigPropertyString::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_String);
}

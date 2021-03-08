#include "Configuration/Properties/ConfigPropertyBool.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/Values/ConfigValueBool.h"

UConfigPropertyBool::UConfigPropertyBool() {
    this->DefaultValue = false;
}

TSubclassOf<UConfigValue> UConfigPropertyBool::GetValueClass_Implementation() const {
    return UConfigValueBool::StaticClass();
}

void UConfigPropertyBool::ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const {
    UConfigValueBool* ValueBool = Cast<UConfigValueBool>(Value);
    if (ValueBool != NULL) {
        ValueBool->Value = DefaultValue;
    }
}

FConfigVariableDescriptor UConfigPropertyBool::CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_Bool);
}

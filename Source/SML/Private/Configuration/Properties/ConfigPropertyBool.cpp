#include "Configuration/Properties/ConfigPropertyBool.h"
#include "CodeGeneration/ConfigVariableDescriptor.h"
#include "CodeGeneration/ConfigVariableLibrary.h"
#include "Values/ConfigValueBool.h"

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

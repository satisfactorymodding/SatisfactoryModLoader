#include "Configuration/Properties/ConfigPropertyBool.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueBool.h"
#include "Reflection/BlueprintReflectedObject.h"

UConfigPropertyBool::UConfigPropertyBool() {
    this->Value = false;
}

void UConfigPropertyBool::PostInitProperties() {
    Super::PostInitProperties();
    if (HasAnyFlags(RF_ClassDefaultObject) || bDefaultValueInitialized) {
        return;
    }
    bDefaultValueInitialized = true;
    DefaultValue = Value;
}

FString UConfigPropertyBool::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[bool %s]"), Value ? TEXT("true") : TEXT("false"));
}

URawFormatValue* UConfigPropertyBool::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueBool* BoolValue = NewObject<URawFormatValueBool>(Outer);
    BoolValue->Value = Value;
    return BoolValue;
}

void UConfigPropertyBool::Deserialize_Implementation(const URawFormatValue* RawValue) {
    const URawFormatValueBool* BoolValue = Cast<URawFormatValueBool>(RawValue);
    if (BoolValue) {
        this->Value = BoolValue->Value;
    }
}

void UConfigPropertyBool::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    ReflectedObject.SetBoolProperty(*VariableName, Value);
}

bool UConfigPropertyBool::ResetToDefault_Implementation() {
    if (!CanResetNow() || !bDefaultValueInitialized) {
        return false;
    }
    Value = DefaultValue;
    MarkDirty();
    return true;
}

bool UConfigPropertyBool::IsSetToDefaultValue_Implementation() const {
    return Value == DefaultValue;
}

FString UConfigPropertyBool::GetDefaultValueAsString_Implementation() const {
    return DefaultValue ? TEXT("true") : TEXT("false");
}

FConfigVariableDescriptor UConfigPropertyBool::CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_Bool);
}

#include "Configuration/Properties/ConfigPropertyBool.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueBool.h"
#include "Reflection/BlueprintReflectedObject.h"

UConfigPropertyBool::UConfigPropertyBool() {
    this->Value = false;
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

FConfigVariableDescriptor UConfigPropertyBool::CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_Bool);
}

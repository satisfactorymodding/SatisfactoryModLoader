#include "ConfigValueBool.h"
#include "RawFormatValueBool.h"

FString UConfigValueBool::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[bool %s]"), Value ? TEXT("true") : TEXT("false"));
}

URawFormatValue* UConfigValueBool::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueBool* BoolValue = NewObject<URawFormatValueBool>(Outer);
    BoolValue->Value = Value;
    return BoolValue;
}

void UConfigValueBool::Deserialize_Implementation(const URawFormatValue* Value) {
    const URawFormatValueBool* BoolValue = Cast<URawFormatValueBool>(Value);
    if (BoolValue) {
        this->Value = BoolValue->Value;
    }
}

void UConfigValueBool::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    ReflectedObject.SetBoolProperty(*VariableName, Value);
}

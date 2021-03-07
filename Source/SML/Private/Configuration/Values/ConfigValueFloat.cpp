#include "Configuration/Values/ConfigValueFloat.h"
#include "Configuration/RawFileFormat/RawFormatValueNumber.h"

FString UConfigValueFloat::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[float %f]"), Value);
}

URawFormatValue* UConfigValueFloat::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueNumber* NumberValue = NewObject<URawFormatValueNumber>(Outer);
    NumberValue->SetValueFloat(Value);
    return NumberValue;
}

void UConfigValueFloat::Deserialize_Implementation(const URawFormatValue* RawValue) {
    const URawFormatValueNumber* NumberValue = Cast<URawFormatValueNumber>(RawValue);
    if (NumberValue != NULL) {
        this->Value = NumberValue->Value;
    }
}

void UConfigValueFloat::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    ReflectedObject.SetFloatProperty(*VariableName, Value);
}

#include "Configuration/Values/ConfigValueInteger.h"
#include "Configuration/RawFileFormat/RawFormatValueNumber.h"

FString UConfigValueInteger::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[integer %d]"), Value);
}

URawFormatValue* UConfigValueInteger::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueNumber* NumberValue = NewObject<URawFormatValueNumber>(Outer);
    NumberValue->SetValueInt(Value);
    return NumberValue;
}

void UConfigValueInteger::Deserialize_Implementation(const URawFormatValue* RawValue) {
    const URawFormatValueNumber* NumberValue = Cast<URawFormatValueNumber>(RawValue);
    if (NumberValue != NULL) {
        this->Value = NumberValue->Value;
    }
}

void UConfigValueInteger::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    ReflectedObject.SetInt32Property(*VariableName, Value);
}

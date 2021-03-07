#include "Configuration/Values/ConfigValueString.h"
#include "Configuration/RawFileFormat/RawFormatValueString.h"

FString UConfigValueString::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[string \"%s\"]"), *Value.ReplaceQuotesWithEscapedQuotes());
}

URawFormatValue* UConfigValueString::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueString* StringValue = NewObject<URawFormatValueString>(Outer);
    StringValue->Value = Value;
    return StringValue;
}

void UConfigValueString::Deserialize_Implementation(const URawFormatValue* RawValue) {
    const URawFormatValueString* StringValue = Cast<URawFormatValueString>(RawValue);
    if (StringValue != NULL) {
        this->Value = StringValue->Value;
    }
}

void UConfigValueString::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    ReflectedObject.SetStringProperty(*VariableName, Value);
}

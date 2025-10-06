#include "Configuration/Properties/ConfigPropertyInteger.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueNumber.h"
#include "Reflection/BlueprintReflectedObject.h"

void UConfigPropertyInteger::PostLoad() {
    Super::PostLoad();
    // Migrate to DefaultValue from Value [Remove only this if statement once migration is no longer needed]
    // PostLoad runs before the user config is deserialized, but it still has the values from the CDO. If DefaultValue
    // is set to the type default and Value is not, then Value has the old default value that we need to migrate.
    if (DefaultValue == 0 && Value != DefaultValue) {
        DefaultValue = Value;
    }
    // Set initial value to default value. This runs before the user config is deserialized
    // and ensures that if the user has never set a value, it's set to the default.
    Value = DefaultValue;
}

FString UConfigPropertyInteger::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[integer %d]"), Value);
}

URawFormatValue* UConfigPropertyInteger::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueNumber* NumberValue = NewObject<URawFormatValueNumber>(Outer);
    NumberValue->SetValueInt(Value);
    return NumberValue;
}

void UConfigPropertyInteger::Deserialize_Implementation(const URawFormatValue* RawValue) {
    const URawFormatValueNumber* NumberValue = Cast<URawFormatValueNumber>(RawValue);
    if (NumberValue != NULL) {
        this->Value = NumberValue->Value;
    }
}

void UConfigPropertyInteger::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    ReflectedObject.SetIntProperty(*VariableName, Value);
}

bool UConfigPropertyInteger::ResetToDefault_Implementation() {
    if (!CanResetNow()) {
        return false;
    }
    Value = DefaultValue;
    MarkDirty();
    return true;
}

bool UConfigPropertyInteger::IsSetToDefaultValue_Implementation() const {
    return Value == DefaultValue;
}

FString UConfigPropertyInteger::GetDefaultValueAsString_Implementation() const {
    return FString::FromInt(DefaultValue);
}

FConfigVariableDescriptor UConfigPropertyInteger::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_Int32);
}

#include "Configuration/Properties/ConfigPropertyString.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueString.h"
#include "Reflection/BlueprintReflectedObject.h"

#if WITH_EDITOR
void UConfigPropertyString::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
    Super::PostEditChangeProperty(PropertyChangedEvent);
    // When DefaultValue is changed in the editor, sync Value to match it.
    // This prevents the old Value from triggering migration on next load.
    // [Remove this entire function once migration is no longer needed]
    if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UConfigPropertyString, DefaultValue)) {
        Value = DefaultValue;
    }
}
#endif

void UConfigPropertyString::PostLoad() {
    Super::PostLoad();
    // Migrate to DefaultValue from Value [Remove only this if statement once migration is no longer needed]
    // PostLoad runs before the user config is deserialized, but it still has the values from the CDO. If DefaultValue
    // is set to the type default and Value is not, then Value has the old default value that we need to migrate.
    if (DefaultValue.IsEmpty() && !Value.IsEmpty()) {
        DefaultValue = Value;
    }
    // Set initial value to default value. This runs before the user config is deserialized
    // and ensures that if the user has never set a value, it's set to the default.
    Value = DefaultValue;
}

FString UConfigPropertyString::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[string \"%s\"]"), *Value.ReplaceQuotesWithEscapedQuotes());
}

URawFormatValue* UConfigPropertyString::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueString* StringValue = NewObject<URawFormatValueString>(Outer);
    StringValue->Value = Value;
    return StringValue;
}

void UConfigPropertyString::Deserialize_Implementation(const URawFormatValue* RawValue) {
    const URawFormatValueString* StringValue = Cast<URawFormatValueString>(RawValue);
    if (StringValue != NULL) {
        this->Value = StringValue->Value;
    }
}

void UConfigPropertyString::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    ReflectedObject.SetStrProperty(*VariableName, Value);
}

bool UConfigPropertyString::ResetToDefault_Implementation() {
    if (!CanResetNow()) {
        return false;
    }
    Value = DefaultValue;
    MarkDirty();
    return true;
}

bool UConfigPropertyString::IsSetToDefaultValue_Implementation() const {
    return Value == DefaultValue;
}

FString UConfigPropertyString::GetDefaultValueAsString_Implementation() const {
    return *DefaultValue.ReplaceQuotesWithEscapedQuotes();
}

FConfigVariableDescriptor UConfigPropertyString::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_String);
}

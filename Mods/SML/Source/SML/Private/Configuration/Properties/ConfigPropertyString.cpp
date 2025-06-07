#include "Configuration/Properties/ConfigPropertyString.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueString.h"
#include "Reflection/BlueprintReflectedObject.h"

UConfigPropertyString::UConfigPropertyString() {
    this->Value = TEXT("");
}

void UConfigPropertyString::PostInitProperties() {
    Super::PostInitProperties();
    if (HasAnyFlags(RF_ClassDefaultObject) || bDefaultValueInitialized) {
        return;
    }
    bDefaultValueInitialized = true;
    DefaultValue = Value;
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
    if (!CanResetNow() || !bDefaultValueInitialized) {
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
    return DefaultValue;
}

FConfigVariableDescriptor UConfigPropertyString::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_String);
}

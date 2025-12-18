#include "Configuration/Properties/ConfigPropertyBool.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueBool.h"
#include "Reflection/BlueprintReflectedObject.h"

#if WITH_EDITOR
void UConfigPropertyBool::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
    Super::PostEditChangeProperty(PropertyChangedEvent);
    // When DefaultValue is changed in the editor, sync Value to match it.
    // This prevents the old Value from triggering migration on next load.
    // [Remove this entire function once migration is no longer needed]
    if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UConfigPropertyBool, DefaultValue)) {
        Value = DefaultValue;
    }
}
#endif

void UConfigPropertyBool::PostLoad() {
    Super::PostLoad();
    // Migrate to DefaultValue from Value [Remove only this if statement once migration is no longer needed]
    // PostLoad runs before the user config is deserialized, but it still has the values from the CDO. If DefaultValue
    // is set to the type default and Value is not, then Value has the old default value that we need to migrate.
    if (DefaultValue == false && Value != DefaultValue) {
        DefaultValue = Value;
    }
    // Set initial value to default value. This runs before the user config is deserialized
    // and ensures that if the user has never set a value, it's set to the default.
    Value = DefaultValue;
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
    if (!CanResetNow()) {
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

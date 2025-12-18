#include "Configuration/Properties/ConfigPropertyFloat.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueNumber.h"
#include "Reflection/BlueprintReflectedObject.h"

#if WITH_EDITOR
void UConfigPropertyFloat::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
    Super::PostEditChangeProperty(PropertyChangedEvent);
    // When DefaultValue is changed in the editor, sync Value to match it.
    // This prevents the old Value from triggering migration on next load.
    // [Remove this entire function once migration is no longer needed]
    if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UConfigPropertyFloat, DefaultValue)) {
        Value = DefaultValue;
    }
}
#endif

void UConfigPropertyFloat::PostLoad() {
    Super::PostLoad();
    // Migrate to DefaultValue from Value [Remove only this if statement once migration is no longer needed]
    // PostLoad runs before the user config is deserialized, but it still has the values from the CDO. If DefaultValue
    // is set to the type default and Value is not, then Value has the old default value that we need to migrate.
    if (FMath::IsNearlyZero(DefaultValue, SMALL_NUMBER) && !FMath::IsNearlyEqual(Value, DefaultValue, SMALL_NUMBER)) {
        DefaultValue = Value;
    }
    // Set initial value to default value. This runs before the user config is deserialized
    // and ensures that if the user has never set a value, it's set to the default.
    Value = DefaultValue;
}

FString UConfigPropertyFloat::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[float %f]"), Value);
}

URawFormatValue* UConfigPropertyFloat::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueNumber* NumberValue = NewObject<URawFormatValueNumber>(Outer);
    NumberValue->SetValueFloat(Value);
    return NumberValue;
}

void UConfigPropertyFloat::Deserialize_Implementation(const URawFormatValue* RawValue) {
    const URawFormatValueNumber* NumberValue = Cast<URawFormatValueNumber>(RawValue);
    if (NumberValue != NULL) {
        this->Value = NumberValue->Value;
    }
}

void UConfigPropertyFloat::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    ReflectedObject.SetFloatProperty(*VariableName, Value);
}

bool UConfigPropertyFloat::ResetToDefault_Implementation() {
    if (!CanResetNow()) {
        return false;
    }
    Value = DefaultValue;
    MarkDirty();
    return true;
}

bool UConfigPropertyFloat::IsSetToDefaultValue_Implementation() const {
    return FMath::IsNearlyEqual(Value, DefaultValue, SMALL_NUMBER);
}

FString UConfigPropertyFloat::GetDefaultValueAsString_Implementation() const {
    return FString::SanitizeFloat(DefaultValue);
}

FConfigVariableDescriptor UConfigPropertyFloat::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_Float);
}

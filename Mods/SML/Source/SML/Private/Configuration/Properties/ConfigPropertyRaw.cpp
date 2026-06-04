#include "Configuration/Properties/ConfigPropertyRaw.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueRawJson.h"
#include "Reflection/BlueprintReflectedObject.h"

void UConfigPropertyRaw::SetValue(TSharedPtr<FJsonValue> NewValue) {
    Value = NewValue.ToSharedRef();
}

void UConfigPropertyRaw::SetValue(TSharedPtr<FJsonObject> NewValue) {
    Value = MakeShared<FJsonValueObject>(NewValue);
}

FString UConfigPropertyRaw::DescribeValue_Implementation() const {
    return TEXT("[raw]");
}

URawFormatValue* UConfigPropertyRaw::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueRawJson* JsonValue = NewObject<URawFormatValueRawJson>(Outer);
    JsonValue->Value = Value;
    return JsonValue;
}

void UConfigPropertyRaw::Deserialize_Implementation(const URawFormatValue* RawValue) {
    const URawFormatValueRawJson* JsonValue = Cast<URawFormatValueRawJson>(RawValue);
    Value = JsonValue->Value;
}

void UConfigPropertyRaw::FillConfigStruct_Implementation(
    const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    checkf(false, TEXT("UConfigPropertyRaw::FillConfigStruct_Implementation: not supported"));
}

bool UConfigPropertyRaw::ResetToDefault_Implementation() {
    return false;
}

bool UConfigPropertyRaw::IsSetToDefaultValue_Implementation() const {
    return false;
}

FString UConfigPropertyRaw::GetDefaultValueAsString_Implementation() const {
    return TEXT("");
}

FConfigVariableDescriptor UConfigPropertyRaw::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_RawJsonValue);
}

void UConfigPropertyRaw::PostInitProperties() {
    Super::PostInitProperties();

    bHidden = 1;
    bAllowUserReset = false;
    bRequiresWorldReload = 0;
}

#if WITH_EDITOR
bool UConfigPropertyRaw::CanEditChange(const FProperty* InProperty) const {
    auto Name = InProperty->GetFName();
    if (Name == GET_MEMBER_NAME_CHECKED(UConfigPropertyRaw, bHidden)) {
        return false;
    }
    if (Name == GET_MEMBER_NAME_CHECKED(UConfigPropertyRaw, bAllowUserReset)) {
        return false;
    }
    if (Name == GET_MEMBER_NAME_CHECKED(UConfigPropertyRaw, bRequiresWorldReload)) {
        return false;
    }
    if (Name == GET_MEMBER_NAME_CHECKED(UConfigPropertyRaw, DisplayName)) {
        return false;
    }
    if (Name == GET_MEMBER_NAME_CHECKED(UConfigPropertyRaw, Tooltip)) {
        return false;
    }

    return Super::CanEditChange(InProperty);
}
#endif

﻿#include "Configuration/Properties/ConfigPropertyInteger.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueNumber.h"
#include "Reflection/BlueprintReflectedObject.h"

UConfigPropertyInteger::UConfigPropertyInteger() {
    this->Value = 0;
}

void UConfigPropertyInteger::PostInitProperties() {
    Super::PostInitProperties();
    if (HasAnyFlags(RF_ClassDefaultObject) || bDefaultValueInitialized) {
        return;
    }
    bDefaultValueInitialized = true;
    DefaultValue = Value;
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
    if (!CanResetNow() || !bDefaultValueInitialized) {
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

#include "Configuration/Properties/ConfigPropertyInteger.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueNumber.h"
#include "Reflection/BlueprintReflectedObject.h"

UConfigPropertyInteger::UConfigPropertyInteger() {
    this->Value = 0;
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

void UConfigPropertyInteger::ResetToDefault_Implementation(const UConfigProperty* DefaultProp) {
	const UConfigPropertyInteger* DefaultInteger = Cast<UConfigPropertyInteger>(DefaultProp);
	if (!DefaultInteger || !this->CanEditNow()) {
		return;
	}
	this->Value = DefaultInteger->Value;
	this->MarkDirty();
}

FConfigVariableDescriptor UConfigPropertyInteger::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariablePrimitive(EConfigVariableType::ECVT_Int32);
}

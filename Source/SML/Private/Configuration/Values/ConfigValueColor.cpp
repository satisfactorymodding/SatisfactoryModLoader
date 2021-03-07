#include "Configuration/Values/ConfigValueColor.h"
#include "Configuration/RawFileFormat/RawFormatValueObject.h"

FString UConfigValueColor::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[color %s]"), *Value.ToString());
}

URawFormatValue* UConfigValueColor::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueObject* ObjectValue = NewObject<URawFormatValueObject>(Outer);
    //Add each color channel individually as separate raw number value
    ObjectValue->SetFloat(TEXT("R"), Value.R);
    ObjectValue->SetFloat(TEXT("G"), Value.G);
    ObjectValue->SetFloat(TEXT("B"), Value.B);
    ObjectValue->SetFloat(TEXT("A"), Value.A);
    return ObjectValue;
}

void UConfigValueColor::Deserialize_Implementation(const URawFormatValue* RawValue) {
    const URawFormatValueObject* ObjectValue = Cast<URawFormatValueObject>(RawValue);
    if (ObjectValue != NULL) {
        this->Value.R = ObjectValue->GetFloat(TEXT("R"));
        this->Value.G = ObjectValue->GetFloat(TEXT("G"));
        this->Value.B = ObjectValue->GetFloat(TEXT("B"));
        this->Value.A = ObjectValue->GetFloat(TEXT("A"));
    }
}

void UConfigValueColor::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    FReflectedObject ColorObject{};
    ColorObject.SetupFromStruct(TBaseStructure<FLinearColor>::Get(), &Value);
    ReflectedObject.SetStructProperty(*VariableName, ColorObject);
}

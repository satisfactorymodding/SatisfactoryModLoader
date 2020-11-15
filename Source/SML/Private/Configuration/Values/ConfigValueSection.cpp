#include "Configuration/Values/ConfigValueSection.h"
#include "RawFormatValueObject.h"

TArray<FSectionProperty> UConfigValueSection::GetProperties() const {
    const UConfigPropertySection* SectionProperty = Cast<UConfigPropertySection>(GetAssociatedProperty());
    if (SectionProperty != NULL) {
        return SectionProperty->SectionProperties;
    }
    return TArray<FSectionProperty>();
}

UConfigValue* UConfigValueSection::GetValueForProperty(const FString& PropertyName) const {
    UConfigValue* const* Value = ConfigurationValues.Find(PropertyName);
    return Value != NULL ? *Value : NULL;
}

void UConfigValueSection::FillConfigStructSelf(const FReflectedObject& ReflectedObject) const {
    for (const FSectionProperty& Property : GetProperties()) {
        UConfigValue* ChildValue = GetValueForProperty(Property.Name);
        if (ChildValue != NULL) {
            ChildValue->FillConfigStruct(ReflectedObject, Property.Name);
        }
    }
}

void UConfigValueSection::InitializedFromProperty_Implementation() {
    //We do not call Property->ApplyDefaultValues here, because
    //First we need to populate our map with child value section objects
    //and since we are creating default value objects, they already have defaults applied
    //Applying defaults is still possible though, for example for resetting configuration
    for (const FSectionProperty& Property : GetProperties()) {
        UConfigValue* ChildValue = Property.Property->CreateNewValue(this);
        ConfigurationValues.Add(Property.Name, ChildValue);
    }
}

FString UConfigValueSection::DescribeValue_Implementation() const {
    const FString ElementsString = FString::JoinBy(GetProperties(), TEXT(", "), [this](const FSectionProperty& Property) {
        UConfigValue* PropertyValue = this->GetValueForProperty(Property.Name);
        return FString::Printf(TEXT("%s = %s"), *Property.Name, *PropertyValue->DescribeValue());
    });
    return FString::Printf(TEXT("[section %s]"), *ElementsString);
}

URawFormatValue* UConfigValueSection::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueObject* ObjectValue = NewObject<URawFormatValueObject>(Outer);
    for (const FSectionProperty& Property : GetProperties()) {
        UConfigValue* ChildValue = GetValueForProperty(Property.Name);
        if (ChildValue != NULL) {
            URawFormatValue* RawChildValue = ChildValue->Serialize(ObjectValue);
            if (RawChildValue != NULL) {
                ObjectValue->AddValue(Property.Name, RawChildValue);
            }
        }
    }
    return ObjectValue;
}

void UConfigValueSection::Deserialize_Implementation(const URawFormatValue* Value) {
    const URawFormatValueObject* ObjectValue = Cast<URawFormatValueObject>(Value);
    if (ObjectValue != NULL) {
        for (const FSectionProperty& Property : GetProperties()) {
            UConfigValue* ChildValue = GetValueForProperty(Property.Name);
            const URawFormatValue* RawChildValue = ObjectValue->GetValue(Property.Name);
            if (ChildValue != NULL && RawChildValue != NULL) {
                ChildValue->Deserialize(RawChildValue);
            }
        }
    }
}

void UConfigValueSection::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    //TODO kinda a special case that's not valid in all config values, should probably find a better way to indicate that passed object is actually a self
    const FReflectedObject ChildObject = VariableName.IsEmpty() ? ReflectedObject : ReflectedObject.GetStructProperty(*VariableName);
    FillConfigStructSelf(ChildObject);
    ReflectedObject.SetStructProperty(*VariableName, ChildObject);
}

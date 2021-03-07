#include "Configuration/Values/ConfigValueSection.h"
#include "Configuration/RawFileFormat/RawFormatValueObject.h"

TMap<FString, UConfigProperty*> UConfigValueSection::GetProperties() const {
    const UConfigPropertySection* SectionProperty = Cast<UConfigPropertySection>(GetAssociatedProperty());
    if (SectionProperty != NULL) {
        return SectionProperty->SectionProperties;
    }
    return TMap<FString, UConfigProperty*>();
}

UConfigValue* UConfigValueSection::GetValueForProperty(const FString& PropertyName) const {
    UConfigValue* const* Value = ConfigurationValues.Find(PropertyName);
    return Value != NULL ? *Value : NULL;
}

void UConfigValueSection::FillConfigStructSelf(const FReflectedObject& ReflectedObject) const {
    for (const TPair<FString, UConfigProperty*>& Property : GetProperties()) {
        UConfigValue* ChildValue = GetValueForProperty(Property.Key);
        if (ChildValue != NULL) {
            ChildValue->FillConfigStruct(ReflectedObject, Property.Key);
        }
    }
}

void UConfigValueSection::InitializedFromProperty_Implementation() {
    //We do not call Property->ApplyDefaultValues here, because
    //First we need to populate our map with child value section objects
    //and since we are creating default value objects, they already have defaults applied
    //Applying defaults is still possible though, for example for resetting configuration
    for (const TPair<FString, UConfigProperty*>& Property : GetProperties()) {
        UConfigValue* ChildValue = Property.Value->CreateNewValue(this);
        ConfigurationValues.Add(Property.Key, ChildValue);
    }
}

FString UConfigValueSection::DescribeValue_Implementation() const {
    const FString ElementsString = FString::JoinBy(GetProperties(), TEXT(", "), [this](const TPair<FString, UConfigProperty*>& Property) {
        UConfigValue* PropertyValue = this->GetValueForProperty(Property.Key);
        return FString::Printf(TEXT("%s = %s"), *Property.Key, *PropertyValue->DescribeValue());
    });
    return FString::Printf(TEXT("[section %s]"), *ElementsString);
}

URawFormatValue* UConfigValueSection::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueObject* ObjectValue = NewObject<URawFormatValueObject>(Outer);
    for (const TPair<FString, UConfigProperty*>& Property : GetProperties()) {
        UConfigValue* ChildValue = GetValueForProperty(Property.Key);
        if (ChildValue != NULL) {
            URawFormatValue* RawChildValue = ChildValue->Serialize(ObjectValue);
            if (RawChildValue != NULL) {
                ObjectValue->AddValue(Property.Key, RawChildValue);
            }
        }
    }
    return ObjectValue;
}

void UConfigValueSection::Deserialize_Implementation(const URawFormatValue* Value) {
    const URawFormatValueObject* ObjectValue = Cast<URawFormatValueObject>(Value);
    if (ObjectValue != NULL) {
        for (const TPair<FString, UConfigProperty*>& Property : GetProperties()) {
            UConfigValue* ChildValue = GetValueForProperty(Property.Key);
            const URawFormatValue* RawChildValue = ObjectValue->GetValue(Property.Key);
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

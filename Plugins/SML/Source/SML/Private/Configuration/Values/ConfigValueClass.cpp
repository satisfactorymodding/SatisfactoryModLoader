#include "Configuration/Values/ConfigValueClass.h"
#include "Configuration/Properties/ConfigPropertyClass.h"
#include "Configuration/RawFileFormat/RawFormatValueString.h"


void UConfigValueClass::SetClassValue(UClass* ClassValue) {
    if (IsClassValueValid(ClassValue)) {
        this->PrivateClassValue = ClassValue;
    }
}

UClass* UConfigValueClass::GetClassValue() const {
    return IsClassValueValid(PrivateClassValue) ? PrivateClassValue : NULL;
}

bool UConfigValueClass::IsClassValueValid(UClass* Class) const {
    const UConfigPropertyClass* ClassProperty = Cast<UConfigPropertyClass>(GetAssociatedProperty());
    return ClassProperty != NULL && ClassProperty->IsValidValueClass(Class);
}

FString UConfigValueClass::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[class %s]"), *GetClassValue()->GetPathName());
}

URawFormatValue* UConfigValueClass::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueString* StringValue = NewObject<URawFormatValueString>(Outer);
    StringValue->Value = GetClassValue()->GetPathName();
    return StringValue;
}

void UConfigValueClass::Deserialize_Implementation(const URawFormatValue* Value) {
    const URawFormatValueString* StringValue = Cast<URawFormatValueString>(Value);
    if (StringValue != NULL) {
        if (StringValue->Value != TEXT("None")) {
            //String indicates full class path name, so use LoadObject<UClass> to actually load it
            //SetClassValue will take care of type checking provided class object
            UClass* LoadedClassObject = LoadObject<UClass>(NULL, *StringValue->Value);
            if (LoadedClassObject != NULL) {
                SetClassValue(LoadedClassObject);
            }
        } else {
            //String is equal to None, and None is a special value indicating NULL class
            //If we don't allow NULL value, IsClassValueValid will return false, and value will remain default
            SetClassValue(NULL);
        }
    }
}

void UConfigValueClass::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    ReflectedObject.SetObjectProperty(*VariableName, GetClassValue());
}

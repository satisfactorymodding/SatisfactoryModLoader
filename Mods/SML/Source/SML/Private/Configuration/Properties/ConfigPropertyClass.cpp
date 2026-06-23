#include "Configuration/Properties/ConfigPropertyClass.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueString.h"
#include "Reflection/BlueprintReflectedObject.h"

#define LOCTEXT_NAMESPACE "SML"

UConfigPropertyClass::UConfigPropertyClass() {
    DefaultValue = NULL;
    BaseClass = UObject::StaticClass();
    bLimitBaseClass = false;
}

#if WITH_EDITOR
void UConfigPropertyClass::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
    Super::PostEditChangeProperty(PropertyChangedEvent);
    // When DefaultValue is changed in the editor, sync Value to match it.
    // This prevents the old Value from triggering migration on next load.
    // [Remove this entire function once migration is no longer needed]
    if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UConfigPropertyClass, DefaultValue)) {
        Value = DefaultValue;
    }
}
#endif

void UConfigPropertyClass::PostLoad() {
    Super::PostLoad();
    // Migrate to DefaultValue from Value [Remove only this if statement once migration is no longer needed]
    // PostLoad runs before the user config is deserialized, but it still has the values from the CDO. If DefaultValue
    // is set to the type default and Value is not, then Value has the old default value that we need to migrate.
    if (DefaultValue == NULL && Value != DefaultValue) {
        DefaultValue = Value;
    }
    // Set initial value to default value. This runs before the user config is deserialized
    // and ensures that if the user has never set a value, it's set to the default.
    Value = DefaultValue;
}

bool UConfigPropertyClass::IsValidValueClass(UClass* Class) const {
    return Class ? (bLimitBaseClass && BaseClass ? Class->IsChildOf(BaseClass) : true) : bAllowNullValue;
}

void UConfigPropertyClass::SetClassValue(UClass* NewValue) {
    if (IsValidValueClass(NewValue)) {
        this->Value = NewValue;
    }
}

#if WITH_EDITOR
EDataValidationResult UConfigPropertyClass::IsDataValid(TArray<FText>& ValidationErrors) {
    if (!IsValidValueClass(Value)) {
        ValidationErrors.Add(FText::Format(LOCTEXT("InvalidDefaultClassValue", "Class property '{0}' default value '{1}' is not valid "
            "with provided BaseClass/bAllowNullValue property settings"),
            FText::FromString(GetPathName()), FText::FromString(Value->GetPathName())));
        return EDataValidationResult::Invalid;
    }
    return EDataValidationResult::Valid;
}
#endif

FString UConfigPropertyClass::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[class %s]"), *Value->GetPathName());
}

URawFormatValue* UConfigPropertyClass::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueString* StringValue = NewObject<URawFormatValueString>(Outer);
    StringValue->Value = Value->GetPathName();
    return StringValue;
}

void UConfigPropertyClass::Deserialize_Implementation(const URawFormatValue* RawValue) {
    const URawFormatValueString* StringValue = Cast<URawFormatValueString>(RawValue);
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

void UConfigPropertyClass::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    ReflectedObject.SetObjectProperty(*VariableName, Value);
}

bool UConfigPropertyClass::ResetToDefault_Implementation() {
    if (!CanResetNow()) {
        return false;
    }
    SetClassValue(DefaultValue);
    MarkDirty();
    return true;
}

bool UConfigPropertyClass::IsSetToDefaultValue_Implementation() const {
    return Value == DefaultValue;
}

FString UConfigPropertyClass::GetDefaultValueAsString_Implementation() const {
    return DefaultValue ? DefaultValue->GetName() : TEXT("");
}

FConfigVariableDescriptor UConfigPropertyClass::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariableClass(BaseClass);
}

#undef LOCTEXT_NAMESPACE
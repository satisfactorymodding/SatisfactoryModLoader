#include "Configuration/Properties/ConfigPropertyArray.h"
#include "Configuration/Properties/ConfigPropertyFloat.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/RawFileFormat/RawFormatValueArray.h"
#include "Reflection/BlueprintReflectedObject.h"

#define LOCTEXT_NAMESPACE "SML"

#if WITH_EDITOR
void UConfigPropertyArray::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
    Super::PostEditChangeProperty(PropertyChangedEvent);
    // When DefaultValues is changed in the editor, sync Values to match it.
    // This prevents the old Values from triggering migration on next load.
    // [Remove this entire function once migration is no longer needed]
    if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UConfigPropertyArray, DefaultValues)) {
        Values.Empty(DefaultValues.Num());
        for (UConfigProperty* Property : DefaultValues) {
            if (Property) {
                UConfigProperty* Clone = DuplicateObject<UConfigProperty>(Property, this);
                Values.Add(Clone);
            } else {
                Values.Add(nullptr);
            }
        }
    }
}
#endif

void UConfigPropertyArray::PostLoad() {
    Super::PostLoad();
    // Migrate to DefaultValues from Values [Remove only this if statement once migration is no longer needed]
    // PostLoad runs before the user config is deserialized, but it still has the values from the CDO. If DefaultValues
    // is set to the type default and Values is not, then Values has the old default value that we need to migrate.
    if (DefaultValues.Num() == 0 && Values.Num() > 0) {
        DefaultValues = Values; // Hand off the pointer, no need to duplicate. Values.Empty() below will not delete the objects
    }
    // Set initial value to default value. This runs before the user config is deserialized
    // and ensures that if the user has never set a value, it's set to the default.
    Values.Empty(DefaultValues.Num());
    for (UConfigProperty* Property : DefaultValues) {
        if (Property) {
            UConfigProperty* Clone = DuplicateObject<UConfigProperty>(Property, this);
            Values.Add(Clone);
        } else {
            Values.Add(nullptr);
        }
    }
}

UConfigProperty* UConfigPropertyArray::AddNewElement() {
    checkf(DefaultValue, TEXT("Cannot add new element without default value defined"));
    UConfigProperty* NewValueProperty = NewObject<UConfigProperty>(this, DefaultValue->GetClass(), NAME_None, RF_NoFlags, DefaultValue);
    Values.Add(NewValueProperty);
    return NewValueProperty;
}

void UConfigPropertyArray::RemoveElementAtIndex(int32 Index) {
    if (Index >= 0 && Index < Values.Num()) {
        Values.RemoveAt(Index);
    }
}

void UConfigPropertyArray::Clear() {
    Values.Empty();
}

#if WITH_EDITOR
bool UConfigPropertyArray::CanEditChange(const FProperty* InProperty) const {
    const bool bCanSuperChange = Super::CanEditChange(InProperty);
    if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UConfigPropertyArray, Values)) {
        return bCanSuperChange && IsValid(DefaultValue);
    }
    return bCanSuperChange;
}

EDataValidationResult UConfigPropertyArray::IsDataValid(TArray<FText>& ValidationErrors) {
 /*
	if (DefaultValue == NULL) {
        ValidationErrors.Add(FText::Format(LOCTEXT("ArrayDefaultValueConfigNotSet",
            "Default Value for Array Property '{0}' is not set."), FText::FromString(GetPathName())));
        return EDataValidationResult::Invalid;
    }
*/
    EDataValidationResult ValidationResult = EDataValidationResult::Valid;
    for (const UConfigProperty* ConfigProperty : Values) {
        if (ConfigProperty == NULL ||
            ConfigProperty->GetClass() != DefaultValue->GetClass()) {
            ValidationErrors.Add(FText::Format(LOCTEXT("ArrayValueInvalid",
                "Array Property '{0}' Value '{1}' is invalid, or does not have the same class as Default Value. "
                "Default Value Class is '{0}', Value Class is '{1}'."),
                FText::FromString(GetPathName()), FText::FromString(ConfigProperty->GetPathName()),
                FText::FromString(DefaultValue->GetClass()->GetName()),
                FText::FromString(ConfigProperty ? ConfigProperty->GetClass()->GetName() : TEXT("None"))));
            ValidationResult = EDataValidationResult::Invalid;
        }
    }
    return ValidationResult;
}
#endif

FString UConfigPropertyArray::DescribeValue_Implementation() const {
    const FString ElementsString = FString::JoinBy(Values, TEXT(", "),
        [](const UConfigProperty* Value) { return Value->DescribeValue(); });
    return FString::Printf(TEXT("[array: %s]"), *ElementsString);
}

URawFormatValue* UConfigPropertyArray::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueArray* SerializedArray = NewObject<URawFormatValueArray>(Outer);
    for (const UConfigProperty* Value : Values) {
        //Specify serialization array as outer for allocated value objects
        SerializedArray->AddValue(Value->Serialize(SerializedArray));
    }
    return SerializedArray;
}

void UConfigPropertyArray::Deserialize_Implementation(const URawFormatValue* Value) {
    const URawFormatValueArray* SerializedArray = Cast<URawFormatValueArray>(Value);
    if (SerializedArray != NULL) {
        //Empty array but reserve enough Slack space to keep all elements we are going to add
        Values.Empty(SerializedArray->Num());
        //Just iterate raw format array and deserialize each of its items
        for (URawFormatValue* RawFormatValue : SerializedArray->GetUnderlyingArrayRef()) {
            UConfigProperty* AllocatedValue = AddNewElement();
            if (!bAllowUserReset || !bParentSectionAllowsUserReset) {
                AllocatedValue->bParentSectionAllowsUserReset = false;
            }
            AllocatedValue->Deserialize(RawFormatValue);
        }
    }
    // Set default values to inherit Allow User Reset
    for (UConfigProperty* Property : DefaultValues) {
        if (Property && (!bAllowUserReset || !bParentSectionAllowsUserReset)) {
            Property->bParentSectionAllowsUserReset = false;
        }
    }
}

void UConfigPropertyArray::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    const FReflectedObject ArrayObject = ReflectedObject.GetArrayProperty(*VariableName);
    ArrayObject.ClearArray();
    for (const UConfigProperty* Property : Values) {
        const int32 NewElementIndex = ArrayObject.AddNewArrayElement();
        check(NewElementIndex >= 0);
        Property->FillConfigStruct(ArrayObject, FString::FromInt(NewElementIndex));
    }
}

bool UConfigPropertyArray::ResetToDefault_Implementation() {
    if (!CanResetNow()) {
        return false;
    }
    Values.Empty(DefaultValues.Num());
    for (UConfigProperty* Property : DefaultValues) {
        if (Property) {
            UConfigProperty* Clone = DuplicateObject<UConfigProperty>(Property, this);
            Values.Add(Clone);
        } else {
            Values.Add(nullptr);
        }
    }
    MarkDirty();
    return true;
}

bool UConfigPropertyArray::IsSetToDefaultValue_Implementation() const {
    if (Values.Num() != DefaultValues.Num()) {
        return false;
    }
    for (int32 i = 0; i < Values.Num(); i++) {
        const UConfigProperty* UserProperty = Values[i];
        const UConfigProperty* DefaultProperty = DefaultValues.IsValidIndex(i) ? DefaultValues[i] : nullptr;
        if (!UserProperty || !DefaultProperty) {
            return false;
        }
        // Check if the classes match and if the values are equal
        if (UserProperty->GetClass() != DefaultProperty->GetClass()) {
            return false;
        }
        // Special case for float properties to use FMath::IsNearlyEqual for comparison
        if (const UConfigPropertyFloat* UserFloat = Cast<UConfigPropertyFloat>(UserProperty)) {
            const UConfigPropertyFloat* DefaultFloat = Cast<UConfigPropertyFloat>(DefaultProperty);
            if (!DefaultFloat || !FMath::IsNearlyEqual(UserFloat->Value, DefaultFloat->Value, SMALL_NUMBER)) {
                return false;
            }
        }
        // For other property types, compare describe values
        else if (UserProperty->DescribeValue() != DefaultProperty->DescribeValue()) {
            return false;
        }
    }
    // MarkDirty();
    return true;
}

FString UConfigPropertyArray::GetDefaultValueAsString_Implementation() const {
    // A bit hacky, but Property->GetDefaultValueAsString() does not work here as the default
    // values are not initialized within the DefaultValues array for whatever reason.
    return FString::JoinBy(DefaultValues, TEXT(", "), [](const UConfigProperty* Property) -> FString {
        if (!Property) {
            return TEXT("null");
        }
        const FString d = Property->DescribeValue();
        int32 i = d.Find(TEXT(" "));
        return (i == INDEX_NONE || d.Len() < 2) ? d : d.Mid(i + 1, d.Len() - i - 2);
    });
}

void UConfigPropertyArray::HandleMarkDirty_Implementation() {
    MarkDirty();
}

FConfigVariableDescriptor UConfigPropertyArray::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariableArray(DefaultValue->CreatePropertyDescriptor(Context, OuterPath));
}

#undef LOCTEXT_NAMESPACE
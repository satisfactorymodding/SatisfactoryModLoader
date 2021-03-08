#include "Configuration/Values/ConfigValueArray.h"
#include "Configuration/RawFileFormat/RawFormatValueArray.h"

int32 UConfigValueArray::ElementCount() const {
    return Values.Num();
}

UConfigValue* UConfigValueArray::GetElement(int32 Index) const {
    if (Index >= 0 && Index < Values.Num()) {
        return Values[Index];
    }
    return NULL;
}


UConfigValue* UConfigValueArray::AddNewElement() {
    checkf(GetAssociatedProperty(), TEXT("Cannot add new element without property associated"));
    UConfigValue* NewAllocatedValue = GetAssociatedProperty()->CreateNewValue(this);
    Values.Add(NewAllocatedValue);
    return NewAllocatedValue;
}

void UConfigValueArray::RemoveElementAtIndex(int32 Index) {
    if (Index >= 0 && Index < Values.Num()) {
        Values.RemoveAt(Index);
    }
}

void UConfigValueArray::Clear() {
    Values.Empty();
}

FString UConfigValueArray::DescribeValue_Implementation() const {
    const FString ElementsString = FString::JoinBy(Values, TEXT(", "),
        [](const UConfigValue* Value) { return Value->DescribeValue(); });
    return FString::Printf(TEXT("[array: %s]"), *ElementsString);
}

URawFormatValue* UConfigValueArray::Serialize_Implementation(UObject* Outer) const {
    URawFormatValueArray* SerializedArray = NewObject<URawFormatValueArray>(Outer);
    for (const UConfigValue* Value : Values) {
        //Specify serialization array as outer for allocated value objects
        SerializedArray->AddValue(Value->Serialize(SerializedArray));
    }
    return SerializedArray;
}

void UConfigValueArray::Deserialize_Implementation(const URawFormatValue* Value) {
    const URawFormatValueArray* SerializedArray = Cast<URawFormatValueArray>(Value);
    if (SerializedArray != NULL) {
        //Empty array but reserve enough Slack space to keep all elements we are going to add
        Values.Empty(SerializedArray->Num());
        //Just iterate raw format array and deserialize each of it's items
        for (URawFormatValue* RawFormatValue : SerializedArray->GetUnderlyingArrayRef()) {
            UConfigValue* AllocatedValue = AddNewElement();
            AllocatedValue->Deserialize(RawFormatValue);
        }
    }
}

void UConfigValueArray::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const {
    
}

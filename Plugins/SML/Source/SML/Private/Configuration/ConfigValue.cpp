#include "Configuration/ConfigValue.h"

FString UConfigValue::DescribeValue_Implementation() const {
    return FString::Printf(TEXT("[unknown value %s]"), *GetClass()->GetPathName());
}

URawFormatValue* UConfigValue::Serialize_Implementation(UObject* Outer) const {
    checkf(false, TEXT("Serialize not implemented"));
    return NULL;
}

void UConfigValue::Deserialize_Implementation(const URawFormatValue* Value) {
    checkf(false, TEXT("Deserialize not implemented"));
}

void UConfigValue::InitializedFromProperty_Implementation() {
    GetAssociatedProperty()->ApplyDefaultPropertyValue(this);
}

void UConfigValue::FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject,
    const FString& VariableName) const {
    checkf(false, TEXT("FillConfigStruct not implemented"));
}

void UConfigValue::MarkDirty() {
    //Let closest Outer object implementing IConfigValueDirtyHandlerInterface handle MarkDirty call
    for (UObject* NextOuter = GetOuter(); NextOuter != NULL; NextOuter = NextOuter->GetOuter()) {
        if (NextOuter->Implements<UConfigValueDirtyHandlerInterface>()) {
            IConfigValueDirtyHandlerInterface::Execute_MarkDirty(NextOuter);
            break;
        }
    }
}

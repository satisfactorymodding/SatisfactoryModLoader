#include "Reflection/BlueprintReflectionLibrary.h"

UObject* UBlueprintReflectionLibrary::GetClassDefaultObject(UClass* Class) {
    return Class->GetDefaultObject();
}

FReflectedObject UBlueprintReflectionLibrary::ReflectObject(UObject* Object) {
    checkf(Object, TEXT("Cannot Reflect NULL object"));
    FReflectedObject ReflectedObject{};
    ReflectedObject.SetupFromUObject(Object);
    return ReflectedObject;
}

FReflectedObject UBlueprintReflectionLibrary::ReflectStruct(const FDynamicStructInfo& StructInfo) {
    checkf(StructInfo.StructValue, TEXT("Cannot Reflect NULL struct"));
    FReflectedObject ReflectedObject{};
    ReflectedObject.SetupFromStruct(StructInfo.Struct, StructInfo.Struct);
    return ReflectedObject;
}

UObject* UBlueprintReflectionLibrary::DeflectObject(const FReflectedObject& ReflectedObject) {
    return ReflectedObject.GetWrappedObject();
}

void UBlueprintReflectionLibrary::DeflectStruct(const FReflectedObject& ReflectedObject, const FDynamicStructInfo& StructInfo) {
    checkf(StructInfo.StructValue, TEXT("Cannot Deflect into NULL struct"));
    checkf(StructInfo.Struct == ReflectedObject.GetStruct(), TEXT("Cannot Deflect into struct of different type"));
    ReflectedObject.CopyWrappedStruct(StructInfo.Struct, StructInfo.StructValue);
}

TArray<FReflectedPropertyInfo> UBlueprintReflectionLibrary::GetReflectedProperties(const FReflectedObject& ReflectedObject) {
    return ReflectedObject.GetReflectedProperties();
}

uint8 UBlueprintReflectionLibrary::GetByteProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex) {
    return ReflectedObject.GetByteProperty(PropertyName, ArrayIndex);
}

void UBlueprintReflectionLibrary::SetByteProperty(const FReflectedObject& ReflectedObject, FName PropertyName, uint8 Value, int32 ArrayIndex) {
    ReflectedObject.SetByteProperty(PropertyName, Value, ArrayIndex);
}

int64 UBlueprintReflectionLibrary::GetInt64Property(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex) {
    return ReflectedObject.GetInt64Property(PropertyName, ArrayIndex);
}

void UBlueprintReflectionLibrary::SetInt64Property(const FReflectedObject& ReflectedObject, FName PropertyName, int64 Value, int32 ArrayIndex) {
    ReflectedObject.SetInt64Property(PropertyName, Value, ArrayIndex);
}

int32 UBlueprintReflectionLibrary::GetInt32Property(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex) {
    return ReflectedObject.GetInt32Property(PropertyName, ArrayIndex);
}

void UBlueprintReflectionLibrary::SetInt32Property(const FReflectedObject& ReflectedObject, FName PropertyName, int32 Value, int32 ArrayIndex) {
    ReflectedObject.SetInt32Property(PropertyName, Value, ArrayIndex);
}

float UBlueprintReflectionLibrary::GetFloatProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex) {
    return ReflectedObject.GetFloatProperty(PropertyName, ArrayIndex);
}

void UBlueprintReflectionLibrary::SetFloatProperty(const FReflectedObject& ReflectedObject, FName PropertyName, float Value, int32 ArrayIndex) {
    ReflectedObject.SetFloatProperty(PropertyName, Value, ArrayIndex);
}

FString UBlueprintReflectionLibrary::GetStringProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex) {
    return ReflectedObject.GetStringProperty(PropertyName, ArrayIndex);
}

void UBlueprintReflectionLibrary::SetStringProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FString& Value, int32 ArrayIndex) {
    ReflectedObject.SetStringProperty(PropertyName, Value, ArrayIndex);
}

bool UBlueprintReflectionLibrary::GetBoolProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex) {
    return ReflectedObject.GetBoolProperty(PropertyName, ArrayIndex);
}

void UBlueprintReflectionLibrary::SetBoolProperty(const FReflectedObject& ReflectedObject, FName PropertyName, bool Value, int32 ArrayIndex) {
    ReflectedObject.SetBoolProperty(PropertyName, Value, ArrayIndex);
}

FName UBlueprintReflectionLibrary::GetNameProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex) {
    return ReflectedObject.GetNameProperty(PropertyName, ArrayIndex);
}

void UBlueprintReflectionLibrary::SetNameProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FName& Name, int32 ArrayIndex) {
    ReflectedObject.SetNameProperty(PropertyName, Name, ArrayIndex);
}

FText UBlueprintReflectionLibrary::GetTextProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex) {
    return ReflectedObject.GetTextProperty(PropertyName, ArrayIndex);
}

void UBlueprintReflectionLibrary::SetTextProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FText& Text, int32 ArrayIndex) {
    ReflectedObject.SetTextProperty(PropertyName, Text, ArrayIndex);
}

UObject* UBlueprintReflectionLibrary::GetObjectProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex) {
    return ReflectedObject.GetObjectProperty(PropertyName, ArrayIndex);
}

void UBlueprintReflectionLibrary::SetObjectProperty(const FReflectedObject& ReflectedObject, FName PropertyName, UObject* Object, int32 ArrayIndex) {
    ReflectedObject.SetObjectProperty(PropertyName, Object, ArrayIndex);
}

FReflectedObject UBlueprintReflectionLibrary::GetStructProperty(const FReflectedObject& ReflectedObject, FName PropertyName, int32 ArrayIndex) {
    return ReflectedObject.GetStructProperty(PropertyName, ArrayIndex);
}

void UBlueprintReflectionLibrary::SetStructProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FReflectedObject& Struct, int32 ArrayIndex) {
    ReflectedObject.SetStructProperty(PropertyName, Struct, ArrayIndex);
}

FReflectedEnumValue UBlueprintReflectionLibrary::GetEnumProperty(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetEnumProperty(PropertyName);
}

void UBlueprintReflectionLibrary::SetEnumProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FReflectedEnumValue& Enum) {
    ReflectedObject.SetEnumProperty(PropertyName, Enum);
}

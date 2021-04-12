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

int32 UBlueprintReflectionLibrary::GetArrayNum(const FReflectedObject& ReflectedObject) {
    return ReflectedObject.GetArrayNum();
}

int32 UBlueprintReflectionLibrary::AddNewArrayElement(const FReflectedObject& ReflectedObject) {
    return ReflectedObject.AddNewArrayElement();
}

void UBlueprintReflectionLibrary::RemoveArrayElements(const FReflectedObject& ReflectedObject, int32 Index, int32 Count) {
    ReflectedObject.RemoveArrayElements(Index, Count);
}

uint8 UBlueprintReflectionLibrary::GetByteProperty(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetByteProperty(PropertyName);
}

void UBlueprintReflectionLibrary::SetByteProperty(const FReflectedObject& ReflectedObject, FName PropertyName, uint8 Value) {
    ReflectedObject.SetByteProperty(PropertyName, Value);
}

int64 UBlueprintReflectionLibrary::GetInt64Property(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetInt64Property(PropertyName);
}

void UBlueprintReflectionLibrary::SetInt64Property(const FReflectedObject& ReflectedObject, FName PropertyName, int64 Value) {
    ReflectedObject.SetInt64Property(PropertyName, Value);
}

int32 UBlueprintReflectionLibrary::GetInt32Property(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetIntProperty(PropertyName);
}

void UBlueprintReflectionLibrary::SetInt32Property(const FReflectedObject& ReflectedObject, FName PropertyName, int32 Value) {
    ReflectedObject.SetIntProperty(PropertyName, Value);
}

float UBlueprintReflectionLibrary::GetFloatProperty(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetFloatProperty(PropertyName);
}

void UBlueprintReflectionLibrary::SetFloatProperty(const FReflectedObject& ReflectedObject, FName PropertyName, float Value) {
    ReflectedObject.SetFloatProperty(PropertyName, Value);
}

FString UBlueprintReflectionLibrary::GetStringProperty(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetStrProperty(PropertyName);
}

void UBlueprintReflectionLibrary::SetStringProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FString& Value) {
    ReflectedObject.SetStrProperty(PropertyName, Value);
}

bool UBlueprintReflectionLibrary::GetBoolProperty(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetBoolProperty(PropertyName);
}

void UBlueprintReflectionLibrary::SetBoolProperty(const FReflectedObject& ReflectedObject, FName PropertyName, bool Value) {
    ReflectedObject.SetBoolProperty(PropertyName, Value);
}

FName UBlueprintReflectionLibrary::GetNameProperty(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetNameProperty(PropertyName);
}

void UBlueprintReflectionLibrary::SetNameProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FName& Name) {
    ReflectedObject.SetNameProperty(PropertyName, Name);
}

FText UBlueprintReflectionLibrary::GetTextProperty(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetTextProperty(PropertyName);
}

void UBlueprintReflectionLibrary::SetTextProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FText& Text) {
    ReflectedObject.SetTextProperty(PropertyName, Text);
}

UObject* UBlueprintReflectionLibrary::GetObjectProperty(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetObjectProperty(PropertyName);
}

void UBlueprintReflectionLibrary::SetObjectProperty(const FReflectedObject& ReflectedObject, FName PropertyName, UObject* Object) {
    ReflectedObject.SetObjectProperty(PropertyName, Object);
}

FReflectedObject UBlueprintReflectionLibrary::GetStructProperty(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetStructProperty(PropertyName);
}

void UBlueprintReflectionLibrary::SetStructProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FReflectedObject& Struct) {
    ReflectedObject.SetStructProperty(PropertyName, Struct);
}

FReflectedEnumValue UBlueprintReflectionLibrary::GetEnumProperty(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetEnumProperty(PropertyName);
}

void UBlueprintReflectionLibrary::SetEnumProperty(const FReflectedObject& ReflectedObject, FName PropertyName, FReflectedEnumValue& Enum) {
    ReflectedObject.SetEnumProperty(PropertyName, Enum);
}

FReflectedObject UBlueprintReflectionLibrary::GetArrayProperty(const FReflectedObject& ReflectedObject, FName PropertyName) {
    return ReflectedObject.GetArrayProperty(PropertyName);
}

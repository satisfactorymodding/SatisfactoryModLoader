#include "Reflection/BlueprintReflectedObject.h"
#include "UObject/TextProperty.h"

#define GET_PROPERTY(PropertyType, bCheckWriteable) \
    PropertyType* Property = Cast<PropertyType>(FindProperty(PropertyName, bCheckWriteable)); \
    void* ObjectValue = GetObjectData(); \
    bool bIsPropertyValid = Property != NULL && ObjectValue != NULL && IsValidIndex(ArrayIndex, Property->ArrayDim);

FReflectedObjectState_UObject::FReflectedObjectState_UObject(UObject* Object) {
    checkf(Object, TEXT("Cannot construct state without valid UObject"));
    this->ReferencedObject = Object;
}

void FReflectedObjectState_UObject::CopyStructValue(UScriptStruct* StructType, void* StructValue) const {
}

UObject* FReflectedObjectState_UObject::GetObjectPointer() const {
    return ReferencedObject;
}

bool FReflectedObjectState_UObject::ShouldStripPropertyNames() const {
    return false;
}

UStruct* FReflectedObjectState_UObject::GetStructObject() const {
    return ReferencedObject ? ReferencedObject->GetClass() : NULL;
}

void* FReflectedObjectState_UObject::GetObjectData() {
    return ReferencedObject;
}

void FReflectedObjectState_UObject::AddReferencedObjects(FReferenceCollector& ReferenceCollector) {
    ReferenceCollector.AddReferencedObject(ReferencedObject);
}

FReflectedObjectState_ScriptStruct::FReflectedObjectState_ScriptStruct(UScriptStruct* Struct) {
    checkf(Struct, TEXT("Cannot construct state with NULL struct"));
    this->ScriptStruct = Struct;
    this->StructDataPointer = FMemory::Malloc(Struct->GetStructureSize());
    Struct->InitializeStruct(StructDataPointer);
}

FReflectedObjectState_ScriptStruct::~FReflectedObjectState_ScriptStruct() {
    if (StructDataPointer != NULL) {
        ScriptStruct->DestroyStruct(StructDataPointer);
        FMemory::Free(StructDataPointer);
        this->StructDataPointer = NULL;
    }
}

void FReflectedObjectState_ScriptStruct::CopyStructValue(UScriptStruct* StructType, void* StructValue) const {
    checkf(StructValue, TEXT("Attempt to Copy Struct Value into NULL struct"));
    checkf(ScriptStruct == StructType, TEXT("Attempt to Copy Struct Value into struct with different type"));
    if (ScriptStruct != NULL && ScriptStruct == StructType) {
        ScriptStruct->CopyScriptStruct(StructValue, StructDataPointer);
    }
}

UObject* FReflectedObjectState_ScriptStruct::GetObjectPointer() const {
    return NULL;
}

bool FReflectedObjectState_ScriptStruct::ShouldStripPropertyNames() const {
    return true;
}

void FReflectedObjectState_ScriptStruct::CopyDataFromStruct(const void* SourceStruct) const {
    if (StructDataPointer != NULL) {
        ScriptStruct->CopyScriptStruct(StructDataPointer, SourceStruct);
    }
}

UStruct* FReflectedObjectState_ScriptStruct::GetStructObject() const {
    return ScriptStruct;
}

void* FReflectedObjectState_ScriptStruct::GetObjectData() {
    return StructDataPointer;
}

void FReflectedObjectState_ScriptStruct::AddReferencedObjects(FReferenceCollector& ReferenceCollector) {
    UScriptStruct* OldStruct = ScriptStruct;
    ReferenceCollector.AddReferencedObject(ScriptStruct);
    //If struct defined custom AddStructReferencedObjects, call it directly
    if (OldStruct->StructFlags & STRUCT_AddStructReferencedObjects) {
        OldStruct->GetCppStructOps()->AddStructReferencedObjects()(StructDataPointer, ReferenceCollector);
    } else {
        //Otherwise fallback to slow UProperty reference traversal via serialization
        OldStruct->SerializeItem(ReferenceCollector.GetVerySlowReferenceCollectorArchive(), StructDataPointer, nullptr);
    }
}

FReflectedEnumValue::FReflectedEnumValue() : EnumerationType(NULL), RawEnumValue(0) {}

FReflectedEnumValue::FReflectedEnumValue(UEnum* EnumType, int64 EnumValue) : EnumerationType(EnumType), RawEnumValue(EnumValue) {}

UEnum* FReflectedEnumValue::GetEnumerationType() const {
    return EnumerationType;
}

int64 FReflectedEnumValue::GetCurrentValue() const {
    return RawEnumValue;
}

void FReflectedEnumValue::SetCurrentValue(int64 NewValue) {
    if (EnumerationType != NULL) {
        checkf(EnumerationType->IsValidEnumValue(NewValue), TEXT("Invalid Enum value: %d"), NewValue);
    }
    this->RawEnumValue = NewValue;
}

void FReflectedObject::SetupFromUObject(UObject* Object) {
    checkf(Object, TEXT("Cannot setup from NULL UObject"));
    this->State = MakeShareable(new FReflectedObjectState_UObject(Object));
}

void FReflectedObject::SetupFromStruct(UScriptStruct* StructType, const void* StructData) {
    checkf(StructType, TEXT("Cannot setup from NULL ScriptStruct"));
    const TSharedPtr<FReflectedObjectState_ScriptStruct> StructState = MakeShareable(new FReflectedObjectState_ScriptStruct(StructType));
    this->State = StructState;
    if (StructData != NULL) {
        StructState->CopyDataFromStruct(StructData);
    }
}

UObject* FReflectedObject::GetWrappedObject() const {
    return State.IsValid() ? State->GetObjectPointer() : NULL;
}

void FReflectedObject::CopyWrappedStruct(UScriptStruct* StructType, void* StructValue) const {
    if (State.IsValid()) {
        State->CopyStructValue(StructType, StructValue);
    }
}

EReflectedPropertyType DeterminePropertyType(UProperty* Property) {
    EReflectedPropertyType PropertyType = EReflectedPropertyType::ERPT_Invalid;
    if (UByteProperty* ByteProperty = Cast<UByteProperty>(Property)) {
        if (ByteProperty->IsEnum())
            PropertyType = EReflectedPropertyType::ERPT_Enum;
        else PropertyType = EReflectedPropertyType::ERPT_Byte;
    } else if (Property->IsA<UIntProperty>()) {
        PropertyType = EReflectedPropertyType::ERPT_Int32;
    } else if (Property->IsA<UInt64Property>()) {
        PropertyType = EReflectedPropertyType::ERPT_Int64;
    } else if (Property->IsA<UFloatProperty>()) {
        PropertyType = EReflectedPropertyType::ERPT_Float;
    } else if (Property->IsA<UStrProperty>()) {
        PropertyType = EReflectedPropertyType::ERPT_String;
    } else if (Property->IsA<UNameProperty>()) {
        PropertyType = EReflectedPropertyType::ERPT_Name;
    } else if (Property->IsA<UTextProperty>()) {
        PropertyType = EReflectedPropertyType::ERPT_Text;
    } else if (Property->IsA<UBoolProperty>()) {
        PropertyType = EReflectedPropertyType::ERPT_Bool;
    } else if (Property->IsA<UEnumProperty>()) {
        PropertyType = EReflectedPropertyType::ERPT_Enum;
    } else if (Property->IsA<UObjectPropertyBase>()) {
        PropertyType = EReflectedPropertyType::ERPT_Object;
    } else if (Property->IsA<UStructProperty>()) {
        PropertyType = EReflectedPropertyType::ERPT_Struct;
    }
    return PropertyType;
}

TArray<FReflectedPropertyInfo> FReflectedObject::GetReflectedProperties() const {
    UStruct* ObjectStruct = GetStruct();
    TArray<FReflectedPropertyInfo> OutPropertyInfo;
    if (ObjectStruct != NULL) {
        for(UProperty* Property = ObjectStruct->PropertyLink; Property; Property = Property->PropertyLinkNext) {
            if (Property->HasAnyPropertyFlags(CPF_BlueprintVisible)) {
                const FName Name = Property->GetFName();
                const EReflectedPropertyType PropertyType = DeterminePropertyType(Property);
                const int32 ArrayDim = Property->ArrayDim;
                if (PropertyType != EReflectedPropertyType::ERPT_Invalid) {
                    OutPropertyInfo.Add(FReflectedPropertyInfo{Name, PropertyType, ArrayDim});
                }
            }
        }
    }
    return OutPropertyInfo;
}

uint8 FReflectedObject::GetByteProperty(FName PropertyName, int32 ArrayIndex) const {
    GET_PROPERTY(UByteProperty, false);
    return bIsPropertyValid ? Property->GetPropertyValue_InContainer(ObjectValue, ArrayIndex) : 0;
}

void FReflectedObject::SetByteProperty(FName PropertyName, uint8 Value, int32 ArrayIndex) const {
    GET_PROPERTY(UByteProperty, true);
    if (bIsPropertyValid) {
        Property->SetPropertyValue_InContainer(ObjectValue, Value, ArrayIndex);
    }
}

int32 FReflectedObject::GetInt32Property(FName PropertyName, int32 ArrayIndex) const {
    GET_PROPERTY(UIntProperty, false);
    return bIsPropertyValid ? Property->GetPropertyValue_InContainer(ObjectValue, ArrayIndex) : 0;
}

void FReflectedObject::SetInt32Property(FName PropertyName, int32 Value, int32 ArrayIndex) const {
    GET_PROPERTY(UIntProperty, true);
    if (bIsPropertyValid) {
        Property->SetPropertyValue_InContainer(ObjectValue, Value, ArrayIndex);
    }
}

int64 FReflectedObject::GetInt64Property(FName PropertyName, int32 ArrayIndex) const {
    GET_PROPERTY(UInt64Property, false);
    return bIsPropertyValid ? Property->GetPropertyValue_InContainer(ObjectValue, ArrayIndex) : 0;
}

void FReflectedObject::SetInt64Property(FName PropertyName, int64 Value, int32 ArrayIndex) const {
    GET_PROPERTY(UInt64Property, true);
    if (bIsPropertyValid) {
        Property->SetPropertyValue_InContainer(ObjectValue, Value, ArrayIndex);
    }
}

float FReflectedObject::GetFloatProperty(FName PropertyName, int32 ArrayIndex) const {
    GET_PROPERTY(UFloatProperty, false);
    return bIsPropertyValid ? Property->GetPropertyValue_InContainer(ObjectValue, ArrayIndex) : 0.0f;
}

void FReflectedObject::SetFloatProperty(FName PropertyName, float Value, int32 ArrayIndex) const {
    GET_PROPERTY(UFloatProperty, true);
    if (bIsPropertyValid) {
        Property->SetPropertyValue_InContainer(ObjectValue, Value, ArrayIndex);
    }
}

FString FReflectedObject::GetStringProperty(FName PropertyName, int32 ArrayIndex) const {
    GET_PROPERTY(UStrProperty, false);
    return bIsPropertyValid ? Property->GetPropertyValue_InContainer(ObjectValue, ArrayIndex) : TEXT("");
}

void FReflectedObject::SetStringProperty(FName PropertyName, const FString& Value, int32 ArrayIndex) const {
    GET_PROPERTY(UStrProperty, true);
    if (bIsPropertyValid) {
        Property->SetPropertyValue_InContainer(ObjectValue, Value, ArrayIndex);
    }
}

bool FReflectedObject::GetBoolProperty(FName PropertyName, int32 ArrayIndex) const {
    GET_PROPERTY(UBoolProperty, false);
    return bIsPropertyValid ? Property->GetPropertyValue_InContainer(ObjectValue, ArrayIndex) : false;
}

void FReflectedObject::SetBoolProperty(FName PropertyName, bool Value, int32 ArrayIndex) const {
    GET_PROPERTY(UBoolProperty, true);
    if (bIsPropertyValid) {
        Property->SetPropertyValue_InContainer(ObjectValue, Value, ArrayIndex);
    }
}

FName FReflectedObject::GetNameProperty(FName PropertyName, int32 ArrayIndex) const {
    GET_PROPERTY(UNameProperty, false);
    return bIsPropertyValid ? Property->GetPropertyValue_InContainer(ObjectValue, ArrayIndex) : NAME_None;
}

void FReflectedObject::SetNameProperty(FName PropertyName, const FName& Name, int32 ArrayIndex) const {
    GET_PROPERTY(UNameProperty, true);
    if (bIsPropertyValid) {
        Property->SetPropertyValue_InContainer(ObjectValue, Name, ArrayIndex);
    }
}

FText FReflectedObject::GetTextProperty(FName PropertyName, int32 ArrayIndex) const {
    GET_PROPERTY(UTextProperty, false);
    return bIsPropertyValid ? Property->GetPropertyValue_InContainer(ObjectValue, ArrayIndex) : FText::FromString(TEXT(""));
}

void FReflectedObject::SetTextProperty(FName PropertyName, const FText& Text, int32 ArrayIndex) const {
    GET_PROPERTY(UTextProperty, true);
    if (bIsPropertyValid) {
        Property->SetPropertyValue_InContainer(ObjectValue, Text, ArrayIndex);
    }
}

UObject* FReflectedObject::GetObjectProperty(FName PropertyName, int32 ArrayIndex) const {
    GET_PROPERTY(UObjectPropertyBase, false);
    return bIsPropertyValid ? Property->GetObjectPropertyValue_InContainer(ObjectValue, ArrayIndex) : NULL;
}

void FReflectedObject::SetObjectProperty(FName PropertyName, UObject* Object, int32 ArrayIndex) const {
    GET_PROPERTY(UObjectPropertyBase, true);
    if (bIsPropertyValid) {
        Property->SetObjectPropertyValue_InContainer(ObjectValue, Object, ArrayIndex);
    }
}

FReflectedObject FReflectedObject::GetStructProperty(FName PropertyName, int32 ArrayIndex) const {
    UStructProperty* Property = Cast<UStructProperty>(FindProperty(PropertyName, false));
    const void* ObjectValue = GetObjectData();
    FReflectedObject ReflectedObject{};
    
    if (Property != NULL && ObjectValue != NULL && IsValidIndex(ArrayIndex, Property->ArrayDim)) {
        UScriptStruct* ScriptStruct = Property->Struct;
        const void* StructValue = Property->ContainerPtrToValuePtr<void>(ObjectValue, ArrayIndex);
        ReflectedObject.SetupFromStruct(ScriptStruct, StructValue);
    }
    return ReflectedObject;
}

void FReflectedObject::SetStructProperty(FName PropertyName, const FReflectedObject& Struct, int32 ArrayIndex) const {
    UStructProperty* Property = Cast<UStructProperty>(FindProperty(PropertyName, true));
    void* ObjectValue = GetObjectData();

    if (Property != NULL && ObjectValue != NULL && IsValidIndex(ArrayIndex, Property->ArrayDim)) {
        UScriptStruct* ScriptStruct = Property->Struct;
        void* StructValue = Property->ContainerPtrToValuePtr<void>(ObjectValue, ArrayIndex);
        if (ScriptStruct == Struct.GetStruct()) {
            ScriptStruct->CopyScriptStruct(StructValue, Struct.GetObjectData());
        }
    }
}

FReflectedEnumValue FReflectedObject::GetEnumProperty(FName PropertyName) const {
    UProperty* Property = FindProperty(PropertyName, false);
    const void* ObjectValue = GetObjectData();

    if (Property != NULL && ObjectValue != NULL) {
        if (UEnumProperty* EnumProperty = Cast<UEnumProperty>(Property)) {
            const void* PropertyValue = Property->ContainerPtrToValuePtr<void>(ObjectValue);
            const int64 RawPropertyValue = EnumProperty->GetUnderlyingProperty()->GetSignedIntPropertyValue(PropertyValue);
            return FReflectedEnumValue{EnumProperty->GetEnum(), RawPropertyValue};
        }

        if (UByteProperty* ByteProperty = Cast<UByteProperty>(Property)) {
            if (ByteProperty->IsEnum()) {
                const int64 RawPropertyValue = ByteProperty->GetPropertyValue_InContainer(ObjectValue);
                return FReflectedEnumValue{ByteProperty->Enum, RawPropertyValue};
            }
        }
    }
    return FReflectedEnumValue{NULL, 0};
}

void FReflectedObject::SetEnumProperty(FName PropertyName, const FReflectedEnumValue& Enum) const {
    UProperty* Property = FindProperty(PropertyName, true);
    void* ObjectValue = GetObjectData();

    if (Property != NULL && ObjectValue != NULL) {
        if (UEnumProperty* EnumProperty = Cast<UEnumProperty>(Property)) {
            if (EnumProperty->GetEnum() == Enum.GetEnumerationType()) {
                void* PropertyValue = Property->ContainerPtrToValuePtr<void>(ObjectValue);
                EnumProperty->GetUnderlyingProperty()->SetIntPropertyValue(PropertyValue, Enum.GetCurrentValue());
            }
        }

        if (UByteProperty* ByteProperty = Cast<UByteProperty>(Property)) {
            if (ByteProperty->IsEnum() && ByteProperty->Enum == Enum.GetEnumerationType()) {
                ByteProperty->SetPropertyValue_InContainer(ObjectValue, (uint8) Enum.GetCurrentValue());
            }
        }
    }
}

void FReflectedObject::AddStructReferencedObjects(FReferenceCollector& Collector) const {
    if (State.IsValid()) {
        State->AddReferencedObjects(Collector);
    }
}

bool ComparePropertyNames(FName Name, FName Pattern, bool bStripName) {
    return bStripName ? (Name.ToString().StartsWith(Pattern.ToString())) : (Name == Pattern);
}

bool CheckPropertyFlags(UProperty* Property, bool bCheckForWriteable) {
    return Property->HasAnyPropertyFlags(CPF_BlueprintVisible) &&
        (!bCheckForWriteable || !Property->HasAnyPropertyFlags(CPF_BlueprintReadOnly));
}

UProperty* FReflectedObject::FindProperty(FName PropertyName, bool bCheckForWriteable) const {
    UStruct* StructObject = GetStruct();
    const bool bShouldStripNames = ShouldStripNames();
    if (StructObject != NULL) {
        for(UProperty* Property = StructObject->PropertyLink; Property; Property = Property->PropertyLinkNext) {
            const FName OtherPropertyName = Property->GetFName();
            if (CheckPropertyFlags(Property, bCheckForWriteable) &&
                ComparePropertyNames(OtherPropertyName, PropertyName, bShouldStripNames)) {
                return Property;
            }
        }
    }
    return NULL;
}

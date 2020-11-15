#include "UObjectHierarchySerializer.h"
#include "Package.h"
#include "Engine/Texture2D.h"
#include "UPropertySerializer.h"

DECLARE_LOG_CATEGORY_CLASS(LogObjectHierarchySerializer, Warning, Log);

//Serialize any properties that are not marked as Transient
bool UObjectHierarchySerializer::ShouldSerializeProperty(UProperty* Property) {
    return !Property->HasAnyPropertyFlags(CPF_Transient);
}

void UObjectHierarchySerializer::Initialize(UPackage* SourcePackage, UObject* Serializer) {
    check(SourcePackage);
    this->SourcePackage = SourcePackage;
    UPropertySerializer* PropertySerializer = Cast<UPropertySerializer>(Serializer);
    check(PropertySerializer);
    this->PropertySerializer = PropertySerializer;
    PropertySerializer->ObjectHierarchySerializer = this;
}

int32 UObjectHierarchySerializer::SerializeObject(UObject* Object) {
    if (Object == nullptr) {
        return INDEX_NONE;
    }
    const int32* ObjectIndex = ObjectIndices.Find(Object);
    if (ObjectIndex != nullptr) {
        return *ObjectIndex;
    }
    const int32 NewObjectIndex = LastObjectIndex++;
    ObjectIndices.Add(Object, NewObjectIndex);
    UPackage* ObjectPackage = Object->GetOutermost();
    TSharedRef<FJsonObject> ResultJson = MakeShareable(new FJsonObject());
    if (ObjectPackage != SourcePackage) {
        ResultJson->SetStringField(TEXT("Type"), TEXT("Import"));
        //Object is imported from different package
        UClass* ObjectClass = Object->GetClass();
        ResultJson->SetStringField(TEXT("ClassPackage"), ObjectClass->GetOutermost()->GetName());
        ResultJson->SetStringField(TEXT("ClassName"), ObjectClass->GetName());
        UObject* OuterObject = Object->GetOuter();
        //Outer object can be null if import is the top UPackage object
        if (OuterObject != nullptr) {
            const int32 OuterObjectIndex = SerializeObject(OuterObject);
            ResultJson->SetNumberField(TEXT("Outer"), OuterObjectIndex);
        }
        ResultJson->SetStringField(TEXT("ObjectName"), Object->GetName());
        
    } else {
        ResultJson->SetStringField(TEXT("Type"), TEXT("Export"));
        //Object is located inside our own package, so we need to serialize it properly
        UClass* ObjectClass = Object->GetClass();
        ResultJson->SetNumberField(TEXT("ObjectClass"), SerializeObject(ObjectClass));
        UObject* OuterObject = Object->GetOuter();
        //Outer object can be null if this is a top level package export, e.g Object == SourcePackage itself
        if (OuterObject != nullptr) {
            const int32 OuterObjectIndex = SerializeObject(OuterObject);
            ResultJson->SetNumberField(TEXT("Outer"), OuterObjectIndex);
            ResultJson->SetStringField(TEXT("ObjectName"), Object->GetName());
        }
        //Serialize SuperStruct for UStruct objects
        if (UStruct* Struct = Cast<UStruct>(Object)) {
            UStruct* SuperStruct = Struct->GetSuperStruct();
            if (SuperStruct != nullptr) {
                const int32 SuperStructObjectIndex = SerializeObject(SuperStruct);
                ResultJson->SetNumberField(TEXT("SuperStruct"), SuperStructObjectIndex);
            }
        }
        //Serialize object flags that match RF_Load specification
        ResultJson->SetNumberField(TEXT("ObjectFlags"), (int32) (Object->GetFlags() & RF_Load));
        
        //Serialize UProperties for this object, but skip UClass since it is natively serialized
        if (ObjectClass != UClass::StaticClass()) {
            const TSharedRef<FJsonObject> Properties = SerializeObjectProperties(Object);
            ResultJson->SetObjectField(TEXT("Properties"), Properties);
        }
    }
    SerializedObjects.Add(NewObjectIndex, ResultJson);
    return NewObjectIndex;
}

UObject* UObjectHierarchySerializer::DeserializeObject(int32 Index) {
    if (Index == INDEX_NONE) {
        return nullptr;
    }
    UObject** LoadedObject = LoadedObjects.Find(Index);
    if (LoadedObject != nullptr) {
        return *LoadedObject;
    }
    if (!SerializedObjects.Contains(Index)) {
        UE_LOG(LogObjectHierarchySerializer, Error, TEXT("DeserializeObject for package %s called with invalid Index: %d"), *SourcePackage->GetName(), Index);
        return nullptr;
    }
    const TSharedPtr<FJsonObject>& ObjectJson = SerializedObjects.FindChecked(Index);
    const FString ObjectType = ObjectJson->GetStringField(TEXT("Type"));
    
    if (ObjectType == TEXT("Import")) {
        //Object is imported from another package, and not located in our own
        const FString PackageName = ObjectJson->GetStringField(TEXT("ClassPackage"));
        const FString ClassName = ObjectJson->GetStringField(TEXT("ClassName"));
        if (UPackage* Package = LoadPackage(NULL, *PackageName, LOAD_None)) {
            if (UClass* ObjectClass = FindObjectFast<UClass>(Package, *ClassName)) {
                const FString ObjectName = ObjectJson->GetStringField(TEXT("ObjectName"));
                //Outer is absent for root UPackage imports - Use ObjectName with LoadPackage directly
                if (!ObjectJson->HasField(TEXT("Outer"))) {
                    check(ObjectClass == UPackage::StaticClass());
                    UPackage* ResultPackage = LoadPackage(NULL, *ObjectName, LOAD_None);
                    if (ResultPackage == nullptr) {
                        UE_LOG(LogObjectHierarchySerializer, Error, TEXT("DeserializeObject for package %s failed: Cannot resolve package %s"), *SourcePackage->GetName(), *ObjectName);
                    }
                    return ResultPackage;
                }
                //Otherwise, it is a normal object inside some outer
                const int32 OuterObjectIndex = ObjectJson->GetIntegerField(TEXT("Outer"));
                UObject* OuterObject = DeserializeObject(OuterObjectIndex);
                if (OuterObject == nullptr) {
                    UE_LOG(LogObjectHierarchySerializer, Error, TEXT("DeserializeObject for package %s failed: Cannot resolve outer object %d"), *SourcePackage->GetName(), OuterObjectIndex);
                    return nullptr;
                }
                //Use FindObjectFast now to resolve our object inside Outer
                UObject* ResultObject = StaticFindObjectFast(ObjectClass, OuterObject, *ObjectName);
                if (ResultObject == nullptr) {
                    UE_LOG(LogObjectHierarchySerializer, Error, TEXT("DeserializeObject for package %s failed: Cannot find object %s inside outer %s"), *SourcePackage->GetName(), *OuterObject->GetPathName(), *ObjectName);
                    return nullptr;
                }
                LoadedObjects.Add(Index, ResultObject);
                return ResultObject;
            }
        }
        //We are here if LoadPackage/FindObjectFast for class are failed
        UE_LOG(LogObjectHierarchySerializer, Error, TEXT("DeserializeObject for package %s failed: Cannot resolve object class %s.%s"), *SourcePackage->GetName(), *PackageName, *ClassName);
        return nullptr;
    }

    if (ObjectType == TEXT("Export")) {
        //Object is defined inside our own package, so we should have
        const int32 ObjectClassIndex = ObjectJson->GetIntegerField(TEXT("ObjectClass"));
        UClass* ObjectClass = Cast<UClass>(DeserializeObject(ObjectClassIndex));
        if (ObjectClass == nullptr) {
            UE_LOG(LogObjectHierarchySerializer, Error, TEXT("DeserializeObject for package %s failed: Cannot resolve object class %d"), *SourcePackage->GetName(), ObjectClassIndex);
            return nullptr;
        }
        //Outer will be missing for root UPackage export, e.g SourcePackage
        if (!ObjectJson->HasField(TEXT("Outer"))) {
            check(ObjectClass == UPackage::StaticClass());
            return SourcePackage;
        }
        const int32 OuterObjectIndex = ObjectJson->GetIntegerField(TEXT("Outer"));
        UObject* OuterObject = DeserializeObject(OuterObjectIndex);
        if (OuterObject == nullptr) {
            UE_LOG(LogObjectHierarchySerializer, Error, TEXT("DeserializeObject for package %s failed: Cannot resolve outer object %d"), *SourcePackage->GetName(), OuterObjectIndex);
            return nullptr;
        }
     
        const EObjectFlags ObjectLoadFlags = (EObjectFlags) ObjectJson->GetIntegerField(TEXT("ObjectFlags"));
        const FString ObjectName = ObjectJson->GetStringField(TEXT("ObjectName"));
        UObject* Template = UObject::GetArchetypeFromRequiredInfo(ObjectClass, OuterObject, *ObjectName, ObjectLoadFlags);
        //Construct our final object now
        UObject* ConstructedObject = StaticConstructObject_Internal(
            ObjectClass, OuterObject, *ObjectName, ObjectLoadFlags, EInternalObjectFlags::None, Template);
        //Set SuperStruct reference if it is a UStruct object
        if (UStruct* Struct = Cast<UStruct>(ConstructedObject)) {
            const int32 SuperStructObjectIndex = ObjectJson->GetIntegerField(TEXT("SuperStruct"));
            UStruct* SuperStruct = Cast<UStruct>(DeserializeObject(SuperStructObjectIndex));
            check(SuperStruct);
            Struct->SetSuperStruct(SuperStruct);
        }
        //If we just have created UClass object, bind it to C++
        if (UClass* Class = Cast<UClass>(ConstructedObject)) {
            Class->Bind();
        }
        //Deserialize object properties now
        if (ObjectJson->HasField(TEXT("Properties"))) {
            const TSharedPtr<FJsonObject>& Properties = ObjectJson->GetObjectField(TEXT("Properties"));
            if (Properties.IsValid()) {
                DeserializeObjectProperties(Properties.ToSharedRef(), ConstructedObject);
            }
        }
        LoadedObjects.Add(Index, ConstructedObject);
        return ConstructedObject;
    }
    UE_LOG(LogObjectHierarchySerializer, Fatal, TEXT("Unhandled object type: %s for package %s"), *ObjectType, *SourcePackage->GetPathName());
    return nullptr;
}

TSharedRef<FJsonObject> UObjectHierarchySerializer::SerializeObjectProperties(UObject* Object) {
    UClass* ObjectClass = Object->GetClass();
    TSharedRef<FJsonObject> Properties = MakeShareable(new FJsonObject());
    for (UProperty* Property = ObjectClass->PropertyLink; Property; Property = Property->PropertyLinkNext) {
        if (ShouldSerializeProperty(Property)) {
            const void* PropertyValue = Property->ContainerPtrToValuePtr<void>(Object);
            TSharedRef<FJsonValue> PropertyValueJson = Cast<UPropertySerializer>(PropertySerializer)->SerializePropertyValue(Property, PropertyValue);
            Properties->SetField(Property->GetName(), PropertyValueJson);
        }
    }
    return Properties;
}

void UObjectHierarchySerializer::DeserializeObjectProperties(const TSharedRef<FJsonObject>& Properties, UObject* Object) {
    UClass* ObjectClass = Object->GetClass();
    for (UProperty* Property = ObjectClass->PropertyLink; Property; Property = Property->PropertyLinkNext) {
        const FString PropertyName = Property->GetName();
        if (ShouldSerializeProperty(Property) && Properties->HasField(PropertyName)) {
            void* PropertyValue = Property->ContainerPtrToValuePtr<void>(Object);
            const TSharedPtr<FJsonValue>& ValueObject = Properties->Values.FindChecked(PropertyName);
            if (ValueObject.IsValid()) {
                Cast<UPropertySerializer>(PropertySerializer)->DeserializePropertyValue(Property, ValueObject.ToSharedRef(), PropertyValue);
            }
        }
    }
}

void UObjectHierarchySerializer::InitializeForDeserialization(const TArray<TSharedPtr<FJsonObject>>& ObjectsArray) {
    this->LastObjectIndex = ObjectsArray.Num();
    for (int32 i = 0; i < LastObjectIndex; i++) {
        SerializedObjects.Add(i, ObjectsArray[i]);
    }
}

TArray<TSharedPtr<FJsonObject>> UObjectHierarchySerializer::FinalizeSerialization() {
    TArray<TSharedPtr<FJsonObject>> ObjectsArray;
    for (int32 i = 0; i < LastObjectIndex; i++) {
        ObjectsArray.Add(SerializedObjects.FindChecked(i));
    }
    return ObjectsArray;
}



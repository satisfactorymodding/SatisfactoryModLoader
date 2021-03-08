#include "Toolkit/AssetTypes/BlueprintAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/KismetBytecodeDisassemblerJson.h"
#include "UObject/Package.h"
#include "Toolkit/PropertySerializer.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/DynamicBlueprintBinding.h"
#include "Engine/InheritableComponentHandler.h"
#include "Engine/SCS_Node.h"
#include "GameFramework/Actor.h"
#include "Engine/TimelineTemplate.h"

void UBlueprintAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);

    //Make sure we contain adequate amount of root objects
    CheckRootObjectSet(AssetPackage, RootPackageObjects);
    
    //Retrieve blueprint generated class instance
    UBlueprintGeneratedClass* BlueprintClass;
    check(RootPackageObjects.FindItemByClass<UBlueprintGeneratedClass>(&BlueprintClass));
    UObject* ClassDefaultObject = BlueprintClass->GetDefaultObject();

    //Make sure root object set contains class default object
    check(RootPackageObjects.Contains(ClassDefaultObject));

    //Serialize blueprint class reference through a simple mark
    //It will be updated accordingly by deserialization first using dummy object, and then actual class for CDO deserialization
    ObjectHierarchySerializer->SetObjectMark(BlueprintClass, TEXT("BlueprintGeneratedClass"));
    
    //Serialize blueprint class first
    const TSharedPtr<FJsonObject> BlueprintClassJson = MakeShareable(new FJsonObject());
    SerializeClassInternal(BlueprintClassJson, BlueprintClass, ObjectHierarchySerializer);
    OutObject->SetObjectField(TEXT("BlueprintClass"), BlueprintClassJson);
    
    //Serialize class default object (to be fair, it will be serialized already at this point anyway)
    const int32 ClassDefaultObjectIndex = ObjectHierarchySerializer->SerializeObject(ClassDefaultObject);
    OutObject->SetNumberField(TEXT("ClassDefaultObject"), ClassDefaultObjectIndex);
}

void UBlueprintAssetSerializer::CheckRootObjectSet(UPackage* AssetPackage, const TArray<UObject*>& RootPackageObjects) const {
    //Blueprint asset packages (usually) contain 2 assets only: generated class and CDO
    //Need to check it to avoid missing any extra objects in packages during serialization
    check(RootPackageObjects.Num() == 2);
}

void UBlueprintAssetSerializer::SerializeClassInternal(TSharedPtr<FJsonObject> OutObject, UBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer) const {
    //Make sure we are serializing UBlueprintGeneratedClass and not something like UWidgetGeneratedClass
    //because widget class extends blueprint generated class, Cast and IsA checks will actually allow it to reach this point
    //since we cannot really handle widget serialization there (and, in fact, widgets are separate asset category),
    //just make sure it never actually happens
    //Child classes will override this to do special handling of their subclasses
    check(Class->GetClass() == UBlueprintGeneratedClass::StaticClass());
    
    SerializeBlueprintClass(OutObject, Class, ObjectHierarchySerializer);
}

void UBlueprintAssetSerializer::SerializeBlueprintClass(TSharedPtr<FJsonObject> OutObject, UBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer) {

    //Serialize parent UClass object first
    FAssetHelper::SerializeClass(OutObject, Class, ObjectHierarchySerializer);
    
    //Serialize dynamic binding objects
    TArray<TSharedPtr<FJsonValue>> DynamicBindingObjects;
    for (UDynamicBlueprintBinding* Binding : Class->DynamicBindingObjects) {
        const int32 ObjectIndex = ObjectHierarchySerializer->SerializeObject(Binding);
        DynamicBindingObjects.Add(MakeShareable(new FJsonValueNumber(ObjectIndex)));
    }
    OutObject->SetArrayField(TEXT("DynamicBindingObjects"), DynamicBindingObjects);

    //Serialize components templates (used by AddComponent kismet node)
    TArray<TSharedPtr<FJsonValue>> ComponentTemplates;
    for (UActorComponent* ActorComponent : Class->ComponentTemplates) {
        const int32 ObjectIndex = ObjectHierarchySerializer->SerializeObject(ActorComponent);
        ComponentTemplates.Add(MakeShareable(new FJsonValueNumber(ObjectIndex)));
    }
    OutObject->SetArrayField(TEXT("ComponentTemplates"), ComponentTemplates);

    //Serialize timeline templates (used by Timeline kismet nodes)
    TArray<TSharedPtr<FJsonValue>> Timelines;
    for (UTimelineTemplate* TimelineTemplate : Class->Timelines) {
        const int32 ObjectIndex = ObjectHierarchySerializer->SerializeObject(TimelineTemplate);
        Timelines.Add(MakeShareable(new FJsonValueNumber(ObjectIndex)));
    }
    OutObject->SetArrayField(TEXT("Timelines"), Timelines);

    //Avoid serializing cooked instancing data as it is only used in cooked build for optimization purposes
    UPropertySerializer* PropertySerializer = ObjectHierarchySerializer->GetPropertySerializer<UPropertySerializer>();
    PropertySerializer->DisablePropertySerialization(USCS_Node::StaticClass(), TEXT("CookedComponentInstancingData"));
    PropertySerializer->DisablePropertySerialization(FComponentOverrideRecord::StaticStruct(), TEXT("CookedComponentInstancingData"));

    //Serialize Simple Construct script entirely without any changes
    const int32 SimpleConstructionScriptIndex = ObjectHierarchySerializer->SerializeObject(Class->SimpleConstructionScript);
    OutObject->SetNumberField(TEXT("SimpleConstructionScript"), SimpleConstructionScriptIndex);

    //Serialize Inheritance component handler
    const int32 InheritanceComponentHandlerIndex = ObjectHierarchySerializer->SerializeObject(Class->InheritableComponentHandler);
    OutObject->SetNumberField(TEXT("InheritableComponentHandler"), InheritanceComponentHandlerIndex);
    
    //Serialize ubergraph function name and property name to aid blueprint decompilation
    if (Class->UberGraphFunction && Class->UberGraphFramePointerProperty) {
        OutObject->SetStringField(TEXT("UberGraphFunction"), Class->UberGraphFunction->GetName());
        OutObject->SetStringField(TEXT("UberGraphFramePointerProperty"), Class->UberGraphFramePointerProperty->GetName());
    }
}

EAssetCategory UBlueprintAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_Blueprint;
}

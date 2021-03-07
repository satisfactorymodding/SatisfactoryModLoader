#include "Toolkit/AssetTypes/UserWidgetAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Toolkit/AssetTypes/BlueprintAssetSerializer.h"
#include "Blueprint/WidgetTree.h"

void UUserWidgetAssetSerializer::SerializeClassInternal(TSharedPtr<FJsonObject> OutObject, UBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer) const {
    //Make sure we are serialized this exact generated class type and not some child
    check(Class->GetClass() == UWidgetBlueprintGeneratedClass::StaticClass());
    
    SerializeWidgetBlueprintClass(OutObject, CastChecked<UWidgetBlueprintGeneratedClass>(Class), ObjectHierarchySerializer);
}

void UUserWidgetAssetSerializer::SerializeWidgetBlueprintClass(TSharedPtr<FJsonObject> OutObject, UWidgetBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer) {
    //Serialize blueprint class
    SerializeBlueprintClass(OutObject, Class, ObjectHierarchySerializer);

    //Serialize WidgetTree object hierarchy
    //It will reference other widgets and their widget trees as outers, too
    const int32 WidgetTreeObjectIndex = ObjectHierarchySerializer->SerializeObject(Class->WidgetTree);
    OutObject->SetNumberField(TEXT("WidgetTree"), WidgetTreeObjectIndex);

    //Serialize runtime delegate bindings
    TArray<TSharedPtr<FJsonValue>> RuntimeDelegateBindings;
    for (const FDelegateRuntimeBinding& Binding : Class->Bindings) {
        TSharedPtr<FJsonObject> DelegateBinding = MakeShareable(new FJsonObject());
        DelegateBinding->SetStringField(TEXT("ObjectName"), Binding.ObjectName);
        DelegateBinding->SetStringField(TEXT("FunctionName"), Binding.FunctionName.ToString());
        DelegateBinding->SetStringField(TEXT("PropertyName"), Binding.PropertyName.ToString());
        DelegateBinding->SetStringField(TEXT("SourcePath"), FAssetHelper::PropertyPathToString(Binding.SourcePath));
        DelegateBinding->SetStringField(TEXT("Kind"), Binding.Kind == EBindingKind::Function ? TEXT("Function") : TEXT("Property"));
        RuntimeDelegateBindings.Add(MakeShareable(new FJsonValueObject(DelegateBinding)));
    }
    OutObject->SetArrayField(TEXT("Bindings"), RuntimeDelegateBindings);

    //Serialize widget animations
    TArray<TSharedPtr<FJsonValue>> WidgetAnimations;
    for (UWidgetAnimation* WidgetAnimation : Class->Animations) {
        const int32 AnimationIndex = ObjectHierarchySerializer->SerializeObject(WidgetAnimation);
        WidgetAnimations.Add(MakeShareable(new FJsonValueNumber(AnimationIndex)));
    }
    OutObject->SetArrayField(TEXT("Animations"), WidgetAnimations);

    //Do not serialize NamedSlots because they can be regenerated
    //By parsing UWidgetTree serialized

    //Serialize native tick requirement
    OutObject->SetBoolField(TEXT("ClassRequiresNativeTick"), Class->ClassRequiresNativeTick());
}

EAssetCategory UUserWidgetAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_UserWidget;
}

void UUserWidgetAssetSerializer::CheckRootObjectSet(UPackage* AssetPackage, const TArray<UObject*>& RootPackageObjects) const {
    //UserWidget blueprints contain one additional root object
    //Initialized template widget, which is used for fast construction or widget tree
    UWidgetBlueprintGeneratedClass* GeneratedClass;
    check(RootPackageObjects.FindItemByClass<UWidgetBlueprintGeneratedClass>(&GeneratedClass));
    check(RootPackageObjects.Contains(GeneratedClass->GetDefaultObject()));

    //Make sure we either contain template archetype or 2 objects only
    check(RootPackageObjects.Num() == 2 || (RootPackageObjects.Num() == 3 && RootPackageObjects.Contains(GeneratedClass->GetTemplate())));
}

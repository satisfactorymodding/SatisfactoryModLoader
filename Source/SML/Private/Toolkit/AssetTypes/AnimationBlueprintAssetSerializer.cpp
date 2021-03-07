#include "Toolkit/AssetTypes/AnimationBlueprintAssetSerializer.h"
#include "Toolkit/PropertySerializer.h"
#include "Animation/AnimBlueprintGeneratedClass.h"

void UAnimationBlueprintAssetSerializer::SerializeAnimBlueprintClass(TSharedPtr<FJsonObject> OutObject, UAnimBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer) {
    //Serialize normal blueprint class
    SerializeBlueprintClass(OutObject, Class, ObjectHierarchySerializer);

    UPropertySerializer* PropertySerializer = ObjectHierarchySerializer->GetPropertySerializer<UPropertySerializer>();

    //Serialize baked state machines without any changes, they don't reference any
    //unserializable stuff outside of some custom curve assets and blend profiles
    TArray<TSharedPtr<FJsonValue>> BakedStateMachines;
    for (const FBakedAnimationStateMachine& AnimationStateMachine : Class->BakedStateMachines) {
        TSharedRef<FJsonObject> MachineObject = PropertySerializer->SerializeStruct(FBakedAnimationStateMachine::StaticStruct(), &AnimationStateMachine);
        BakedStateMachines.Add(MakeShareable(new FJsonValueObject(MachineObject)));
    }
    OutObject->SetArrayField(TEXT("BakedStateMachines"), BakedStateMachines);

    //Target skeleton is just an external asset reference
    const int32 TargetSkeletonObjectIndex = ObjectHierarchySerializer->SerializeObject(Class->TargetSkeleton);
    OutObject->SetNumberField(TEXT("TargetSkeleton"), TargetSkeletonObjectIndex);

    //Serialize anim notifies. They can reference external assets such as movie scenes,
    //but overall there shouldn't be any not serializable stuff too
    TArray<TSharedPtr<FJsonValue>> AnimNotifies;
    for (const FAnimNotifyEvent& AnimNotifyEvent : Class->AnimNotifies) {
        TSharedRef<FJsonObject> NotifyEventObject = PropertySerializer->SerializeStruct(FAnimNotifyEvent::StaticStruct(), &AnimNotifyEvent);
        AnimNotifies.Add(MakeShareable(new FJsonValueObject(NotifyEventObject)));
    }
    OutObject->SetArrayField(TEXT("AnimNotifies"), AnimNotifies);

    //Serialize save pose indices (array of indices of SavePose animation nodes)
    //Technically they can be easily reversed by class struct property traversal, but save them to help blueprint decompilation
    TSharedPtr<FJsonObject> OrderedSavedPoseIndicesByLayer;
    for (const TPair<FName, FCachedPoseIndices>& Pair : Class->OrderedSavedPoseIndicesMap) {
        TArray<TSharedPtr<FJsonValue>> OrderedSavedPoseIndices;
        for (int32 SavedPoseIndex : Pair.Value.OrderedSavedPoseNodeIndices) {
            OrderedSavedPoseIndices.Add(MakeShareable(new FJsonValueNumber(SavedPoseIndex)));
        }
        OrderedSavedPoseIndicesByLayer->SetArrayField(Pair.Key.ToString(), OrderedSavedPoseIndices);
    }
    OutObject->SetObjectField(TEXT("OrderedSavedPoseIndicesMap"), OrderedSavedPoseIndicesByLayer);

    //Serialize declared blueprint animation functions
    TArray<TSharedPtr<FJsonValue>> AnimBlueprintFunctions;
    for (const FAnimBlueprintFunction& BlueprintFunction : Class->AnimBlueprintFunctions) {
        const TSharedPtr<FJsonObject> OutStruct = PropertySerializer->SerializeStruct(FAnimBlueprintFunction::StaticStruct(), &BlueprintFunction);
        AnimBlueprintFunctions.Add(MakeShareable(new FJsonValueObject(OutStruct)));
    }
    OutObject->SetArrayField(TEXT("AnimBlueprintFunctions"), AnimBlueprintFunctions);

    //Serialize GraphAssetPlayerInformation
    TSharedPtr<FJsonObject> GraphAssetPlayerInformation;
    for (const TPair<FName, FGraphAssetPlayerInformation>& Pair : Class->GraphAssetPlayerInformation) {
        TArray<TSharedPtr<FJsonValue>> PlayerNodeIndices;
        for (int32 SavedPoseIndex : Pair.Value.PlayerNodeIndices) {
            PlayerNodeIndices.Add(MakeShareable(new FJsonValueNumber(SavedPoseIndex)));
        }
        GraphAssetPlayerInformation->SetArrayField(Pair.Key.ToString(), PlayerNodeIndices);
    }
    OutObject->SetObjectField(TEXT("GraphAssetPlayerInformation"), GraphAssetPlayerInformation);

    //Serialize GraphBlendOptions
    TSharedPtr<FJsonObject> GraphBlendOptions;
    for (const TPair<FName, FAnimGraphBlendOptions>& Pair : Class->GraphBlendOptions) {
        const TSharedPtr<FJsonObject> OptionObject = MakeShareable(new FJsonObject());
        OptionObject->SetNumberField("BlendInTime", Pair.Value.BlendInTime);
        OptionObject->SetNumberField("BlendOutTime", Pair.Value.BlendOutTime);
        GraphBlendOptions->SetObjectField(Pair.Key.ToString(), OptionObject);
    }
    OutObject->SetObjectField(TEXT("GraphBlendOptions"), GraphBlendOptions);
    
    //Serialize sync group names (just to aid with BP decompilation)
    TArray<TSharedPtr<FJsonValue>> SyncGroupNames;
    for (FName SyncGroup : Class->SyncGroupNames) {
        SyncGroupNames.Add(MakeShareable(new FJsonValueString(SyncGroup.ToString())));
    }
    OutObject->SetArrayField(TEXT("SyncGroupNames"), SyncGroupNames);

    //Disable serialization of Function object, it is just a fast path to BoundFunction property, which is also serialized
    PropertySerializer->DisablePropertySerialization(FExposedValueHandler::StaticStruct(), TEXT("Function"));

    //Now we can just perform normal serialization
    TArray<TSharedPtr<FJsonValue>> ExposedValueHandlers;
    for (const FExposedValueHandler& ExposedValueHandler : Class->EvaluateGraphExposedInputs) {
        TSharedRef<FJsonObject> SerializedStruct = PropertySerializer->SerializeStruct(FExposedValueHandler::StaticStruct(), &ExposedValueHandler);
        ExposedValueHandlers.Add(MakeShareable(new FJsonValueObject(SerializedStruct)));
    }
    OutObject->SetArrayField(TEXT("EvaluateGraphExposedInputs"), ExposedValueHandlers);
}

EAssetCategory UAnimationBlueprintAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_AnimationBlueprint;
}

void UAnimationBlueprintAssetSerializer::SerializeClassInternal(TSharedPtr<FJsonObject> OutObject, UBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer) const {
    //Make sure we are serialized this exact generated class type and not some child
    check(Class->GetClass() == UAnimBlueprintGeneratedClass::StaticClass());
    
    SerializeAnimBlueprintClass(OutObject, CastChecked<UAnimBlueprintGeneratedClass>(Class), ObjectHierarchySerializer);
}

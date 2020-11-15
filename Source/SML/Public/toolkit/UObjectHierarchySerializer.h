#pragma once
#include "Object.h"
#include "Json.h"
#include "UObjectHierarchySerializer.generated.h"

UCLASS()
class UObjectHierarchySerializer : public UObject {
    GENERATED_BODY()
private:
    UPROPERTY()
    UPackage* SourcePackage;
    UPROPERTY()
    TMap<UObject*, int32> ObjectIndices;
    UPROPERTY()
    TMap<int32, UObject*> LoadedObjects;
    int32 LastObjectIndex = 1;
    UPROPERTY()
    UObject* PropertySerializer;
    TMap<int32, TSharedPtr<FJsonObject>> SerializedObjects;
public:
    static bool ShouldSerializeProperty(UProperty* Property);
    TSharedRef<FJsonObject> SerializeObjectProperties(UObject* Object);
    void DeserializeObjectProperties(const TSharedRef<FJsonObject>& Properties, UObject* Object);
    
    void Initialize(UPackage* SourcePackage, UObject* Serializer);
    
    void InitializeForDeserialization(const TArray<TSharedPtr<FJsonObject>>& ObjectsArray);
    UObject* DeserializeObject(int32 Index);
    
    int32 SerializeObject(UObject* Object);
    TArray<TSharedPtr<FJsonObject>> FinalizeSerialization();
};

#pragma once
#include "JsonObject.h"
#include "Object.h"
#include "UObjectHierarchySerializer.h"

#include "UPropertySerializer.generated.h"

UCLASS()
class UPropertySerializer : public UObject {
    GENERATED_BODY()
private:
    friend class UObjectHierarchySerializer;
private:
    UPROPERTY()
    UObjectHierarchySerializer* ObjectHierarchySerializer;
public:
    TSharedRef<FJsonValue> SerializePropertyValue(UProperty* Property, const void* Value);
    TSharedRef<FJsonObject> SerializeStruct(UScriptStruct* Struct, const void* Value);
    
    void DeserializePropertyValue(UProperty* Property, const TSharedRef<FJsonValue>& Value, void* OutValue);
    void DeserializeStruct(UScriptStruct* Struct, const TSharedRef<FJsonObject>& Value, void* OutValue);
};

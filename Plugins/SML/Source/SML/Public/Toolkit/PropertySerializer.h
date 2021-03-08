#pragma once
#include "Dom/JsonObject.h"
#include "UObject/Object.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "PropertySerializer.generated.h"

UCLASS()
class SML_API UPropertySerializer : public UObject {
    GENERATED_BODY()
private:
    friend class UObjectHierarchySerializer;
private:
    using FPropertySerializer = TFunction<TSharedRef<FJsonValue>(UProperty* Property, const void* Value)>;
    using FPropertyDeserializer = TFunction<void(UProperty* Property, TSharedRef<FJsonValue> Value, void* OutValue)>;
    
    UPROPERTY()
    UObjectHierarchySerializer* ObjectHierarchySerializer;

    UPROPERTY()
    TArray<UProperty*> BlacklistedProperties;

    UPROPERTY()
    TArray<UProperty*> PropertiesWithCustomSerializers;
    
    TMap<UProperty*, FPropertySerializer> CustomPropertySerializers;
    TMap<UProperty*, FPropertyDeserializer> CustomPropertyDeserializers;
public:
    /** Disables property serialization entirely */
    void DisablePropertySerialization(UStruct* Struct, FName PropertyName);

    /** Sets up custom property serializer for provided property */
    void SetCustomSerializer(UStruct* Struct, FName PropertyName, FPropertySerializer Serializer);

    /** Sets up custom property deserializer for provided property */
    void SetCustomDeserializer(UStruct* Struct, FName PropertyName, FPropertyDeserializer Deserializer);

    /** Checks whenever we should serialize property in question at all */
    bool ShouldSerializeProperty(UProperty* Property) const;

    TSharedRef<FJsonValue> SerializePropertyByName(UObject* Object, FName PropertyName);
    TSharedRef<FJsonValue> SerializePropertyValue(UProperty* Property, const void* Value);
    TSharedRef<FJsonObject> SerializeStruct(UScriptStruct* Struct, const void* Value);
    
    void DeserializePropertyValue(UProperty* Property, const TSharedRef<FJsonValue>& Value, void* OutValue);
    void DeserializeStruct(UScriptStruct* Struct, const TSharedRef<FJsonObject>& Value, void* OutValue);
private:
    void DeserializePropertyValueInner(UProperty* Property, const TSharedRef<FJsonValue>& Value, void* OutValue);
    TSharedRef<FJsonValue> SerializePropertyValueInner(UProperty* Property, const void* Value);
};

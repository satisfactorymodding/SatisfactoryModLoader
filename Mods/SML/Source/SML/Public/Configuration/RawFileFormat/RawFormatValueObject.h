#pragma once
#include "Templates/SubclassOf.h"
#include "Configuration/ConfigProperty.h"
#include "Configuration/ConfigValueObjectInterface.h"
#include "Configuration/RawFileFormat/Json/JsonRawFormatConverter.h"
#include "Configuration/RawFileFormat/RawFormatValueArray.h"
#include "SatisfactoryModLoader.h"
#include "RawFormatValueObject.generated.h"

/** Describes raw map (also known as object) value */
UCLASS()
class SML_API URawFormatValueObject : public URawFormatValue {
    GENERATED_BODY()
public:
    /** Actual of raw map object */
    UPROPERTY(BlueprintReadWrite)
    TMap<FString, TObjectPtr<URawFormatValue>> Values;

    UFUNCTION(BlueprintPure)
    FORCEINLINE URawFormatValue* GetValue(const FString& Key) const {
        const TObjectPtr<URawFormatValue>* Value = Values.Find(Key);
        return Value ? *Value : NULL;
    }

    /** Retrieves value at the given key as array */
    UFUNCTION(BlueprintPure)
    FORCEINLINE URawFormatValueArray* GetArray(const FString& Key) const {
        return Cast<URawFormatValueArray>(GetValue(Key));
    }

    UFUNCTION(BlueprintCallable)
    FORCEINLINE URawFormatValueArray* SetArray(const FString& Key) {
        return AddNewValue<URawFormatValueArray>(Key);
    }

    /** Retrieves value at the given key as object */
    UFUNCTION(BlueprintPure)
    FORCEINLINE URawFormatValueObject* GetObject(const FString& Key) const {
        return Cast<URawFormatValueObject>(GetValue(Key));
    }

    UFUNCTION(BlueprintCallable)
    FORCEINLINE URawFormatValueObject* SetObject(const FString& Key) {
        return AddNewValue<URawFormatValueObject>(Key);
    }

    /** Retrieves value at the given key as string, falling back to empty string if it's not a string */
    UFUNCTION(BlueprintPure)
    FORCEINLINE FString GetString(const FString& Key) const {
        URawFormatValueString* StringValue = Cast<URawFormatValueString>(GetValue(Key));
        return StringValue ? StringValue->Value : TEXT("");
    }

    UFUNCTION(BlueprintCallable)
    void SetString(const FString& Key, const FString& Value);

    /** Retrieves value at the given key as integer, falling back to zero if it's not a number */
    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetInteger(const FString& Key) const {
        URawFormatValueNumber* NumberValue = Cast<URawFormatValueNumber>(GetValue(Key));
        return NumberValue ? NumberValue->AsInt() : 0;
    }

    UFUNCTION(BlueprintCallable)
    void SetInteger(const FString& Key, const int32 Value);

    /** Retrieves value at the given key as floating point number, falling back to zero if it's not a number */
    UFUNCTION(BlueprintPure)
    FORCEINLINE float GetFloat(const FString& Key) const {
        URawFormatValueNumber* NumberValue = Cast<URawFormatValueNumber>(GetValue(Key));
        return NumberValue ? NumberValue->AsFloat() : 0.0f;
    }

    UFUNCTION(BlueprintCallable)
    void SetFloat(const FString& Key, const float Value);

    /** Adds value into the object */
    UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ValueClass"))
    void AddValue(const FString& Key, URawFormatValue* ValueClass);

    /** Adds value into the map and returns pointer to it. Replaces value with duplicate key */
    UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ValueClass"))
    FORCEINLINE URawFormatValue* AddNewValue(const FString& Key, TSubclassOf<URawFormatValue> ValueClass) {
        URawFormatValue* NewValue = NewObject<URawFormatValue>(this, ValueClass);
        AddValue(Key, NewValue);
        return NewValue;
    }

    /** Template version of AddValue for C++ usage */
    template<typename T>
    FORCEINLINE T* AddNewValue(const FString& Key) {
        return Cast<T>(AddNewValue(Key, T::StaticClass()));
    }

    virtual TSharedPtr<FJsonValue> ToJson() const override;

    /** Creates a new URawFormatValueObject from the given JSON value */
    static URawFormatValueObject* FromJson(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue);
};

FORCEINLINE void URawFormatValueObject::SetString(const FString& Key, const FString& Value) {
    AddNewValue<URawFormatValueString>(Key)->Value = Value;
}

FORCEINLINE void URawFormatValueObject::SetInteger(const FString& Key, const int32 Value) {
    AddNewValue<URawFormatValueNumber>(Key)->SetValueInt(Value);
}

FORCEINLINE void URawFormatValueObject::SetFloat(const FString& Key, const float Value) {
    AddNewValue<URawFormatValueNumber>(Key)->SetValueFloat(Value);
}

FORCEINLINE void URawFormatValueObject::AddValue(const FString& Key, URawFormatValue* ValueClass) {
    //Sanity check to ensure hierarchical view inside this raw value
    checkf(ValueClass && ValueClass->GetOuter() == this, TEXT("Cannot add URawFormatValue residuing inside another outer object (should be URawFormatValueArray)"));
    Values.Add(Key, ValueClass);
};

FORCEINLINE TSharedPtr<FJsonValue> URawFormatValueObject::ToJson() const {
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    for (TPair<FString, URawFormatValue*> Pair : Values) {
        JsonObject->SetField(Pair.Key, Pair.Value->ToJson());
    }
    return MakeShareable(new FJsonValueObject(JsonObject));
}

FORCEINLINE URawFormatValueObject* URawFormatValueObject::FromJson(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue) {
    URawFormatValueObject* Object = NewObject<URawFormatValueObject>(Outer);
    for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : JsonValue->AsObject()->Values) {
        UConfigProperty* Owner = Cast<UConfigProperty>(Outer);
        if (IsValid(Owner) && Owner->Implements<UConfigValueObjectInterface>()) {
            UConfigProperty* ChildProperty = IConfigValueObjectInterface::Execute_GetChildProperty(Owner, Pair.Key);
            if (IsValid(ChildProperty)) {
                Object->AddValue(Pair.Key, ChildProperty->CreateRawFormatValue(Object, Pair.Value));
                continue;
            }
        }

        UE_LOG(LogSatisfactoryModLoader, Warning, TEXT("Deserializing JSON value for property %s with fallback implementation."), *Pair.Key);
        #pragma warning(suppress : 4996)
        Object->AddValue(Pair.Key, FJsonRawFormatConverter::ConvertToRawFormat(Object, Pair.Value));
    }
    return Object;
}
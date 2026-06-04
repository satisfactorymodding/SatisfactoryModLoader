#pragma once
#include "Configuration/ConfigProperty.h"
#include "Configuration/RawFileFormat/Json/JsonRawFormatConverter.h"
#include "Configuration/RawFileFormat/RawFormatValue.h"
#include "Configuration/RawFileFormat/RawFormatValueNumber.h"
#include "Configuration/RawFileFormat/RawFormatValueString.h"
#include "Templates/SubclassOf.h"
#include "SatisfactoryModLoader.h"
#include "RawFormatValueArray.generated.h"

/** Describes raw array value */
UCLASS()
class SML_API URawFormatValueArray : public URawFormatValue {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 Num() const { return Values.Num(); }
    
    UFUNCTION(BlueprintPure)
    FORCEINLINE URawFormatValue* GetValue(int32 Index) const {
        if (Index >= 0 && Index < Values.Num())
            return Values[Index];
        return NULL;
    }

    /** Retrieves value at the given index as array */
    UFUNCTION(BlueprintPure)
    FORCEINLINE URawFormatValueArray* GetArray(int32 Index) const {
        return Cast<URawFormatValueArray>(GetValue(Index));
    }

    UFUNCTION(BlueprintCallable)
    FORCEINLINE URawFormatValueArray* AddArray() {
        return AddNewValue<URawFormatValueArray>();
    }
    
    /** Retrieves value at the given index as string, falling back to empty string if it's not a string */
    UFUNCTION(BlueprintPure)
    FORCEINLINE FString GetString(int32 Index) const {
        URawFormatValueString* StringValue = Cast<URawFormatValueString>(GetValue(Index));
        return StringValue ? StringValue->Value : TEXT("");
    }

    UFUNCTION(BlueprintCallable)
    void AddString(const FString& Value);

    /** Retrieves value at the given index as integer, falling back to zero if it's not a number */
    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetInteger(int32 Index) const {
        URawFormatValueNumber* NumberValue = Cast<URawFormatValueNumber>(GetValue(Index));
        return NumberValue ? NumberValue->AsInt() : 0;
    }

    UFUNCTION(BlueprintCallable)
    void AddInteger(int32 Value);

    /** Retrieves value at the given index as floating point number, falling back to zero if it's not a number */
    UFUNCTION(BlueprintPure)
    FORCEINLINE float GetFloat(int32 Index) const {
        URawFormatValueNumber* NumberValue = Cast<URawFormatValueNumber>(GetValue(Index));
        return NumberValue ? NumberValue->AsFloat() : 0.0f;
    }

    UFUNCTION(BlueprintCallable)
    void AddFloat(float Value);
    
    /** Adds value into the array and returns pointer to it */
    UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ValueClass"))
    void AddValue(URawFormatValue* ValueClass);

    /** Adds value into the map and returns pointer to it. Replaces value with duplicate key */
    UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ValueClass"))
    FORCEINLINE URawFormatValue* AddNewValue(TSubclassOf<URawFormatValue> ValueClass) {
        URawFormatValue* NewValue = NewObject<URawFormatValue>(this, ValueClass);
        AddValue(NewValue);
        return NewValue;
    }

    /** Template version of AddValue for C++ usage */
    template<typename T>
    FORCEINLINE T* AddNewValue() {
        return Cast<T>(AddNewValue(T::StaticClass()));
    }

    /** Returns copy of the underlying array object. */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetUnderlyingArray"))
    FORCEINLINE TArray<URawFormatValue*> K2_GetUnderlyingArray() const { return Values; }

    /** Returns underlying array object reference. Reference is valid as long as this object is valid. */
    FORCEINLINE const TArray<URawFormatValue*>& GetUnderlyingArrayRef() const { return Values; }

    virtual TSharedPtr<FJsonValue> ToJson() const override;

    /** Creates a new URawFormatValueArray from the given JSON value */
    static URawFormatValueArray* FromJson(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue);

private:
    /** Private to ensure that added objects have valid outer */
    UPROPERTY()
    TArray<TObjectPtr<URawFormatValue>> Values;
};

FORCEINLINE void URawFormatValueArray::AddString(const FString& Value) {
    AddNewValue<URawFormatValueString>()->Value = Value;
}

FORCEINLINE void URawFormatValueArray::AddInteger(int32 Value) {
    AddNewValue<URawFormatValueNumber>()->SetValueInt(Value);
}

FORCEINLINE void URawFormatValueArray::AddFloat(float Value) {
    AddNewValue<URawFormatValueNumber>()->SetValueFloat(Value);
}

FORCEINLINE void URawFormatValueArray::AddValue(URawFormatValue* ValueClass) {
    //Sanity check to ensure hierarchical view inside this raw value
    checkf(ValueClass && ValueClass->GetOuter() == this, TEXT("Cannot add URawFormatValue residuing inside another outer object (should be URawFormatValueArray)"));
    Values.Add(ValueClass);
}

FORCEINLINE TSharedPtr<FJsonValue> URawFormatValueArray::ToJson() const {
    TArray<TSharedPtr<FJsonValue>> OutJsonArray;
    for (const URawFormatValue* ChildValue : Values) {
      OutJsonArray.Add(ChildValue->ToJson());
    }
    return MakeShareable(new FJsonValueArray(OutJsonArray));
}

FORCEINLINE URawFormatValueArray* URawFormatValueArray::FromJson(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue) {
    URawFormatValueArray* Array = NewObject<URawFormatValueArray>(Outer);
    for (const TSharedPtr<FJsonValue>& ChildValue : JsonValue->AsArray()) {
        // TODO: Base child property deserialization on the child config property.
        UE_LOG(LogSatisfactoryModLoader, Warning, TEXT("Deserializing JSON array value for property with fallback implementation."));
        #pragma warning(suppress : 4996)
        Array->AddValue(FJsonRawFormatConverter::ConvertToRawFormat(Array, ChildValue));
    }
    return Array;
}
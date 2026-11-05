#pragma once
#include "Configuration/RawFileFormat/RawFormatValue.h"
#include "RawFormatValueString.generated.h"

/** Describes raw string value */
UCLASS()
class SML_API URawFormatValueString : public URawFormatValue {
    GENERATED_BODY()
public:
    /** Value of this raw value as string */
    UPROPERTY(BlueprintReadWrite)
    FString Value;

    virtual TSharedPtr<FJsonValue> ToJson() const override;

    static URawFormatValueString* FromJson(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue);
};

FORCEINLINE TSharedPtr<FJsonValue> URawFormatValueString::ToJson() const {
    return MakeShareable(new FJsonValueString(Value));
}

FORCEINLINE URawFormatValueString* URawFormatValueString::FromJson(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue) {
    URawFormatValueString* String = NewObject<URawFormatValueString>(Outer);
    String->Value = JsonValue->AsString();
    return String;
}
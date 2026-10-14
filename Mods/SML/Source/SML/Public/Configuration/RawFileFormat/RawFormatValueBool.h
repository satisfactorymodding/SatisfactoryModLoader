#pragma once
#include "Configuration/RawFileFormat/RawFormatValue.h"
#include "RawFormatValueBool.generated.h"

/** Describes raw boolean value */
UCLASS()
class SML_API URawFormatValueBool : public URawFormatValue {
    GENERATED_BODY()
public:
    /** Actual boolean value stored */
    UPROPERTY(BlueprintReadWrite)
    bool Value;

    virtual TSharedPtr<FJsonValue> ToJson() const override;

    /** Creates a new URawFormatValueBool from the given JSON value */
    static URawFormatValueBool* FromJson(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue);
};

FORCEINLINE TSharedPtr<FJsonValue> URawFormatValueBool::ToJson() const {
    return MakeShareable(new FJsonValueBoolean(Value));
}

FORCEINLINE URawFormatValueBool* URawFormatValueBool::FromJson(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue) {
    URawFormatValueBool* Boolean = NewObject<URawFormatValueBool>(Outer);
    Boolean->Value = JsonValue->AsBool();
    return Boolean;
}
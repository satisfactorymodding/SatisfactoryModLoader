#pragma once
#include "Configuration/RawFileFormat/RawFormatValue.h"
#include "CoreMinimal.h"
#include "RawFormatValueRawJson.generated.h"

/** 
 * Holds a raw JSON value.
 * 
 * Note: Changes to this value will need to be made through C++ code.
 *       Blueprint editing of this value is not supported.
 */
UCLASS()
class SML_API URawFormatValueRawJson : public URawFormatValue {
    GENERATED_BODY()
public:
    TSharedRef<FJsonValue> Value = MakeShared<FJsonValueNull>();

    virtual TSharedPtr<FJsonValue> ToJson() const override;

    /** Creates a new URawFormatValueRawJson from the given JSON value */
    static URawFormatValueRawJson* FromJson(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue);
};

FORCEINLINE TSharedPtr<FJsonValue> URawFormatValueRawJson::ToJson() const {
    return Value.ToSharedPtr();
}

FORCEINLINE URawFormatValueRawJson* URawFormatValueRawJson::FromJson(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue) {
    URawFormatValueRawJson* JsonValueWrapper = NewObject<URawFormatValueRawJson>(Outer);
    JsonValueWrapper->Value = JsonValue.ToSharedRef();
    return JsonValueWrapper;
}
#include "Configuration/RawFileFormat/Json/JsonRawFormatConverter.h"
#include "Configuration/RawFileFormat/RawFormatValueArray.h"
#include "Configuration/RawFileFormat/RawFormatValueBool.h"
#include "Configuration/RawFileFormat/RawFormatValueNumber.h"
#include "Configuration/RawFileFormat/RawFormatValueObject.h"
#include "Configuration/RawFileFormat/RawFormatValueString.h"
#include "Dom/JsonObject.h"

TSharedPtr<FJsonValue> FJsonRawFormatConverter::ConvertToJson(const URawFormatValue* RawFormatValue) {
    if (const URawFormatValueNumber* Number = Cast<URawFormatValueNumber>(RawFormatValue)) {
        return Number->ToJson();
    }
    if (const URawFormatValueString* String = Cast<URawFormatValueString>(RawFormatValue)) {
        return String->ToJson();
    }
    if (const URawFormatValueBool* Boolean = Cast<URawFormatValueBool>(RawFormatValue)) {
        return Boolean->ToJson();
    }
    if (const URawFormatValueArray* Array = Cast<URawFormatValueArray>(RawFormatValue)) {
        return Array->ToJson();
    }
    if (const URawFormatValueObject* Object = Cast<URawFormatValueObject>(RawFormatValue)) {
        return Object->ToJson();
    }
    checkf(false, TEXT("Unreachable code"));
    return NULL;
}

URawFormatValue* FJsonRawFormatConverter::ConvertToRawFormat(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue) {
    switch (JsonValue->Type) {
        case EJson::Number: {
            return URawFormatValueNumber::FromJson(Outer, JsonValue);
        }
        case EJson::String: {
            return URawFormatValueString::FromJson(Outer, JsonValue);
        }
        case EJson::Boolean: {
            return URawFormatValueBool::FromJson(Outer, JsonValue);
        }
        case EJson::Array: {
            return URawFormatValueArray::FromJson(Outer, JsonValue);
        }
        case EJson::Object: {
            return URawFormatValueObject::FromJson(Outer, JsonValue);
        }
        case EJson::Null: {
            checkf(false, TEXT("JSON Null value is not supported"));
            return NULL;
        }
        default: {
            checkf(false, TEXT("Unreachable code"));
            return NULL;
        }
    }
}

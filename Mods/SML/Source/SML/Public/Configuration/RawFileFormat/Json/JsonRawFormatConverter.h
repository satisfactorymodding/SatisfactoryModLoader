#pragma once
#include "CoreMinimal.h"
#include "Configuration/RawFileFormat/RawFormatValue.h"
#include "Dom/JsonValue.h"

/**
 * Class handling conversion from raw format value to
 * json and vice versa. Is separate from RawFormatValue module to aid with
 * switching configuration format to other one without need of changing API or
 * recompiling mods using modern configuration API
 */
class SML_API FJsonRawFormatConverter {
public:
    /** Converts raw format value into the corresponding JSON element */
    [[deprecated("Use ToJson on the raw format value directly")]]
    static TSharedPtr<FJsonValue> ConvertToJson(const URawFormatValue* RawFormatValue);

    /** Converts JSON element into the raw format value, using specified object as Outer for raw value */
    [[deprecated("Use FromJson on the raw format class directly")]]
    static URawFormatValue* ConvertToRawFormat(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue);
};

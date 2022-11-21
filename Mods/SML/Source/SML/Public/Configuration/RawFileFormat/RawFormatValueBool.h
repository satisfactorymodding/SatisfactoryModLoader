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
};

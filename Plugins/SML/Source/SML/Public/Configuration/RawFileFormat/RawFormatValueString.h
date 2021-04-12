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
};

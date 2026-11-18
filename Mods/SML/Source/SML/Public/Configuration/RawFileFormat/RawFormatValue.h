#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RawFormatValue.generated.h"

UCLASS(Abstract, BlueprintType)
class SML_API URawFormatValue : public UObject {
    GENERATED_BODY()

public:
    /** Converts this object into a JSON value */
    virtual TSharedPtr<FJsonValue> ToJson() const {
        checkf(false, TEXT("ToJson not implemented"));
        return NULL;
    }
};

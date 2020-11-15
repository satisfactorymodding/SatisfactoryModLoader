#pragma once
#include "RawFormatValue.h"
#include "RawFormatValueNumber.generated.h"

/** Describes raw number value */
UCLASS()
class SML_API URawFormatValueNumber : public URawFormatValue {
    GENERATED_BODY()
public:
    /** Actual value stored, as double precision floating point number */
    UPROPERTY()
    double Value;

    /** Retrieves number value as floating point */
    UFUNCTION(BlueprintPure)
    FORCEINLINE float AsFloat() const { return Value; };

    /** Updates raw value to specified floating point value */
    FORCEINLINE
    UFUNCTION(BlueprintCallable)
    void SetValue(float Value) { this->Value = Value; }
    
    /** Retrieves number value as 32-bit signed integer */
    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 AsInt() const { return (int32) Value; }

    /** Updates raw value to specified 32-bit signed integer */
    FORCEINLINE
    UFUNCTION(BlueprintCallable)
    void SetValue(int32 Value) { this->Value = Value; }
};

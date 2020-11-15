#pragma once
#include "Configuration/ConfigValue.h"
#include "ConfigValueInteger.generated.h"

UCLASS()
class SML_API UConfigValueInteger : public UConfigValue {
    GENERATED_BODY()
public:
    /** Current integer value of this state */
    UPROPERTY(BlueprintReadWrite)
    int32 Value;

    virtual FString DescribeValue_Implementation() const override;
    virtual URawFormatValue* Serialize_Implementation(UObject* Outer) const override;
    virtual void Deserialize_Implementation(const URawFormatValue* Value) override;
    void FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const override;
};
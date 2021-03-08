#pragma once
#include "../ConfigValue.h"
#include "ConfigValueString.generated.h"

UCLASS()
class SML_API UConfigValueString : public UConfigValue {
    GENERATED_BODY()
public:
    /** Current string value associated with this state */
    UPROPERTY(BlueprintReadWrite)
    FString Value;

    virtual FString DescribeValue_Implementation() const override;
    virtual URawFormatValue* Serialize_Implementation(UObject* Outer) const override;
    virtual void Deserialize_Implementation(const URawFormatValue* Value) override;
    void FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const override;
};
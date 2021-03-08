#pragma once
#include "Configuration/ConfigValue.h"
#include "ConfigValueColor.generated.h"

UCLASS()
class SML_API UConfigValueColor : public UConfigValue {
    GENERATED_BODY()
public:
    /** Current color value of this state */
    UPROPERTY(BlueprintReadWrite)
    FLinearColor Value;

    virtual FString DescribeValue_Implementation() const override;
    virtual URawFormatValue* Serialize_Implementation(UObject* Outer) const override;
    virtual void Deserialize_Implementation(const URawFormatValue* Value) override;
    void FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const override;
};
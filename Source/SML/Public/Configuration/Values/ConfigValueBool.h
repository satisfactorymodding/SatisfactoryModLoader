#pragma once
#include "Configuration/ConfigValue.h"
#include "ConfigValueBool.generated.h"

UCLASS()
class SML_API UConfigValueBool : public UConfigValue {
    GENERATED_BODY()
public:
    /** Current boolean value of this property */
    UPROPERTY(BlueprintReadWrite)
    bool Value;

    virtual FString DescribeValue_Implementation() const override;
    virtual URawFormatValue* Serialize_Implementation(UObject* Outer) const override;
    virtual void Deserialize_Implementation(const URawFormatValue* Value) override;
    void FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const override;
};
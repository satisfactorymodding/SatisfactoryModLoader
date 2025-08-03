#pragma once
#include "Configuration/ConfigProperty.h"
#include "ConfigPropertyInteger.generated.h"

UCLASS()
class SML_API UConfigPropertyInteger : public UConfigProperty {
    GENERATED_BODY()
public:
    /** Current value of this configuration property. At editor time, this is the default value. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration Property")
    int32 Value;

    /** Cached value this configuration property should reset to */
    UPROPERTY(Transient, BlueprintReadOnly, Category = "Internal")
    int32 DefaultValue;


public:
    UConfigPropertyInteger();
    virtual void PostInitProperties() override;

	//Begin UConfigProperty
	virtual FString DescribeValue_Implementation() const override;
	virtual URawFormatValue* Serialize_Implementation(UObject* Outer) const override;
	virtual void Deserialize_Implementation(const URawFormatValue* Value) override;
    virtual FConfigVariableDescriptor CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const override;
    virtual void FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const override;
    virtual bool ResetToDefault_Implementation() override;
    virtual bool IsSetToDefaultValue_Implementation() const override;
    virtual FString GetDefaultValueAsString_Implementation() const override;
	//End UConfigProperty

private:
    bool bDefaultValueInitialized = false;
};

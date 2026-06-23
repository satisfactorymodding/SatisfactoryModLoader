#pragma once
#include "Configuration/ConfigProperty.h"
#include "ConfigPropertyInteger.generated.h"

UCLASS()
class SML_API UConfigPropertyInteger : public UConfigProperty {
    GENERATED_BODY()
public:
    /** Default value of this configuration property. This is the value the property resets to. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration Property")
    int32 DefaultValue;

    /** Runtime value of this configuration property. */
    UPROPERTY(BlueprintReadWrite, Category = "Configuration Property")
    int32 Value;

public:
    //Begin UObject
#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
    //End UObject

    virtual void PostLoad() override;

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
};

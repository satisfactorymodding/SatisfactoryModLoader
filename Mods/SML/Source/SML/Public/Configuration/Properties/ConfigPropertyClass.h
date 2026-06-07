#pragma once
#include "Configuration/ConfigProperty.h"
#include "ConfigPropertyClass.generated.h"

UCLASS()
class SML_API UConfigPropertyClass : public UConfigProperty {
    GENERATED_BODY()
public:
    /** True if we should limit which classes can be set to this property values by particular base class type */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration Property")
    bool bLimitBaseClass;

    /** Base class that values of this type should have */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bLimitBaseClass",AllowAbstract = "true"), Category = "Configuration Property")
    TObjectPtr<UClass> BaseClass;

    /** Whenever to allow NULL class value on this property. If NULL is not allowed, it will fallback to default value instead */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration Property")
    bool bAllowNullValue;

    /** Default value of this configuration property. This is the value the property resets to. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowAbstract = "true"), Category = "Configuration Property")
    TObjectPtr<UClass> DefaultValue;

    /** Runtime value of this configuration property. DO NOT SET DIRECTLY, USE SetClassValue */
    UPROPERTY(BlueprintReadOnly, meta = (AllowAbstract = "true"), Category = "Configuration Property")
    TObjectPtr<UClass> Value;

public:
    UConfigPropertyClass();

    //Begin UObject
#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
    //End UObject

    /** Returns true if this class is a valid value for this property */
    UFUNCTION(BlueprintPure)
    bool IsValidValueClass(UClass* Class) const;

    /** Updates current class value to the provided one, if it is possible */
    UFUNCTION(BlueprintCallable)
    void SetClassValue(UClass* NewValue);

    //Begin UObject
#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(TArray<FText>& ValidationErrors) override;
#endif
    //End UObject

    virtual void PostLoad() override;

    //Begin UConfigProperty
    virtual FString DescribeValue_Implementation() const override;
    virtual URawFormatValue* Serialize_Implementation(UObject* Outer) const override;
    virtual void Deserialize_Implementation(const URawFormatValue* RawValue) override;
    virtual FConfigVariableDescriptor CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const override;
    virtual void FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const override;
    virtual bool ResetToDefault_Implementation() override;
    virtual bool IsSetToDefaultValue_Implementation() const override;
    virtual FString GetDefaultValueAsString_Implementation() const override;
    //End UConfigProperty
};
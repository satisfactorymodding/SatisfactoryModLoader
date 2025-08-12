﻿#pragma once
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
    UClass* BaseClass;

    /** Whenever to allow NULL class value on this property. If NULL is not allowed, it will fallback to default value instead */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration Property")
    bool bAllowNullValue;

    /** Current value of this configuration property. At editor time, this is the default value. DO NOT SET DIRECTLY, USE SetClassValue */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowAbstract = "true"), Category = "Configuration Property")
    UClass* Value;

    /** Cached value this configuration property should reset to */
    UPROPERTY(Transient, BlueprintReadOnly, Category = "Internal")
    UClass* DefaultValue;


public:
    UConfigPropertyClass();

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

    virtual void PostInitProperties() override;

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

private:
    bool bDefaultValueInitialized = false;
};
#pragma once
#include "Configuration/ConfigProperty.h"
#include "ConfigPropertyClass.generated.h"

UCLASS(EditInlineNew)
class SML_API UConfigPropertyClass : public UConfigProperty {
    GENERATED_BODY()
public:
    /** True if we should limit which classes can be set to this property values by particular base class type */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bLimitBaseClass;
    
    /** Base class that values of this type should have */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bLimitBaseClass"))
    UClass* BaseClass;

    /** Whenever to allow NULL class value on this property. If NULL is not allowed, it will fallback to default value instead */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bAllowNullValue;

    /** Default value of this class property */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UClass* DefaultValueClass;

    /** Returns true if this class is a valid value for this property */
    UFUNCTION(BlueprintPure)
    bool IsValidValueClass(UClass* Class) const;

    UConfigPropertyClass();
    TSubclassOf<UConfigValue> GetValueClass_Implementation() const override;
    void ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const override;
    FConfigVariableDescriptor CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const override;
};
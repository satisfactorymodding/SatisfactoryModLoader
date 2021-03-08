#pragma once
#include "Configuration/ConfigProperty.h"
#include "ConfigPropertyInteger.generated.h"

UCLASS(EditInlineNew)
class SML_API UConfigPropertyInteger : public UConfigProperty {
    GENERATED_BODY()
public:
    /** Default value of this property to be used in config */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 DefaultValue;
    
    UConfigPropertyInteger();
    TSubclassOf<UConfigValue> GetValueClass_Implementation() const override;
    void ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const override;
    FConfigVariableDescriptor CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const override;
};

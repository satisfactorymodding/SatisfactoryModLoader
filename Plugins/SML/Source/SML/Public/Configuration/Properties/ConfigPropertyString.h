#pragma once
#include "Configuration/ConfigProperty.h"
#include "ConfigPropertyString.generated.h"

UCLASS(EditInlineNew)
class SML_API UConfigPropertyString : public UConfigProperty {
    GENERATED_BODY()
public:
    /** Default value of this property to be applied to configuration */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString DefaultValue;
    
    UConfigPropertyString();
    TSubclassOf<UConfigValue> GetValueClass_Implementation() const override;
    void ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const override;
    FConfigVariableDescriptor CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const override;
};
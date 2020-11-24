#pragma once
#include "Configuration/ConfigProperty.h"
#include "ConfigPropertyFloat.generated.h"

UCLASS(EditInlineNew)
class SML_API UConfigPropertyFloat : public UConfigProperty {
    GENERATED_BODY()
public:
    /** Default value of this property */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float DefaultValue;
    
    UConfigPropertyFloat();
    TSubclassOf<UConfigValue> GetValueClass_Implementation() const override;
    void ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const override;
    FConfigVariableDescriptor CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const override;
};
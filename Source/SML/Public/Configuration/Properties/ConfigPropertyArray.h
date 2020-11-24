#pragma once
#include "Configuration/ConfigProperty.h"
#include "ConfigPropertyArray.generated.h"

/** Describes array configuration property with single nested element type */
UCLASS(EditInlineNew)
class SML_API UConfigPropertyArray : public UConfigProperty {
    GENERATED_BODY()
public:
    /** Element type of this array property */
    UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly)
    UConfigProperty* ElementValue;

    TSubclassOf<UConfigValue> GetValueClass_Implementation() const override;
    FConfigVariableDescriptor CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const override;
};
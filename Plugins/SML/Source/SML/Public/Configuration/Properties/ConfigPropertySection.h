#pragma once
#include "Configuration/ConfigProperty.h"
#include "ConfigPropertySection.generated.h"

/** Describes a single configuration section with nested properties */
UCLASS(EditInlineNew)
class SML_API UConfigPropertySection : public UConfigProperty {
    GENERATED_BODY()
public:
    /**
     * All properties contained in this section
     * Consider using alphanumerical characters only in property names
     */
    UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly)
    TMap<FString, UConfigProperty*> SectionProperties;

    void ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const override;
    TSubclassOf<UConfigValue> GetValueClass_Implementation() const override;
    FConfigVariableDescriptor CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const override;
};
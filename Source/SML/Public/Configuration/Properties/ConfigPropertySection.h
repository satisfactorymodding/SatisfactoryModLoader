#pragma once
#include "Configuration/ConfigProperty.h"
#include "ConfigPropertySection.generated.h"

/** Describes single section property */
USTRUCT(BlueprintType)
struct SML_API FSectionProperty {
    GENERATED_BODY()
public:
    /** Name of this property inside the configuration file. Consider using alphanumerical characters only */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Name;
    
    /** Display name of this property as it is visible to the user */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString DisplayName;

    /** Tooltip visible to user hovering over this property */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Tooltip;

    /** Property describing this property of this section */
    UPROPERTY(Instanced, BlueprintReadOnly)
    UConfigProperty* Property;
};

/** Describes a single configuration section with nested properties */
UCLASS()
class SML_API UConfigPropertySection : public UConfigProperty {
    GENERATED_BODY()
public:
    /** All properties contained in this section */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FSectionProperty> SectionProperties;

    void ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const override;
    TSubclassOf<UConfigValue> GetValueClass_Implementation() const override;
    FConfigVariableDescriptor CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const override;
};
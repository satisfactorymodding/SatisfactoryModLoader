#pragma once
#include "Configuration/Properties/ConfigPropertySection.h"
#include "ModConfiguration.generated.h"

UCLASS(Blueprintable)
class SML_API UModConfiguration : public UObject {
    GENERATED_BODY()
public:
    /** Display name of this configuration, as it will be visible to user */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FString DisplayName;
    
    /** Description of this configuration, can be empty */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FString Description;

    /** Root property of this configuration describing it's values */
    UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly)
    UConfigPropertySection* RootSection;   
};

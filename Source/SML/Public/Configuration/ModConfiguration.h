#pragma once
#include "ConfigPropertySection.h"
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

    /**
     * Version of the schema of this configuration.
     * When this value doesn't match with the filesystem one, configuration
     * file will be re-saved on the disk to make sure all properties are defined inside of it,
     * even if there are not any changes to configuration values themselves pending
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 SchemaVersion;
};
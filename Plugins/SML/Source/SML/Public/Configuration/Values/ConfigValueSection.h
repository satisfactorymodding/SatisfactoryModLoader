#pragma once
#include "../ConfigValue.h"
#include "Configuration/Properties/ConfigPropertySection.h"
#include "ConfigValueSection.generated.h"

UCLASS()
class SML_API UConfigValueSection : public UConfigValue {
    GENERATED_BODY()
public:
    /** Returns section properties list this state has */
    UFUNCTION(BlueprintPure)
    TMap<FString, UConfigProperty*> GetProperties() const;

    /** Returns configuration state for given property name */
    UFUNCTION(BlueprintPure)
    UConfigValue* GetValueForProperty(const FString& PropertyName) const;

    /** Same as FillConfigStruct, but instead of getting value from passed object it reads passed object AS the value itself */
    UFUNCTION(BlueprintCallable)
    void FillConfigStructSelf(const FReflectedObject& ReflectedObject) const;

    void InitializedFromProperty_Implementation() override;
    virtual FString DescribeValue_Implementation() const override;
    virtual URawFormatValue* Serialize_Implementation(UObject* Outer) const override;
    virtual void Deserialize_Implementation(const URawFormatValue* Value) override;
    void FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const override;
private:
    /** Map of child state to name stored in section */
    UPROPERTY()
    TMap<FString, UConfigValue*> ConfigurationValues;
};
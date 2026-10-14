#pragma once
#include "Configuration/ConfigProperty.h"
#include "Configuration/ConfigValueDirtyHandlerInterface.h"
#include "Configuration/RawFileFormat/RawFormatValueRawJson.h"
#include "ConfigPropertyRaw.generated.h"

/**
 * Describes a raw configuration property not designed to be edited by the player.
 * 
 * Note: Changes to this property's value will need to be made through C++ code.
 *       Blueprint editing of this property is not supported.
 */
UCLASS()
class SML_API UConfigPropertyRaw : public UConfigProperty {
    GENERATED_BODY()
public:
    TSharedRef<FJsonValue> Value = MakeShared<FJsonValueNull>();

    void SetValue(TSharedPtr<FJsonValue> NewValue);
    void SetValue(TSharedPtr<FJsonObject> NewValue);

    // Begin UConfigProperty
public:
    virtual FString DescribeValue_Implementation() const override;
    virtual URawFormatValue* Serialize_Implementation(UObject* Outer) const override;
    virtual void Deserialize_Implementation(const URawFormatValue* Value) override;
    virtual FConfigVariableDescriptor CreatePropertyDescriptor_Implementation( UConfigGenerationContext* Context, const FString& OuterPath) const override;
    virtual void FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const override;
    virtual bool ResetToDefault_Implementation() override;
    virtual bool IsSetToDefaultValue_Implementation() const override;
    virtual FString GetDefaultValueAsString_Implementation() const override;
    
    virtual URawFormatValueRawJson* CreateRawFormatValue(UObject* Outer, const TSharedPtr<FJsonValue>& JsonValue) override {
        return URawFormatValueRawJson::FromJson(Outer, JsonValue);
    }
    // End UConfigProperty

    // Begin UObject
protected:
    virtual void PostInitProperties() override;

public:
#if WITH_EDITOR
    virtual bool CanEditChange(const FProperty* InProperty) const override;
#endif
    // End UObject
};

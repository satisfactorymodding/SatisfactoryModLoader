#pragma once
#include "Configuration/ConfigProperty.h"
#include "Configuration/ConfigValueDirtyHandlerInterface.h"
#include "ConfigPropertyArray.generated.h"

/** Describes array configuration property with single nested element type */
UCLASS()
class SML_API UConfigPropertyArray : public UConfigProperty, public IConfigValueDirtyHandlerInterface {
    GENERATED_BODY()
public:
    /** Defines the "template" default value used for allocating other values in the array */
    UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Configuration Property", meta = (DisplayName= "New Value Template"))
    UConfigProperty* DefaultValue;

    /** Current values of this configuration property. At editor time, this is the default contents of the array. Should be of the same type as DefaultValue, names don't matter */
    UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Configuration Property")
    TArray<UConfigProperty*> Values;

    /** Cached value this configuration property should reset to */
    UPROPERTY(Transient, BlueprintReadOnly, Category = "Internal")
    TArray<UConfigProperty*> DefaultValues;


public:
    /** Allocates new default element and inserts it at the specified index */
    UFUNCTION(BlueprintCallable)
    UConfigProperty* AddNewElement();

    /** Removes element at the specified index */
    UFUNCTION(BlueprintCallable)
    void RemoveElementAtIndex(int32 Index);

    /** Clears all of the current values stored in the array */
    UFUNCTION(BlueprintCallable)
    void Clear();

    //Begin UObject
#if WITH_EDITOR
    virtual bool CanEditChange(const FProperty* InProperty) const override;
    virtual EDataValidationResult IsDataValid(TArray<FText>& ValidationErrors) override;
#endif
    //End UObject

    virtual void PostInitProperties() override;

    //Begin UConfigProperty
    virtual FString DescribeValue_Implementation() const override;
    virtual URawFormatValue* Serialize_Implementation(UObject* Outer) const override;
    virtual void Deserialize_Implementation(const URawFormatValue* Value) override;
    virtual FConfigVariableDescriptor CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const override;
    virtual void FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const override;
    virtual bool ResetToDefault_Implementation() override;
    virtual bool IsSetToDefaultValue_Implementation() const override;
    virtual FString GetDefaultValueAsString_Implementation() const override;
    //End UConfigProperty

    //Begin IConfigValueDirtyHandlerInterface
    virtual void HandleMarkDirty_Implementation() override;
    //End IConfigValueDirtyHandlerInterface

private:
    bool bDefaultValueInitialized = false;
};
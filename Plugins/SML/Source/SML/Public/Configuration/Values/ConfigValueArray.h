#pragma once
#include "Configuration/ConfigValue.h"
#include "ConfigValueArray.generated.h"

UCLASS()
class SML_API UConfigValueArray : public UConfigValue {
    GENERATED_BODY()
public:
    /** Returns amount of elements in the array */
    UFUNCTION(BlueprintPure)
    int32 ElementCount() const;

    /** Returns element at the index specified */
    UFUNCTION(BlueprintPure)
    UConfigValue* GetElement(int32 Index) const;

    /** Allocates new default element and adds it into the array */
    UFUNCTION(BlueprintCallable)
    UConfigValue* AddNewElement();

    /** Remove element at the specified index in the array */
    UFUNCTION(BlueprintCallable)
    void RemoveElementAtIndex(int32 Index);

    /** Clear the array out so it is empty afterwards */
    UFUNCTION(BlueprintCallable)
    void Clear();
    
    virtual FString DescribeValue_Implementation() const override;
    virtual URawFormatValue* Serialize_Implementation(UObject* Outer) const override;
    virtual void Deserialize_Implementation(const URawFormatValue* Value) override;
    void FillConfigStruct_Implementation(const FReflectedObject& ReflectedObject, const FString& VariableName) const override;
private:
    /** Array of child states stored in this array compound state */
    UPROPERTY()
    TArray<UConfigValue*> Values;
};
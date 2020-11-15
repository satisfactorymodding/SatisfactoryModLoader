#pragma once
#include "ConfigVariableDescriptor.h"
#include "CoreMinimal.h"
#include "Object.h"
#include "SubclassOf.h"
#include "ConfigProperty.generated.h"

class UConfigValue;

/**
 * Describes single value inside the configuration
 * Value doesn't actually hold any mutable data, instead, it manages
 * ConfigurationState and provides method for working with it
 * It provides editing functionality for state, and default value to start from
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class SML_API UConfigProperty : public UObject {
    GENERATED_BODY()
public:
    /** Retrieves type of the configuration state this value is operating on */
    UFUNCTION(BlueprintPure, BlueprintNativeEvent)
    TSubclassOf<UConfigValue> GetValueClass() const;

    /** Called by CreateNewValue() to fill created object with default value of this property */
    UFUNCTION(BlueprintNativeEvent)
    void ApplyDefaultPropertyValue(UConfigValue* Value) const;

    /** Creates new value object from this property and fills it with default settings */
    UFUNCTION(BlueprintCallable)
    UConfigValue* CreateNewValue(UObject* Outer) const;
    
    /** Creates widget instance for editing provided configuration value. Can be NULL if widget is not supported */
    UFUNCTION(BlueprintPure, BlueprintNativeEvent)
    class UUserWidget* CreateEditorWidget(class UUserWidget* ParentWidget, UConfigValue* Value) const;

    /** Creates config property descriptor for code generation */
    UFUNCTION(BlueprintPure, BlueprintNativeEvent)
    FConfigVariableDescriptor CreatePropertyDescriptor(class UConfigGenerationContext* Context, const FString& OuterPath) const;
};
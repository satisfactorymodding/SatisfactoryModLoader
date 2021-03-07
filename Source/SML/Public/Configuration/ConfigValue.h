#pragma once
#include "Configuration/ConfigProperty.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObject/Object.h"
#include "RawFileFormat/RawFormatValue.h"
#include "Reflection/BlueprintReflectedObject.h"
#include "ConfigValue.generated.h"

/** Just a blueprint wrapper for UInterface object */
UINTERFACE(Blueprintable)
class SML_API UConfigValueDirtyHandlerInterface : public UInterface {
    GENERATED_BODY()
};

/**
 * Used to mark configuration value dirty.
 * First instance of the Outer object implementing this interface is selected
 * upon UConfigValue.MarkDirty() call and then called to process
 * marking configuration dirty
 */
class SML_API IConfigValueDirtyHandlerInterface {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent)
    void MarkDirty();
};

/**
 * Describes state of the single configuration value
 * Each configuration value type can have it's own state class,
 * and value is also responsible for converting state into raw file format and back
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class SML_API UConfigValue : public UObject {
    GENERATED_BODY()
public:
    /** Retrieves property object associated with this value */
    UFUNCTION(BlueprintPure)
    FORCEINLINE UConfigProperty* GetAssociatedProperty() const { return AssociatedProperty; }
    
    /** Describes this value for debugging purposes */
    UFUNCTION(BlueprintPure, BlueprintNativeEvent)
    FString DescribeValue() const;
    
    /** Serializes this state into the raw file format. Please use specified Outer for creating raw value object */
    UFUNCTION(BlueprintPure, BlueprintNativeEvent)
    URawFormatValue* Serialize(UObject* Outer) const;

    /** Deserializes passed raw file format value into this state */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Deserialize(const URawFormatValue* Value);

    /** Fills config struct with data provided in this property */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void FillConfigStruct(const FReflectedObject& ReflectedObject, const FString& VariableName) const;

    /**
     * Called when config value is initialized with associated property
     * By default it will call ApplyDefaultPropertyValue on property object
     * to initialize this value with default state obtained from configuration
     * You can override it to perform early property-sensitive initialization of value
     */
    UFUNCTION(BlueprintNativeEvent)
    void InitializedFromProperty();

    /** Marks this state as dirty, e.g that it needs synchronization with file system */
    UFUNCTION(BlueprintCallable)
    virtual void MarkDirty();
private:
    friend class UConfigProperty;

    /** Updates associated property. Casts away const because UPROPERTY doesn't support constant modifier */
    FORCEINLINE void SetAssociatedProperty(const UConfigProperty* Property) { AssociatedProperty = const_cast<UConfigProperty*>(Property); }
    
    /** Backing property storing master property that created this value */
    UPROPERTY(Transient)
    UConfigProperty* AssociatedProperty;
};

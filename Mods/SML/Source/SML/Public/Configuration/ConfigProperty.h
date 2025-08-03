#pragma once
#include "CoreMinimal.h"
#include "FGGameMode.h"
#include "UObject/Object.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Reflection/BlueprintReflectedObject.h"
#include "ConfigProperty.generated.h"

class URawFormatValue;
class UUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPropertyValueChanged);

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
    /** Display name of this property as it is visible to the user */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration Property")
    FText DisplayName;

    /** Tooltip visible to user hovering over this property */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration Property", meta = (MultiLine = true))
    FText Tooltip;

	/** If this value is only editable from the main menu -> can't be edited from the pause menu when loaded into a game world */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration Property")
	uint8 bRequiresWorldReload: 1;

	/** If this value should not be displayed in Config Widgets, meaning the user can't see it to configure it (unless they manually edit the config file on disk)  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration Property")
	uint8 bHidden : 1;

	/** If true, this property can be reset by the user from the Config Widget. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration Property")
	bool bAllowUserReset;

	/** Cached. If the parent section allows this property to be reset. It is up to container properties to implement setting this value. */
	UPROPERTY(BlueprintReadOnly, Transient, Category="Internal")
	bool bParentSectionAllowsUserReset = true;


public:
	/** Describes value of this property for debugging purposes */
	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
    FString DescribeValue() const;

	/** Serializes value of this property into raw file format. Please use specified Outer for creating raw value object */
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta = (DefaultToSelf = "Outer"))
    URawFormatValue* Serialize(UObject* Outer) const;

	/** Deserializes passed raw file format value into this property state */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Deserialize(const URawFormatValue* Value);

	/** Marks this property directly, forcing file system synchronization to happen afterwards */
	UFUNCTION(BlueprintCallable)
    virtual void MarkDirty();

	UPROPERTY(BlueprintAssignable)
	FOnPropertyValueChanged OnPropertyValueChanged;

    /** Creates widget instance for editing this configuration property's value. Can return NULL if property doesn't support direct UI editing */
    UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta = (DefaultToSelf = "ParentWidget"))
    UUserWidget* CreateEditorWidget(class UUserWidget* ParentWidget) const;

    /** Creates config property descriptor for code generation */
    UFUNCTION(BlueprintPure, BlueprintNativeEvent)
    FConfigVariableDescriptor CreatePropertyDescriptor(class UConfigGenerationContext* Context, const FString& OuterPath) const;

	/** Fills variable of provided object with the value carried by this property */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure = false)
    void FillConfigStruct(const FReflectedObject& ReflectedObject, const FString& VariableName) const;

	/** Resets this property to its default value */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Configuration Property")
	bool ResetToDefault();

	/** Returns true if this property is currently able to be reset by the user */
	UFUNCTION(BlueprintCallable, Category="Configuration Property")
	bool CanResetNow() const;

	/** Returns true if this property's current value is equal to its default value */
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Configuration Property")
	bool IsSetToDefaultValue() const;

	/** Returns the default value as a string */
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category="Configuration Property")
	FString GetDefaultValueAsString() const;

private:
    /** The Serialize() definition above shadows the native UObject::Serialize. Declare that we want to keep the UBOject implementation. */
    using UObject::Serialize;
};

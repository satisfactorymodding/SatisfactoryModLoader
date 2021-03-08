#include "Configuration/ConfigProperty.h"
#include "Configuration/ConfigValue.h"
#include "Configuration/CodeGeneration/ConfigGenerationContext.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"

TSubclassOf<UConfigValue> UConfigProperty::GetValueClass_Implementation() const {
    checkf(false, TEXT("GetValueClass not implemented"));
    return UConfigValue::StaticClass();
}

void UConfigProperty::ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const {
}

UConfigValue* UConfigProperty::CreateNewValue(UObject* Outer) const {
    UClass* ValueClass = GetValueClass();
    checkf(ValueClass, TEXT("GetValueClass returned NULL class"));
    checkf(!ValueClass->HasAnyClassFlags(CLASS_Abstract), TEXT("GetValueClass returned Abstract class"));
    
    UConfigValue* ConfigValue = NewObject<UConfigValue>(Outer, ValueClass);
    check(ConfigValue);
    ConfigValue->SetAssociatedProperty(this);
    ConfigValue->InitializedFromProperty();
    return ConfigValue;
}

FConfigVariableDescriptor UConfigProperty::CreatePropertyDescriptor_Implementation(UConfigGenerationContext* Context, const FString& OuterPath) const {
    checkf(false, TEXT("CreatePropertyDescriptor not implemented"));
    return FConfigVariableDescriptor{};
}

UUserWidget* UConfigProperty::CreateEditorWidget_Implementation(UUserWidget* ParentWidget, UConfigValue* Value) const {
    return NULL;
}

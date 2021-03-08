#include "Configuration/Properties/ConfigPropertyClass.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/Values/ConfigValueClass.h"

UConfigPropertyClass::UConfigPropertyClass() {
    DefaultValueClass = NULL;
    BaseClass = UObject::StaticClass();
    bLimitBaseClass = false;
}

bool UConfigPropertyClass::IsValidValueClass(UClass* Class) const {
    return Class ? (bLimitBaseClass && BaseClass ? Class->IsChildOf(BaseClass) : true) : bAllowNullValue;
}

TSubclassOf<UConfigValue> UConfigPropertyClass::GetValueClass_Implementation() const {
    return UConfigValueClass::StaticClass();
}

void UConfigPropertyClass::ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const {
    UConfigValueClass* ValueClass = Cast<UConfigValueClass>(Value);
    if (ValueClass != NULL) {
        ValueClass->SetClassValue(DefaultValueClass);
    }
}

FConfigVariableDescriptor UConfigPropertyClass::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariableClass(BaseClass);
}

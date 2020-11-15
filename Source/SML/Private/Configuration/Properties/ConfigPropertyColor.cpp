#include "Configuration/Properties/ConfigPropertyColor.h"
#include "CodeGeneration/ConfigVariableDescriptor.h"
#include "CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/Values/ConfigValueColor.h"

UConfigPropertyColor::UConfigPropertyColor() {
    DefaultColor = FLinearColor::White;
}

TSubclassOf<UConfigValue> UConfigPropertyColor::GetValueClass_Implementation() const {
    return UConfigValueColor::StaticClass();
}

void UConfigPropertyColor::ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const {
    UConfigValueColor* ColorValue = Cast<UConfigValueColor>(Value);
    if (ColorValue != NULL) {
        ColorValue->Value = DefaultColor;
    }
}

FConfigVariableDescriptor UConfigPropertyColor::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    return UConfigVariableLibrary::MakeConfigVariableStruct(FDynamicStructInfo{ TBaseStructure<FLinearColor>::Get() });
}

#include "Configuration/Properties/ConfigPropertySection.h"
#include "CodeGeneration/ConfigGenerationContext.h"
#include "CodeGeneration/ConfigVariableDescriptor.h"
#include "CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/Values/ConfigValueSection.h"

void UConfigPropertySection::ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const {
    //Note that this method will not be called directly from UConfigValueSection#InitializedFromProperty
    //Because there is no need to apply default values twice
    //It can be still called for resetting configuration value to default though
    UConfigValueSection* SectionValue = Cast<UConfigValueSection>(Value);
    if (SectionValue != NULL) {
        for (const FSectionProperty& Property : SectionProperties) {
            UConfigValue* ChildValue = SectionValue->GetValueForProperty(Property.Name);
            if (ChildValue != NULL) {
                Property.Property->ApplyDefaultPropertyValue(ChildValue);
            }
        }
    }
}

TSubclassOf<UConfigValue> UConfigPropertySection::GetValueClass_Implementation() const {
    return UConfigValueSection::StaticClass();
}

FConfigVariableDescriptor UConfigPropertySection::CreatePropertyDescriptor_Implementation(
    UConfigGenerationContext* Context, const FString& OuterPath) const {
    UConfigGeneratedStruct* GeneratedStruct = Context->CreateNewConfigStruct(OuterPath);
    for (const FSectionProperty& Property : SectionProperties) {
        const FString InnerPath = FString::Printf(TEXT("%s_%s"), *OuterPath, *Property.Name);
        const FConfigVariableDescriptor Descriptor = Property.Property->CreatePropertyDescriptor(Context, InnerPath);
        GeneratedStruct->AddConfigVariable(Descriptor, Property.Name);
    }
    return UConfigVariableLibrary::MakeConfigVariableGeneratedStruct(GeneratedStruct);
}

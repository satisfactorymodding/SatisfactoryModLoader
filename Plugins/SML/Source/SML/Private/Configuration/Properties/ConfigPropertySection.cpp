#include "Configuration/Properties/ConfigPropertySection.h"
#include "Configuration/CodeGeneration/ConfigGenerationContext.h"
#include "Configuration/CodeGeneration/ConfigVariableDescriptor.h"
#include "Configuration/CodeGeneration/ConfigVariableLibrary.h"
#include "Configuration/Values/ConfigValueSection.h"

void UConfigPropertySection::ApplyDefaultPropertyValue_Implementation(UConfigValue* Value) const {
    //Note that this method will not be called directly from UConfigValueSection#InitializedFromProperty
    //Because there is no need to apply default values twice
    //It can be still called for resetting configuration value to default though
    UConfigValueSection* SectionValue = Cast<UConfigValueSection>(Value);
    if (SectionValue != NULL) {
        for (const TPair<FString, UConfigProperty*>& Property : SectionProperties) {
            UConfigValue* ChildValue = SectionValue->GetValueForProperty(Property.Key);
            if (ChildValue != NULL) {
                Property.Value->ApplyDefaultPropertyValue(ChildValue);
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
    for (const TPair<FString, UConfigProperty*>& Property : SectionProperties) {
        const FString InnerPath = FString::Printf(TEXT("%s_%s"), *OuterPath, *Property.Key);
        const FConfigVariableDescriptor Descriptor = Property.Value->CreatePropertyDescriptor(Context, InnerPath);
        GeneratedStruct->AddConfigVariable(Descriptor, Property.Key);
    }
    return UConfigVariableLibrary::MakeConfigVariableGeneratedStruct(GeneratedStruct);
}

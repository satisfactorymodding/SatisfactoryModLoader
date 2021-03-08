#pragma once
#include "CoreMinimal.h"
#include "Configuration/CodeGeneration/ConfigGeneratedStruct.h"
#include "EdGraph/EdGraphPin.h"

class SMLEDITOR_API FUserDefinedStructCodeGenerator {

    /**
     * Generates user defined configuration struct inside of the given package name
     * From the provided context, and returns boolean indicating whenever it was successful or failure
     */
    static bool GenerateConfigurationStruct(const FString& PackageName, UConfigGenerationContext* Context);

    //Populates generated struct with variable declarations
    static void PopulateGeneratedStruct(UConfigGeneratedStruct* GeneratedStruct, class UUserDefinedStruct* UserStruct,
        const TMap<UConfigGeneratedStruct*, UUserDefinedStruct*>& GeneratedStructs);

    //Creates blueprint variable type for descriptor
    static FEdGraphPinType CreatePinTypeForVariable(const FConfigVariableDescriptor& Descriptor, const TMap<UConfigGeneratedStruct*, UUserDefinedStruct*>& GeneratedStructs);
};

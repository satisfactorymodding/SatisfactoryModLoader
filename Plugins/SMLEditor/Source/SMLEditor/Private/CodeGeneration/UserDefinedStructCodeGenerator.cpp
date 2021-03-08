#include "CodeGeneration/UserDefinedStructCodeGenerator.h"
#include "AssetToolsModule.h"
#include "EdGraphSchema_K2.h"
#include "FileHelpers.h"
#include "Configuration/CodeGeneration/ConfigGenerationContext.h"
#include "Engine/UserDefinedStruct.h"
#include "Factories/StructureFactory.h"
#include "UserDefinedStructure/UserDefinedStructEditorData.h"
#define LOCTEXT_NAMESPACE "SML"

bool FUserDefinedStructCodeGenerator::GenerateConfigurationStruct(const FString& PackageName, UConfigGenerationContext* Context) {
    //Load required modules and create factories for making new struct assets
    UStructureFactory* StructureFactory = NewObject<UStructureFactory>();
    FAssetToolsModule& Module = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
    IAssetTools& AssetTools = Module.Get();
    TMap<UConfigGeneratedStruct*, UUserDefinedStruct*> GeneratedStructs;
    TArray<UPackage*> PackagesToSave;
    
    //Generate asset for each struct we have
    for (UConfigGeneratedStruct* GeneratedStruct : Context->GetAllGeneratedStructs()) {
        UObject* AssetObject = AssetTools.CreateAsset(GeneratedStruct->GetStructName(), PackageName, NULL, StructureFactory);
        if (AssetObject == NULL) {
            FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("NameOccupied", "Couldn't create config struct due already existing asset with the same name"));
            return false;
        }
        UUserDefinedStruct* UserDefinedStruct = CastChecked<UUserDefinedStruct>(AssetObject);
        GeneratedStructs.Add(GeneratedStruct, UserDefinedStruct);
        PackagesToSave.Add(AssetObject->GetOutermost());
    }
    
    //Populate each struct generated with properties
    for (const TPair<UConfigGeneratedStruct*, UUserDefinedStruct*>& Pair : GeneratedStructs) {
        PopulateGeneratedStruct(Pair.Key, Pair.Value, GeneratedStructs);
    }
    
    //Remove dummy variable created as a part of structure initial creation
    for (const TPair<UConfigGeneratedStruct*, UUserDefinedStruct*>& Pair : GeneratedStructs) {
        UUserDefinedStruct* DefinedStruct = Pair.Value;
        const FStructVariableDescription& Description = FStructureEditorUtils::GetVarDesc(DefinedStruct)[0];
        FStructureEditorUtils::RemoveVariable(DefinedStruct, Description.VarGuid);
    }
    
    //Save packages that we just created
    FEditorFileUtils::PromptForCheckoutAndSave(PackagesToSave, /*bCheckDirty*/false, /*bPromptToSave*/false);
    return true;
}

void FUserDefinedStructCodeGenerator::PopulateGeneratedStruct(UConfigGeneratedStruct* GeneratedStruct, UUserDefinedStruct* UserStruct,
    const TMap<UConfigGeneratedStruct*, UUserDefinedStruct*>& GeneratedStructs) {
    //Generate each config variable
    for (const TPair<FString, FConfigVariableDescriptor>& Pair : GeneratedStruct->GetVariables()) {
        //Creates new variable with specified type
        const FEdGraphPinType GraphPin = CreatePinTypeForVariable(Pair.Value, GeneratedStructs);
        FStructureEditorUtils::AddVariable(UserStruct, GraphPin);
        
        //Rename variable to match display name specified earlier
        const FStructVariableDescription& Description = FStructureEditorUtils::GetVarDesc(UserStruct).Last();
        FStructureEditorUtils::RenameVariable(UserStruct, Description.VarGuid, Pair.Key);
    }
}

FEdGraphPinType FUserDefinedStructCodeGenerator::CreatePinTypeForVariable(const FConfigVariableDescriptor& Descriptor,
    const TMap<UConfigGeneratedStruct*, UUserDefinedStruct*>& GeneratedStructs) {

    const EConfigVariableType VariableType = Descriptor.GetVariableType();
    FEdGraphPinType GraphPinType{};
    
    if (VariableType == EConfigVariableType::ECVT_Bool) {
        GraphPinType.PinCategory = UEdGraphSchema_K2::PC_Boolean;
    }
    else if (VariableType == EConfigVariableType::ECVT_Float) {
        GraphPinType.PinCategory = UEdGraphSchema_K2::PC_Float;
    }
    else if (VariableType == EConfigVariableType::ECVT_Int32) {
        GraphPinType.PinCategory = UEdGraphSchema_K2::PC_Int;
    }
    else if (VariableType == EConfigVariableType::ECVT_Int64) {
        GraphPinType.PinCategory = UEdGraphSchema_K2::PC_Int64;
    }
    else if (VariableType == EConfigVariableType::ECVT_String) {
        GraphPinType.PinCategory = UEdGraphSchema_K2::PC_String;
    }
    else if (VariableType == EConfigVariableType::ECVT_Float) {
        GraphPinType.PinCategory = UEdGraphSchema_K2::PC_Float;
    }
    else if (VariableType == EConfigVariableType::ECVT_CustomStruct) {
        GraphPinType.PinCategory = UEdGraphSchema_K2::PC_Struct;
        GraphPinType.PinSubCategoryObject = Descriptor.GetCustomStructType();
    }
    else if (VariableType == EConfigVariableType::ECVT_ConfigGeneratedStruct) {
        GraphPinType.PinCategory = UEdGraphSchema_K2::PC_Struct;
        UUserDefinedStruct* MatchingStruct = GeneratedStructs.FindChecked(Descriptor.GetConfigGeneratedStruct());
        GraphPinType.PinSubCategoryObject = MatchingStruct;
    }
    else if (VariableType == EConfigVariableType::ECVT_Object) {
        GraphPinType.PinCategory = UEdGraphSchema_K2::PC_Object;
        UClass* BaseObjectClass = Descriptor.GetBaseObjectClass();
        GraphPinType.PinSubCategoryObject = BaseObjectClass ? BaseObjectClass : UObject::StaticClass();
    }
    else if (VariableType == EConfigVariableType::ECVT_Class) {
        GraphPinType.PinCategory = UEdGraphSchema_K2::PC_Class;
        UClass* BaseClassType = Descriptor.GetBaseClassType();
        GraphPinType.PinSubCategoryObject = BaseClassType ? BaseClassType : UClass::StaticClass();
    }
    else if (VariableType == EConfigVariableType::ECVT_Array) {
        FEdGraphPinType InnerGraphPinType = CreatePinTypeForVariable(Descriptor.GetArrayElementDescriptor(), GeneratedStructs);
        GraphPinType = InnerGraphPinType;
        GraphPinType.ContainerType = EPinContainerType::Array;
    }
    else if (VariableType == EConfigVariableType::ECVT_Map) {
        FEdGraphPinType KeyPinType = CreatePinTypeForVariable(Descriptor.GetMapKeyDescriptor(), GeneratedStructs);
        FEdGraphPinType ValuePinType = CreatePinTypeForVariable(Descriptor.GetMapValueDescriptor(), GeneratedStructs);
        GraphPinType = KeyPinType;
        GraphPinType.ContainerType = EPinContainerType::Map;
        GraphPinType.PinValueType = FEdGraphTerminalType::FromPinType(ValuePinType);
    }
    return GraphPinType;
}

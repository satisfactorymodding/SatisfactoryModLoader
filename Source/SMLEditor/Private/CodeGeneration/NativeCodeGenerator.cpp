#include "CodeGeneration/NativeCodeGenerator.h"
#include "Engine/UserDefinedStruct.h"
#include "UObject/Object.h"

bool FNativeCodeGenerator::CanGenerateNativeConfiguration(UConfigGenerationContext* Context, FString& OutFailureMessage) {
    for (UConfigGeneratedStruct* GeneratedStruct : Context->GetAllGeneratedStructs()) {
        for (const TPair<FString, FConfigVariableDescriptor>& Pair : GeneratedStruct->GetVariables()) {
            const FConfigVariableDescriptor Descriptor = Pair.Value;
            const EConfigVariableType VariableType = Descriptor.GetVariableType();
            if (VariableType == EConfigVariableType::ECVT_CustomStruct) {
                UScriptStruct* ScriptStruct = Descriptor.GetCustomStructType();
                if (Cast<UUserDefinedStruct>(ScriptStruct) != NULL) {
                    OutFailureMessage = TEXT("UserDefinedStruct is referenced in configuration");
                    return false;
                }
            }
            if (VariableType == EConfigVariableType::ECVT_Object) {
                UClass* BaseObjectClass = Descriptor.GetBaseObjectClass();
                if (BaseObjectClass != NULL && !BaseObjectClass->IsNative()) {
                    OutFailureMessage = TEXT("Blueprint class is referenced in configuration");
                    return false;
                }
            }
            if (VariableType == EConfigVariableType::ECVT_Class) {
                UClass* BaseClassType = Descriptor.GetBaseClassType();
                if (BaseClassType != NULL && !BaseClassType->IsNative()) {
                    OutFailureMessage = TEXT("Blueprint class is referenced in configuration");
                    return false;
                }
            }
        }
    }
    OutFailureMessage = TEXT("");
    return true;
}

void FNativeCodeGenerator::GenerateConfigurationCodeHeader(const FString& HeaderFileName, UConfigGenerationContext* Context, FOutputDevice& OutputDevice) {
    //Populate referenced classes data required for generating includes
    FReferencedClassesData ReferencedClasses;
    PopulateReferencedClasses(Context, ReferencedClasses);
    
    //Generate includes and pre-declarations first
    GenerateIncludesAndPredeclarations(HeaderFileName, ReferencedClasses, OutputDevice);

    //Sort structs in the level of their nesting
    TArray<UConfigGeneratedStruct*> GeneratedStructs = Context->GetAllGeneratedStructs();
    GeneratedStructs.StableSort([](const UConfigGeneratedStruct& First, const UConfigGeneratedStruct& Second){
        const int32 NestedCountFirst = GetNestedLevelOfStruct(&First);
        const int32 NestedCountSecond = GetNestedLevelOfStruct(&Second);
        return NestedCountFirst > NestedCountSecond;
    });
    
    //Generate each struct now
    for (UConfigGeneratedStruct* GeneratedStruct : GeneratedStructs) {
        GenerateConfigStruct(GeneratedStruct, OutputDevice);
    }
}

void FNativeCodeGenerator::GenerateConfigStruct(UConfigGeneratedStruct* Struct, FOutputDevice& OutputDevice) {
    //Open struct body, mark it as USTRUCT accessible in blueprints
    OutputDevice.Log(TEXT("USTRUCT(BlueprintType)"));
    OutputDevice.Logf(TEXT("struct F%s {"), *Struct->GetStructName());
    OutputDevice.Log(TEXT("    GENERATED_BODY()"));
    OutputDevice.Log(TEXT("public:"));

    //Generate each variable now
    for (const TPair<FString, FConfigVariableDescriptor>& Pair : Struct->GetVariables()) {
        //Determine C++ type for passed descriptor
        const FString CppTypeForDescriptor = GenerateCppTypeForVariable(Pair.Value);
        //Mark variable as BlueprintReadWrite for it to be accessible via BP limited reflection
        OutputDevice.Logf(TEXT("    UPROPERTY(BlueprintReadWrite)"));
        OutputDevice.Logf(TEXT("    %s %s;"), *CppTypeForDescriptor, *Pair.Key);
    }

    //Terminate struct body with closing bracket
    OutputDevice.Log(TEXT("};"));
}

FString FNativeCodeGenerator::GenerateCppTypeForVariable(const FConfigVariableDescriptor& Descriptor) {
    const EConfigVariableType VariableType = Descriptor.GetVariableType();
    if (VariableType == EConfigVariableType::ECVT_Int32) {
        return TEXT("int32");
    }
    if (VariableType == EConfigVariableType::ECVT_Int64) {
        return TEXT("int64");
    }
    if (VariableType == EConfigVariableType::ECVT_Float) {
        return TEXT("float");
    }
    if (VariableType == EConfigVariableType::ECVT_String) {
        return TEXT("FString");
    }
    if (VariableType == EConfigVariableType::ECVT_Bool) {
        return TEXT("bool");
    }
    if (VariableType == EConfigVariableType::ECVT_Array) {
        const FString InnerType = GenerateCppTypeForVariable(Descriptor.GetArrayElementDescriptor());
        return FString::Printf(TEXT("TArray<%s>"), *InnerType);
    }
    if (VariableType == EConfigVariableType::ECVT_Map) {
        const FString KeyType = GenerateCppTypeForVariable(Descriptor.GetMapKeyDescriptor());
        const FString ValueType = GenerateCppTypeForVariable(Descriptor.GetMapValueDescriptor());
        return FString::Printf(TEXT("TMap<%s, %s>"), *KeyType, *ValueType);
    }
    if (VariableType == EConfigVariableType::ECVT_ConfigGeneratedStruct) {
        UConfigGeneratedStruct* GeneratedStruct = Descriptor.GetConfigGeneratedStruct();
        const FString StructName = GeneratedStruct ? GeneratedStruct->GetStructName() : TEXT("Unknown");
        return FString::Printf(TEXT("F%s"), *StructName);
    }
    if (VariableType == EConfigVariableType::ECVT_CustomStruct) {
        UScriptStruct* CustomStruct = Descriptor.GetCustomStructType();
        if (CustomStruct == NULL) {
            CustomStruct = TBaseStructure<FLinearColor>::Get();
        }
        return FString::Printf(TEXT("%s%s"), CustomStruct->GetPrefixCPP(), *CustomStruct->GetName());
    }
    if (VariableType == EConfigVariableType::ECVT_Object) {
        UClass* BaseObjectClass = Descriptor.GetBaseObjectClass();
        if (BaseObjectClass == NULL) {
            BaseObjectClass = UObject::StaticClass();
        }
        const FString ClassName = FString::Printf(TEXT("%s%s"), BaseObjectClass->GetPrefixCPP(), *BaseObjectClass->GetName());
        return FString::Printf(TEXT("%s*"), *ClassName);
    }
    if (VariableType == EConfigVariableType::ECVT_Class) {
        UClass* BaseClassType = Descriptor.GetBaseClassType();
        if (BaseClassType == NULL || BaseClassType == UClass::StaticClass()) {
            //No lower limit is set or it is set to bare UClass, in which case we don't need TSubclassOf
            //And can just use raw UClass object pointer
            return TEXT("UClass*");
        }
        const FString ClassName = FString::Printf(TEXT("%s%s"), BaseClassType->GetPrefixCPP(), *BaseClassType->GetName());
        return FString::Printf(TEXT("TSubclassOf<%s>"), *ClassName);
    }
    checkf(false, TEXT("Unrechable code"));
    return TEXT("");
}

void FNativeCodeGenerator::GenerateIncludesAndPredeclarations(const FString& HeaderFileName, const FReferencedClassesData& ReferencedClasses, FOutputDevice& OutputDevice) {
    //Include pragma once and all the includes referenced
    OutputDevice.Log(TEXT("#pragma once"));
    OutputDevice.Log(TEXT("#include \"CoreMinimal.h\""));
    if (ReferencedClasses.bUsedClassPropertyWithLimitedType) {
        OutputDevice.Log(TEXT("#include \"SubclassOf.h\""));
    }
    TArray<FString> AllIncludePaths;
    for (UStruct* ReferencedClass : ReferencedClasses.ReferencedClasses) {
        FString IncludePath = GetIncludePathForClass(ReferencedClass);
        //We can get duplicates since multiple objects can be defined in one header file
        AllIncludePaths.AddUnique(IncludePath);
    }
    for (const FString& IncludePath : AllIncludePaths) {
        OutputDevice.Logf(TEXT("#include \"%s\""), *IncludePath);
    }
    //Generated include should always be the last include in the file
    OutputDevice.Logf(TEXT("#include \"%s.generated.h\""), *HeaderFileName);

    //Include an empty line between includes and pre-declarations
    OutputDevice.Log(TEXT(""));

    //Include pre-declarations
    for (const FString& ConfigStruct : ReferencedClasses.ReferencedGeneratedStructs) {
        OutputDevice.Logf(TEXT("struct F%s"), *ConfigStruct);
    }
}

void FNativeCodeGenerator::PopulateReferencedClasses(UConfigGenerationContext* Context, FReferencedClassesData& ReferencedClasses) {
    for (UConfigGeneratedStruct* GeneratedStruct : Context->GetAllGeneratedStructs()) {
        for (const TPair<FString, FConfigVariableDescriptor>& Pair : GeneratedStruct->GetVariables()) {
            const FConfigVariableDescriptor& VariableDescriptor = Pair.Value;
            AddReferencedVariable(VariableDescriptor, ReferencedClasses);
        }
    }
}

FString FNativeCodeGenerator::GetIncludePathForClass(UStruct* Class) {
    //We cannot use "IncludePath" metadata attribute here because it's not added for UScriptStruct,
    //and object we have as argument can be either UClass or UScriptStruct, or maybe even UEnum if we decide to
    //support them at some point. However, "ModuleRelativePath" is present on all of these objects,
    //and even on function and property objects. According to UHT source, only difference
    //between these two is that include path has Public/Private/Classes prefixes stripped. We can
    //mimic that behavior and get uniform include paths for all defined objects

    FString IncludePath = Class->GetMetaData(TEXT("ModuleRelativePath"));
    checkf(!IncludePath.IsEmpty(), TEXT("ModuleRelativePath metadata not found on object %s"), *Class->GetPathName());
    // Walk over the first potential slash
    if (IncludePath.StartsWith(TEXT("/"))) {
        IncludePath.RemoveAt(0);
    }
    // Does this module path start with a known include path location? If so, we can cut that part out of the include path
    static const TCHAR PublicFolderName[]  = TEXT("Public/");
    static const TCHAR PrivateFolderName[] = TEXT("Private/");
    static const TCHAR ClassesFolderName[] = TEXT("Classes/");
    if (IncludePath.StartsWith(PublicFolderName)) {
        IncludePath.RemoveAt(0, ARRAY_COUNT(PublicFolderName) - 1);
    }
    if (IncludePath.StartsWith(PrivateFolderName)) {
        IncludePath.RemoveAt(0, ARRAY_COUNT(PrivateFolderName) - 1);
    }
    if (IncludePath.StartsWith(ClassesFolderName)) {
        IncludePath.RemoveAt(0, ARRAY_COUNT(ClassesFolderName) - 1);
    }
    return IncludePath;
}

int FNativeCodeGenerator::GetNestedLevelOfStruct(const UConfigGeneratedStruct* Struct) {
    const FString& StructName = Struct->GetStructName();
    int32 NumUnderscores = 0;
    for (int32 i = 0; i < StructName.Len(); i++) {
        if (StructName[i] == TEXT('_'))
            NumUnderscores++;
    }
    return NumUnderscores;
}

void FNativeCodeGenerator::AddReferencedVariable(const FConfigVariableDescriptor& Descriptor, FReferencedClassesData& ReferencedClasses) {
    const EConfigVariableType VariableType = Descriptor.GetVariableType();
    if (VariableType == EConfigVariableType::ECVT_ConfigGeneratedStruct) {
        //Config generated struct needs pre-declaration to be referenced
        UConfigGeneratedStruct* GeneratedStruct = Descriptor.GetConfigGeneratedStruct();
        if (GeneratedStruct != NULL) {
            ReferencedClasses.ReferencedGeneratedStructs.Add(GeneratedStruct->GetStructName());
        }
    }
    else if (VariableType == EConfigVariableType::ECVT_CustomStruct) {
        //Custom structure needs import too, unless it is BP struct, but we shouldn't encounter BP structs
        UScriptStruct* ReferencedStruct = Descriptor.GetCustomStructType();
        if (ReferencedStruct != NULL) {
            checkf(Cast<UUserDefinedStruct>(ReferencedStruct) == NULL, TEXT("User defined structs are not supported"));
            ReferencedClasses.ReferencedClasses.Add(ReferencedStruct);
        }
    }
    else if (VariableType == EConfigVariableType::ECVT_Object) {
        UClass* BaseObjectClass = Descriptor.GetBaseObjectClass();
        if (BaseObjectClass != NULL) {
            checkf(BaseObjectClass->IsNative(), TEXT("Non-native classes are not supported"));
            ReferencedClasses.ReferencedClasses.Add(BaseObjectClass);
        }
    }
    else if (VariableType == EConfigVariableType::ECVT_Class) {
        UClass* BaseClassType = Descriptor.GetBaseClassType();
        if (BaseClassType != NULL) {
            checkf(BaseClassType->IsNative(), TEXT("Non-native classes are not supported"));
            ReferencedClasses.ReferencedClasses.Add(BaseClassType);
        }
        if (BaseClassType != UClass::StaticClass()) {
            ReferencedClasses.bUsedClassPropertyWithLimitedType = true;
        }
    }
}


#pragma once
#include "CoreMinimal.h"
#include "KismetIntermediateFormat.h"
#include "Json.h"

/**
 * Handles transformation of kismet bytecode into the intermediate format
 * To aid with decompilation and represent bytecode in a format closer to the source text
 */
class SMLEDITOR_API FKismetBytecodeTransformer {
public:
    FKismetBytecodeTransformer();
    void SetSourceStatements(const TArray<TSharedPtr<FJsonObject>>& Statements);
    void FinishGeneration();
private:
    static bool IsContextExpression(const FString& InstructionName);
    static bool IsCallFunctionInstruction(const FString& InstructionName);
    static bool IsCallFunctionInstruction(TSharedPtr<FJsonObject> Expression);
    
    TSharedPtr<FKismetCompiledStatement> ProcessStatement(TSharedPtr<FJsonObject> Statement);
    TSharedPtr<FKismetTerminal> ProcessExpression(TSharedPtr<FJsonObject> Expression);
    TSharedPtr<FKismetCompiledStatement> ProcessFunctionCallStatement(TSharedPtr<FJsonObject> Statement);
    TSharedPtr<FKismetTerminal> ResolveContext(TSharedPtr<FJsonObject> Expression, TSharedPtr<FJsonObject>& OutResultExpression, bool& bOutIsInterfaceContext);
    UFunction* ResolveFunctionByNameFromContext(TSharedPtr<FKismetTerminal> Context, const FString& FunctionName);
    
    TMap<int32, TSharedPtr<FKismetCompiledStatement>> StatementsByOffset;
    TArray<TSharedPtr<FKismetCompiledStatement>> ResultStatements;

    //Map of patch-ups to apply to target labels after all expressions have been parsed
    //It will convert int32 offsets in bytecode to absolute statement references
    //It might also end up converting statement type if referenced statement is happens to be Return
    //then jump is converted to KCST_GotoReturn
    TMap<TSharedPtr<FKismetCompiledStatement>, int32> JumpPatchUpTable;
};
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
    /** Class specified by this string should exist and be loadable for EX_Self resolution */
    FKismetBytecodeTransformer(const FString& SelfClassPath);

    /** Begins statement generation by populating transformer with serialized bytecode */
    void SetSourceStatements(const TArray<TSharedPtr<FJsonObject>>& Statements);

    /** Finishes generation and returns result statements */
    TArray<TSharedPtr<FKismetCompiledStatement>> FinishGeneration();
private:
    /** Class path of the class this bytecode belongs to. Should exist and be populated with function stubs */
    FString SelfClassPath;
    
    static bool IsContextInstruction(const FString& InstructionName);
    static bool IsCallFunctionInstruction(const FString& InstructionName);
    static bool IsVariableInstruction(const FString& InstructionName);
    
    TSharedPtr<FKismetCompiledStatement> ProcessStatement(TSharedPtr<FJsonObject> Statement);
    TSharedPtr<FKismetTerminal> ProcessExpression(TSharedPtr<FJsonObject> Expression);
    TSharedPtr<FKismetTerminal> ProcessLiteralExpression(TSharedPtr<FJsonObject> Expression, bool bIsDelimited);
    TSharedPtr<FKismetCompiledStatement> ProcessFunctionCallStatement(TSharedPtr<FJsonObject> Statement);
    TSharedPtr<FKismetTerminal> ProcessFunctionParameter(TSharedPtr<FJsonObject> Expression);

    TMap<int32, TSharedPtr<FKismetCompiledStatement>> StatementsByOffset;
    TArray<TSharedPtr<FKismetCompiledStatement>> ResultStatements;

    //Map of patch-ups to apply to target labels after all expressions have been parsed
    //It will convert int32 offsets in bytecode to absolute statement references
    //It might also end up converting statement type if referenced statement is happens to be Return
    //then jump is converted to KCST_GotoReturn
    TMap<TSharedPtr<FKismetCompiledStatement>, int32> JumpPatchUpTable;
};
#pragma once

#include "CoreMinimal.h"
#include "HookingTargetSpecifier.h"
#include "Patching/BlueprintHookingTypes.h"

struct FHookCodeGenInsertionHookData {
	UFunction* TargetFunctionOrEvent{};
	TSharedPtr<FScriptExpr> TargetFunctionOrEventReturnStatement;
	TSharedPtr<FScriptExpr> TargetStatement;
	TArray<TSharedPtr<FScriptExpr>> TargetExpressions;
	UFunction* HookFunction{};
};
struct FHookCodeGenRedirectHookData {
	UFunction* TargetFunctionOrEvent{};
	UFunction* HookFunction{};
};

struct FHookCodeGenParameterDescriptor {
	FProperty* ParameterProperty{};
};

struct FHookCodeGenStatementModificationData {
	TArray<FHookCodeGenInsertionHookData> InsertBeforeHooks;
	TOptional<FHookCodeGenInsertionHookData> ReplacementHook;
	TArray<FHookCodeGenInsertionHookData> InsertAfterHooks;
	TMap<TSharedPtr<FScriptExpr>, TArray<FHookCodeGenRedirectHookData>> ExpressionToRedirectHooks;
};

/**
 * Handles hooking-related code generation for a provided function. Applies all hooks and returns new function code
 */
class SML_API FHookCodeGenFunctionContext {
protected:
	UFunction* OwnerFunction{};
	TArray<TSharedPtr<FScriptExpr>> FunctionScript;
	TSharedPtr<FScriptExpr> FunctionReturnStatement;
	bool bIsUberGraphFunction{false};
	TMap<UFunction*, TPair<TArray<TSharedPtr<FScriptExpr>>, TSharedPtr<FScriptExpr>>> EventFunctionToReachableStatements;
	TMap<TSharedPtr<FScriptExpr>, TSharedPtr<FScriptExpr>> EventFunctionStatementToSyntheticReturnStatement;
	TMap<UFunction*, TSharedPtr<FScriptExpr>> EventGraphEventToEntryPoint;
	TSet<TSharedPtr<FScriptExpr>> EventGraphEntryPointStatements;
	TMap<TSharedPtr<FScriptExpr>, FHookCodeGenStatementModificationData> StatementToHookModificationData;
	TArray<TSharedPtr<FScriptExpr>> SyntheticReturnStatements;
	TMap<UFunction*, TMap<FName, FProperty*>> EventGraphEventToParameterNameToUbergraphStackFrameProperty;
	bool bFunctionUsesFlowStack{false};
public:
	/** Initializes the function context with the provided function and its script */
	FHookCodeGenFunctionContext(UFunction* OwnerFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript);

	/** Called to populate the ubergraph function context with the entry points to the ubergraph from other functions */
	void InitializeUbergraphFunction(const TMap<UFunction*, TSharedPtr<FScriptExpr>>& UberGraphEventEntryPoints, const TMap<UFunction*, TArray<TSharedPtr<FScriptExpr>>>& EventFunctionToEventStubScript);

	/** Attempts to resolve the targets of the provided hooks in this function, and prepare them for application */
	void ResolveHookTargets(const TArray<FBlueprintHookDefinition>& Hooks);

	/** Generate new function code for this function by applying the previously resolved hooks. Returns true if all hooks have been installed successfully */
	bool GenerateFunctionCode(TArray<TSharedPtr<FScriptExpr>>& OutFunctionScript, TMap<UFunction*, TSharedPtr<FScriptExpr>>& OutUberGraphEventEntryPoints);
protected:
	/** Generates a common function invocation expression using the provided parameter generator. Will make sure that parameter types are valid */
	static TSharedPtr<FScriptExpr> GenerateStaticFunctionInvocationExpression(UFunction* CallTarget, UClass* OuterFunctionUClass, const TFunctionRef<TSharedPtr<FScriptExpr>(FProperty*)>& ParameterExpressionGenerator);

	/** Generates expression to populate the hook parameter with data available during the function execution */
	TSharedPtr<FScriptExpr> GenerateFunctionOrObjectContextHookParameterValue(UFunction* OwnerFunctionOrEvent, const FHookCodeGenParameterDescriptor& ParameterDescriptor) const;
	
	/** Generates insertion hook invocation and appends it to the output script */
	bool GenerateInsertionHookInvocation(const FHookCodeGenInsertionHookData& HookData, TArray<TSharedPtr<FScriptExpr>>& OutGeneratedStatements) const;

	/** Generates redirection hook invocation that wraps the original (redirected) expression */
	TSharedPtr<FScriptExpr> GenerateRedirectHookInvocation(const FHookCodeGenRedirectHookData& HookData, const TSharedPtr<FScriptExpr>& RedirectedExpression) const;

	/** Recursively applies redirect hooks to the provided expression and its subexpressions */
	TSharedPtr<FScriptExpr> ProcessExpressionTreeWithRedirectHooks(const FHookCodeGenStatementModificationData& StatementData, const TSharedPtr<FScriptExpr>& Expression, const TSharedPtr<FScriptExpr>& ExpressionContext);
public:
	/** Returns true if it is currently safe to modify function code [and local variable frame layout] */
	static bool CheckCanModifyFunctionScriptAndLocals(const UFunction* TargetFunction, bool bCheckLocalVariableModification);
};

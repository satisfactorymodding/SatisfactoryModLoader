#pragma once

#include "CoreMinimal.h"
#include "ScriptExprAssembler.h"

class FScriptExprType;

/** Helpers for working with expressions */
class SML_API FScriptExprHelper {
public:
	/** Recursively iterates all expressions in the list and their sub-expressions */
	template<typename InLambdaT>
	FORCEINLINE static void ForEachExpressionInListRecursive(const TArray<TSharedPtr<FScriptExpr>>& LinearExecutionList, InLambdaT InLambda) {
		for (const TSharedPtr<FScriptExpr>& Statement : LinearExecutionList) {
			Statement->ForEachExpressionRecursive(InLambda);
		}
	}

	/** Explodes the linear execution list and returns an array containing all the statements and their sub-expressions */
	FORCEINLINE static TArray<TSharedPtr<FScriptExpr>> ExplodeExpressionList(const TArray<TSharedPtr<FScriptExpr>>& LinearExecutionList) {
		TArray<TSharedPtr<FScriptExpr>> ResultExpressionList;
		ResultExpressionList.Reserve(LinearExecutionList.Num() * 2);
		ForEachExpressionInListRecursive(LinearExecutionList, [&](const TSharedPtr<FScriptExpr>& Expr) {
			ResultExpressionList.Add(Expr);
		});
		return ResultExpressionList;
	}

	/** Looks for the first top level statement of the given type and returns it. Returns nullptr if not found */
	FORCEINLINE static TSharedPtr<FScriptExpr> FindFirstStatementOfType(const TArray<TSharedPtr<FScriptExpr>>& LinearExecutionList, uint8 InOpcode) {
		for (const TSharedPtr<FScriptExpr>& Statement : LinearExecutionList) {
			if (Statement->Opcode == InOpcode) {
				return Statement;
			}
		}
		return nullptr;
	}

	/** Returns a statement at the specified script offset */
	static TSharedPtr<FScriptExpr> FindStatementByScriptOffset(const TArray<TSharedPtr<FScriptExpr>>& LinearExecutionSequence, int32 ScriptOffset);

	/** Returns an effective value of a constant expression. This function will return a value even for special case constants like EX_IntZero or EX_True */
	static FScriptExprOperand GetSimpleConstantEffectiveValue(const TSharedPtr<FScriptExpr>& SimpleConstantExpr);
	
	/** Attempts to implicitly convert expression to the provided type. Returns nullptr if that is not possible. Only implicit conversions allowed are derived-to-base and range extension, so that no information is lost */
	static TSharedPtr<FScriptExpr> ImplicitlyConvertExpressionToType(const TSharedPtr<FScriptExpr>& Expression, UClass* OuterUFunctionClass, const TSharedPtr<FScriptExprType>& CoercePropertyType);

	/** Makes sure that the provided expression exactly matches the expected type */
	static TSharedPtr<FScriptExpr> ConformExpressionToType(const TSharedPtr<FScriptExpr>& Expression, UClass* OuterUFunctionClass, const TSharedPtr<FScriptExprType>& ExpectedType);

	/** Returns the function that is a target of the provided function call expression */
	static UFunction* GetFunctionCallTarget(const TSharedPtr<FScriptExpr>& FunctionCallExpression, UClass* OuterUFunctionClass);
	
	/** If the expression provided is an expression that yields (or could yield) a UObject, returns the most specified type of that object */
	static UClass* GetObjectExpressionResultType(const TSharedPtr<FScriptExpr>& Expression, UClass* OuterUFunctionClass, bool bAllowInterfaceClass = false);
	
	/**
	 * If the expression in question is an LValue property reference, retrieves the type of that property.
	 * This only works for expressions that write MostRecentPropertyAddress, e.g. Property Opcodes, EX_ArrayGetByRef and EX_StructMemberOffset.
	 * Context expressions are also supported if they ultimately wrap the expression type specified above
	 */
	static FProperty* GetExpressionDestPropertyType(const TSharedPtr<FScriptExpr>& Expression);

	/** Returns the LHS of the assignment statement. Note that EX_LetValueOnPersistentFrame will return nullptr because LHS expression is implicit and there is no Script VM bytecode to represent it */
	static TSharedPtr<FScriptExpr> GetAssignmentStatementLHS(const TSharedPtr<FScriptExpr>& AssignmentStatement);

	/** Returns the LHS of the single assignment statement. This only works for single assignment statements, not for array, set or map assignments */
	static TSharedPtr<FScriptExpr> GetSingleAssignmentStatementRHS(const TSharedPtr<FScriptExpr>& AssignmentStatement);
	
	/** Wraps the expression with a context expression that ensures that it will always run under the original Stack.Object context */
	static TSharedPtr<FScriptExpr> WrapExpressionWithDefaultContext(const TSharedPtr<FScriptExpr>& Expression);

	/** If the provided expression represents a chain of contexts, this returns the outermost non-context expression */
	static TSharedPtr<FScriptExpr> UnwrapExpressionContextChain(const TSharedPtr<FScriptExpr>& Expression);

	/**
	 * Extracts the expression so that it does not depend on its current surrounding context.
	 * This will, essentially, return the same expression potentially prefixed with EX_Context to make sure it runs in the correct context
	 * The return value is always a copy of the expression and any outer expressions
	 */
	static TSharedPtr<FScriptExpr> ExtractExpressionFromContext(const TSharedPtr<FScriptExpr>& Expression);

	/** Returns the innermost outer context expression that is used as a context for evaluating the provided expression. Returns nullptr if there is no context */
	static TSharedPtr<FScriptExpr> GetOuterContextSwitchExpression(const TSharedPtr<FScriptExpr>& Expression);

	/** Returns true if the provided expression and all of its sub expressions are pure */
	static bool IsExpressionPure(const TSharedPtr<FScriptExpr>& Expression);

	/** Performs a reachability analysis on the provided linear execution sequence, finding all statements rechable from the provided entry point statement */
	static void PerformReachabilityAnalysis(const TArray<TSharedPtr<FScriptExpr>>& LinearExecutionSequence, const TSharedPtr<FScriptExpr>& EntryPoint, TArray<TSharedPtr<FScriptExpr>>& OutReachableStatements);

	/** Dumps function code, flags and local variables to string builder */
	static void DumpFunctionToString(const UFunction* Function, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, int32 IndentLevel, FStringBuilderBase& StringBuilder);

	/** Dumps class to string builder */
	static void DumpClassToString(const UClass* Class, FStringBuilderBase& StringBuilder);
};

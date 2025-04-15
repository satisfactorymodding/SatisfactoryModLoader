#include "Toolkit/HookingTargetSpecifier.h"
#include "Toolkit/ScriptExprClassification.h"
#include "Toolkit/ScriptExprHelper.h"
#include "UObject/Script.h"
#include "UObject/Class.h"

FBlueprintHookTargetResolver_Constant::FBlueprintHookTargetResolver_Constant(uint8 InConstantOpcode, const FScriptExprOperand& InConstantValue, double InFloatEpsilon) : ConstantOpcode(InConstantOpcode), ConstantValue(InConstantValue), FloatEpsilon(InFloatEpsilon) {
}

TSharedPtr<FBlueprintHookTargetResolver> FBlueprintHookTargetResolver_Constant::CreateIntConstant(int64 InIntegerValue) {
	return MakeShared<FBlueprintHookTargetResolver_Constant>(EX_Int64Const, InIntegerValue);
}
TSharedPtr<FBlueprintHookTargetResolver> FBlueprintHookTargetResolver_Constant::CreateUIntConstant(uint64 InIntegerValue) {
	return MakeShared<FBlueprintHookTargetResolver_Constant>(EX_UInt64Const, InIntegerValue);
}

TSharedPtr<FBlueprintHookTargetResolver> FBlueprintHookTargetResolver_Constant::CreateNameConstant(const FName& InNameValue) {
	return MakeShared<FBlueprintHookTargetResolver_Constant>(EX_NameConst, NameToScriptName(InNameValue));
}
TSharedPtr<FBlueprintHookTargetResolver> FBlueprintHookTargetResolver_Constant::CreateStringConstant(const FString& InStringValue) {
	return MakeShared<FBlueprintHookTargetResolver_Constant>(EX_StringConst, InStringValue);
}

TSharedPtr<FBlueprintHookTargetResolver> FBlueprintHookTargetResolver_Constant::CreateDoubleConstant(double InFloatValue, double InFloatEpsilon) {
	return MakeShared<FBlueprintHookTargetResolver_Constant>(EX_DoubleConst, InFloatValue, InFloatEpsilon);
}
TSharedPtr<FBlueprintHookTargetResolver> FBlueprintHookTargetResolver_Constant::CreateObjectConstant(const UObject* InObjectValue) {
	return MakeShared<FBlueprintHookTargetResolver_Constant>(EX_ObjectConst, const_cast<UObject*>(InObjectValue));
}

void FBlueprintHookTargetResolver_Constant::ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const {
	for (const TSharedPtr<FScriptExpr>& Statement : FunctionScript) {
		Statement->ForEachExpressionRecursive([&](const TSharedPtr<FScriptExpr>& Expression) {
			if ((Expression->Opcode == EX_NameConst && ConstantValue.Type == FScriptExprOperand::TypeScriptName) ||
				((Expression->Opcode == EX_StringConst || Expression->Opcode == EX_UnicodeStringConst) && ConstantValue.Type == FScriptExprOperand::TypeString) ||
				(Expression->Opcode == EX_ObjectConst && ConstantValue.Type == FScriptExprOperand::TypeObject) ||
				((Expression->Opcode == EX_FloatConst || Expression->Opcode == EX_DoubleConst) && ConstantValue.Type == FScriptExprOperand::TypeFloat) ||
				(FScriptExprClassification::IsIntConstantOpcode(Expression->Opcode) && ConstantValue.Type == FScriptExprOperand::TypeInteger)) {

				// Retrieve the effective operand. This will give us the operand even for opcodes like EX_IntZero which technically do not have an operand
				const FScriptExprOperand ExpressionConstantValue = FScriptExprHelper::GetSimpleConstantEffectiveValue(Expression);
				if (ConstantValue.Type != FScriptExprOperand::TypeFloat) {
					if (ExpressionConstantValue == ConstantValue) {
						OutTargetExpressions.Add(Expression);
					}
				} else {
					// If this is a floating point constant, we want to compare using epsilon and not by doing exact equality check
					if (FMath::Abs(ExpressionConstantValue.Float - ConstantValue.Float) <= FloatEpsilon) {
						OutTargetExpressions.Add(Expression);
					}
				}
			}
		});
	}
}

FBlueprintHookTargetResolver_FunctionCall::FBlueprintHookTargetResolver_FunctionCall(UFunction* InFunctionCallTarget) : FunctionCallTarget(InFunctionCallTarget) {
}

void FBlueprintHookTargetResolver_FunctionCall::ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const {
	FScriptExprHelper::ForEachExpressionInListRecursive(FunctionScript, [&](const TSharedPtr<FScriptExpr>& StatementOrExpression) {
		if (FScriptExprClassification::IsFunctionCallOpcode(StatementOrExpression->Opcode)) {
			UFunction* ExprFunctionCallTarget = FScriptExprHelper::GetFunctionCallTarget(StatementOrExpression, TargetFunction->GetOuterUClass());
			if (ExprFunctionCallTarget && ExprFunctionCallTarget == FunctionCallTarget) {
				OutTargetExpressions.Add(StatementOrExpression);
			}
		}
	});
}

FBlueprintHookTargetResolver_PropertyAccess::FBlueprintHookTargetResolver_PropertyAccess(FProperty* InPropertyTarget) : PropertyTarget(InPropertyTarget) {
}

void FBlueprintHookTargetResolver_PropertyAccess::ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const {
	for (const TSharedPtr<FScriptExpr>& Statement : FunctionScript) {
		Statement->ForEachExpressionRecursive([&](const TSharedPtr<FScriptExpr>& Expression) {
			if (FScriptExprClassification::IsPropertyOpcode(Expression->Opcode)) {
				const FProperty* PropertyReadTarget = FScriptExprHelper::GetExpressionDestPropertyType(Expression);
				// Target the property read as long as it is not a right hand side of an impure assignment
				if (PropertyReadTarget && PropertyReadTarget == PropertyTarget) {
					OutTargetExpressions.Add(Expression);
				}
			}
		});
	}
}

FBlueprintHookTargetResolver_PropertySingleAssignment::FBlueprintHookTargetResolver_PropertySingleAssignment(FProperty* InPropertyTarget) : PropertyTarget(InPropertyTarget) {
}

void FBlueprintHookTargetResolver_PropertySingleAssignment::ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const {
	for (const TSharedPtr<FScriptExpr>& Statement : FunctionScript) {
		// Target single property assignment statements only, so skip set, map and array initializers, as well as delegate binds
		if (FScriptExprClassification::IsSingleAssignmentOpcode(Statement->Opcode)) {
			const TSharedPtr<FScriptExpr> AssignmentLeftSide = FScriptExprHelper::GetAssignmentStatementLHS(Statement);
			const FProperty* PropertyWriteTarget = FScriptExprHelper::GetExpressionDestPropertyType(AssignmentLeftSide);
			// Target the property assignment right side
			if (PropertyWriteTarget && PropertyWriteTarget == PropertyTarget) {
				if (const TSharedPtr<FScriptExpr>& AssignmentRightSide = FScriptExprHelper::GetSingleAssignmentStatementRHS(Statement)) {
					OutTargetExpressions.Add(AssignmentRightSide);	
				}
			}
		}
	}
}

void FBlueprintHookTargetResolver_ReturnValue::ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const {
	// Do not target synthetic return statements in ubergraph, in that case the opcode would be EX_Jump and not EX_Return
	if (ReturnStatement && ReturnStatement->Opcode == EX_Return) {
		const TSharedPtr<FScriptExpr> ReturnExpression = ReturnStatement->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
		// Make sure not to target EX_Nothing return expression in functions that do not actually return any value
		if (ReturnExpression && ReturnExpression->Opcode != EX_Nothing) {
			OutTargetExpressions.Add(ReturnExpression);
		}
	}
}

void FBlueprintHookTargetResolver_FunctionExit::ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const {
	if (ReturnStatement) {
		OutTargetExpressions.Add(ReturnStatement);
	}
}

void FBlueprintHookTargetResolver_FunctionEntry::ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const {
	if (!FunctionScript.IsEmpty()) {
		OutTargetExpressions.Add(FunctionScript[0]);
	}
}

FBlueprintHookTargetResolver_OuterExpression::FBlueprintHookTargetResolver_OuterExpression(const TSharedPtr<FBlueprintHookTargetResolver>& InInnerExpression) : InnerExpression(InInnerExpression) {
}

void FBlueprintHookTargetResolver_OuterExpression::ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const {
	// Evaluate inner expression first
	TArray<TSharedPtr<FScriptExpr>> ResolvedParentExpressions;
	if (InnerExpression) {
		InnerExpression->ResolveTargets(TargetFunction, FunctionScript,	ReturnStatement, ResolvedParentExpressions);
	}

	// Return outers of expressions that are not statements
	for (const TSharedPtr<FScriptExpr>& TargetExpression : ResolvedParentExpressions) {
		if (const TSharedPtr<FScriptExpr> OuterExpression = TargetExpression->OuterExpression.Pin()) {
			OutTargetExpressions.Add(OuterExpression);
		}
	}
}

FBlueprintHookTargetResolver_ExpressionOperand::FBlueprintHookTargetResolver_ExpressionOperand(const TSharedPtr<FBlueprintHookTargetResolver>& InInnerExpression, const int32 InOperandIndex) : InnerExpression(InInnerExpression), OperandIndex(InOperandIndex) {
}

void FBlueprintHookTargetResolver_ExpressionOperand::ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const {
	// Evaluate inner expression first
	TArray<TSharedPtr<FScriptExpr>> ResolvedParentExpressions;
	if (InnerExpression) {
		InnerExpression->ResolveTargets(TargetFunction, FunctionScript,	ReturnStatement, ResolvedParentExpressions);
	}

	// Return operands at the specified index for each expression
	for (const TSharedPtr<FScriptExpr>& TargetExpression : ResolvedParentExpressions) {
		// Find all expression operands for that expression
		TArray<TSharedPtr<FScriptExpr>> ExpressionOperands;
		for (const FScriptExprOperand& Operand : TargetExpression->Operands) {
			if (Operand.Type == FScriptExprOperand::TypeExpr && Operand.Expr) {
				ExpressionOperands.Add(Operand.Expr);
			}
		}

		// If we have one at the specified index, target it
		if (ExpressionOperands.IsValidIndex(OperandIndex)) {
			OutTargetExpressions.Add(ExpressionOperands[OperandIndex]);
		}
	}
}

FBlueprintHookTargetResolver_TargetSelectionMode::FBlueprintHookTargetResolver_TargetSelectionMode(const TSharedPtr<FBlueprintHookTargetResolver>& InInnerExpression, EBlueprintFunctionHookTargetSelectionMode InTargetSelectionMode, int32 InCustomOrdinal) :
	InnerExpression(InInnerExpression), TargetSelectionMode(InTargetSelectionMode), CustomOrdinal(InCustomOrdinal) {
}

void FBlueprintHookTargetResolver_TargetSelectionMode::ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const {
	// Evaluate inner expression first
	TArray<TSharedPtr<FScriptExpr>> ResolvedParentExpressions;
	if (InnerExpression) {
		InnerExpression->ResolveTargets(TargetFunction, FunctionScript,	ReturnStatement, ResolvedParentExpressions);
	}
	// Apply target selection mode
	OutTargetExpressions.Append(ApplyTargetSelectionMode(TargetSelectionMode, CustomOrdinal, ResolvedParentExpressions));
}

TArray<TSharedPtr<FScriptExpr>> FBlueprintHookTargetResolver_TargetSelectionMode::ApplyTargetSelectionMode(const EBlueprintFunctionHookTargetSelectionMode SelectionMode, const int32 TargetOrdinal, const TArray<TSharedPtr<FScriptExpr>>& TargetExpressions) {
	TArray<TSharedPtr<FScriptExpr>> ResultTargetExpressions;
	// Exit early if we have no target expressions
	if (TargetExpressions.IsEmpty()) {
		return ResultTargetExpressions;
	}

	// Calculate the final target expression list
	if (SelectionMode == EBlueprintFunctionHookTargetSelectionMode::First) {
		ResultTargetExpressions.Add(TargetExpressions[0]);
	} else if (SelectionMode == EBlueprintFunctionHookTargetSelectionMode::Last) {
		ResultTargetExpressions.Add(TargetExpressions.Last());
	} else if (SelectionMode == EBlueprintFunctionHookTargetSelectionMode::Ordinal) {
		if (TargetExpressions.IsValidIndex(TargetOrdinal)) {
			ResultTargetExpressions.Add(TargetExpressions[TargetOrdinal]);
		}
	} else if (SelectionMode == EBlueprintFunctionHookTargetSelectionMode::All) {
		ResultTargetExpressions.Append(TargetExpressions);
	} else if (SelectionMode == EBlueprintFunctionHookTargetSelectionMode::Single) {
		if (TargetExpressions.Num() == 1) {
			ResultTargetExpressions.Add(TargetExpressions[0]);
		}
	}
	return ResultTargetExpressions;
}

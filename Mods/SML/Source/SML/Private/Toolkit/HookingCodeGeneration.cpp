#include "Toolkit/HookingCodeGeneration.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Toolkit/ScriptExprAssembler.h"
#include "Toolkit/ScriptExprClassification.h"
#include "Toolkit/ScriptExprHelper.h"
#include "Toolkit/ScriptExprTypeResolver.h"
#include "UObject/UnrealType.h"

DEFINE_LOG_CATEGORY_STATIC(LogBlueprintHookingCodeGen, All, All);

FHookCodeGenFunctionContext::FHookCodeGenFunctionContext(UFunction* OwnerFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript) : OwnerFunction(OwnerFunction), FunctionScript(FunctionScript) {
	FunctionReturnStatement = FScriptExprHelper::FindFirstStatementOfType(FunctionScript, EX_Return);
	bFunctionUsesFlowStack = !FunctionScript.IsEmpty() && FunctionScript[0]->Opcode == EX_PushExecutionFlow;
}

void FHookCodeGenFunctionContext::InitializeUbergraphFunction(const TMap<UFunction*, TSharedPtr<FScriptExpr>>& UberGraphEventEntryPoints, const TMap<UFunction*, TArray<TSharedPtr<FScriptExpr>>>& EventFunctionToEventStubScript) {
	// Mark the function as the ubergraph
	bIsUberGraphFunction = true;
	
	// Perform reachability analysis to deduce all statements that are rechable from the entry point of a particular event into the event graph
	for (const TPair<UFunction*, TSharedPtr<FScriptExpr>>& EntryPointData : UberGraphEventEntryPoints) {
		EventGraphEventToEntryPoint.Add(EntryPointData.Key, EntryPointData.Value);
		EventGraphEntryPointStatements.Add(EntryPointData.Value);
		
		TArray<TSharedPtr<FScriptExpr>> ReachableStatements;
		FScriptExprHelper::PerformReachabilityAnalysis(FunctionScript, EntryPointData.Value, ReachableStatements);

		// Stable sort by the script offset within the uber graph function, so that the order appears "natural" to the target resolution strategies
		ReachableStatements.StableSort([&](const TSharedPtr<FScriptExpr>& A, const TSharedPtr<FScriptExpr>& B) {
			// First statement must always be the entry point
			if (A == EntryPointData.Value || B == EntryPointData.Value) {
				return A == EntryPointData.Value;
			}
			// Sort by script offset otherwise
			return A->ScriptOffset < B->ScriptOffset;
		});
		// Remove statements that are reachable from this function but are shared by multiple events, e.g. EX_Return
		ReachableStatements.RemoveAll([](const TSharedPtr<FScriptExpr>& Statement) {
			return Statement->Opcode == EX_Return;
		});

		// Create a synthetic return statement that is unique to this event function specifically
		TSharedPtr<FScriptExpr> SyntheticEventReturnStatement;
		if (FunctionReturnStatement) {
			if (bFunctionUsesFlowStack) {
				// If function is using the flow stack, synthetic return statement is just a simple EX_PopExecutionFlow to jump to the real return statement
				SyntheticEventReturnStatement = MakeShared<FScriptExpr>(EX_PopExecutionFlow);
			} else {
				// If function is not using the flow stack, just jump to the return statement directly
				SyntheticEventReturnStatement = MakeShared<FScriptExpr>(EX_Jump);
				SyntheticEventReturnStatement->Operands.Add(FScriptExprOperand::CreateUnresolvedLabel(FunctionReturnStatement));
			}

			// Tell each of the reachable statements to use this synthetic return statement instead of the normal return statement
			for (const TSharedPtr<FScriptExpr>& ReachableStatement : ReachableStatements) {
				EventFunctionStatementToSyntheticReturnStatement.Add(ReachableStatement, SyntheticEventReturnStatement);
			}
			// Add the return statement to the reachable statements since it will technically be reachable after the final patch-ups
			ReachableStatements.Add(SyntheticEventReturnStatement);
			SyntheticReturnStatements.Add(SyntheticEventReturnStatement);
		}
		// Associate the list of reachable statements with this event function so that event target resolvers can find their targets
		EventFunctionToReachableStatements.Add(EntryPointData.Key, {ReachableStatements, SyntheticEventReturnStatement});
		TMap<FName, FProperty*>& StubLocalVariableToEventGraphLocalVariable = EventGraphEventToParameterNameToUbergraphStackFrameProperty.FindOrAdd(EntryPointData.Key);
		
		// Process event stub to determine the intermediate variable names used in event graph frame for event parameters
		for (const TSharedPtr<FScriptExpr>& EventStubStatement : EventFunctionToEventStubScript.FindChecked(EntryPointData.Key)) {

			// We are dealing with a persistent ubergraph frame
			if (EventStubStatement->Opcode == EX_LetValueOnPersistentFrame) {
				FProperty* EventGraphLocalVariable = EventStubStatement->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
				const TSharedPtr<FScriptExpr> ValueExpression = EventStubStatement->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;

				// Assignment expression in event graph stub must always be a simple local variable read
				if (ValueExpression->Opcode == EX_LocalVariable) {
					const FProperty* EventStubLocalVariable = ValueExpression->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
					StubLocalVariableToEventGraphLocalVariable.Add(EventStubLocalVariable->GetFName(), EventGraphLocalVariable);
				}
			}
			// We are dealing with a non-persistent ubergraph frame
			else if (FScriptExprClassification::IsSingleAssignmentOpcode(EventStubStatement->Opcode)) {
				const TSharedPtr<FScriptExpr> AssignmentExpression = FScriptExprHelper::GetAssignmentStatementLHS(EventStubStatement);
				const TSharedPtr<FScriptExpr> ValueExpression = FScriptExprHelper::GetSingleAssignmentStatementRHS(EventStubStatement);

				// Assignment should be from a simple local variable to a simple instance variable in default context
				if (AssignmentExpression->Opcode == EX_InstanceVariable && ValueExpression->Opcode == EX_LocalVariable) {
					FProperty* EventGraphInstanceVariable = AssignmentExpression->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
					const FProperty* EventStubLocalVariable = ValueExpression->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
					StubLocalVariableToEventGraphLocalVariable.Add(EventStubLocalVariable->GetFName(), EventGraphInstanceVariable);
				}
			}
		}
	}
}

TSharedPtr<FScriptExpr> FHookCodeGenFunctionContext::GenerateStaticFunctionInvocationExpression(UFunction* CallTarget, UClass* OuterFunctionUClass, const TFunctionRef<TSharedPtr<FScriptExpr>(FProperty*)>& ParameterExpressionGenerator) {
	// Create function call expression
	const TSharedPtr<FScriptExpr> FunctionCallExpression = MakeShared<FScriptExpr>(EX_LocalFinalFunction);
	FunctionCallExpression->Operands.Add(CallTarget);

	// Generate expressions for all parameters the hook needs
	for (TFieldIterator<FProperty> It(CallTarget, EFieldIterationFlags::None); It; ++It) {

		// Skip non-parameters and return value property
		FProperty* ParameterProperty = *It;
		if (!ParameterProperty->HasAnyPropertyFlags(CPF_Parm)) continue;
		if (ParameterProperty->HasAnyPropertyFlags(CPF_ReturnParm)) continue;

		// Generate the value using the provided generator
		const TSharedPtr<FScriptExpr> ParameterValueExpr = ParameterExpressionGenerator(ParameterProperty);

		if (ParameterValueExpr == nullptr) {
			UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to generate call to function %s because value for parameter %s could not be resolved"),
				*CallTarget->GetFullName(), *ParameterProperty->GetFullName());
			return nullptr;
		}

		// Determine the type of the parameter to make sure that the expression type either matches it precisely or can be converted to it
		const TSharedPtr<FScriptExprType> ExpectedParameterType = FScriptExprTypeResolver::ResolvePropertyType(ParameterProperty);
		const bool bIsOutOrReferenceParm = ParameterProperty->HasAnyPropertyFlags(CPF_OutParm);

		// We do not allow implicit type conversion for parameters passed by reference, we need to ensure that types match exactly since the function can also write value to the parameter
		const TSharedPtr<FScriptExpr> ConvertedParameterValueExpr = bIsOutOrReferenceParm ?
			FScriptExprHelper::ConformExpressionToType(ParameterValueExpr, OuterFunctionUClass, ExpectedParameterType) :
			FScriptExprHelper::ImplicitlyConvertExpressionToType(ParameterValueExpr, OuterFunctionUClass, ExpectedParameterType);

		if (ConvertedParameterValueExpr == nullptr) {
			UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to generate call to function %s because value of type %s for parameter %s could not be implicitly converted to the defined parameter type %s"),
				*CallTarget->GetFullName(), *FScriptExprTypeResolver::ResolveExpressionType(ParameterValueExpr, OuterFunctionUClass)->ToString(), *ParameterProperty->GetFullName(), *ExpectedParameterType->ToString());
			return nullptr;
		}

		// If the parameter takes the expression value by reference or outputs it, we need to make sure the expression is an RValue reference, otherwise the function will not be able to write to it
		const bool bIsExpressionLValueReference = FScriptExprHelper::GetExpressionDestPropertyType(ConvertedParameterValueExpr) != nullptr;
		if (bIsOutOrReferenceParm && !bIsExpressionLValueReference) {
			UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to generate call to function %s because value for a reference or output parameter %s is not an LValue Reference (e.g. a Property Read)"),
				*CallTarget->GetFullName(), *ParameterProperty->GetFullName());
			return nullptr;
		}

		// Finally add the parameter to the operands of the expression
		FunctionCallExpression->Operands.Add(ConvertedParameterValueExpr);
	}
	
	// Function must be static since we will use a class default object as a context, and we do not support Net functions
	if (!CallTarget->HasAnyFunctionFlags(FUNC_Static)) {
		UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to emit call to function %s, function is not Static"), *CallTarget->GetFullName());
		return nullptr;
	}

	// Create constant expression for the function class CDO
	const TSharedPtr<FScriptExpr> ClassDefaultObjectConstant = MakeShared<FScriptExpr>(EX_ObjectConst);
	ClassDefaultObjectConstant->Operands.Add(CallTarget->GetOuterUClass()->GetDefaultObject());

	// Wrap the call into the context expression. We do not need to emit context skip data since this context is not fail safe
	const TSharedPtr<FScriptExpr> FunctionCallContextExpression = MakeShared<FScriptExpr>(EX_Context);
	FunctionCallContextExpression->Operands.Add(ClassDefaultObjectConstant);
	FunctionCallContextExpression->Operands.Add(FScriptExprOperand::CreateUnresolvedLabel(nullptr));
	FunctionCallContextExpression->Operands.Add(static_cast<FProperty*>(nullptr));
	FunctionCallContextExpression->Operands.Add(FunctionCallExpression);

	return FunctionCallContextExpression;
}

TSharedPtr<FScriptExpr> FHookCodeGenFunctionContext::GenerateFunctionOrObjectContextHookParameterValue(UFunction* OwnerFunctionOrEvent, const FHookCodeGenParameterDescriptor& ParameterDescriptor) const {
	const FName ParameterName = ParameterDescriptor.ParameterProperty->GetFName();

	// Attempt to resolve as class instance variable (but only if function is not marked as Static)
	if (!OwnerFunction->HasAnyFunctionFlags(FUNC_Static)) {
		if (FProperty* InstanceVariableProperty = FindFProperty<FProperty>(OwnerFunction->GetOuterUClass(), ParameterName)) {
			const TSharedPtr<FScriptExpr> LocalVariableReadExpression = MakeShared<FScriptExpr>();
			LocalVariableReadExpression->Opcode = EX_InstanceVariable;
			LocalVariableReadExpression->Operands.Add(InstanceVariableProperty);
			return LocalVariableReadExpression;
		}
	}

	// If this is an ubergraph event hook, the hook might attempt to capture event function parameters as local variables, but they have mangled names inside the ubergraph.
	// So we need to look up the original parameter name to the evenr graph property it maps to before attempting to look up locals normally
	if (bIsUberGraphFunction && OwnerFunctionOrEvent && EventGraphEventToParameterNameToUbergraphStackFrameProperty.Contains(OwnerFunctionOrEvent)) {
		const TMap<FName, FProperty*>& EventParameterNameToEventGraphProperty = EventGraphEventToParameterNameToUbergraphStackFrameProperty.FindChecked(OwnerFunctionOrEvent);
		if (EventParameterNameToEventGraphProperty.Contains(ParameterName)) {
			FProperty* LocalVariableProperty = EventParameterNameToEventGraphProperty.FindChecked(ParameterName);

			// This is a local variable on the persistent ubergraph frame or an instance level variable, so pick the correct opcode based on the owner struct
			const TSharedPtr<FScriptExpr> EventGraphLocalVariableReadExpression = MakeShared<FScriptExpr>();
			EventGraphLocalVariableReadExpression->Opcode = LocalVariableProperty->GetOwnerStruct()->IsA<UClass>() ? EX_InstanceVariable :
				(LocalVariableProperty->HasAnyPropertyFlags(CPF_OutParm) ? EX_LocalOutVariable : EX_LocalVariable);
			EventGraphLocalVariableReadExpression->Operands.Add(LocalVariableProperty);
			return EventGraphLocalVariableReadExpression;
		}
	}

	// Attempt to resolve a parameter as a local variable (or function parameter)
	if (FProperty* LocalVariableProperty = FindFProperty<FProperty>(OwnerFunction, ParameterName)) {
		const TSharedPtr<FScriptExpr> LocalVariableReadExpression = MakeShared<FScriptExpr>();
		LocalVariableReadExpression->Opcode = LocalVariableProperty->HasAnyPropertyFlags(CPF_OutParm) ? EX_LocalOutVariable : EX_LocalVariable;
		LocalVariableReadExpression->Operands.Add(LocalVariableProperty);
		return LocalVariableReadExpression;
	}

	// When we are attempting to resolve the return value as a parameter, we cannot use ReturnValue directly, since return value of the hook has special meaning depending on the hook type
	// So to refer to the return value of the target function, the hook can use TargetReturnValue instead
	if (ParameterName == TEXT("TargetReturnValue") || ParameterName == TEXT("__TargetReturnValue")) {
		if (FProperty* ReturnValueProperty = OwnerFunction->GetReturnProperty()) {
			const TSharedPtr<FScriptExpr> LocalVariableReadExpression = MakeShared<FScriptExpr>();
			LocalVariableReadExpression->Opcode = EX_LocalOutVariable;
			LocalVariableReadExpression->Operands.Add(ReturnValueProperty);
			return LocalVariableReadExpression;
		}
	}

	// Built-in pointer to the object on which the hook is being executed
	if (!OwnerFunction->HasAnyFunctionFlags(FUNC_Static)) {
		if (ParameterName == TEXT("Target") || ParameterName == TEXT("__Target")) {
			const TSharedPtr<FScriptExpr> LocalVariableReadExpression = MakeShared<FScriptExpr>();
			LocalVariableReadExpression->Opcode = EX_Self;
			return LocalVariableReadExpression;
		}
		// If we have an implicit world context pin, Target of the hooked instance function will be our world context
		// On static functions, __WorldContext should resolve to the function parameter with the same name in the target function
		if (ParameterName == TEXT("__WorldContext")) {
			const TSharedPtr<FScriptExpr> SelfWorldContextExpression = MakeShared<FScriptExpr>();
			SelfWorldContextExpression->Opcode = EX_Self;
			return SelfWorldContextExpression;
		}
	}

	// Don't know how to resolve other properties
	return nullptr;
}

bool FHookCodeGenFunctionContext::GenerateInsertionHookInvocation(const FHookCodeGenInsertionHookData& HookData, TArray<TSharedPtr<FScriptExpr>>& OutGeneratedStatements) const {
	// If this insertion hook targeted a single expression inside the statement, it can receive that expression as a parameter, granted that the expression is pure
	TSharedPtr<FScriptExpr> HookTargetExpressionParameter;
	if (HookData.TargetExpressions.Num() == 1) {
		const TSharedPtr<FScriptExpr> ExtractedTargetExpression = FScriptExprHelper::ExtractExpressionFromContext(HookData.TargetExpressions[0]);
		if (ExtractedTargetExpression && FScriptExprHelper::IsExpressionPure(ExtractedTargetExpression)) {
			HookTargetExpressionParameter = ExtractedTargetExpression;
		}
	}

	// If this hook is being inserted relative to a statement that represents an assignment, we can provide an assignment LHS to the hook so that the hook can read and modify the value being assigned
	TSharedPtr<FScriptExpr> HookAssignmentTargetExpression;
	if (HookData.TargetStatement && FScriptExprClassification::IsAssignmentOpcode(HookData.TargetStatement->Opcode)) {
		HookAssignmentTargetExpression = FScriptExprHelper::GetAssignmentStatementLHS(HookData.TargetStatement);
	}

	// Generate the hook invocation expression
	const TSharedPtr<FScriptExpr> HookInvocationExpression = GenerateStaticFunctionInvocationExpression(HookData.HookFunction, OwnerFunction->GetOuterUClass(), [&](FProperty* HookParameter) {
		FHookCodeGenParameterDescriptor ParameterDescriptor;
		ParameterDescriptor.ParameterProperty = HookParameter;

		// Generate common hook parameter value
		TSharedPtr<FScriptExpr> ParameterExpression = GenerateFunctionOrObjectContextHookParameterValue(HookData.TargetFunctionOrEvent, ParameterDescriptor);
		if (ParameterExpression) {
			return ParameterExpression;
		}

		// If common parameters are not a match (i.e. not instance or local variables), check for special parameters
		
		// Handle hook target expression being requested as a hook parameter
		const FName ParameterName = ParameterDescriptor.ParameterProperty->GetFName();
		if (HookTargetExpressionParameter && (ParameterName == TEXT("HookTarget") || ParameterName == TEXT("__HookTarget"))) {
			return HookTargetExpressionParameter->DeepCopy();
		}

		// Handle target statement assignment left hand side being requested as a hook parameter
		if (HookAssignmentTargetExpression && (ParameterName == TEXT("AssignmentTarget") || ParameterName == TEXT("_AssignmentTarget"))) {
			return HookAssignmentTargetExpression->DeepCopy();
		}

		return TSharedPtr<FScriptExpr>(nullptr);
	});

	// Check that we have successfully generated the invocation expression
	if (HookInvocationExpression == nullptr) {
		UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to generate insertion hook %s invocation expression"), *HookData.HookFunction->GetFullName());
		return false;
	}

	// Handle return value of the hook potentially being able to cancel the original function execution
	const FProperty* HookReturnValueProperty = HookData.HookFunction->GetReturnProperty();
	if (HookData.TargetFunctionOrEventReturnStatement && HookReturnValueProperty) {
		// Make sure return value actually has the correct type
		if (!HookReturnValueProperty->IsA<FBoolProperty>()) {
			UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Invalid return value %s type for insertion hook %s. Insertion hook can only return a boolean or nothing"),
				*HookReturnValueProperty->GetFullName(), *HookData.HookFunction->GetFullName());
			return false;
		}

		// Wrap the hook invocation into JumpIfNot to return value statement if the function does not use the flow stack
		if (!bFunctionUsesFlowStack) {
			const TSharedPtr<FScriptExpr> JumpToFunctionReturnStatementIfFalse = MakeShared<FScriptExpr>(EX_JumpIfNot);
			JumpToFunctionReturnStatementIfFalse->Operands.Add(FScriptExprOperand::CreateUnresolvedLabel(HookData.TargetFunctionOrEventReturnStatement));
			JumpToFunctionReturnStatementIfFalse->Operands.Add(HookInvocationExpression);
			
			OutGeneratedStatements.Add(JumpToFunctionReturnStatementIfFalse);
		} else {
			// If the function uses the flow stack, we cannot jump to the return statement directly. Instead, we need to use EX_PopExecutionFlow
			// Note that this does not actually mean that we will get to the end of the function, but it will always skip the current execution thread
			const TSharedPtr<FScriptExpr> ExitCurrentExecutionThreadIfFalse = MakeShared<FScriptExpr>(EX_PopExecutionFlowIfNot);
			ExitCurrentExecutionThreadIfFalse->Operands.Add(HookInvocationExpression);
			
			OutGeneratedStatements.Add(ExitCurrentExecutionThreadIfFalse);
		}
		return true;
	}
	// Append the invocation expression as a statement normally otherwise
	OutGeneratedStatements.Add(HookInvocationExpression);
	return true;
}

TSharedPtr<FScriptExpr> FHookCodeGenFunctionContext::GenerateRedirectHookInvocation(const FHookCodeGenRedirectHookData& HookData, const TSharedPtr<FScriptExpr>& RedirectedExpression) const {
	// Generate the hook invocation expression
	int32 OriginalValueUseCount = 0;
	const TSharedPtr<FScriptExpr> HookInvocationExpression = GenerateStaticFunctionInvocationExpression(HookData.HookFunction, OwnerFunction->GetOuterUClass(), [&](FProperty* HookParameter) {
		FHookCodeGenParameterDescriptor ParameterDescriptor;
		ParameterDescriptor.ParameterProperty = HookParameter;

		// Generate common hook parameter value
		TSharedPtr<FScriptExpr> ParameterExpression = GenerateFunctionOrObjectContextHookParameterValue(HookData.TargetFunctionOrEvent, ParameterDescriptor);
		if (ParameterExpression) {
			return ParameterExpression;
		}

		// If common parameters are not a match (i.e. not instance or local variables), check for special parameters

		// Handle reference to the original value that the redirect hook receives. Make sure the hook cannot use the original value twice
		const FName ParameterName = ParameterDescriptor.ParameterProperty->GetFName();
		if (ParameterName == TEXT("OriginalValue") || ParameterName == TEXT("__OriginalValue")) {
			return OriginalValueUseCount++ == 0 ? RedirectedExpression : nullptr;
		}

		return TSharedPtr<FScriptExpr>(nullptr);
	});

	// Check that we have successfully generated the invocation expression
	if (HookInvocationExpression == nullptr) {
		UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to generate redirection hook %s invocation expression"), *HookData.HookFunction->GetFullName());
		return nullptr;
	}
	
	// Check that the hook has actually taken the original value as a parameter
	if (OriginalValueUseCount == 0) {
		UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to generate redirection hook %s because it did not take original redirected expression value as an 'OriginalValue' parameter"), *HookData.HookFunction->GetFullName());
		return nullptr;
	}

	// Make sure that the hook actually has a return value, which is a requirement for redirect hooks
	const FProperty* HookReturnValueProperty = HookData.HookFunction->GetReturnProperty();
	if (HookReturnValueProperty == nullptr) {
		UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to generate redirection hook %s because it does not have a return value. All redirect hooks must return a value."), *HookData.HookFunction->GetFullName());
		return nullptr;
	}

	// Make sure that the return value type is identical to the redirected expression type
	const TSharedPtr<FScriptExprType> ReturnValueType = FScriptExprTypeResolver::ResolveExpressionType(RedirectedExpression, OwnerFunction->GetOuterUClass());
	const TSharedPtr<FScriptExpr> ConformedHookInvocationExpression = FScriptExprHelper::ConformExpressionToType(HookInvocationExpression, OwnerFunction->GetOuterUClass(), ReturnValueType);
	if (ConformedHookInvocationExpression == nullptr) {
		UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to generate redirection hook %s because its return value %s does not conform to the type of the redirected expression"),
			*HookData.HookFunction->GetFullName(), *HookReturnValueProperty->GetFullName());
		return nullptr;
	}
	return ConformedHookInvocationExpression;
}

TSharedPtr<FScriptExpr> FHookCodeGenFunctionContext::ProcessExpressionTreeWithRedirectHooks(const FHookCodeGenStatementModificationData& StatementData, const TSharedPtr<FScriptExpr>& Expression, const TSharedPtr<FScriptExpr>& ExpressionContext) {
	TSharedPtr<FScriptExpr> NewExpression;

	// Copy the original expression and process all of its nested expression operands
	if (!FScriptExprClassification::IsContextOpcode(Expression->Opcode)) {
		NewExpression = MakeShared<FScriptExpr>(Expression->Opcode);

		// Replace the original operand with the processed expression tree if this operand is an expression
		for (const FScriptExprOperand& OriginalOperand : Expression->Operands) {
			if (OriginalOperand.Type == FScriptExprOperand::TypeExpr && OriginalOperand.Expr) {
				NewExpression->Operands.Add(ProcessExpressionTreeWithRedirectHooks(StatementData, OriginalOperand.Expr, ExpressionContext));
			} else {
				// Just copy the operand value normally otherwise
				NewExpression->Operands.Add(OriginalOperand);
			}
		}	
	} else {
		// Context switch expressions need additional processing since they override the running context for their second operand
		const TSharedPtr<FScriptExpr>& OriginalContextExpression = Expression->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
		const TSharedPtr<FScriptExpr>& OriginalEvaluatedExpression = Expression->RequireOperand(3, FScriptExprOperand::TypeExpr).Expr;

		// For context switch expression types, we need to first process the context expression with redirect hooks (in the current context), and then run the evaluated expression in that new context
		const TSharedPtr<FScriptExpr> NewContextExpression = ProcessExpressionTreeWithRedirectHooks(StatementData, OriginalContextExpression, ExpressionContext);
		const TSharedPtr<FScriptExpr> NewEvaluatedExpression = ProcessExpressionTreeWithRedirectHooks(StatementData, OriginalEvaluatedExpression, NewContextExpression);
		
		// Processed context switches also cannot fail safely, even if the original context switch could
		NewExpression = MakeShared<FScriptExpr>(EX_Context);
		NewExpression->Operands.Add(NewContextExpression);
		NewExpression->Operands.Add(FScriptExprOperand::CreateUnresolvedLabel(nullptr));
		NewExpression->Operands.Add(static_cast<FProperty*>(nullptr));
		NewExpression->Operands.Add(NewEvaluatedExpression);
	}

	// Apply redirect hooks to the resulting expression
	const TArray<FHookCodeGenRedirectHookData>* StatementRedirectHooks = StatementData.ExpressionToRedirectHooks.Find(Expression);
	if (StatementRedirectHooks != nullptr) {

		// Cannot apply redirect hooks to expressions that do not actually yield a value, e.g. statements and functions returning void (they can be an expression as well, e.g. if they are wrapped in EX_Context)
		const TSharedPtr<FScriptExprType> RedirectedExpressionType = FScriptExprTypeResolver::ResolveExpressionType(Expression, OwnerFunction->GetOuterUClass());
		if (RedirectedExpressionType == nullptr || RedirectedExpressionType->PropertyType == nullptr) {
			UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Cannot install redirect hooks on target expression because it does not result in a value. Redirect hooks cannot be installed on statements. Target function: %s."),
				*OwnerFunction->GetFullName());
			return NewExpression;
		}

		// Since function arguments will always run in the original context of the owning function, we need to wrap the new expression into the current context object to ensure that it will run under the correct context
		if (ExpressionContext != nullptr) {
			const TSharedPtr<FScriptExpr> ContextWrappedNewExpression = MakeShared<FScriptExpr>(EX_Context);

			ContextWrappedNewExpression->Operands.Add(ExpressionContext->DeepCopy());
			ContextWrappedNewExpression->Operands.Add(FScriptExprOperand::CreateUnresolvedLabel(nullptr));
			ContextWrappedNewExpression->Operands.Add(static_cast<FProperty*>(nullptr));
			ContextWrappedNewExpression->Operands.Add(NewExpression);
			NewExpression = ContextWrappedNewExpression;
		}

		// Apply redirect hook chain to the resulting expression now
		for (const FHookCodeGenRedirectHookData& RedirectHookData : *StatementRedirectHooks) {
			const TSharedPtr<FScriptExpr> RedirectedExpression = GenerateRedirectHookInvocation(RedirectHookData, NewExpression);

			// Make sure the hook application was actually successful before overwriting the current expression
			if (RedirectedExpression == nullptr) {
				UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to install redirect hook %s"), *RedirectHookData.HookFunction->GetFullName());
				continue;
			}
			NewExpression = RedirectedExpression;
		}
	}
	return NewExpression;
}

void FHookCodeGenFunctionContext::ResolveHookTargets(const TArray<FBlueprintHookDefinition>& Hooks) {
	for (const FBlueprintHookDefinition& HookDefinition : Hooks) {
		// Skip invalid hook definitions
		if (HookDefinition.HookFunction == nullptr || HookDefinition.TargetSpecifier == nullptr) continue;
		
		// Skip hooks that are not actually targeting this function
		if (HookDefinition.TargetFunction != OwnerFunction && !EventGraphEventToEntryPoint.Contains(HookDefinition.TargetFunction)) {
			UE_LOG(LogBlueprintHookingCodeGen, Warning, TEXT("Skipping hook application %s on function %s because the hook does not target the function"), *HookDefinition.HookFunction->GetFullName(), *OwnerFunction->GetFullName());
		}

		// Create target resolver and make sure it is valid
		const TSharedPtr<FBlueprintHookTargetResolver> TargetResolver = HookDefinition.TargetSpecifier->CreateTargetResolver();
		if (TargetResolver == nullptr) {
			UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Cannot apply hook %s because its target resolver is not valid"), *HookDefinition.HookFunction->GetFullName());
			continue;
		}

		// If this is event graph function, make sure to pass only the statements belonging to the event being targeted and not the entire ubergraph script
		TArray<TSharedPtr<FScriptExpr>> TargetFunctionScript = FunctionScript;
		TSharedPtr<FScriptExpr> TargetFunctionReturnStatement = FunctionReturnStatement;
		if (const TPair<TArray<TSharedPtr<FScriptExpr>>, TSharedPtr<FScriptExpr>>* TargetFunctionReachableStatements = EventFunctionToReachableStatements.Find(HookDefinition.TargetFunction)) {
			TargetFunctionScript = TargetFunctionReachableStatements->Key;
			TargetFunctionReturnStatement = TargetFunctionReachableStatements->Value;
		}

		// Resolve target expressions for the hook
		TArray<TSharedPtr<FScriptExpr>> TargetExpressions;
		TargetResolver->ResolveTargets(HookDefinition.TargetFunction, TargetFunctionScript, TargetFunctionReturnStatement, TargetExpressions);
		if (TargetExpressions.IsEmpty()) {
			UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to find any hook targets for hook %s"), *HookDefinition.HookFunction->GetFullName());
			continue;
		}

		// Filter targets based on the target selection mode
		TArray<TSharedPtr<FScriptExpr>> FilteredTargetExpressions = FBlueprintHookTargetResolver_TargetSelectionMode::ApplyTargetSelectionMode(HookDefinition.TargetSelectionMode, HookDefinition.TargetOrdinal, TargetExpressions);
		if (FilteredTargetExpressions.IsEmpty()) {
			UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to select a target expression out of %d targets for hook %s"), TargetExpressions.Num(),
				*HookDefinition.HookFunction->GetFullName());
			continue;
		}

		TargetExpressions = FilteredTargetExpressions;

		// Apply the insertion hook to the statements referenced
		if (HookDefinition.Type == EBlueprintFunctionHookType::InsertionHook) {
			// Transform target expressions into the actual statements that we are inserting relative to
			TMap<TSharedPtr<FScriptExpr>, TArray<TSharedPtr<FScriptExpr>>> TargetStatementsToTargetExpressions;
			for (const TSharedPtr<FScriptExpr>& TargetExpression : TargetExpressions) {
				TargetStatementsToTargetExpressions.FindOrAdd(TargetExpression->GetStatement()).Add(TargetExpression);
			}
			
			// Apply hook relative to each statement in question
			for (const TPair<TSharedPtr<FScriptExpr>, TArray<TSharedPtr<FScriptExpr>>>& TargetStatementAndExpressions : TargetStatementsToTargetExpressions) {
				FHookCodeGenStatementModificationData& ModificationData = StatementToHookModificationData.FindOrAdd(TargetStatementAndExpressions.Key);

				// Populate insertion hook data necessary to perform the code generation later
				FHookCodeGenInsertionHookData InsertionHookData;
				InsertionHookData.HookFunction = HookDefinition.HookFunction;
				InsertionHookData.TargetFunctionOrEvent = HookDefinition.TargetFunction;
				InsertionHookData.TargetStatement = TargetStatementAndExpressions.Key;
				InsertionHookData.TargetExpressions = TargetStatementAndExpressions.Value;
				InsertionHookData.TargetFunctionOrEventReturnStatement = TargetFunctionReturnStatement;

				// Apply the hook either after or before the target statement
				if (HookDefinition.InsertLocation == EBlueprintFunctionHookInsertLocation::AfterTarget) {
					ModificationData.InsertAfterHooks.Add(InsertionHookData);
				} else if (HookDefinition.InsertLocation == EBlueprintFunctionHookInsertLocation::BeforeTarget) {
					ModificationData.InsertBeforeHooks.Add(InsertionHookData);
				} else if (HookDefinition.InsertLocation == EBlueprintFunctionHookInsertLocation::ReplaceTarget) {
					// Make sure that no another redirect hook has been applied to the same statement
					if (ModificationData.ReplacementHook.IsSet()) {
						UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to apply replacement hook %s to target statement because another replacement hook %s was already applied to the same statement"),
							*HookDefinition.HookFunction->GetFullName(), *ModificationData.ReplacementHook.GetValue().HookFunction->GetFullName());
						continue;
					}
					ModificationData.ReplacementHook = InsertionHookData;
				}
			}
		}
		
		// Apply redirect hook to the statements
		if (HookDefinition.Type == EBlueprintFunctionHookType::RedirectHook) {
			// Apply the redirect hook to each expression in question
			for (const TSharedPtr<FScriptExpr>& TargetExpression : TargetExpressions) {

				// Make sure that the target expression is not a statement
				const TSharedPtr<FScriptExpr> TargetStatement = TargetExpression->GetStatement();
				if (TargetStatement == TargetExpression) {
					UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to apply redirect hook %s to a target expression because target expression was a statement"), *HookDefinition.HookFunction->GetFullName());
					continue;
				}

				// Make sure the target expression is actually an expression that yields a type
				const TSharedPtr<FScriptExprType> TargetExpressionType = FScriptExprTypeResolver::ResolveExpressionType(TargetExpression, OwnerFunction->GetOuterUClass());
				if (TargetExpressionType == nullptr || TargetExpressionType->PropertyType == nullptr) {
					UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Failed to apply redirect hook %s to expression because the target expression does not yield a value"), *HookDefinition.HookFunction->GetFullName());
					continue;
				}

				// Construct the hook data for the redirect hook
				FHookCodeGenRedirectHookData RedirectHookData;
				RedirectHookData.HookFunction = HookDefinition.HookFunction;
				RedirectHookData.TargetFunctionOrEvent = HookDefinition.TargetFunction;

				// Add the resulting code gen hook data to the statement
				FHookCodeGenStatementModificationData& ModificationData = StatementToHookModificationData.FindOrAdd(TargetStatement);
				ModificationData.ExpressionToRedirectHooks.FindOrAdd(TargetExpression).Add(RedirectHookData);
			}
		}
	}
}

bool FHookCodeGenFunctionContext::GenerateFunctionCode(TArray<TSharedPtr<FScriptExpr>>& OutFunctionScript, TMap<UFunction*, TSharedPtr<FScriptExpr>>& OutUberGraphEventEntryPoints) {
	TMap<TSharedPtr<FScriptExpr>, TSharedPtr<FScriptExpr>> OriginalStatementLabelToNewStatementLabel;
	TMap<TSharedPtr<FScriptExpr>, TSharedPtr<FScriptExpr>> OutputStatementToOverrideReturnStatementLabel;
	TSet<TSharedPtr<FScriptExpr>> GeneratedSyntheticReturnStatements;
	bool bInstalledAllHooksSuccessfully = true;
	
	// Generate the resulting code by sequentially transforming each statement
	OutFunctionScript.Empty();
	for (const TSharedPtr<FScriptExpr>& OriginalScriptStatement : FunctionScript) {
		
		const FHookCodeGenStatementModificationData* StatementModificationData = StatementToHookModificationData.Find(OriginalScriptStatement);
		const int32 FirstStatementIndex = OutFunctionScript.Num();

		// If this is an ubergraph function that uses the flow stack, we need to push the return address to the top of the stack before the original event entry point runs
		if (bIsUberGraphFunction && EventGraphEntryPointStatements.Contains(OriginalScriptStatement)) {
			const TSharedPtr<FScriptExpr>* SyntheticReturnStatement = EventFunctionStatementToSyntheticReturnStatement.Find(OriginalScriptStatement);
			if (SyntheticReturnStatement && bFunctionUsesFlowStack) {
				// If synthetic return statement does not have any hooks attached to it, we do not need to actually generate it or to redirect existing code to it
				const FHookCodeGenStatementModificationData* SyntheticReturnStatementModificationData = StatementToHookModificationData.Find(*SyntheticReturnStatement);
				if (SyntheticReturnStatementModificationData != nullptr) {
					const TSharedPtr<FScriptExpr> PushSyntheticReturnStatementToFlowStack = MakeShared<FScriptExpr>(EX_PushExecutionFlow);
					PushSyntheticReturnStatementToFlowStack->Operands.Add(FScriptExprOperand::CreateUnresolvedLabel(*SyntheticReturnStatement));
					OutFunctionScript.Add(PushSyntheticReturnStatementToFlowStack);
				}
			}
		}

		// Apply hooks if we actually have them. Do not attempt to apply hooks to UberGraph ComputedJump or Return statements
		const bool bIsInternalStatement = OriginalScriptStatement->Opcode == EX_EndOfScript ||
			OriginalScriptStatement->Opcode == EX_ComputedJump ||
			(bIsUberGraphFunction && OriginalScriptStatement->Opcode == EX_Return) ||
			(bIsUberGraphFunction && bFunctionUsesFlowStack && OriginalScriptStatement->ScriptOffset == 0); // To handle EX_PushExecutionFlow at entry to the ubergraph
		if (StatementModificationData != nullptr && !bIsInternalStatement) {
			// Generate insert before hooks
			for (const FHookCodeGenInsertionHookData& BeforeHook : StatementModificationData->InsertBeforeHooks) {
				bInstalledAllHooksSuccessfully &= GenerateInsertionHookInvocation(BeforeHook, OutFunctionScript);
			}
			
			// Replacement hook overrides the original statement if it is set, and it has successfully generated the code
			if (!StatementModificationData->ReplacementHook.IsSet() || OriginalScriptStatement->Opcode == EX_Return || !GenerateInsertionHookInvocation(StatementModificationData->ReplacementHook.GetValue(), OutFunctionScript)) {
				const TSharedPtr<FScriptExpr> RedirectedStatement = ProcessExpressionTreeWithRedirectHooks(*StatementModificationData, OriginalScriptStatement, nullptr);
				OutFunctionScript.Add(RedirectedStatement);

				// Print a warning if the caller attempted to install a "replace" hook on return value statement
				if (StatementModificationData->ReplacementHook.IsSet() && OriginalScriptStatement->Opcode == EX_Return) {
					UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Cannot install replace hook on function return statement in function %s"), *OwnerFunction->GetFullName());
					bInstalledAllHooksSuccessfully = false;
				}
			} else {
				// Print a warning if replacement hook resulted in redirect hooks being overwritten
				if (!StatementModificationData->ExpressionToRedirectHooks.IsEmpty()) {
					UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Cannot install redirect hooks for statement in function %s because they are overwritten by an insertion Replace hook installed on the same statement"), *OwnerFunction->GetFullName());
					bInstalledAllHooksSuccessfully = false;
				}
			}
			
			// We cannot actually insert after hooks if this statement represents an unconditional control flow jump, since they would never be called
			if (!FScriptExprClassification::IsUnconditionalControlFlowStop(OriginalScriptStatement->Opcode)) {
				// Generate insert after hooks
				for (const FHookCodeGenInsertionHookData& BeforeHook : StatementModificationData->InsertAfterHooks) {
					bInstalledAllHooksSuccessfully &= GenerateInsertionHookInvocation(BeforeHook, OutFunctionScript);
				}
			} else if (!StatementModificationData->InsertAfterHooks.IsEmpty()) {
				// Print a warning if we have actually registered after hooks for this statement, but could not install them
				UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Cannot insert after hooks for statement in function %s because that statement represents an unconditional control flow jump"), *OwnerFunction->GetFullName());
				bInstalledAllHooksSuccessfully = false;
			}
		} else {
			// Warn that hooks cannot be applied to EX_ComputedJump
			if (StatementModificationData != nullptr) {
				UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Cannot apply insertion and redirect hooks to Computed Jump and Return statements in UberGraph, hook individual Events instead of hooking the Ubergraph Entry %s"), *OwnerFunction->GetFullName());
				bInstalledAllHooksSuccessfully = false;
			}
			// Copy the original statement without any changes otherwise
			OutFunctionScript.Add(OriginalScriptStatement->DeepCopy());
		}
		
		// Associate the old statement with the new statement (first "before hook" invocation, so before hooks are not skipped)
		OriginalStatementLabelToNewStatementLabel.Add(OriginalScriptStatement, OutFunctionScript[FirstStatementIndex]);

		// If this is an ubergraph function, and we have just emitted a computed jump entry point, append all synthetic return statements after it, and apply prefix hooks to them
		if (bIsUberGraphFunction && OriginalScriptStatement->Opcode == EX_ComputedJump) {
			for (const TSharedPtr<FScriptExpr>& SyntheticReturnStatement : SyntheticReturnStatements) {
				// If synthetic return statement does not have any hooks attached to it, we do not need to actually generate it or to redirect existing code to it
				const FHookCodeGenStatementModificationData* SyntheticReturnStatementModificationData = StatementToHookModificationData.Find(SyntheticReturnStatement);
				if (SyntheticReturnStatementModificationData == nullptr) continue;

				const int32 FirstReturnStatementIndex = OutFunctionScript.Num();
				
				// Generate insert before hooks
				for (const FHookCodeGenInsertionHookData& BeforeHook : SyntheticReturnStatementModificationData->InsertBeforeHooks) {
					GenerateInsertionHookInvocation(BeforeHook, OutFunctionScript);
				}
				
				// Append the original return statement. Replacement and redirect hooks are not allowed on return statements
				if (SyntheticReturnStatementModificationData->ReplacementHook.IsSet()) {
					UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Cannot use replace insert hook on return statement in function %s"), *OwnerFunction->GetFullName());
					bInstalledAllHooksSuccessfully = false;
				}
				if (!SyntheticReturnStatementModificationData->ExpressionToRedirectHooks.IsEmpty()) {
					UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Cannot use redirect hooks in event graph function %s because events do not return a value"), *OwnerFunction->GetFullName());
					bInstalledAllHooksSuccessfully = false;
				}
				OutFunctionScript.Add(SyntheticReturnStatement);

				// Print a warning if we have insert after hooks for return value, this is not allowed
				if (!SyntheticReturnStatementModificationData->InsertAfterHooks.IsEmpty()) {
					UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Cannot insert after hooks past the event return statement in %s"), *OwnerFunction->GetFullName());
					bInstalledAllHooksSuccessfully = false;
				}

				// Mark this return statement as generated so that we can redirect original statements down the line to it
				GeneratedSyntheticReturnStatements.Add(SyntheticReturnStatement);
				// Also redirect any labels targeting the synthetic return statement to the first insert before hook before it to make sure that insert before hooks are executed
				OriginalStatementLabelToNewStatementLabel.Add(SyntheticReturnStatement, OutFunctionScript[FirstReturnStatementIndex]);
			}
			// Cleanup the list of synthetic return statements now that we have processed them all
			SyntheticReturnStatements.Empty();
		}

		// If this is an event graph, and the original statement belongs to an event, we need to remap the original event graph return statement labels to this events return statement instead
		// This logic not necessary if the event graph is using the flow stack, since no direct jumps will be performed in that case
		if (bIsUberGraphFunction && !bFunctionUsesFlowStack) {
			if (const TSharedPtr<FScriptExpr>* StatementOverrideReturnStatement = EventFunctionStatementToSyntheticReturnStatement.Find(OriginalScriptStatement)) {
				if (GeneratedSyntheticReturnStatements.Contains(*StatementOverrideReturnStatement)) {
					for (int32 StatementIndex = FirstStatementIndex; StatementIndex < OutFunctionScript.Num(); StatementIndex++) {
						OutputStatementToOverrideReturnStatementLabel.Add(OutFunctionScript[StatementIndex], *StatementOverrideReturnStatement);
					}
				}
			}
		}
	}

	// Perform jump target fix-ups on the generated code, since target labels still point to the original function code statements and not to the
	const TSet<TSharedPtr<FScriptExpr>> ValidJumpTargets{OutFunctionScript};
	for (const TSharedPtr<FScriptExpr>& GeneratedScriptStatement : OutFunctionScript) {
		const TSharedPtr<FScriptExpr>* StatementReturnStatementOverride = OutputStatementToOverrideReturnStatementLabel.Find(GeneratedScriptStatement);
		
		GeneratedScriptStatement->ForEachOperandRecursive([&](FScriptExprOperand& Operand) {
			if (Operand.Type == FScriptExprOperand::TypeLabel && Operand.TargetLabel) {
				// If we are processing an ubergraph and this is a jump to the shared ubergraph return statement, we need to redirect it to the event-specific return statement
				if (StatementReturnStatementOverride && Operand.TargetLabel == FunctionReturnStatement) {
					Operand.TargetLabel = *StatementReturnStatementOverride;
				}
				// Replace the reference to the original statement in the label to the new statement in the generated function script
				if (const TSharedPtr<FScriptExpr>* RemappedTargetLabel = OriginalStatementLabelToNewStatementLabel.Find(Operand.TargetLabel)) {
					Operand.TargetLabel = *RemappedTargetLabel;
				}
				// Sanity check that the jump target is valid
				check(Operand.TargetLabel == nullptr || ValidJumpTargets.Contains(Operand.TargetLabel));
			}
		});
	}

	// For ubergraph, also return the new entry points of the event stubs into the ubergraph
	for (const TPair<UFunction*, TSharedPtr<FScriptExpr>>& EventToEntryPointPair : EventGraphEventToEntryPoint) {
		const TSharedPtr<FScriptExpr> RemappedEventEntryPoint = OriginalStatementLabelToNewStatementLabel.FindChecked(EventToEntryPointPair.Value);
		OutUberGraphEventEntryPoints.Add(EventToEntryPointPair.Key, RemappedEventEntryPoint);
	}
	return bInstalledAllHooksSuccessfully;
}

bool FHookCodeGenFunctionContext::CheckCanModifyFunctionScriptAndLocals(const UFunction* TargetFunction, bool bCheckLocalVariableModification) {
	// Make sure we are running on the game thread
	if (!IsInGameThread()) {
		UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Attempt to apply blueprint function hook outside the game thread for %s. This is not safe."), *TargetFunction->GetFullName());
		return false;
	}

	// Investigate the current script call stack to make sure that the function does not appear on it
	const FFrame* CurrentStackFrame = FFrame::GetThreadLocalTopStackFrame();
	while (CurrentStackFrame) {

		// Check if this is the function that is on the call stack
		if (CurrentStackFrame->Node == TargetFunction) {
			UE_LOG(LogBlueprintHookingCodeGen, Error, TEXT("Attempt to modify blueprint function %s while it is on the script call stack for the current thread. This is not safe or supported."), *TargetFunction->GetFullName());
			return false;
		}
		CurrentStackFrame = CurrentStackFrame->PreviousTrackingFrame;
	}

	// If we need local variable frame modification, and this is an ubergraph function, we will need to modify persistent ubergraph frames
	// Since the way we perform the modification is by re-creating the frames from scratch, data stored on these frames will be lost. So this ideally should not be done while there are objects of this type alive that are not archetypes
	if (bCheckLocalVariableModification && TargetFunction->HasAnyFunctionFlags(FUNC_UbergraphFunction)) {
		ForEachObjectOfClass(TargetFunction->GetOuterUClass(), [&](const UObject* BlueprintObjectInstance){
			// Blueprint instances in game worlds and editor worlds might have script events queued up in the graph, data currently used by them will be lost
			const UWorld* BlueprintWorldContext = BlueprintObjectInstance->GetWorld();
			if (BlueprintWorldContext && (BlueprintWorldContext->WorldType == EWorldType::PIE || BlueprintWorldContext->WorldType == EWorldType::Game)) {
				UE_LOG(LogBlueprintHookingCodeGen, Warning, TEXT("Modifying blueprint ubergraph function %s while having a live instance of the blueprint in world %s. Blueprint instance will cancel any pending latent actions such as delays"),
					*TargetFunction->GetFullName(), *BlueprintObjectInstance->GetFullName());
			}
		}, true, RF_ArchetypeObject | RF_ClassDefaultObject);
	}
	// Should be safe to modify otherwise. Note that if this does not check for execution of the script function on other threads
	return true;
}

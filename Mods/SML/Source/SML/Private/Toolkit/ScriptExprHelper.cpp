#include "Toolkit/ScriptExprHelper.h"
#include "Kismet/KismetMathLibrary.h"
#include "Toolkit/ScriptExprClassification.h"
#include "Toolkit/ScriptExprTypeResolver.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"

TSharedPtr<FScriptExpr> FScriptExprHelper::FindStatementByScriptOffset(const TArray<TSharedPtr<FScriptExpr>>& LinearExecutionSequence, int32 ScriptOffset) {
	for (const TSharedPtr<FScriptExpr>& Statement : LinearExecutionSequence) {
		if (Statement->ScriptOffset == ScriptOffset) {
			return Statement;
		}
	}
	return nullptr;
}

FScriptExprOperand FScriptExprHelper::GetSimpleConstantEffectiveValue(const TSharedPtr<FScriptExpr>& SimpleConstantExpr) {
	// Handle EX_IntZero/EX_IntOne special case constants
	if (SimpleConstantExpr->Opcode == EX_IntZero || SimpleConstantExpr->Opcode == EX_IntOne) {
		return FScriptExprOperand(SimpleConstantExpr->Opcode == EX_IntOne ? 1 : 0);
	}
	// Handle EX_True/EX_False special case constants
	if (SimpleConstantExpr->Opcode == EX_False || SimpleConstantExpr->Opcode == EX_False) {
		return FScriptExprOperand(SimpleConstantExpr->Opcode == EX_False ? 1 : 0);
	}
	// Handle EX_NoObject special case
	if (SimpleConstantExpr->Opcode == EX_NoObject) {
		return FScriptExprOperand(static_cast< UObject* >(nullptr));
	}
	// For simple constants that have only a single operand (e.g. all non-struct constants), return that operand
	if (FScriptExprClassification::IsSimpleConstantOpcode(SimpleConstantExpr->Opcode) &&
		!FScriptExprClassification::IsStructConstantOpcode(SimpleConstantExpr->Opcode) &&
		SimpleConstantExpr->Operands.Num() == 1) {
		return SimpleConstantExpr->Operands[0];
	}
	return FScriptExprOperand();
}

TSharedPtr<FScriptExpr> FScriptExprHelper::ImplicitlyConvertExpressionToType(const TSharedPtr<FScriptExpr>& Expression, UClass* OuterUFunctionClass, const TSharedPtr<FScriptExprType>& CoercePropertyType) {
	// Resolve the current expression type. If it is a complete match, no type coercion is necessary
	const TSharedPtr<FScriptExprType> ExpressionType = FScriptExprTypeResolver::ResolveExpressionType(Expression, OuterUFunctionClass);
	if (ExpressionType->Identical(CoercePropertyType)) {
		return Expression;
	}

	// Arithmetic type conversions
	// Note that only a few types are actually supported, since most of the integral types are not marked as "blueprint compatible" and do not have conversion functions, but can be handled by the Kismet VM
	if (ExpressionType->IsA<FNumericProperty>() && CoercePropertyType->IsA<FNumericProperty>()) {

		// Range extension conversion from float to double using a Cast
		if (ExpressionType->IsA<FFloatProperty>() && CoercePropertyType->IsA<FDoubleProperty>()) {
			const TSharedPtr<FScriptExpr> FloatToDoubleCast = MakeShared<FScriptExpr>(EX_CallMath);
			FloatToDoubleCast->Operands.Add(UKismetMathLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UKismetMathLibrary, Conv_FloatToDouble)));
			FloatToDoubleCast->Operands.Add(Expression);
			return FloatToDoubleCast;
		}
		
		// Range extension conversion from int32 to int64
		if (ExpressionType->IsA<FIntProperty>() && CoercePropertyType->IsA<FInt64Property>()) {
			const TSharedPtr<FScriptExpr> IntToInt64 = MakeShared<FScriptExpr>(EX_CallMath);
			IntToInt64->Operands.Add(UKismetMathLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UKismetMathLibrary, Conv_IntToInt64)));
			IntToInt64->Operands.Add(Expression);
			return IntToInt64;
		}
		
		// Range extension conversion from uint8 to int32
		if (ExpressionType->IsA<FByteProperty>() && ExpressionType->Operands.IsEmpty() && CoercePropertyType->IsA<FIntProperty>()) {
			const TSharedPtr<FScriptExpr> ByteToInt = MakeShared<FScriptExpr>(EX_CallMath);
			ByteToInt->Operands.Add(UKismetMathLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UKismetMathLibrary, Conv_ByteToInt)));
			ByteToInt->Operands.Add(Expression);
			return ByteToInt;
		}
		
		// Range extension conversion from uint8 to int64
		if (ExpressionType->IsA<FByteProperty>() && ExpressionType->Operands.IsEmpty() && CoercePropertyType->IsA<FInt64Property>()) {
			const TSharedPtr<FScriptExpr> ByteToInt = MakeShared<FScriptExpr>(EX_CallMath);
			ByteToInt->Operands.Add(UKismetMathLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UKismetMathLibrary, Conv_ByteToInt64)));
			ByteToInt->Operands.Add(Expression);
			return ByteToInt;
		}
	}

	// Class property to class property conversion
	if (ExpressionType->IsA<FClassProperty>() && CoercePropertyType->IsA<FClassProperty>()) {
		const UClass* SourcePropertyClass = Cast<UClass>(ExpressionType->RequireOperand<FClassProperty>(0, FScriptExprTypeOperand::TypeObject).Object);
		const UClass* SourceMetaClass = Cast<UClass>(ExpressionType->RequireOperand<FClassProperty>(2, FScriptExprTypeOperand::TypeObject).Object);

		UClass* DestPropertyClass = Cast<UClass>(CoercePropertyType->RequireOperand<FClassProperty>(0, FScriptExprTypeOperand::TypeObject).Object);
		UClass* DestMetaClass = Cast<UClass>(CoercePropertyType->RequireOperand<FClassProperty>(2, FScriptExprTypeOperand::TypeObject).Object);
		const bool bHasValidPropertyData = SourcePropertyClass && DestPropertyClass && SourceMetaClass && DestMetaClass;
		
		// Coercion from a more specific derived class type to a less specific base class type
		if (bHasValidPropertyData && SourcePropertyClass == DestPropertyClass && SourceMetaClass->IsChildOf(DestMetaClass)) {
			const TSharedPtr<FScriptExpr> MetaCast = MakeShared<FScriptExpr>(EX_MetaCast);
			MetaCast->Operands.Add(DestMetaClass);
			MetaCast->Operands.Add(Expression);
			return MetaCast;
		}
		// Coercion from a more specific class of a class to a less specific class of a class
		if(bHasValidPropertyData && SourceMetaClass == DestMetaClass && SourcePropertyClass->IsChildOf(DestPropertyClass)) {
			const TSharedPtr<FScriptExpr> DynamicCast = MakeShared<FScriptExpr>(EX_DynamicCast);
			DynamicCast->Operands.Add(DestPropertyClass);
			DynamicCast->Operands.Add(Expression);
			return DynamicCast;
		}
		// Coercion from a more specific class of a class to a less specific class of a class and a less specific base class type
		if (bHasValidPropertyData && SourcePropertyClass->IsChildOf(DestPropertyClass) && SourceMetaClass->IsChildOf(DestMetaClass)) {
			const TSharedPtr<FScriptExpr> DynamicCast = MakeShared<FScriptExpr>(EX_DynamicCast);
			DynamicCast->Operands.Add(DestPropertyClass);
			DynamicCast->Operands.Add(Expression);

			const TSharedPtr<FScriptExpr> MetaCast = MakeShared<FScriptExpr>(EX_MetaCast);
			MetaCast->Operands.Add(DestMetaClass);
			MetaCast->Operands.Add(DynamicCast);
			return MetaCast;
		}
	}
	// Object (or class) to object conversion. Note that this will not convert object to class
	else if (ExpressionType->IsA<FObjectProperty>() && CoercePropertyType->IsA<FObjectProperty>() && !CoercePropertyType->IsA<FClassProperty>()) {
		const UClass* SourcePropertyClass = Cast<UClass>(ExpressionType->RequireOperand<FObjectProperty>(0, FScriptExprTypeOperand::TypeObject).Object);
		UClass* DestPropertyClass = Cast<UClass>(CoercePropertyType->RequireOperand<FObjectProperty>(0, FScriptExprTypeOperand::TypeObject).Object);

		// Coercion from more specific source type to a less specific destination type
		if (SourcePropertyClass && DestPropertyClass && SourcePropertyClass->IsChildOf(DestPropertyClass)) {
			const TSharedPtr<FScriptExpr> DynamicCast = MakeShared<FScriptExpr>(EX_DynamicCast);
			DynamicCast->Operands.Add(DestPropertyClass);
			DynamicCast->Operands.Add(Expression);
			return DynamicCast;
		}
	}
	
	// Object to interface conversion
	if (ExpressionType->IsA<FObjectProperty>() && CoercePropertyType->IsA<FInterfaceProperty>()) {
		const UClass* SourcePropertyClass = Cast<UClass>(ExpressionType->RequireOperand<FObjectProperty>(0, FScriptExprTypeOperand::TypeObject).Object);
		UClass* DestInterfaceClass = Cast<UClass>(CoercePropertyType->RequireOperand<FInterfaceProperty>(0, FScriptExprTypeOperand::TypeObject).Object);

		// Coerce an object type that implements the interface to that interface
		if (SourcePropertyClass && DestInterfaceClass && SourcePropertyClass->ImplementsInterface(DestInterfaceClass)) {
			const TSharedPtr<FScriptExpr> ObjectToInterfaceCast = MakeShared<FScriptExpr>(EX_ObjToInterfaceCast);
			ObjectToInterfaceCast->Operands.Add(DestInterfaceClass);
			ObjectToInterfaceCast->Operands.Add(Expression);
			return ObjectToInterfaceCast;
		}
	}
	
	// Interface to object conversion
	if (ExpressionType->IsA<FInterfaceProperty>() && CoercePropertyType->IsA<FObjectProperty>()) {
		const UClass* SourceInterfaceClass = Cast<UClass>(ExpressionType->RequireOperand<FInterfaceProperty>(0, FScriptExprTypeOperand::TypeObject).Object);
		UClass* DestPropertyClass = Cast<UClass>(CoercePropertyType->RequireOperand<FObjectProperty>(0, FScriptExprTypeOperand::TypeObject).Object);

		// We only allow downcasting to the base UObject type, since there is no way to ensure that any other type will be a parent of the converted interface
		if (SourceInterfaceClass && DestPropertyClass && DestPropertyClass == UObject::StaticClass()) {
			const TSharedPtr<FScriptExpr> InterfaceToObjectCast = MakeShared<FScriptExpr>(EX_InterfaceToObjCast);
			InterfaceToObjectCast->Operands.Add(DestPropertyClass);
			InterfaceToObjectCast->Operands.Add(Expression);
			return InterfaceToObjectCast;
		}
	}
	// Do not know how to implicitly convert to the result type otherwise
	return nullptr;
}

TSharedPtr<FScriptExpr> FScriptExprHelper::ConformExpressionToType(const TSharedPtr<FScriptExpr>& Expression, UClass* OuterUFunctionClass, const TSharedPtr<FScriptExprType>& ExpectedType) {
	const TSharedPtr<FScriptExprType> ExpressionType = FScriptExprTypeResolver::ResolveExpressionType(Expression, OuterUFunctionClass);
	if (ExpressionType->Identical(ExpectedType)) {
		return Expression;
	}
	return nullptr;
}

UFunction* FScriptExprHelper::GetFunctionCallTarget(const TSharedPtr<FScriptExpr>& FunctionCallExpression, UClass* OuterUFunctionClass) {
	// We can only handle function call opcodes
	if (FScriptExprClassification::IsFunctionCallOpcode(FunctionCallExpression->Opcode)) {
		// For virtual functions, we need to calculate the type of the context in which they will run to determine the archetype UFunction object from the base class
		if (FunctionCallExpression->Opcode == EX_VirtualFunction || FunctionCallExpression->Opcode == EX_LocalVirtualFunction) {
			const FName FunctionName = ScriptNameToName(FunctionCallExpression->RequireOperand(0, FScriptExprOperand::TypeScriptName).ScriptName);

			const TSharedPtr<FScriptExpr> OuterContextSwitchExpression = GetOuterContextSwitchExpression(FunctionCallExpression);

			UClass* FunctionOwnerOrInterfaceClass;
			if (OuterContextSwitchExpression == nullptr) {
				// If outer context switch expression is null, the function will get called on the class of the function that this code belongs to
				FunctionOwnerOrInterfaceClass = OuterUFunctionClass;
			} else {
				// Otherwise, determine the object expression type for the context object
				const TSharedPtr<FScriptExpr> ContextExpression = OuterContextSwitchExpression->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
				FunctionOwnerOrInterfaceClass = GetObjectExpressionResultType(ContextExpression, OuterUFunctionClass);
			}

			return FunctionOwnerOrInterfaceClass ? FunctionOwnerOrInterfaceClass->FindFunctionByName(FunctionName) : nullptr;
		}
		// For non-virtual functions, the call target is directly given as the first operand
		return Cast<UFunction>(FunctionCallExpression->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
	}
	return nullptr;
}

UClass* FScriptExprHelper::GetObjectExpressionResultType(const TSharedPtr<FScriptExpr>& Expression, UClass* OuterUFunctionClass, const bool bAllowInterfaceClass) {
	// Unwrap potential context expression chain leading to the expression
	const TSharedPtr<FScriptExpr> UnwrappedExpression = UnwrapExpressionContextChain(Expression);
	
	// If this is a reference to Self, this expression refers to our current context, which is either an expression given by the last context switch statement, or an outer function class type
	if (UnwrappedExpression->Opcode == EX_Self) {
		const TSharedPtr<FScriptExpr> OuterContextSwitchExpression = GetOuterContextSwitchExpression(UnwrappedExpression);
			
		// If outer context switch expression is null, the type of the context is the class of the function that this code belongs to
		if (OuterContextSwitchExpression == nullptr) {
			return OuterUFunctionClass;
		}
		// Otherwise, EX_Self returns the active context object, so determine the object expression type for that object
		const TSharedPtr<FScriptExpr> ContextExpression = OuterContextSwitchExpression->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
		return GetObjectExpressionResultType(ContextExpression, OuterUFunctionClass, bAllowInterfaceClass);
	}
	
	// If this expression has a dest property type, PropertyClass of that property is the type of the object
	if (FScriptExprClassification::IsPropertyOpcode(UnwrappedExpression->Opcode) || UnwrappedExpression->Opcode == EX_StructMemberContext || UnwrappedExpression->Opcode == EX_ArrayGetByRef) {
		const FObjectProperty* DestObjectProperty = CastField<FObjectProperty>(GetExpressionDestPropertyType(Expression));
		return DestObjectProperty ? DestObjectProperty->PropertyClass : nullptr;
	}

	// If this expression is a function call, return value property of that function call is a type of the object
	if (FScriptExprClassification::IsFunctionCallOpcode(UnwrappedExpression->Opcode)) {
		const UFunction* FunctionTarget = GetFunctionCallTarget(UnwrappedExpression, OuterUFunctionClass);
		const FObjectProperty* ReturnValueProperty = FunctionTarget ? CastField<FObjectProperty>(FunctionTarget->GetReturnProperty()) : nullptr;
		return ReturnValueProperty ? ReturnValueProperty->PropertyClass : nullptr;
	}

	// If this expression is a cast to object or interface, the cast result type is a type of the object
	if (FScriptExprClassification::IsCastOpcode(UnwrappedExpression->Opcode)) {
		// MetaCast does not actually change the type of the object, it stays a UClass, so we need to look up the nested expression
		if (UnwrappedExpression->Opcode == EX_MetaCast) {
			const TSharedPtr<FScriptExpr>& CastedExpression = UnwrappedExpression->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;
			return GetObjectExpressionResultType(CastedExpression, OuterUFunctionClass, bAllowInterfaceClass);
		}
		
		// DynamicCast always resutls in an object. However, it will only actually cast to the object type if the provided class is an interface
		if (UnwrappedExpression->Opcode == EX_DynamicCast) {
			UClass* ObjectOrInterfaceClass = Cast<UClass>(UnwrappedExpression->RequireOperand(0, FScriptExprOperand::TypeObject).Object);
			const TSharedPtr<FScriptExpr>& CastedExpression = UnwrappedExpression->RequireOperand(1, FScriptExprOperand::TypeExpr).Expr;

			// If cast class is not valid, or this is an interface implementation check and the caller does not want an interface class, continue looking by checking the casted expression
			if (ObjectOrInterfaceClass == nullptr || (ObjectOrInterfaceClass->HasAnyClassFlags(CLASS_Interface) && !bAllowInterfaceClass)) {
				return GetObjectExpressionResultType(CastedExpression, OuterUFunctionClass, bAllowInterfaceClass);
			}
			// Return the object or interface class otherwise
			return ObjectOrInterfaceClass;
		}
		
		// Interface to object class results in an object of that class
		if (UnwrappedExpression->Opcode == EX_InterfaceToObjCast) {
			return Cast<UClass>(UnwrappedExpression->RequireOperand(0, FScriptExprOperand::TypeObject).Object);	
		}
		// Other cast expressions do not result in an object type
		return nullptr;
	}

	// If this expression is a constant, type of the object is a type of that constant value
	if (FScriptExprClassification::IsConstantOpcode(UnwrappedExpression->Opcode)) {
		if (UnwrappedExpression->Opcode == EX_ObjectConst) {
			const UObject* ObjectConstant = UnwrappedExpression->RequireOperand(0, FScriptExprOperand::TypeObject).Object;
			return ObjectConstant ? ObjectConstant->GetClass() : nullptr;
		}
		// Other constants do not result in an object type, or in a non-null object
		return nullptr;
	}
	
	// Other expression types do not result in an object of a determined type
	return nullptr;
}

FProperty* FScriptExprHelper::GetExpressionDestPropertyType(const TSharedPtr<FScriptExpr>& Expression) {
	// Unwrap potential context expression chain leading to the expression
	const TSharedPtr<FScriptExpr> UnwrappedExpression = UnwrapExpressionContextChain(Expression);

	// Property type matches the type of the property being read
	if (FScriptExprClassification::IsPropertyOpcode(UnwrappedExpression->Opcode)) {
		return UnwrappedExpression->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
	}
	// First operand of the EX_StructMemberOffset is the property of the struct that will be assigned to
	if (UnwrappedExpression->Opcode == EX_StructMemberContext) {
		return UnwrappedExpression->RequireOperand(0, FScriptExprOperand::TypeProperty).Property;
	}
	// EX_ArrayGetByRef type is the type of the Inner array element
	if (UnwrappedExpression->Opcode == EX_ArrayGetByRef) {
		const TSharedPtr<FScriptExpr>& ArrayDestExpression = UnwrappedExpression->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
		const FArrayProperty* ArrayPropertyType = CastField<FArrayProperty>(GetExpressionDestPropertyType(ArrayDestExpression));
		return ArrayPropertyType ? ArrayPropertyType->Inner : nullptr;
	}
	// Not a valid LValue reference opcode otherwise
	return nullptr;
}

TSharedPtr<FScriptExpr> FScriptExprHelper::GetAssignmentStatementLHS(const TSharedPtr<FScriptExpr>& AssignmentStatement) {
	// There is no LHS for the LetValueOnPersistentFrame, it is implicit and there is no Script VM opcode to get a reference to it as an expression
	if (AssignmentStatement->Opcode == EX_LetValueOnPersistentFrame) {
		return nullptr;
	}

	// All other assignment expressions have LHS as one of their operands
	if (FScriptExprClassification::IsAssignmentOpcode(AssignmentStatement->Opcode)) {
		
		// LHS is operand 1 for EX_Let and EX_BindDelegate, and operand 0 for everything else
		const int32 LhsOperandIndex = AssignmentStatement->Opcode == EX_Let || AssignmentStatement->Opcode == EX_BindDelegate ? 1 : 0;
		return AssignmentStatement->RequireOperand(LhsOperandIndex, FScriptExprOperand::TypeExpr).Expr;
	}
	return nullptr;
}

TSharedPtr<FScriptExpr> FScriptExprHelper::GetSingleAssignmentStatementRHS(const TSharedPtr<FScriptExpr>& AssignmentStatement) {
	if (FScriptExprClassification::IsSingleAssignmentOpcode(AssignmentStatement->Opcode)) {
		const int32 LhsOperandIndex = AssignmentStatement->Opcode == EX_Let ? 2 : 1;
		return AssignmentStatement->RequireOperand(LhsOperandIndex, FScriptExprOperand::TypeExpr).Expr;
	}
	return nullptr;
}

TSharedPtr<FScriptExpr> FScriptExprHelper::WrapExpressionWithDefaultContext(const TSharedPtr<FScriptExpr>& Expression) {
	// Since DynamicCast always runs in the original context, and has no effect on object values, we could produce the following code
	// to run any expression in object context at all times: EX_Context(EX_DynamicCast(/Script/CoreUObject.Object, EX_Self), CommonFunctionParameter)

	const TSharedPtr<FScriptExpr> DynamicCastExpression = MakeShared<FScriptExpr>(EX_DynamicCast);
	DynamicCastExpression->Operands.Add(UObject::StaticClass());
	DynamicCastExpression->Operands.Add(MakeShared<FScriptExpr>(EX_Self).ToSharedPtr());

	const TSharedPtr<FScriptExpr> ContextExpression = MakeShared<FScriptExpr>(EX_Context);
	ContextExpression->Operands.Add(DynamicCastExpression);
	// Since this context cannot fail, we do not need to emit a valid skip info or Rvalue reference property
	ContextExpression->Operands.Add(FScriptExprOperand::CreateUnresolvedLabel(nullptr));
	ContextExpression->Operands.Add(static_cast<FProperty*>(nullptr));
	ContextExpression->Operands.Add(Expression);
	return ContextExpression;
}

TSharedPtr<FScriptExpr> FScriptExprHelper::UnwrapExpressionContextChain(const TSharedPtr<FScriptExpr>& Expression) {
	// Resolve the evaluated expression of the context as long as we keep encountering context opcodes
	TSharedPtr<FScriptExpr> ResultExpression = Expression;
	while (ResultExpression && FScriptExprClassification::IsContextOpcode(ResultExpression->Opcode)) {
		ResultExpression = ResultExpression->RequireOperand(3, FScriptExprOperand::TypeExpr).Expr;
	}
	return ResultExpression;
}

TSharedPtr<FScriptExpr> FScriptExprHelper::ExtractExpressionFromContext(const TSharedPtr<FScriptExpr>& Expression) {
	// Find the context expression that defines the context in which we are running. If we have no context switch expression, this expression is already extracted
	const TSharedPtr<FScriptExpr> OuterContextSwitchExpression = GetOuterContextSwitchExpression(Expression);
	if (OuterContextSwitchExpression == nullptr) {
		return Expression->DeepCopy();
	}

	// Retrieve the expression that defines our context, and extract it from its context
	const TSharedPtr<FScriptExpr> ContextExpression = OuterContextSwitchExpression->RequireOperand(0, FScriptExprOperand::TypeExpr).Expr;
	const TSharedPtr<FScriptExpr> ExtractedContextExpression = ExtractExpressionFromContext(ContextExpression);

	// Create a new context switch expression using our newly extracted context
	const uint8 NewContextOpcode = OuterContextSwitchExpression->Opcode == EX_Context_FailSilent ? EX_Context : OuterContextSwitchExpression->Opcode;
	const TSharedPtr<FScriptExpr> NewContextSwitchExpression = MakeShared<FScriptExpr>(NewContextOpcode);

	// Since this context cannot fail, we do not need to emit a valid skip info or Rvalue reference property
	NewContextSwitchExpression->Operands.Add(ExtractedContextExpression);
	NewContextSwitchExpression->Operands.Add(FScriptExprOperand::CreateUnresolvedLabel(nullptr));
	NewContextSwitchExpression->Operands.Add(static_cast<FProperty*>(nullptr));
	NewContextSwitchExpression->Operands.Add(Expression->DeepCopy());
	
	return NewContextSwitchExpression;
}

TSharedPtr<FScriptExpr> FScriptExprHelper::GetOuterContextSwitchExpression(const TSharedPtr<FScriptExpr>& Expression) {
	TSharedPtr<FScriptExpr> PreviousExpressionOuter = Expression;
	TSharedPtr<FScriptExpr> CurrentExpressionOuter = Expression->OuterExpression.Pin();

	// Walk the outer chain until we find a context expression that overrides our context
	while (CurrentExpressionOuter) {
		if (FScriptExprClassification::IsContextOpcode(CurrentExpressionOuter->Opcode)) {

			// Current expression only counts as valid context for the previous expression if previous expression is actually on the RHS of the context expression
			const TSharedPtr<FScriptExpr>& EvaluatedExpression = CurrentExpressionOuter->RequireOperand(3, FScriptExprOperand::TypeExpr).Expr;
			if (EvaluatedExpression == PreviousExpressionOuter) {
				return CurrentExpressionOuter;
			}
		}
		// Continue looking for the outer context expression otherwise
		PreviousExpressionOuter = CurrentExpressionOuter;
		CurrentExpressionOuter = PreviousExpressionOuter->OuterExpression.Pin();
	}
	// We did not find any context expression affecting our context
	return nullptr;
}

bool FScriptExprHelper::IsExpressionPure(const TSharedPtr<FScriptExpr>& Expression) {
	// Only pure opcodes are considered pure expressions
	if (!FScriptExprClassification::IsPureOpcode(Expression->Opcode)) {
		return false;
	}
	// Make sure that all operand expressions of this expression are also pure
	for (const FScriptExprOperand& Operand : Expression->Operands) {
		if (Operand.Type == FScriptExprOperand::TypeExpr && Operand.Expr && !IsExpressionPure(Operand.Expr)) {
			return false;
		}
	}
	// This expression hierarchy is considered pure
	return true;
}

void FScriptExprHelper::PerformReachabilityAnalysis(const TArray<TSharedPtr<FScriptExpr>>& LinearExecutionSequence, const TSharedPtr<FScriptExpr>& EntryPoint, TArray<TSharedPtr<FScriptExpr>>& OutReachableStatements) {
	TMap<TSharedPtr<FScriptExpr>, TArray<TSharedPtr<FScriptExpr>>> StatementToControlFlowDependencies;

	// Generate a graph by listing all potential jump destinations for each statement
	for (int32 StatementIndex = 0; StatementIndex < LinearExecutionSequence.Num(); StatementIndex++) {
		const TSharedPtr<FScriptExpr> TargetStatement = LinearExecutionSequence[StatementIndex];
		TArray<TSharedPtr<FScriptExpr>> StatementControlFlowDependencies;

		// Factor in potential jump targets from the statement operands
		TargetStatement->ForEachOperandRecursive([&](const FScriptExprOperand& Operand) {
			if (Operand.Type == FScriptExprOperand::TypeLabel && Operand.TargetLabel) {
				StatementControlFlowDependencies.Add(Operand.TargetLabel);
			}
		});
		// Factor in next statement as the potential target if this statement is not an unconditional control flow stop
		if (!FScriptExprClassification::IsUnconditionalControlFlowStop(TargetStatement->Opcode) && LinearExecutionSequence.IsValidIndex(StatementIndex + 1)) {
			StatementControlFlowDependencies.Add(LinearExecutionSequence[StatementIndex + 1]);
		}
		StatementToControlFlowDependencies.Add(TargetStatement, StatementControlFlowDependencies);
	}

	// Start at the entry point, and visit all statements that it depends on, as well as their dependencies
	TSet<TSharedPtr<FScriptExpr>> VisitedStatementSet;
	TArray<TSharedPtr<FScriptExpr>> UnvisitedStatements;
	UnvisitedStatements.Add(EntryPoint);
	
	while (!UnvisitedStatements.IsEmpty()) {
		// Mark the current statement as visited
		const TSharedPtr<FScriptExpr> CurrentStatement = UnvisitedStatements.Pop(false);
		VisitedStatementSet.Add(CurrentStatement);

		// Add all statements that have not been visited yet that this statement dependends to the unvisited statements set
		const TArray<TSharedPtr<FScriptExpr>> ControlFlowDependencies = StatementToControlFlowDependencies.FindOrAdd(CurrentStatement);
		for (const TSharedPtr<FScriptExpr>& PotentialNextStatement : ControlFlowDependencies) {
			if (!VisitedStatementSet.Contains(PotentialNextStatement)) {
				UnvisitedStatements.Add(PotentialNextStatement);
			}
		}
	}
	// All reachable statements are all the statements that we have visited at this point
	OutReachableStatements = VisitedStatementSet.Array();
}

void FScriptExprHelper::DumpFunctionToString(const UFunction* Function, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, int32 IndentLevel, FStringBuilderBase& StringBuilder) {
	FString FunctionPrefix;
	for (int32 i = 0; i < IndentLevel; i++) FunctionPrefix.AppendChar(TEXT('\t'));
	// Print function name and flags
	StringBuilder.Appendf(TEXT("%sFunction %s (Flags 0x%x)\n"), *FunctionPrefix, *Function->GetName(), Function->FunctionFlags);

	// Print function locals
	StringBuilder.Appendf(TEXT("%s\tFunction Locals:\n"), *FunctionPrefix);
	for (TFieldIterator<FProperty> PropertyIterator(Function, EFieldIterationFlags::IncludeDeprecated); PropertyIterator; ++PropertyIterator) {
		StringBuilder.Appendf(TEXT("%s\t\t%s: %s (%llx)\n"), *FunctionPrefix, *PropertyIterator->GetName(), *FScriptExprTypeResolver::ResolvePropertyType(*PropertyIterator)->ToString(), PropertyIterator->PropertyFlags);
	}
	StringBuilder.Appendf(TEXT("%s\tFunction Script:\n"), *FunctionPrefix);

	// Print function code
	for (const TSharedPtr<FScriptExpr>& FunctionStatement : FunctionScript) {
		StringBuilder.Appendf(TEXT("%s\t\t0x%x: %s\n"), *FunctionPrefix, FunctionStatement->ScriptOffset, *FunctionStatement->ToString());
	}
}

void FScriptExprHelper::DumpClassToString(const UClass* Class, FStringBuilderBase& StringBuilder) {
	// Print class info
	StringBuilder.Appendf(TEXT("Class %s (Flags 0x%x)\n"), *Class->GetPathName(), Class->ClassFlags);
	if (Class != UObject::StaticClass()) {
		StringBuilder.Appendf(TEXT("\tSuper Class: %s\n"), *Class->GetSuperClass()->GetPathName());
	}

	// Print implemented interfaces
	StringBuilder.Append(TEXT("\tImplemented Interfaces:\n"));
	for (const FImplementedInterface& ImplementedInterface : Class->Interfaces) {
		StringBuilder.Appendf(TEXT("\t\t%s\n"), *ImplementedInterface.Class->GetPathName());
	}
	StringBuilder.Append(TEXT("\n"));
	
	// Print class properties
	StringBuilder.Append(TEXT("\tClass Properties:\n"));
	for (TFieldIterator<FProperty> PropertyIterator(Class, EFieldIterationFlags::IncludeDeprecated); PropertyIterator; ++PropertyIterator) {
		StringBuilder.Appendf(TEXT("\t\t%s: %s (%llx)\n"), *PropertyIterator->GetName(), *FScriptExprTypeResolver::ResolvePropertyType(*PropertyIterator)->ToString(), PropertyIterator->PropertyFlags);
	}
	StringBuilder.Append(TEXT("\n"));

	// Print class functions
	StringBuilder.Append(TEXT("\tClass Functions:\n"));
	for (TFieldIterator<UFunction> FunctionIterator(Class, EFieldIterationFlags::IncludeDeprecated); FunctionIterator; ++FunctionIterator) {
		TArray<TSharedPtr<FScriptExpr>> FunctionScript;
		FScriptExprAssembler::DisassembleFunction(FunctionIterator->Script, FunctionScript);
		DumpFunctionToString(*FunctionIterator, FunctionScript, 2, StringBuilder);
		StringBuilder.Append(TEXT("\n"));
	}
}

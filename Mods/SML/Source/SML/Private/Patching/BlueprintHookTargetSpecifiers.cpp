#include "Patching/BlueprintHookTargetSpecifiers.h"
#include "Toolkit/HookingTargetSpecifier.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

TSharedPtr<FBlueprintHookTargetResolver> UBlueprintHookTargetSpecifier_FunctionEntry::CreateTargetResolver() const {
	return MakeShared<FBlueprintHookTargetResolver_FunctionEntry>();
}

TSharedPtr<FBlueprintHookTargetResolver> UBlueprintHookTargetSpecifier_FunctionExit::CreateTargetResolver() const {
	return MakeShared<FBlueprintHookTargetResolver_FunctionExit>();
}

TSharedPtr<FBlueprintHookTargetResolver> UBlueprintHookTargetSpecifier_ReturnValue::CreateTargetResolver() const {
	return MakeShared<FBlueprintHookTargetResolver_ReturnValue>();
}

TSharedPtr<FBlueprintHookTargetResolver> UBlueprintHookTargetSpecifier_OuterExpression::CreateTargetResolver() const {
	return MakeShared<FBlueprintHookTargetResolver_OuterExpression>(InnerExpression->CreateTargetResolver());
}

TSharedPtr<FBlueprintHookTargetResolver> UBlueprintHookTargetSpecifier_ExpressionOperand::CreateTargetResolver() const {
	return MakeShared<FBlueprintHookTargetResolver_ExpressionOperand>(Expression->CreateTargetResolver(), OperandIndex);
}

TSharedPtr<FBlueprintHookTargetResolver> UBlueprintHookTargetSpecifier_PropertyAccess::CreateTargetResolver() const {
	if (FProperty* ResolvedProperty = TargetProperty.ResolveMember<FProperty>()) {
		return MakeShared<FBlueprintHookTargetResolver_PropertyAccess>(ResolvedProperty);
	}
	return nullptr;
}

TSharedPtr<FBlueprintHookTargetResolver> UBlueprintHookTargetSpecifier_PropertySingleAssignment::CreateTargetResolver() const {
	if (FProperty* ResolvedProperty = TargetProperty.ResolveMember<FProperty>()) {
		return MakeShared<FBlueprintHookTargetResolver_PropertySingleAssignment>(ResolvedProperty);
	}
	return nullptr;
}

TSharedPtr<FBlueprintHookTargetResolver> UBlueprintHookTargetSpecifier_FunctionCall::CreateTargetResolver() const {
	if (UFunction* ResolvedFunctionObject = TargetFunction.ResolveMember<UFunction>()) {
		return MakeShared<FBlueprintHookTargetResolver_FunctionCall>(ResolvedFunctionObject);
	}
	return nullptr;
}

TSharedPtr<FBlueprintHookTargetResolver> UBlueprintHookTargetSpecifier_Constant::CreateTargetResolver() const {
	switch(ConstantType) {
		case EHookTargetConstantType::Integer: return FBlueprintHookTargetResolver_Constant::CreateIntConstant(SignedIntegerValue);
		case EHookTargetConstantType::UnsignedInteger: return FBlueprintHookTargetResolver_Constant::CreateIntConstant(UnsignedIntegerValue);
		case EHookTargetConstantType::FloatingPoint: return FBlueprintHookTargetResolver_Constant::CreateDoubleConstant(FloatingPointValue, FloatingPointEpsilon);
		case EHookTargetConstantType::Name: return FBlueprintHookTargetResolver_Constant::CreateNameConstant(FName(*StringValue));
		case EHookTargetConstantType::String: return FBlueprintHookTargetResolver_Constant::CreateStringConstant(StringValue);
		case EHookTargetConstantType::Object: return FBlueprintHookTargetResolver_Constant::CreateObjectConstant(ObjectValue.LoadSynchronous());
		default: return nullptr;
	}
}

TSharedPtr<FBlueprintHookTargetResolver> UBlueprintHookTargetSpecifier_TargetSelector::CreateTargetResolver() const {
	return MakeShared<FBlueprintHookTargetResolver_TargetSelectionMode>(InnerExpression->CreateTargetResolver(), TargetSelectionMode, TargetOrdinal);
}

#if WITH_EDITOR

FText UBlueprintHookTargetSpecifier_FunctionEntry::GetTargetSpecifierTitle() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_FunctionEntry_Title", "Function Entry Statement");
}

FText UBlueprintHookTargetSpecifier_FunctionEntry::GetTargetSpecifierDescription() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_FunctionEntry_Description", "A Target Specifier that resolves into the First Statement in the Target Function.");
}

FText UBlueprintHookTargetSpecifier_FunctionExit::GetTargetSpecifierTitle() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_FunctionExit_Title", "Function Exit Statement");
}

FText UBlueprintHookTargetSpecifier_FunctionExit::GetTargetSpecifierDescription() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_FunctionExit_Description", "A Target Specifier that resolves into the Exit Statement in the Target Statement (also known as Return Statement).");
}

FText UBlueprintHookTargetSpecifier_ReturnValue::GetTargetSpecifierTitle() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_ReturnValue_Title", "Return Value Expression");
}

FText UBlueprintHookTargetSpecifier_ReturnValue::GetTargetSpecifierDescription() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_ReturnValue_Description", "A Target Specifier that resolves into the Return Value Expression in the Target Function. \nTarget Function must have a Return Value.");
}

FText UBlueprintHookTargetSpecifier_OuterExpression::GetTargetSpecifierTitle() const{
	return LOCTEXT("BlueprintHookTargetSpecifier_OuterExpression_Title", "Outer Expression");
}

FText UBlueprintHookTargetSpecifier_OuterExpression::GetTargetSpecifierDescription() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_OuterExpression_Description", "Targets an Expression that is the Outer Expression of the provided Expression. \nIf Expression is a Function Argument, Outer Expression is a Function Call.");
}

FText UBlueprintHookTargetSpecifier_ExpressionOperand::GetTargetSpecifierTitle() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_ExpressionOperand_Title", "Expression Operand");
}

FText UBlueprintHookTargetSpecifier_ExpressionOperand::GetTargetSpecifierDescription() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_ExpressionOperand_Description", "Returns a numbered Operand of the targeted Expression. \nIf Expression is a Function Call, Expression Operand 0 is its first Argument.");
}

FText UBlueprintHookTargetSpecifier_PropertyAccess::GetTargetSpecifierTitle() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_PropertyAccess_Title", "Property Read");
}

FText UBlueprintHookTargetSpecifier_PropertyAccess::GetTargetSpecifierDescription() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_PropertyAccess_Description", "Returns all expressions reading a value from the given Property. \nProperty Writes are not included into the results, but writes that happen by ref might be.");
}

FText UBlueprintHookTargetSpecifier_PropertySingleAssignment::GetTargetSpecifierTitle() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_PropertySingleAssignment_Title", "Property Assignment");
}

FText UBlueprintHookTargetSpecifier_PropertySingleAssignment::GetTargetSpecifierDescription() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_PropertySingleAssignment_Description", "Returns Right Hand Side (RHS) Expression that will be written to the provided Property. \nNote that multi-initializers (container initialization such as array and map) are not targeted.");
}

FText UBlueprintHookTargetSpecifier_FunctionCall::GetTargetSpecifierTitle() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_FunctionCall_Title", "Function Call");
}

FText UBlueprintHookTargetSpecifier_FunctionCall::GetTargetSpecifierDescription() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_FunctionCall_Description", "Returns all expressions (and statements) that represent Function Calls to the provided Function Object. \nIf function is virtual (overridable), calls to overrides are also included in the results.");
}

FText UBlueprintHookTargetSpecifier_Constant::GetTargetSpecifierTitle() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_Constant_Title", "Constant");
}

FText UBlueprintHookTargetSpecifier_Constant::GetTargetSpecifierDescription() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_Constant_Description", "Returns all expressions that denote a provided Constant Value, such as Integer, String or Object.");
}

FText UBlueprintHookTargetSpecifier_TargetSelector::GetTargetSpecifierTitle() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_TargetSelector_Title", "Target Selector");
}

FText UBlueprintHookTargetSpecifier_TargetSelector::GetTargetSpecifierDescription() const {
	return LOCTEXT("BlueprintHookTargetSpecifier_TargetSelector_Description", "Filters results of matching the provided Inner Expression and returns only one of them based on the provided Selection Mode.");
}

#endif

#undef LOCTEXT_NAMESPACE

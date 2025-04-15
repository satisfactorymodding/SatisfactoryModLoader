#pragma once

#include "CoreMinimal.h"
#include "ScriptExprAssembler.h"
#include "Patching/BlueprintHookingTypes.h"

class SML_API FBlueprintHookTargetResolver {
public:
	virtual ~FBlueprintHookTargetResolver() = default;

	/** Resolves hooking target sites for this hook */
	virtual void ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const = 0;
};

class SML_API FBlueprintHookTargetResolver_Constant final : public FBlueprintHookTargetResolver {
	int32 ConstantOpcode{};
	FScriptExprOperand ConstantValue;
	double FloatEpsilon{};
public:
	FBlueprintHookTargetResolver_Constant(uint8 InConstantOpcode, const FScriptExprOperand& InConstantValue, double InFloatEpsilon = UE_KINDA_SMALL_NUMBER);

	static TSharedPtr<FBlueprintHookTargetResolver> CreateIntConstant(int64 InIntegerValue);
	static TSharedPtr<FBlueprintHookTargetResolver> CreateUIntConstant(uint64 InIntegerValue);
	static TSharedPtr<FBlueprintHookTargetResolver> CreateNameConstant(const FName& InNameValue);
	static TSharedPtr<FBlueprintHookTargetResolver> CreateStringConstant(const FString& InStringValue);
	static TSharedPtr<FBlueprintHookTargetResolver> CreateDoubleConstant(double InFloatValue, double InFloatEpsilon);
	static TSharedPtr<FBlueprintHookTargetResolver> CreateObjectConstant(const UObject* InObjectValue);

	// Begin FBlueprintHookTargetResolver interface
	virtual void ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const override;
	// End FBlueprintHookTargetResolver interface
};

class SML_API FBlueprintHookTargetResolver_FunctionCall final : public FBlueprintHookTargetResolver {
	UFunction* FunctionCallTarget{};
public:
	explicit FBlueprintHookTargetResolver_FunctionCall(UFunction* InFunctionCallTarget);

	// Begin FBlueprintHookTargetResolver interface
	virtual void ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const override;
	// End FBlueprintHookTargetResolver interface
};

class SML_API FBlueprintHookTargetResolver_PropertyAccess final : public FBlueprintHookTargetResolver {
	FProperty* PropertyTarget{};
public:
	explicit FBlueprintHookTargetResolver_PropertyAccess(FProperty* InPropertyTarget);

	// Begin FBlueprintHookTargetResolver interface
	virtual void ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const override;
	// End FBlueprintHookTargetResolver interface
};

class SML_API FBlueprintHookTargetResolver_PropertySingleAssignment final : public FBlueprintHookTargetResolver {
	FProperty* PropertyTarget{};
public:
	explicit FBlueprintHookTargetResolver_PropertySingleAssignment(FProperty* InPropertyTarget);

	// Begin FBlueprintHookTargetResolver interface
	virtual void ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const override;
	// End FBlueprintHookTargetResolver interface
};

class SML_API FBlueprintHookTargetResolver_ReturnValue final : public FBlueprintHookTargetResolver {
public:
	// Begin FBlueprintHookTargetResolver interface
	virtual void ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const override;
	// End FBlueprintHookTargetResolver interface
};

class SML_API FBlueprintHookTargetResolver_FunctionExit final : public FBlueprintHookTargetResolver {
public:
	// Begin FBlueprintHookTargetResolver interface
	virtual void ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const override;
	// End FBlueprintHookTargetResolver interface
};

class SML_API FBlueprintHookTargetResolver_FunctionEntry final : public FBlueprintHookTargetResolver {
public:
	// Begin FBlueprintHookTargetResolver interface
	virtual void ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const override;
	// End FBlueprintHookTargetResolver interface
};

class SML_API FBlueprintHookTargetResolver_OuterExpression final : public FBlueprintHookTargetResolver {
protected:
	TSharedPtr<FBlueprintHookTargetResolver> InnerExpression;
public:
	explicit FBlueprintHookTargetResolver_OuterExpression(const TSharedPtr<FBlueprintHookTargetResolver>& InInnerExpression);

	// Begin FBlueprintHookTargetResolver interface
	virtual void ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const override;
	// End FBlueprintHookTargetResolver interface
};

class SML_API FBlueprintHookTargetResolver_ExpressionOperand final : public FBlueprintHookTargetResolver {
protected:
	TSharedPtr<FBlueprintHookTargetResolver> InnerExpression;
	int32 OperandIndex{0};
public:
	explicit FBlueprintHookTargetResolver_ExpressionOperand(const TSharedPtr<FBlueprintHookTargetResolver>& InInnerExpression, const int32 InOperandIndex);
	
	// Begin FBlueprintHookTargetResolver interface
	virtual void ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const override;
	// End FBlueprintHookTargetResolver interface
};

class SML_API FBlueprintHookTargetResolver_TargetSelectionMode final : public FBlueprintHookTargetResolver {
protected:
	TSharedPtr<FBlueprintHookTargetResolver> InnerExpression;
	EBlueprintFunctionHookTargetSelectionMode TargetSelectionMode{EBlueprintFunctionHookTargetSelectionMode::Single};
	int32 CustomOrdinal{0};
public:
	explicit FBlueprintHookTargetResolver_TargetSelectionMode(const TSharedPtr<FBlueprintHookTargetResolver>& InInnerExpression, EBlueprintFunctionHookTargetSelectionMode InTargetSelectionMode, int32 InCustomOrdinal);
	
	// Begin FBlueprintHookTargetResolver interface
	virtual void ResolveTargets(UFunction* TargetFunction, const TArray<TSharedPtr<FScriptExpr>>& FunctionScript, const TSharedPtr<FScriptExpr>& ReturnStatement, TArray<TSharedPtr<FScriptExpr>>& OutTargetExpressions) const override;
	// End FBlueprintHookTargetResolver interface
	
	/** Apply target selection mode to filter the target expressions */
	static TArray<TSharedPtr<FScriptExpr>> ApplyTargetSelectionMode(EBlueprintFunctionHookTargetSelectionMode SelectionMode, int32 TargetOrdinal, const TArray<TSharedPtr<FScriptExpr>>& TargetExpressions);
};

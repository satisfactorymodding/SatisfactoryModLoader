// ReSharper disable CppNonExplicitConvertingConstructor
#pragma once

#include "CoreMinimal.h"

class FScriptExpr;

struct FScriptExprOperand {
	enum EScriptExprOperand {
		TypeNull, TypeExpr, TypeScriptName, TypeLabel, TypeProperty, TypeObject, TypeInteger, TypeFloat, TypeString
	};
	EScriptExprOperand Type{TypeNull};
	TSharedPtr<FScriptExpr> Expr;
	FScriptName ScriptName;
	int32 TargetLabelCodeOffset{};
	TSharedPtr<FScriptExpr> TargetLabel;
	FProperty* Property{};
	UObject* Object{};
	uint64 Integer{0};
	double Float{0.0f};
	FString String;

	// Conversion constructors for complex types
	FORCEINLINE FScriptExprOperand() = default;
	FORCEINLINE FScriptExprOperand(TSharedPtr<FScriptExpr> Expr) : Type(TypeExpr), Expr(MoveTemp(Expr)) {}
	FORCEINLINE FScriptExprOperand(const FScriptName& ScriptName) : Type(TypeScriptName), ScriptName(ScriptName) {}
	FORCEINLINE FScriptExprOperand(const FString& String) : Type(TypeString), String(String) {}
	// Conversion constructors for raw pointer types
	FORCEINLINE FScriptExprOperand(FProperty* Property) : Type(TypeProperty), Property(Property) {}
	FORCEINLINE FScriptExprOperand(UObject* Object) : Type(TypeObject), Object(Object) {}
	// Conversion constructors for trivial integral types
	template<typename IntegralType> requires(std::is_integral_v<IntegralType>)
	FORCEINLINE FScriptExprOperand(const IntegralType Integer) : Type(TypeInteger), Integer(Integer) {}
	template<typename FloatingType> requires(std::is_floating_point_v<FloatingType>)
	FORCEINLINE FScriptExprOperand(const FloatingType Float) : Type(TypeFloat),  Float(Float) {}

	// Absolute code offset is absolute, starting at 0 and ending at the script size
	static FScriptExprOperand CreateResolvedLabel(const int32 InAbsoluteCodeOffset) {
		FScriptExprOperand ResultOperand;
		ResultOperand.Type = TypeLabel;
		ResultOperand.TargetLabel = nullptr;
		ResultOperand.TargetLabelCodeOffset = InAbsoluteCodeOffset;
		return ResultOperand;
	}

	/** Creates an absolute code offset operand using a label that should be resolved when assembling the instruction stream */
	static FScriptExprOperand CreateUnresolvedLabel(const TSharedPtr<FScriptExpr>& TargetLabel) {
		FScriptExprOperand ResultOperand;
		ResultOperand.Type = TypeLabel;
		ResultOperand.TargetLabel = TargetLabel;
		ResultOperand.TargetLabelCodeOffset = INDEX_NONE;
		return ResultOperand;
	}

	/** Returns true if operands are identical */
	friend bool operator==(const FScriptExprOperand& A, const FScriptExprOperand& B);

	/** Prints this operand to string */
	void PrintOperand(FStringBuilderBase& StringBuilder) const;
};

class SML_API FScriptExpr : public TSharedFromThis<FScriptExpr> {
public:
	int32 ScriptOffset{0};
	uint8 Opcode{0};
	TArray<FScriptExprOperand> Operands;
	TWeakPtr<FScriptExpr> OuterExpression;

	FScriptExpr() = default;
	FScriptExpr(const uint8 Opcode) : Opcode(Opcode) {}

	/** Recursively iterates this expression and all of its sub expressions */
	template<typename InLambdaT>
	FORCEINLINE void ForEachExpressionRecursive(InLambdaT InLambda) {
		InLambda(AsShared());
		for (const FScriptExprOperand& Operand : Operands) {
			if (Operand.Type == FScriptExprOperand::TypeExpr && Operand.Expr) {
				Operand.Expr->ForEachExpressionRecursive(InLambda);
			}
		}
	}
	/** Recursively iterates all operands for this expression */
	template<typename InLambdaT>
	FORCEINLINE void ForEachOperandRecursive(InLambdaT InLambda) {
		for (FScriptExprOperand& Operand : Operands) {
			InLambda(Operand);
			if (Operand.Type == FScriptExprOperand::TypeExpr && Operand.Expr) {
				Operand.Expr->ForEachOperandRecursive(InLambda);
			}
		}
	}

	/** Requires that this expression have the operand of the given type at the given position */
	const FScriptExprOperand& RequireOperand(int32 InOperandIndex, FScriptExprOperand::EScriptExprOperand InOperandType);

	/** Returns the statement that this expression belongs to, e.g. a top level expression */
	TSharedPtr<FScriptExpr> GetStatement();

	/** Copies this expression and it's operand tree. Does not copy labels */
	TSharedPtr<FScriptExpr> DeepCopy() const;

	/** Prints this expression to string */
	void PrintExpression(FStringBuilderBase& StringBuilder) const;

	/** Prints this expression (or statement) to the string and returns it */
	FString ToString() const;
};

/** Handles assembling and disassembling of script bytecode streams */
class SML_API FScriptExprAssembler {
public:
	/** Disassembles the script input stream into an individual instruction and its operands */
	static TSharedPtr<FScriptExpr> DisassembleScriptExpr(const uint8* ScriptData, int32& ScriptOffset, const TSharedPtr<FScriptExpr> OuterExpression = nullptr);

	/** Assembles individual instruction and its operands into a script stream */
	static void AssembleScriptExpr(TArray<uint8>& OutScriptData, int32& ScriptOffset, const TSharedPtr<FScriptExpr>& Expr);

	/** Returns the human-readable name of the opcode for the provided code */
	static const TCHAR* GetInstructionName(uint8 InOpcode);

	/** Disassembles the function script until it reaches the end of the script or the end of script statement */
	static void DisassembleFunction(const TArray<uint8>& ScriptBytecode, TArray<TSharedPtr<FScriptExpr>>& OutLinearExecutionSequence);

	/** Assembles the provided statement list into a function bytecode stream */
	static void AssembleFunction(const TArray<TSharedPtr<FScriptExpr>>& LinearExecutionSequence, TArray<uint8>& OutScriptBytecode);
};

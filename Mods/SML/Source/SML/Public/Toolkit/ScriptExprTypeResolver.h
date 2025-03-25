// ReSharper disable CppNonExplicitConvertingConstructor
#pragma once

#include "CoreMinimal.h"

class FScriptExprType;
class FScriptExpr;
class FFieldClass;

/** Describes an operand to the expression type */
struct SML_API FScriptExprTypeOperand {
	enum EScriptExprTypeOperand {
		TypeNull, TypeObject, TypeExprType
	};
	EScriptExprTypeOperand Type{TypeNull};
	UObject* Object{};
	TSharedPtr<FScriptExprType> ExprType;

	FScriptExprTypeOperand() = default;
	FScriptExprTypeOperand(UObject* Object) : Type(TypeObject), Object(Object) {}
	FScriptExprTypeOperand(const TSharedPtr<FScriptExprType>& ExprType) : Type(TypeExprType), ExprType(ExprType) {}

	/** Returns true if two operands are identical, e.g. point to the identical struct or expression type */
	friend bool operator==(const FScriptExprTypeOperand& A, const FScriptExprTypeOperand& B);

	/** Prints this type operand to the string builder */
	void PrintExpressionTypeOperand(FStringBuilderBase& StringBuilder) const;
};

/** Describes a type of the script expression */
class SML_API FScriptExprType : public TSharedFromThis<FScriptExprType> {
public:
	FFieldClass* PropertyType{};
	TArray<FScriptExprTypeOperand> Operands;

	FScriptExprType() = default;
	explicit FScriptExprType(FFieldClass* PropertyClass) : PropertyType(PropertyClass) {}

	/** Returns true if this expression type is of the provided property type or its subtype */
	bool IsA(const FFieldClass* InPropertyClass) const;

	/** Returns the operand at the specific index after checking its type and the property type of the type */
	const FScriptExprTypeOperand& RequireOperand(int32 InOperandIndex, FScriptExprTypeOperand::EScriptExprTypeOperand InOperandType, const FFieldClass* InPropertyClass = nullptr) const;

	/** This will also check implemented interface as well as the property class */
	UFunction* FindFunctionInObjectPropertyClass(const FName& FunctionName) const;

	/** Returns true if this type is identical to another type */
	bool Identical(const TSharedPtr<FScriptExprType>& Other) const;

	/** Prints type of this expression to the string builder */
	void PrintExpressionType(FStringBuilderBase& StringBuilder) const;

	/** Prints this type to a newly allocated string */
	FString ToString() const;

	/** Returns true if this expression type is of the provided property type or its subtype */
	template<typename InPropertyType>
	FORCEINLINE bool IsA() const {
		return IsA(InPropertyType::StaticClass());
	}

	/** Returns the operand at the specific index */
	template<typename InPropertyType>
	const FScriptExprTypeOperand& RequireOperand(int32 InOperandIndex, FScriptExprTypeOperand::EScriptExprTypeOperand InOperandType) const {
		return RequireOperand(InOperandIndex, InOperandType, InPropertyType::StaticClass());
	}

	/** Creates an expression type of nothing */
	static TSharedPtr<FScriptExprType> CreateNothing() { return MakeShared<FScriptExprType>(); }
	/** Creates a property type with no additional data */
	static TSharedPtr<FScriptExprType> CreateProperty(FFieldClass* PropertyClass) { return MakeShared<FScriptExprType>(PropertyClass); }

	/** Creates a property type with no additional data */
	template<typename InPropertyType>
	FORCEINLINE static TSharedPtr<FScriptExprType> CreateProperty() { return CreateProperty(InPropertyType::StaticClass()); }

	/** These are implemented in CPP file to avoid having to include UnrealType.h and others */
	static TSharedPtr<FScriptExprType> CreateObjectProperty(UClass* PropertyClass, UClass* ImplementedInterface = nullptr);
	static TSharedPtr<FScriptExprType> CreateInterfaceProperty(UClass* InterfaceClass);
	static TSharedPtr<FScriptExprType> CreateClassProperty(UClass* MetaClass, UClass* PropertyClass = nullptr);
	static TSharedPtr<FScriptExprType> CreateStructProperty(UScriptStruct* ScriptStruct);
	static TSharedPtr<FScriptExprType> CreateDelegateProperty(UFunction* DelegateSignatureFunction);
	static TSharedPtr<FScriptExprType> CreateMulticastDelegateProperty(FFieldClass* DelegatePropertyClass, UFunction* DelegateSignatureFunction);
	static TSharedPtr<FScriptExprType> CreateArrayProperty(const TSharedPtr<FScriptExprType>& ElementProperty);
	static TSharedPtr<FScriptExprType> CreateSetProperty(const TSharedPtr<FScriptExprType>& ElementProperty);
	static TSharedPtr<FScriptExprType> CreateMapProperty(const TSharedPtr<FScriptExprType>& KeyProperty, const TSharedPtr<FScriptExprType>& ValueProperty);
	static TSharedPtr<FScriptExprType> CreateOptionalProperty(const TSharedPtr<FScriptExprType>& ValueProperty);
	static TSharedPtr<FScriptExprType> CreateByteProperty(UEnum* InEnum);
	static TSharedPtr<FScriptExprType> CreateEnumProperty(UEnum* InEnum, const TSharedPtr<FScriptExprType>& UnderlyingProp);
};

/** Resolves type of the script expressions */
class SML_API FScriptExprTypeResolver {
public:
	/** Returns the type of the provided script expression */
	static TSharedPtr<FScriptExprType> ResolveExpressionType(const TSharedPtr<FScriptExpr>& Expr, UClass* OwnerFunctionOuterClass);

	/** Returns the type of the provided script expression. Takes explicit context type */
	static TSharedPtr<FScriptExprType> ResolveExpressionTypeWithExplicitContext(const TSharedPtr<FScriptExpr>& Expr, const TSharedPtr<FScriptExprType>& ContextType);

	/** Creates a property expression type from a property instance */
	static TSharedPtr<FScriptExprType> ResolvePropertyType(const FProperty* Property);
};

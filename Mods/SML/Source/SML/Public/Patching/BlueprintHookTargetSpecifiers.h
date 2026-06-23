#pragma once

#include "CoreMinimal.h"
#include "BlueprintHookingTypes.h"
#include "Engine/MemberReference.h"
#include "BlueprintHookTargetSpecifiers.generated.h"

UCLASS()
class SML_API UBlueprintHookTargetSpecifier_FunctionEntry : public UBlueprintHookTargetSpecifier {
	GENERATED_BODY()
public:
	// Begin UBlueprintHookTargetSpecifier interface
	virtual TSharedPtr<FBlueprintHookTargetResolver> CreateTargetResolver() const override;
#if WITH_EDITOR
	virtual FText GetTargetSpecifierTitle() const override;
	virtual FText GetTargetSpecifierDescription() const override;
	virtual bool IsStatementOnlyTarget() const override { return true; }
#endif
	// End UBlueprintHookTargetSpecifier interface
};

UCLASS()
class SML_API UBlueprintHookTargetSpecifier_FunctionExit : public UBlueprintHookTargetSpecifier {
	GENERATED_BODY()
public:
	// Begin UBlueprintHookTargetSpecifier interface
	virtual TSharedPtr<FBlueprintHookTargetResolver> CreateTargetResolver() const override;
#if WITH_EDITOR
	virtual FText GetTargetSpecifierTitle() const override;
	virtual FText GetTargetSpecifierDescription() const override;
	virtual bool IsStatementOnlyTarget() const override { return true; }
#endif
	// End UBlueprintHookTargetSpecifier interface
};

UCLASS()
class SML_API UBlueprintHookTargetSpecifier_ReturnValue : public UBlueprintHookTargetSpecifier {
	GENERATED_BODY()
public:
	// Begin UBlueprintHookTargetSpecifier interface
	virtual TSharedPtr<FBlueprintHookTargetResolver> CreateTargetResolver() const override;
#if WITH_EDITOR
	virtual FText GetTargetSpecifierTitle() const override;
	virtual FText GetTargetSpecifierDescription() const override;
#endif
	// End UBlueprintHookTargetSpecifier interface
};

UCLASS()
class SML_API UBlueprintHookTargetSpecifier_OuterExpression : public UBlueprintHookTargetSpecifier {
	GENERATED_BODY()
public:
	/** The expression that this target should get the outer expression from */
	UPROPERTY(meta = (GraphPin))
	TObjectPtr<UBlueprintHookTargetSpecifier> InnerExpression{};
	
	// Begin UBlueprintHookTargetSpecifier interface
	virtual TSharedPtr<FBlueprintHookTargetResolver> CreateTargetResolver() const override;
#if WITH_EDITOR
	virtual FText GetTargetSpecifierTitle() const override;
	virtual FText GetTargetSpecifierDescription() const override;
#endif
	// End UBlueprintHookTargetSpecifier interface
};

UCLASS()
class SML_API UBlueprintHookTargetSpecifier_ExpressionOperand : public UBlueprintHookTargetSpecifier {
	GENERATED_BODY()
public:
	/** The expression operand of which we should retrieve */
	UPROPERTY(meta = (GraphPin))
	TObjectPtr<UBlueprintHookTargetSpecifier> Expression{};

	/** Index of the operand that this specifier should target in the provided expression. Indices are zero-based. Non-expression operands are not considered */
	UPROPERTY(EditAnywhere, Category = "Expression Operand")
	int32 OperandIndex{0};
	
	// Begin UBlueprintHookTargetSpecifier interface
	virtual TSharedPtr<FBlueprintHookTargetResolver> CreateTargetResolver() const override;
#if WITH_EDITOR
	virtual FText GetTargetSpecifierTitle() const override;
	virtual FText GetTargetSpecifierDescription() const override;
#endif
	// End UBlueprintHookTargetSpecifier interface
};

UCLASS()
class SML_API UBlueprintHookTargetSpecifier_PropertyAccess : public UBlueprintHookTargetSpecifier {
	GENERATED_BODY()
public:
	/** Property the access to which we should target */
	UPROPERTY(meta = (MemberReference, PropertyReference))
	FMemberReference TargetProperty;
	
	// Begin UBlueprintHookTargetSpecifier interface
	virtual TSharedPtr<FBlueprintHookTargetResolver> CreateTargetResolver() const override;
#if WITH_EDITOR
	virtual FText GetTargetSpecifierTitle() const override;
	virtual FText GetTargetSpecifierDescription() const override;
#endif
	// End UBlueprintHookTargetSpecifier interface
};

UCLASS()
class SML_API UBlueprintHookTargetSpecifier_PropertySingleAssignment : public UBlueprintHookTargetSpecifier {
	GENERATED_BODY()
public:
	/** Property the assignment to which we should target */
	UPROPERTY(meta = (MemberReference, PropertyReference))
	FMemberReference TargetProperty;
	
	// Begin UBlueprintHookTargetSpecifier interface
	virtual TSharedPtr<FBlueprintHookTargetResolver> CreateTargetResolver() const override;
#if WITH_EDITOR
	virtual FText GetTargetSpecifierTitle() const override;
	virtual FText GetTargetSpecifierDescription() const override;
#endif
	// End UBlueprintHookTargetSpecifier interface
};

UCLASS()
class SML_API UBlueprintHookTargetSpecifier_FunctionCall : public UBlueprintHookTargetSpecifier {
	GENERATED_BODY()
public:
	/** Function the call to which we should target */
	UPROPERTY(meta = (MemberReference))
	FMemberReference TargetFunction;
	
	// Begin UBlueprintHookTargetSpecifier interface
	virtual TSharedPtr<FBlueprintHookTargetResolver> CreateTargetResolver() const override;
#if WITH_EDITOR
	virtual FText GetTargetSpecifierTitle() const override;
	virtual FText GetTargetSpecifierDescription() const override;
#endif
	// End UBlueprintHookTargetSpecifier interface
};

/** Possible types of constants to target */
UENUM()
enum class EHookTargetConstantType : uint8 {
	/** Signed integer constant (Int) */
	Integer,
	/** Unsigned integer constant (Byte and UInt64) */
	UnsignedInteger,
	/** String constant */
	String,
	/** FName constant */
	Name,
	/** Float or Double constant */
	FloatingPoint,
	/** Object constant */
	Object
};

UCLASS()
class SML_API UBlueprintHookTargetSpecifier_Constant : public UBlueprintHookTargetSpecifier {
	GENERATED_BODY()
public:
	/** Type of the constant that this specifier will target */
	UPROPERTY(EditAnywhere, Category = "Constant")
	EHookTargetConstantType ConstantType{EHookTargetConstantType::Integer};
	
	/** If this is a unsigned integer constant, this is a constants value */
	UPROPERTY(EditAnywhere, Category = "Constant", meta = (DisplayName = "Value", EditConditionHides, EditCondition = "ConstantType == EHookTargetConstantType::UnsignedInteger"))
	uint64 UnsignedIntegerValue{0};

	/** If this is a signed integer constant, this is a constants value */
	UPROPERTY(EditAnywhere, Category = "Constant", meta = (DisplayName = "Value", EditConditionHides, EditCondition = "ConstantType == EHookTargetConstantType::Integer"))
	int64 SignedIntegerValue{0};

	/** If this is a string or a name constant, this is the value that we will target */
	UPROPERTY(EditAnywhere, Category = "Constant", meta = (DisplayName = "Value", EditConditionHides, EditCondition = "ConstantType == EHookTargetConstantType::String || ConstantType == EHookTargetConstantType::Name"))
	FString StringValue;

	/** If this is a floating point constant, this is the value that we will target */
	UPROPERTY(EditAnywhere, Category = "Constant", meta = (DisplayName = "Value", EditConditionHides, EditCondition = "ConstantType == EHookTargetConstantType::FloatingPoint"))
	double FloatingPointValue{0.0f};

	/** If this is a floating point constant, this is epsilon */
	UPROPERTY(EditAnywhere, Category = "Constant", meta = (DisplayName = "Epsilon", EditConditionHides, EditCondition = "ConstantType == EHookTargetConstantType::FloatingPoint"))
	double FloatingPointEpsilon{0.0f};

	/** If this is an object constant, this is a path to the object */
	UPROPERTY(EditAnywhere, Category = "Constant", meta = (DisplayName = "Value", EditConditionHides, EditCondition = "ConstantType == EHookTargetConstantType::Object"))
	TSoftObjectPtr<UObject> ObjectValue;

	// Begin UBlueprintHookTargetSpecifier interface
	virtual TSharedPtr<FBlueprintHookTargetResolver> CreateTargetResolver() const override;
#if WITH_EDITOR
	virtual FText GetTargetSpecifierTitle() const override;
	virtual FText GetTargetSpecifierDescription() const override;
#endif
	// End UBlueprintHookTargetSpecifier interface
};

UCLASS()
class SML_API UBlueprintHookTargetSpecifier_TargetSelector : public UBlueprintHookTargetSpecifier {
	GENERATED_BODY()
public:
	/** The expression result of matching which we should filter */
	UPROPERTY(meta = (GraphPin))
	TObjectPtr<UBlueprintHookTargetSpecifier> InnerExpression{};
	
	/** Selection Mode for the Inner Expression results */
	UPROPERTY(EditAnywhere, Category = "Target Selector")
	EBlueprintFunctionHookTargetSelectionMode TargetSelectionMode{EBlueprintFunctionHookTargetSelectionMode::Single};

	/** Ordinal of the result that this selector will return */
	UPROPERTY(EditAnywhere, Category = "Target Selector", meta = (EditConditionHides, EditCondition = "TargetSelectionMode == EBlueprintFunctionHookTargetSelectionMode::Ordinal"))
	int32 TargetOrdinal{0};
	
	// Begin UBlueprintHookTargetSpecifier interface
	virtual TSharedPtr<FBlueprintHookTargetResolver> CreateTargetResolver() const override;
#if WITH_EDITOR
	virtual FText GetTargetSpecifierTitle() const override;
	virtual FText GetTargetSpecifierDescription() const override;
#endif
	// End UBlueprintHookTargetSpecifier interface
};

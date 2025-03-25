#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BlueprintHookingTypes.generated.h"

class FBlueprintHookTargetResolver;

/** Parent class for static blueprint hooks */
UCLASS(Abstract, Blueprintable, BlueprintInternalUseOnly, meta = (ShowWorldContextPin))
class SML_API UStaticBlueprintHook : public UObject {
	GENERATED_BODY()
};

UENUM()
enum class EBlueprintFunctionHookType : uint8 {
	Invalid,
	InsertionHook,
	RedirectHook,
};

UENUM()
enum class EBlueprintFunctionHookInsertLocation : uint8 {
	Invalid UMETA(Hidden),
	BeforeTarget,
	AfterTarget,
	ReplaceTarget,
};

/** Possible resolution modes when multiple applicable hook targets are found */
UENUM()
enum class EBlueprintFunctionHookTargetSelectionMode : uint8 {
	/** Install hook on a single target. If multiple targets are found, hook application fails */
	Single UMETA(DisplayName = "Single (Single, Error If Multiple)"),
	/** Install hook on the first found target if there are multiple */
	First UMETA(DisplayName = "First (Single)"),
	/** Install hook on the last found target if there are multiple */
	Last UMETA(DisplayName = "Last (Single)"),
	/** Hook will be installed on all matching targets */
	All UMETA(DisplayName = "All (Multiple)"),
	/** Hook will be installed at a call site with the specific ordinal. Ordinal numbers start at 0 for the first target */
	Ordinal UMETA(DisplayName = "Ordinal (Single, Target N)")
};

/** Abstract class for target resolvers */
UCLASS(Abstract)
class SML_API UBlueprintHookTargetSpecifier : public UObject
{
	GENERATED_BODY()
public:
	/** Creates a target resolver using the data from this object */
	virtual TSharedPtr<FBlueprintHookTargetResolver> CreateTargetResolver() const { return nullptr; }

#if WITH_EDITOR
	/** Returns the name of the target specifier to be used as the name of the node */
	virtual FText GetTargetSpecifierTitle() const { return FText::GetEmpty(); }

	/** Returns the description of the target specifier node */
	virtual FText GetTargetSpecifierDescription() const { return FText::GetEmpty(); }

	/** Returns true if node spawner should automatically be created for this target specifier */
	virtual bool ShouldCreateNodeSpawnerForTargetSpecifier() const { return true; }
	
	/** Returns true if this specifier targets exclusively statements */
	virtual bool IsStatementOnlyTarget() const { return false; }

	/** Gives target specifier archetype a chance to validate itself before the compilation */
	virtual bool ValidateTargetSpecifierConfiguration(FText& OutErrorDescription) const { return true; }
#endif
};

USTRUCT()
struct FBlueprintHookDefinition {
	GENERATED_BODY()

	UPROPERTY()
	UFunction* TargetFunction{};
	UPROPERTY()
	UFunction* HookFunction{};
	UPROPERTY()
	EBlueprintFunctionHookType Type{};
	UPROPERTY()
	EBlueprintFunctionHookInsertLocation InsertLocation{};
	UPROPERTY()
	UBlueprintHookTargetSpecifier* TargetSpecifier{};
	UPROPERTY()
	EBlueprintFunctionHookTargetSelectionMode TargetSelectionMode{};
	UPROPERTY()
	int32 TargetOrdinal{};
};

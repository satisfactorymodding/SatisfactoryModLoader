#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlueprintHookingTypes.generated.h"

class FBlueprintHookTargetResolver;

/** Base class for all blueprint hooks, both static and instance based */
UCLASS(Abstract, BlueprintInternalUseOnly)
class SML_API UBlueprintHook : public UObject {
	GENERATED_BODY()
};

/** Parent class for static blueprint hooks */
UCLASS(Abstract, Blueprintable, BlueprintInternalUseOnly, meta = (ShowWorldContextPin))
class SML_API UStaticBlueprintHook : public UBlueprintHook {
	GENERATED_BODY()
};

/** Parent class for blueprint hooks that represent actor mixins */
UCLASS(Abstract, Blueprintable, BlueprintInternalUseOnly, Within = Actor)
class SML_API UBlueprintActorMixin : public UBlueprintHook {
	GENERATED_BODY()
public:
	// Begin UObject interface
#if WITH_EDITOR
	virtual bool ImplementsGetWorld() const override { return true; }
#endif
	// End UObject interface

	/** Retrieves actor mixin instance of the provided type from the actor instance */
	UFUNCTION(BlueprintPure, Category = "Actor Mixin", meta = (DeterminesOutputType = "InMixinClass", CallableWithoutWorldContext))
	static UBlueprintActorMixin* GetActorMixin( const AActor* InActor, TSubclassOf<UBlueprintActorMixin> InMixinClass);

	/** Internal function used by generated hooking code */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	static UObject* GetHookObjectInstanceFromTargetMethodInstance(UObject* InObjectInstance, UClass* InHookObjectClass);

	/** Called when mixin is created on the actor instance */
	void DispatchMixinCreated();

	/** Dispatches BeginPlay to the mixin */
	void DispatchBeginPlay();

	/** Dispatches Tick to the mixin. Will only be called if bEnableMixinTick is true */
	void DispatchTick(float DeltaTime);

	/** Dispatches EndPlay to the mixin */
	void DispatchEndPlay(EEndPlayReason::Type EndPlayReason);
protected:
	/** Called when the mixin is created on the actor. Mixins are created during SCS initialization. */
	virtual void OnMixinCreated() {}
	
	/** Called when the actor receives BeginPlay. This is called after the actors BeginPlay */
	virtual void BeginPlay() {}

	/** Called when the actor receives tick. Requires bEnableMixinTick to be set to true */
	virtual void Tick(float DeltaTime) {}

	/** Called when the actor receives EndPlay. This is called before the actors EndPlay */
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) {}
	
	/** Called when the mixin is created on the actor. This is called before Actor construction script is executed */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Construction Script"))
	void UserConstructionScript();
	
	/** Called when BeginPlay is dispatched on the actor this mixin is attached to */
	UFUNCTION(BlueprintImplementableEvent, Category = "Actor Mixin", meta = (DisplayName = "Begin Play"))
	void ReceiveBeginPlay();

	/** Called to dispatch Tick to blueprint classes */
	UFUNCTION(BlueprintImplementableEvent, Category = "Actor Mixin", meta = (DisplayName = "Tick"))
	void ReceiveTick(float DeltaTime);

	/** Called when EndPlay is dispatched on the actor this mixin is attached to */
	UFUNCTION(BlueprintImplementableEvent, Category = "Actor Mixin", meta = (DisplayName = "End Play"))
	void ReceiveEndPlay();
public:
	/** True to enable Tick to be dispatched for this mixin. Tick will not be called unless this is enabled */
	UPROPERTY(EditDefaultsOnly, Category = "Actor Mixin")
	bool bEnableMixinTick{false};
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
	TObjectPtr<UFunction> TargetFunction{};
	UPROPERTY()
	TObjectPtr<UFunction> HookFunction{};
	UPROPERTY()
	EBlueprintFunctionHookType Type{};
	UPROPERTY()
	EBlueprintFunctionHookInsertLocation InsertLocation{};
	UPROPERTY()
	TObjectPtr<UBlueprintHookTargetSpecifier> TargetSpecifier{};
	UPROPERTY()
	EBlueprintFunctionHookTargetSelectionMode TargetSelectionMode{};
	UPROPERTY()
	int32 TargetOrdinal{};
};

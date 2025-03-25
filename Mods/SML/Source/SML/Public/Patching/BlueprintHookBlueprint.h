#pragma once

#include "CoreMinimal.h"
#include "BlueprintHookingTypes.h"
#include "Engine/Blueprint.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "BlueprintHookBlueprint.generated.h"

UCLASS()
class SML_API UHookBlueprintDerivedDataRoot : public UObject {
	GENERATED_BODY()
};

UCLASS()
class SML_API UHookBlueprintGeneratedClass : public UBlueprintGeneratedClass {
	GENERATED_BODY()
public:
	/** Descriptors for the hooks defined in this function library */
	UPROPERTY()
	TArray<FBlueprintHookDefinition> HookDescriptors;

	/** Root object derived hook descriptor objects will be parented to */
	UPROPERTY()
	UHookBlueprintDerivedDataRoot* HookDescriptorDerivedDataRoot;
};

UCLASS(NotBlueprintType)
class SML_API UHookBlueprint : public UBlueprint {
	GENERATED_BODY()
public:
#if WITH_EDITOR
	// Begin UBlueprint interface
	virtual UClass* GetBlueprintClass() const override { return UHookBlueprintGeneratedClass::StaticClass(); }
	virtual bool SupportedByDefaultBlueprintFactory() const override { return false; }
	virtual bool AlwaysCompileOnLoad() const override { return true; }
	// End UBlueprint interface
#endif

#if WITH_EDITORONLY_DATA
	/** Editor graph with the data for the hook definition generation */
	UPROPERTY()
	UEdGraph* HookTargetGraph{};
#endif
};

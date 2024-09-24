#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Subsystems/EngineSubsystem.h"
#include "BlueprintSCSHookManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBlueprintSCSHookManager, All, All);

class USCS_Node;
class UBlueprintSCSHookData;
class URootBlueprintSCSHookData;

USTRUCT()
struct SML_API FBPSCSHookDescriptor {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Default")
	URootBlueprintSCSHookData* RootHookData;

	UPROPERTY(VisibleAnywhere, Category = "Default")
	USimpleConstructionScript* SimpleConstructionScript;

	UPROPERTY(VisibleAnywhere, Category = "Default")
	TMap<UBlueprintSCSHookData*, USCS_Node*> InstalledNodes;

	UPROPERTY(VisibleAnywhere, Category = "Default")
	TArray<USCS_Node*> InstalledNodesOrdered;
};

/** Data required to hook into the SCS tree */
UCLASS(NotBlueprintable, BlueprintType, EditInlineNew)
class SML_API UBlueprintSCSHookData : public UDataAsset {
	GENERATED_BODY()
public:
	/** Template of the actor component to add to the SCS */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", BlueprintSetter = SetActorComponentClass)
	TSubclassOf<UActorComponent> ActorComponentClass;

	/** Name of the component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", BlueprintSetter = SetVariableName)
	FName VariableName;

	/** The component that will be added to the SCS */
	UPROPERTY(VisibleAnywhere, Category = "Default", BlueprintReadOnly, meta = (ShowInnerProperties))
	UActorComponent* ActorComponentTemplate;
	
	/** Name of the socket to attach to on the parent component (leave empty if not needed) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (GetOptions = "GetAvailableSocketNames"))
	FName AttachToName;

	/** Child components to hook on top of this component to simulate SCS behavior for hooked components */
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Default")
	TArray<UBlueprintSCSHookData*> Children;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	/** Updates component class for the hook */
	UFUNCTION(BlueprintSetter)
	void SetActorComponentClass(TSubclassOf<UActorComponent> NewActorComponentClass);

	/** Updates variable name for the hook */
	UFUNCTION(BlueprintSetter)
	void SetVariableName(FName NewVariableName);

	UFUNCTION(BlueprintPure)
	TArray<FString> GetAvailableSocketNames() const;
	
	void ReinitializeActorComponentTemplate();
	virtual bool ResolveParentComponent(struct FParentComponentInfo& OutParentComponent) const;
};

/** Data required to hook into the existing SCS tree at the provided point */
UCLASS(BlueprintType, EditInlineNew)
class SML_API URootBlueprintSCSHookData : public UBlueprintSCSHookData {
	GENERATED_BODY()
public:
	/** Blueprint class to hook. Must be a Blueprint! */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ShowTreeView, BlueprintBaseOnly))
	TSoftClassPtr<AActor> ActorClass;
	
	/**
	 * Parent Component Name to Attach to. If left empty, it will be attached to the DefaultSceneRoot component.
	 * Example names (for Char_Player):
	 * 
	 * " PlayerCamera " (native component)
	 * PPTakeDamage (SCS root component)
	 * FlashLight1P (SCS root component)
	 * FlashLight3P (SCS child component, child of HelmetMesh SCS root component)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (GetOptions = "GetParentComponentNames"))
	FName ParentComponentName;
	
	UFUNCTION(BlueprintPure)
	TArray<FString> GetParentComponentNames() const;

	virtual bool ResolveParentComponent(FParentComponentInfo& OutParentComponent) const override;
};

UCLASS()
class SML_API UBlueprintSCSHookManager : public UEngineSubsystem {
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, Category = "Default")
	TArray<FBPSCSHookDescriptor> InstalledHooks;
public:
	/** Installs the SCS hook with the provided parameters */
	UFUNCTION(BlueprintCallable)
	void RegisterBlueprintSCSHook(URootBlueprintSCSHookData* HookData);

	/** Removes the previously installed SCS hook */
	UFUNCTION(BlueprintCallable)
	void UnregisterBlueprintSCSHook(URootBlueprintSCSHookData* HookData);
private:
	static void InstallSCSHookRecursive(UBlueprintSCSHookData* HookData, FBPSCSHookDescriptor& OutHookDescriptor);
	static void UninstallSCSHookOrdered(const FBPSCSHookDescriptor& HookDescriptor);
};

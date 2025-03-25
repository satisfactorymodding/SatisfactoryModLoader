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
	URootBlueprintSCSHookData* RootHookData{};

	UPROPERTY(VisibleAnywhere, Category = "Default")
	class USimpleConstructionScript* SimpleConstructionScript{};

	UPROPERTY(VisibleAnywhere, Category = "Default")
	TMap<UBlueprintSCSHookData*, USCS_Node*> InstalledNodes;

	UPROPERTY(VisibleAnywhere, Category = "Default")
	TArray<USCS_Node*> InstalledNodesOrdered;
	
	int32 RegistrationCount{0};
};

struct FSoftEditorBPSCSHookRegistration
{
	TSoftObjectPtr<URootBlueprintSCSHookData> HookAsset;
	int32 RegistrationCount{0};
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
	virtual bool ResolveParentComponentOnArchetype(struct FParentComponentInfo& OutParentComponent) const;
	virtual void ExecuteSCSHookOnInstance(AActor* InActorInstance, USceneComponent* InParentComponent) const;
};

/** Data required to hook into the existing SCS tree at the provided point */
UCLASS(BlueprintType, EditInlineNew)
class SML_API URootBlueprintSCSHookData : public UBlueprintSCSHookData {
	GENERATED_BODY()
public:
	/** Use this field to leave future you notes about what this hook is supposed to accomplish */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (MultiLine = "true"))
	FString DeveloperComment;

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

	virtual bool ResolveParentComponentOnArchetype(FParentComponentInfo& OutParentComponent) const override;
	bool ResolveParentComponentOnInstance(AActor* ActorInstance, class USceneComponent*& OutParentComponent) const;
	void ExecuteSCSHookOnInstanceRootComponent(AActor* InActorInstance) const;
};

UCLASS()
class SML_API UBlueprintSCSHookManager : public UEngineSubsystem {
	GENERATED_BODY()
private:
	/** Used in runtime to install hooks directly to the archetypes of the blueprints */
	UPROPERTY()
	TArray<FBPSCSHookDescriptor> InstalledArchetypeHooks;

	/**
	 * Used in the editor and standalone to instead populate the components on the instances, and does not retain hard references to the hooks in question
	 * Keep in mind that such hooks are reference counted, so each register must be correctly paired up with unregister
	 */
	TMap<FTopLevelAssetPath, TArray<FSoftEditorBPSCSHookRegistration>> InstalledSlowPerInstanceHooks;
public:
	/** Installs the SCS hook with the provided parameters */
	UFUNCTION(BlueprintCallable)
	void RegisterBlueprintSCSHook(URootBlueprintSCSHookData* HookData);

	/** Removes the previously installed SCS hook */
	UFUNCTION(BlueprintCallable)
	void UnregisterBlueprintSCSHook(URootBlueprintSCSHookData* HookData);

	/** Called from the initialization to register static hooks if necessary */
	static void RegisterStaticHooks();
private:
	static void BlueprintGeneratedClassCreateComponentsFromActor(const UClass* ThisClass, AActor* Actor);
	static void InstallArchetypeSCSHookRecursive(UBlueprintSCSHookData* HookData, FBPSCSHookDescriptor& OutHookDescriptor);
	static void RemoveArchetypeSCSHookOrdered(const FBPSCSHookDescriptor& HookDescriptor);
};

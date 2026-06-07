#pragma once

#include "CoreMinimal.h"
#include "BlueprintHookingTypes.h"
#include "Engine/Blueprint.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "BlueprintHookBlueprint.generated.h"

class USCS_Node;

UCLASS()
class SML_API UHookBlueprintDerivedDataRoot : public UObject {
	GENERATED_BODY()
};

/** Represents a single mixin node */
UCLASS(Within = BlueprintMixinOverlayComponentTree)
class SML_API UBlueprintMixinComponentNode : public UObject {
	GENERATED_BODY()
public:
	/** True if the parent component for this component node is a C++ component that is identified by its name */
	UPROPERTY()
	bool bIsParentComponentNative{false};
	
	/** Component template or variable that this node is parented to, can be None */
	UPROPERTY()
	FName ParentComponentOrVariableName;

	/** If this node is parented to a SCS node and not a native component, this is a FName of the blueprint class that owns the SCS node */
	UPROPERTY()
	FName ParentComponentOwnerClassName;
	
	/** Class of the component this node represents */
	UPROPERTY()
	TSubclassOf<UActorComponent> ComponentClass;

	/** Name of the component variable that will be generated and populated with the reference to this component */
	UPROPERTY()
	FName ComponentVariableName;

	/** Name of the component. This is equivalent to the component variable prefixed with the blueprint name */
	UPROPERTY()
	FName ComponentName;

	/** Name of the socket on the parent component to which this component must be attached */
	UPROPERTY()
	FName AttachToSocketName;

	/** Template for the creation of this component. This template will be duplicated to create the final component. Template outer will be an SCS node */
	UPROPERTY()
	TObjectPtr<UActorComponent> ComponentTemplate{};

	/** Child nodes for this component mixin node */
	UPROPERTY()
	TArray<TObjectPtr<UBlueprintMixinComponentNode>> ChildNodes;

	/** Executes this node on the provided actor, and assigns the component variable to the mixin instance */
	void ExecuteNodeOnActor(AActor* InTargetActor, UBlueprintActorMixin* InOwnerMixin, USceneComponent* InParentComponent);

#if WITH_EDITOR
	/** Updates the variable name on this node. Will also rename the template object */
	void SetInternalVariableName(const FName& InNewVariableName);
	/** Adds the node to the list of children on this node and to the list of all nodes */
	void AddChildNode(UBlueprintMixinComponentNode* InChildNode);
	/** Removes provided child node from this parent node and from the AllNodes list */
	void RemoveChildNode(UBlueprintMixinComponentNode* InChildNode);

	/** Detaches this node from its parent node, and attaches it to the parent node of the parent node */
	void DetachFromParent();
	/** Removes this node from its parent, or from the root node list if this is a root node. Will automatically migrate children up the tree */
	void RemoveNodeFromParent();

	/** Attaches this node as a child to the provided SCS node */
	bool AttachToSCSNode(const USCS_Node* InNewAttachmentNode);
	/** Attaches this node to a native parent component */
	bool AttachToNativeActorComponent(const UActorComponent* InNativeActorComponent);
	/** Attaches this node to another parent node */
	bool AttachToNode(UBlueprintMixinComponentNode* InNewParentNode);

	/** Preloads this node and all of its children */
	void PreloadChain();
#endif
};

UCLASS(Within = HookBlueprintGeneratedClass)
class SML_API UBlueprintMixinOverlayComponentTree : public UObject {
	GENERATED_BODY()
public:
	static const FName OverlayComponentTag;
	
	/** All nodes that this overlay component tree contains */
	UPROPERTY()
	TArray<TObjectPtr<UBlueprintMixinComponentNode>> AllNodes;

	/** Root component tree nodes that can be parented to the external nodes in the target blueprint */
	UPROPERTY()
	TArray<TObjectPtr<UBlueprintMixinComponentNode>> RootNodes;

#if WITH_EDITOR
	/** Resolves a reference to the SCS node using the blueprint class name and the name of the node variable */
	USCS_Node* ResolveExternalSCSNodeReference(const FName& OwnerBlueprintClassName, const FName& NodeVariableName) const;
	
	/** Resolves a reference to a native component by its name */
	const UActorComponent* ResolveNativeComponentReference(const FName& NativeComponentName) const;
	
	/** Returns the parent node for the provided component node. Returns nullptr if the node is a root node */
	UBlueprintMixinComponentNode* GetParentNodeForNode(UBlueprintMixinComponentNode* InComponentNode) const;
	
	/** Creates a new node parented to this component tree. Note that the node must still be added to the tree after */
	UBlueprintMixinComponentNode* CreateNewNode(const TSubclassOf<UActorComponent>& ComponentClass, const FName& ComponentVariableName, const UActorComponent* InActorComponentTemplate = nullptr);
	
	/** Adds root node to the tree */
	void AddRootNode(UBlueprintMixinComponentNode* InRootNode);
	
	/** Removes root node from the tree and from the list of all nodes. Note that it must not have any children at this point */
	void RemoveRootNode(UBlueprintMixinComponentNode* InRootNode);
#endif

	/** Executes this node on the provided actor, and assigns the component variable to the mixin instance (if provided, nullptr is allowed as well) */
	void ExecuteOnActor(AActor* InTargetActor, UBlueprintActorMixin* InOwnerMixin);
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
	TObjectPtr<UHookBlueprintDerivedDataRoot> HookDescriptorDerivedDataRoot;

	/** Class into which this mixin will be injected*/
	UPROPERTY()
	TObjectPtr<UBlueprintGeneratedClass> MixinTargetClass{};

	/** Overlay component tree for this mixin. Can be nullptr if this blueprint is not a mixin */
	UPROPERTY()
	TObjectPtr<UBlueprintMixinOverlayComponentTree> OverlayComponentTree{};

	// Begin UBlueprintGeneratedClass interface
	virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;
#if WITH_EDITOR
	virtual UClass* RegenerateClass(UClass* ClassToRegenerate, UObject* PreviousCDO) override;
#endif
	// End UBlueprintGeneratedClass interface
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
	virtual UClass* RegenerateClass(UClass* ClassToRegenerate, UObject* PreviousCDO) override;
	// End UBlueprint interface
#endif

#if WITH_EDITORONLY_DATA
	/** Editor graph with the data for the hook definition generation */
	UPROPERTY()
	TObjectPtr<UEdGraph> HookTargetGraph{};

	/** Class into which this mixin will be injected, if this hook blueprint represents a mixin */
	UPROPERTY(VisibleAnywhere, Category = "Hook Blueprint", AssetRegistrySearchable)
	TObjectPtr<UBlueprintGeneratedClass> MixinTargetClass{};

	/** Overlay component tree for this mixin. Can be nullptr if this blueprint is not a mixin */
	UPROPERTY()
	TObjectPtr<UBlueprintMixinOverlayComponentTree> OverlayComponentTree{};
#endif
};

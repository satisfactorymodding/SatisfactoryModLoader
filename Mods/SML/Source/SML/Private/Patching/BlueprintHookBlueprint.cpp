#include "Patching/BlueprintHookBlueprint.h"
#include "Engine/SimpleConstructionScript.h"
#include "Engine/SCS_Node.h"
#include "UObject/LinkerLoad.h"

const FName UBlueprintMixinOverlayComponentTree::OverlayComponentTag(TEXT("OverlayComponent"));

void UHookBlueprintGeneratedClass::GetPreloadDependencies(TArray<UObject*>& OutDeps) {
	Super::GetPreloadDependencies(OutDeps);
}

#if WITH_EDITOR

static void PreloadOverlayComponentTree(UBlueprintMixinOverlayComponentTree* OverlayComponentTree) {
	if (FLinkerLoad* TargetLinker = OverlayComponentTree->GetLinker()) {
		TargetLinker->Preload(OverlayComponentTree);

		const TArray<UBlueprintMixinComponentNode*>& RootNodes = OverlayComponentTree->RootNodes;
		for (int32 NodeIndex = 0; NodeIndex < RootNodes.Num(); ++NodeIndex) {
			RootNodes[NodeIndex]->PreloadChain();
		}
	}
}

UClass* UHookBlueprintGeneratedClass::RegenerateClass(UClass* ClassToRegenerate, UObject* PreviousCDO) {
	// Preload the overlay component tree because we need to have valid data on the nodes to regenerate class layout
	if (OverlayComponentTree) {
		PreloadOverlayComponentTree(OverlayComponentTree);
	}
	return Super::RegenerateClass(ClassToRegenerate, PreviousCDO);
}

UClass* UHookBlueprint::RegenerateClass(UClass* ClassToRegenerate, UObject* PreviousCDO) {
	// Preload the overlay component tree because we need to have valid data on the nodes to regenerate class layout
	if (OverlayComponentTree) {
		PreloadOverlayComponentTree(OverlayComponentTree);
	}
	return Super::RegenerateClass(ClassToRegenerate, PreviousCDO);
}

#endif

void UBlueprintMixinOverlayComponentTree::ExecuteOnActor(AActor* InTargetActor, UBlueprintActorMixin* InOwnerMixin) {
	TInlineComponentArray<UActorComponent*> ActorComponents;
	InTargetActor->GetComponents(ActorComponents);

	// Determine a list of all native components to allow finding them by name
	TInlineComponentArray<USceneComponent*> NativeSceneComponents;
	for (UActorComponent* ActorComponent : ActorComponents) {
		if (USceneComponent* SceneComponent = Cast<USceneComponent>(ActorComponent)) {
			// Exclude subcomponents of native components, as these could unintentionally be matched by name during SCS execution
			if (SceneComponent->CreationMethod == EComponentCreationMethod::Native && SceneComponent->GetOuter()->IsA<AActor>()) {
				NativeSceneComponents.Add(SceneComponent);
			}
		}
	}

	// Execute root overlay tree nodes
	for (UBlueprintMixinComponentNode* RootNode : RootNodes) {
		USceneComponent* AttachmentParentComponent = InTargetActor->GetRootComponent();
		
		// Find native component with a matching name
		if (RootNode->bIsParentComponentNative) {
			for (USceneComponent* NativeSceneComponent : NativeSceneComponents) {
				if (NativeSceneComponent->GetFName() == RootNode->ParentComponentOrVariableName) {
					AttachmentParentComponent = NativeSceneComponent;
					break;
				}
			}
		} else {
			// Find SCS component by resolving the property it is assigned to
			if (const FObjectProperty* ComponentProperty = FindFProperty<FObjectProperty>(InTargetActor->GetClass(), RootNode->ParentComponentOrVariableName)) {
				if (USceneComponent* SCSSceneComponent = Cast<USceneComponent>(ComponentProperty->GetObjectPropertyValue_InContainer(InTargetActor))) {
					AttachmentParentComponent = SCSSceneComponent;
				}
			}
		}
		
		// Execute the root SCS node on the resolved parent component
		RootNode->ExecuteNodeOnActor(InTargetActor, InOwnerMixin, AttachmentParentComponent);
	}
}

void UBlueprintMixinComponentNode::ExecuteNodeOnActor(AActor* InTargetActor, UBlueprintActorMixin* InOwnerMixin, USceneComponent* InParentComponent) {
	if (ComponentTemplate != nullptr) {
		// Duplicate the component from the template using the actor as an outer
		UActorComponent* DuplicatedActorComponent = DuplicateObject<UActorComponent>(ComponentTemplate, InTargetActor, ComponentName);
		check(DuplicatedActorComponent);

		// Set up the attachment if the duplicated component represents a scene component
		USceneComponent* DuplicatedSceneComponent = Cast<USceneComponent>(DuplicatedActorComponent);
		if (DuplicatedSceneComponent) {
			DuplicatedSceneComponent->SetupAttachment(InParentComponent, AttachToSocketName);
		}
		// Make sure the component is tagged as overlay component
		DuplicatedActorComponent->ComponentTags.AddUnique(UBlueprintMixinOverlayComponentTree::OverlayComponentTag);

		// Assign the component to the mixin variable if we have been provided with a mixin instance
		if (InOwnerMixin != nullptr && ComponentVariableName != NAME_None) {
			if (const FObjectProperty* ComponentProperty = FindFProperty<FObjectProperty>(InOwnerMixin->GetClass(), ComponentVariableName)) {
				ComponentProperty->SetObjectPropertyValue_InContainer(InOwnerMixin, DuplicatedActorComponent);
			}
		}

		// Finally, register the component
		DuplicatedActorComponent->RegisterComponent();

		// Evaluate child nodes for this component now
		for (UBlueprintMixinComponentNode* ChildComponentNode : ChildNodes) {
			ChildComponentNode->ExecuteNodeOnActor(InTargetActor, InOwnerMixin, DuplicatedSceneComponent);
		}
	}
}

#if WITH_EDITOR

void UBlueprintMixinComponentNode::SetInternalVariableName(const FName& InNewVariableName) {
	if (ComponentVariableName != InNewVariableName && InNewVariableName != NAME_None) {
		const UHookBlueprintGeneratedClass* OwnerClass = CastChecked<UHookBlueprintGeneratedClass>(GetOuter()->GetOuter());
		Modify();
		ComponentVariableName = InNewVariableName;
		ComponentName = *FString::Printf(TEXT("%s_%s"), *OwnerClass->GetName(), *InNewVariableName.ToString());
		if (ComponentTemplate != nullptr) {
			ComponentTemplate->Modify();
			ComponentTemplate->Rename(*(TEXT("OVERLAY_TEMPLATE_") + ComponentName.ToString()), nullptr, REN_DontCreateRedirectors | REN_ForceNoResetLoaders);
		}
	}
}

void UBlueprintMixinComponentNode::AddChildNode( UBlueprintMixinComponentNode* InChildNode) {
	if (InChildNode != nullptr && !ChildNodes.Contains(InChildNode)) {
		Modify();
		ChildNodes.AddUnique(InChildNode);
		if (UBlueprintMixinOverlayComponentTree* OwnerComponentTree = CastChecked<UBlueprintMixinOverlayComponentTree>(GetOuter())) {
			OwnerComponentTree->Modify();
			OwnerComponentTree->AllNodes.AddUnique(InChildNode);
		}
	}
}

void UBlueprintMixinComponentNode::RemoveChildNode(UBlueprintMixinComponentNode* InChildNode) {
	if (InChildNode != nullptr && ChildNodes.Contains(InChildNode)) {
		Modify();
		ChildNodes.Remove(InChildNode );
		if (UBlueprintMixinOverlayComponentTree* OwnerComponentTree = CastChecked<UBlueprintMixinOverlayComponentTree>(GetOuter())) {
			OwnerComponentTree->Modify();
			OwnerComponentTree->AllNodes.Remove(InChildNode);
		}
	}
}

void UBlueprintMixinComponentNode::DetachFromParent() {
	UBlueprintMixinOverlayComponentTree* OwnerComponentTree = CastChecked<UBlueprintMixinOverlayComponentTree>(GetOuter());

	// If we have a parent node, we have to detach from another node within the overlay component tree
	if (UBlueprintMixinComponentNode* ParentNode = OwnerComponentTree->GetParentNodeForNode(this)) {
		UBlueprintMixinComponentNode* ParentParentNode = OwnerComponentTree->GetParentNodeForNode(ParentNode);

		// Remove oruselves from our parents child node list
		ParentNode->RemoveChildNode(this);

		// If our parent node does not have a parent node, we need to add ourselves to the root set, and copy targeting data from our parent
		if (ParentParentNode == nullptr) {
			Modify();
			bIsParentComponentNative = ParentNode->bIsParentComponentNative;
			ParentComponentOwnerClassName = ParentNode->ParentComponentOwnerClassName;
			ParentComponentOrVariableName = ParentNode->ParentComponentOrVariableName;

			// Add ourselves to the root set now
			OwnerComponentTree->AddRootNode(this);
		} else {
			// Just add ourselves to the parent node of our parent node now
			ParentParentNode->AddChildNode(this);
		}
	} else {
		// This is a root node - we need to modify our attachment
		Modify();
		if (bIsParentComponentNative) {
			// Resolve the reference to the native component and change the variable name to the attach parent of that component
			const USceneComponent* CurrentParentNativeComponent = Cast<USceneComponent>(OwnerComponentTree->ResolveNativeComponentReference(ParentComponentOrVariableName));
			ParentComponentOrVariableName = NAME_None;
			if (CurrentParentNativeComponent && CurrentParentNativeComponent->GetAttachParent()) {
				ParentComponentOrVariableName = CurrentParentNativeComponent->GetAttachParent()->GetFName();
			}
		} else {
			// Resolve the SCS node that we are referencing and reset the reference
			USCS_Node* CurrentParentNode = OwnerComponentTree->ResolveExternalSCSNodeReference(ParentComponentOwnerClassName, ParentComponentOrVariableName);
			const USimpleConstructionScript* ParentSimpleConstructionScript = CurrentParentNode ? CastChecked<USimpleConstructionScript>(CurrentParentNode->GetOuter()) : nullptr;
			bIsParentComponentNative = false;
			ParentComponentOwnerClassName = NAME_None;
			ParentComponentOrVariableName = NAME_None;

			// Determine whenever this is a root node or a child node, and update the reference to point to its parent
			if (CurrentParentNode != nullptr) {
				// If the node that we are attached to has a parent, we are attached to that parent now
				if (const USCS_Node* ParentNodeParent = ParentSimpleConstructionScript->FindParentNode(CurrentParentNode)) {
					bIsParentComponentNative = false;
					ParentComponentOwnerClassName = ParentSimpleConstructionScript->GetOwnerClass()->GetFName();
					ParentComponentOrVariableName = ParentNodeParent->GetVariableName();
				} else {
					// Otherwise, we are attached to a root node, so just copy its parent reference to this node
					bIsParentComponentNative = CurrentParentNode->bIsParentComponentNative;
					ParentComponentOwnerClassName = CurrentParentNode->ParentComponentOwnerClassName;
					ParentComponentOrVariableName = CurrentParentNode->ParentComponentOrVariableName;
				}
			}
		}
	}
}

void UBlueprintMixinComponentNode::RemoveNodeFromParent() {
	UBlueprintMixinOverlayComponentTree* OwnerComponentTree = CastChecked<UBlueprintMixinOverlayComponentTree>(GetOuter());
	UBlueprintMixinComponentNode* ParentNode = OwnerComponentTree->GetParentNodeForNode(this);
	
	// If we have a parent node, remove from the parent. Otherwise, remove from the root list
	if (ParentNode == nullptr) {
		OwnerComponentTree->RemoveRootNode(this);
	} else {
		ParentNode->RemoveChildNode(this);
	}
}

bool UBlueprintMixinComponentNode::AttachToSCSNode(const USCS_Node* InNewAttachmentNode) {
	UBlueprintMixinOverlayComponentTree* OwnerComponentTree = CastChecked<UBlueprintMixinOverlayComponentTree>(GetOuter());
	const FName NewBlueprintOwnerClassName = InNewAttachmentNode ? CastChecked<USimpleConstructionScript>(InNewAttachmentNode->GetOuter())->GetOwnerClass()->GetFName() : NAME_None;
	const FName NewComponentOrVariableName = InNewAttachmentNode ? InNewAttachmentNode->GetVariableName() : NAME_None;

	// Make sure the suggested parent node can actually be resolved from the current mixin context of this class
	if (InNewAttachmentNode && OwnerComponentTree->ResolveExternalSCSNodeReference(NewBlueprintOwnerClassName, NewComponentOrVariableName) == InNewAttachmentNode) {
		// If we are not currently a root set node, remove ourselves from the parent and add to the root
		if (!OwnerComponentTree->RootNodes.Contains(this)) {
			RemoveNodeFromParent();
			OwnerComponentTree->AddRootNode(this);
		}
		
		// Update the reference to the parent component on this root node
		Modify();
		bIsParentComponentNative = false;
		ParentComponentOwnerClassName = NewBlueprintOwnerClassName;
		ParentComponentOrVariableName = NewComponentOrVariableName;
		return true;
	}
	return false;
}

bool UBlueprintMixinComponentNode::AttachToNativeActorComponent(const UActorComponent* InNativeActorComponent) {
	UBlueprintMixinOverlayComponentTree* OwnerComponentTree = CastChecked<UBlueprintMixinOverlayComponentTree>(GetOuter());
	const FName NewComponentName = InNativeActorComponent->GetFName();

	// Make sure this native component actually belongs to this mixin target class
	if (InNativeActorComponent && OwnerComponentTree->ResolveNativeComponentReference(NewComponentName) == InNativeActorComponent) {
		// If we are not currently a root set node, remove ourselves from the parent and add to the root
		if (!OwnerComponentTree->RootNodes.Contains(this)) {
			RemoveNodeFromParent();
			OwnerComponentTree->AddRootNode(this);
		}
		
		// Update the reference to the parent component on this root node
		Modify();
		bIsParentComponentNative = true;
		ParentComponentOwnerClassName = NAME_None;
		ParentComponentOrVariableName = NewComponentName;
		return true;
	}
	return false;
}

bool UBlueprintMixinComponentNode::AttachToNode(UBlueprintMixinComponentNode* InNewParentNode) {
	UBlueprintMixinOverlayComponentTree* OwnerComponentTree = CastChecked<UBlueprintMixinOverlayComponentTree>(GetOuter());
	
	// Make sure this native component actually belongs to the same blueprint
	if (InNewParentNode && InNewParentNode->GetOuter() == GetOuter() && OwnerComponentTree->GetParentNodeForNode(this) != InNewParentNode) {
		// Remove this node from its parent
		RemoveNodeFromParent();

		// Reset reference data that is only relevant for root nodes
		Modify();
		bIsParentComponentNative = false;
		ParentComponentOwnerClassName = NAME_None;
		ParentComponentOrVariableName = NAME_None;

		// Attach this node to its new parent node
		InNewParentNode->AddChildNode(this);
		return true;
	}
	return false;
}

void UBlueprintMixinComponentNode::PreloadChain() {
	// Preload the properties of this node
	if(HasAnyFlags(RF_NeedLoad)) {
		GetLinker()->Preload(this);
	}

	// Preload the component class. We do not have to preload the actual component template since they are non-inheritable in our case and not required for class layout generation
	if (ComponentClass && ComponentClass->HasAnyFlags(RF_NeedLoad)) {
		if (ensureMsgf(ComponentClass->GetLinker(), TEXT("Failed to find linker for %s, likely a circular dependency"), *ComponentTemplate->GetPathName())) {
			ComponentClass->GetLinker()->Preload(ComponentClass);
		}
	}

	// Preload any child nodes that we might have
	for (UBlueprintMixinComponentNode* ChildNode : ChildNodes) {
		if (ChildNode) {
			ChildNode->PreloadChain();
		}
	}
}

USCS_Node* UBlueprintMixinOverlayComponentTree::ResolveExternalSCSNodeReference(const FName& OwnerBlueprintClassName, const FName& NodeVariableName) const {
	const UHookBlueprintGeneratedClass* OwnerClass = CastChecked<UHookBlueprintGeneratedClass>(GetOuter());

	// Attempt to find the exact node declaration
	const UBlueprintGeneratedClass* CurrentParentClass = OwnerClass->MixinTargetClass;
	while (CurrentParentClass != nullptr) {
		// If this is the class that we are looking for, resolve the node within it and return the reference
		if (CurrentParentClass->GetFName() == OwnerBlueprintClassName && CurrentParentClass->SimpleConstructionScript) {
			return CurrentParentClass->SimpleConstructionScript->FindSCSNode(NodeVariableName);
		}
		// Lookup its parent class to see if it contains the node in question
		CurrentParentClass = Cast<UBlueprintGeneratedClass>(CurrentParentClass->GetSuperClass());
	}
	return nullptr;
}

const UActorComponent* UBlueprintMixinOverlayComponentTree::ResolveNativeComponentReference(const FName& NativeComponentName) const {
	const UHookBlueprintGeneratedClass* OwnerClass = CastChecked<UHookBlueprintGeneratedClass>(GetOuter());
	if (OwnerClass->MixinTargetClass) {
		// Retrieve a list of all native components
		TArray<UActorComponent*> NativeActorComponents;
		if (const AActor* ClassDefaultObject = OwnerClass->MixinTargetClass->GetDefaultObject<AActor>()) {
			ClassDefaultObject->GetComponents(NativeActorComponents);
		}

		// Find a component with a matching name
		for (const UActorComponent* NativeActorComponent : NativeActorComponents) {
			if (NativeActorComponent && NativeActorComponent->GetFName() == NativeComponentName) {
				return NativeActorComponent;
			}
		}
	}
	return nullptr;
}

UBlueprintMixinComponentNode* UBlueprintMixinOverlayComponentTree::GetParentNodeForNode(UBlueprintMixinComponentNode* InComponentNode) const {
	for (UBlueprintMixinComponentNode* PotentialParentNode : AllNodes) {
		if (PotentialParentNode != nullptr && PotentialParentNode->ChildNodes.Contains(InComponentNode)) {
			return PotentialParentNode;
		}
	}
	return nullptr;
}

UBlueprintMixinComponentNode* UBlueprintMixinOverlayComponentTree::CreateNewNode( const TSubclassOf<UActorComponent>& ComponentClass, const FName& ComponentVariableName, const UActorComponent* InActorComponentTemplate) {
	if (ComponentClass && ComponentVariableName != NAME_None && !ComponentClass->HasAnyClassFlags( CLASS_Abstract | CLASS_Deprecated)) {
		UHookBlueprintGeneratedClass* OwnerClass = CastChecked<UHookBlueprintGeneratedClass>(GetOuter());
		UBlueprintMixinComponentNode* NewNode = NewObject<UBlueprintMixinComponentNode>( this, NAME_None, RF_Transactional);
		
		NewNode->ComponentClass = ComponentClass;
		NewNode->ComponentVariableName = ComponentVariableName;
		NewNode->ComponentName = *FString::Printf(TEXT("%s_%s"), *OwnerClass->GetName(), *ComponentVariableName.ToString());
		const FName ComponentTemplateName = *(TEXT("OVERLAY_TEMPLATE_") + NewNode->ComponentName.ToString());

		if (InActorComponentTemplate && InActorComponentTemplate->GetClass() == ComponentClass) {
			// Create a new template by duplicating an existing component or a template. Do not copy any flags, but ensure that the template is marked as transactional
			NewNode->ComponentTemplate = CastChecked<UActorComponent>(StaticDuplicateObject(InActorComponentTemplate, OwnerClass, ComponentTemplateName, RF_Transactional));
			NewNode->ComponentTemplate->SetFlags(RF_Transactional);
		} else {
			// Create a new component template otherwise
			NewNode->ComponentTemplate = NewObject<UActorComponent>(NewNode, ComponentClass, ComponentTemplateName, RF_Transactional);
		}
		NewNode->ComponentTemplate->Modify();
		
		return NewNode;
	}
	return nullptr;
}

void UBlueprintMixinOverlayComponentTree::AddRootNode(UBlueprintMixinComponentNode* InRootNode) {
	if (InRootNode != nullptr && !RootNodes.Contains(InRootNode)) {
		Modify();
		RootNodes.AddUnique(InRootNode);
		AllNodes.AddUnique(InRootNode);
	}
}

void UBlueprintMixinOverlayComponentTree::RemoveRootNode(UBlueprintMixinComponentNode* InRootNode) {
	if (InRootNode != nullptr && RootNodes.Contains(InRootNode)) {
		Modify();
		RootNodes.Remove(InRootNode);
		AllNodes.Remove(InRootNode);
	}
}

#endif

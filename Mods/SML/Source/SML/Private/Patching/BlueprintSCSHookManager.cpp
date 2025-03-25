#include "Patching/BlueprintSCSHookManager.h"

#include "SatisfactoryModLoader.h"
#include "Engine/Engine.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "Misc/App.h"
#include "Patching/NativeHookManager.h"
#include "UObject/Package.h"

#if WITH_EDITOR
	// Fast path can be used if we are running Standalone (-game or -server) and not running a Commandlet
	#define GAllowUsingFastBlueprintSCSHookPath !GIsEditor && !IsRunningCommandlet()
#else
	// Fast path can be used at all times in non-editor builds
	#define GAllowUsingFastBlueprintSCSHookPath true
#endif

DEFINE_LOG_CATEGORY(LogBlueprintSCSHookManager);

/** Possible cases of parent component for an SCS component */
enum class EParentComponentType {
	/** Nothing will be populated */
	NONE,
	/** SimpleConstructionScript will be populated */
	SCS_ROOT_NODE,
	/** SimpleConstructionScript and ParentSCSNode will be populated */
	SCS_NODE,
	/** ParentComponentOrVariableName will be populated */
	NATIVE_PARENT_COMPONENT,
	/** ParentComponentOrVariableName and ParentComponentOwnerClassName will be populated */
	SUPER_BLUEPRINT_COMPONENT,
	/** Parent is another SCS hook, ParentHookData will be populated */
	SCS_HOOK_NODE,
};

struct FParentComponentInfo {
	EParentComponentType Type{};
	UActorComponent* ParentActorComponent{};
	
	USimpleConstructionScript* SimpleConstructionScript{};
	USCS_Node* ParentSCSNode{};
	
	FName ParentComponentOrVariableName;
	FName ParentComponentOwnerClassName;

	UBlueprintSCSHookData* ParentHookData{};
};

#if WITH_EDITOR

void UBlueprintSCSHookData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	UObject::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.MemberProperty->GetFName();
	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, VariableName) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, ActorComponentClass)) {
		ReinitializeActorComponentTemplate();
	}
}

#endif

void UBlueprintSCSHookData::SetActorComponentClass(TSubclassOf<UActorComponent> NewActorComponentClass) {
	this->ActorComponentClass = NewActorComponentClass;
	ReinitializeActorComponentTemplate();
}

void UBlueprintSCSHookData::SetVariableName(FName NewVariableName) {
	this->VariableName = NewVariableName;
	ReinitializeActorComponentTemplate();
}

TArray<FString> UBlueprintSCSHookData::GetAvailableSocketNames() const {
	TArray<FString> ResultArray;
	ResultArray.Add(FName(NAME_None).ToString());

	FParentComponentInfo ParentComponentInfo{};
	if (ResolveParentComponentOnArchetype(ParentComponentInfo)) {

		if (const USceneComponent* SceneComponent = Cast<USceneComponent>(ParentComponentInfo.ParentActorComponent)) {
			for (const FName& SocketName : SceneComponent->GetAllSocketNames()) {
				ResultArray.Add(SocketName.ToString());
			}
		}
	}
	return ResultArray;
}

void UBlueprintSCSHookData::ReinitializeActorComponentTemplate() {
	const UClass* CurrentActorTemplateClass = ActorComponentTemplate ? ActorComponentTemplate->GetClass() : NULL;

	//Re-initialize with the new class if it does not match currently
	if (CurrentActorTemplateClass != ActorComponentClass) {
		//Thrash the old object so it does not occupy the name we have now
		if (ActorComponentTemplate != NULL) {
			ActorComponentTemplate->Rename(nullptr, GetTransientPackage(), REN_DontCreateRedirectors | REN_ForceNoResetLoaders);
		}
		if (ActorComponentClass != NULL) {
			//The object needs RF_Public, otherwise a blueprint referencing an instance of UBlueprintSCSHookData
			//(or another object containing it) will cause a cooking error, since it would be referencing a private object
			//in another package
			UActorComponent* OldActorComponentTemplate = ActorComponentTemplate;
			ActorComponentTemplate = NewObject<UActorComponent>(this, ActorComponentClass, VariableName, RF_Public | RF_ArchetypeObject | RF_Transactional);

			//Transfer properties from the old object to the new one
			if (OldActorComponentTemplate && ActorComponentTemplate) {
				UEngine::CopyPropertiesForUnrelatedObjects(OldActorComponentTemplate, ActorComponentTemplate);
			}
			ActorComponentTemplate->Modify();
		} else {
			//If we have no class anymore
			ActorComponentTemplate = NULL;
		}
	}
	//Rename the component if its name does not match the variable name
	if (ActorComponentTemplate != NULL) {
		if (ActorComponentTemplate->GetFName() != VariableName) {
			ActorComponentTemplate->Rename(*VariableName.ToString(), NULL, REN_DontCreateRedirectors | REN_ForceNoResetLoaders);
		}
	}
}

bool UBlueprintSCSHookData::ResolveParentComponentOnArchetype(FParentComponentInfo& OutParentComponent) const {
	//We, as a child, hold no data about any parent component
	//Therefore the only way for us to get a parent is to check our outer, which should be URootBlueprintSCSHookData
	//That particular hook will be our parent
	if (URootBlueprintSCSHookData* ParentHookData = Cast<URootBlueprintSCSHookData>(GetOuter())) {
		OutParentComponent.Type = EParentComponentType::SCS_HOOK_NODE;
		OutParentComponent.ParentHookData = ParentHookData;
		OutParentComponent.ParentActorComponent = ParentHookData->ActorComponentTemplate;
		return true;
	}

	//Otherwise we have no data for hooking
	return false;
}

void UBlueprintSCSHookData::ExecuteSCSHookOnInstance(AActor* InActorInstance, USceneComponent* InParentComponent) const {
	// Failsafe to avoid attempting to create invalid components
	if (ActorComponentTemplate == nullptr || ActorComponentClass == nullptr || !ActorComponentTemplate->IsA(ActorComponentClass)) {
		return;
	}
	// Create a new component from the template
	UActorComponent* NewActorComponent = NewObject<UActorComponent>(InActorInstance, ActorComponentClass, VariableName, RF_NoFlags, ActorComponentTemplate);

	NewActorComponent->CreationMethod = EComponentCreationMethod::SimpleConstructionScript;
	NewActorComponent->SetNetAddressable();

	// Call OnComponentCreated on the resulting component before RegisterComponentWithWorld is called later
	if (!NewActorComponent->HasBeenCreated()) {
		NewActorComponent->OnComponentCreated();
	}
	USceneComponent* NewSceneComponent = Cast<USceneComponent>(NewActorComponent);
	
	// Set up the attachment to the parent component if this is a scene component
	if (NewSceneComponent) {
		NewSceneComponent->SetupAttachment(InParentComponent, AttachToName);
	}

	// Execute child hooks on this component
	for (const UBlueprintSCSHookData* ChildHookData : Children) {
		if (ChildHookData && ChildHookData->ActorComponentTemplate) {
			ChildHookData->ExecuteSCSHookOnInstance(InActorInstance, NewSceneComponent);
		}
	}
}

TArray<FString> URootBlueprintSCSHookData::GetParentComponentNames() const {
	TArray<FString> ResultArray;
	ResultArray.Add(FName(NAME_None).ToString());

	if (const UBlueprintGeneratedClass* BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(ActorClass.LoadSynchronous())) {
		//Append native component names first
		ForEachObjectWithOuter(BlueprintGeneratedClass->GetDefaultObject(), [&](const UObject* NestedObject){
			//We only want direct UActorComponent children that are default subobjects
			if (NestedObject->IsA<UActorComponent>() && NestedObject->HasAnyFlags(RF_DefaultSubObject)) {
				ResultArray.AddUnique(NestedObject->GetName());
			}
		}, false);

		//Append SCS component names from the current class and from outer classes
		const UBlueprintGeneratedClass* CurrentClass = BlueprintGeneratedClass;
		while (CurrentClass != NULL) {
			if (const USimpleConstructionScript* SimpleConstructionScript = CurrentClass->SimpleConstructionScript) {
				for (const USCS_Node* SCSNode : SimpleConstructionScript->GetAllNodes()) {
					const FName OtherVariableName = SCSNode->GetVariableName();
					if (OtherVariableName != NAME_None) {
						ResultArray.AddUnique(OtherVariableName.ToString());
					}
				}
			}
			CurrentClass = Cast<UBlueprintGeneratedClass>(CurrentClass->GetSuperClass());
		}
	}
	return ResultArray;
}

bool URootBlueprintSCSHookData::ResolveParentComponentOnArchetype(FParentComponentInfo& OutParentComponent) const {
	//If we have a parent node, make sure its actor class always matched what we expect
	//We might end up in a really, really weird situations if user picks some nonsense in the editor
	//Realistically speaking, root nodes should never end up as other node children, but users are dumb and weird
	if (const URootBlueprintSCSHookData* ParentRootData = GetTypedOuter<URootBlueprintSCSHookData>()) {
		if (!ensureAlwaysMsgf(ParentRootData->ActorClass == ActorClass,
			TEXT("Invalid root hook data %s found as a child of root data %s with different actor classes (%s vs %s)"),
			*GetPathName(), *ParentRootData->GetPathName(), *ParentRootData->ActorClass->GetPathName(), *ActorClass->GetPathName())) {
			return false;
		}
	}
	
	UBlueprintGeneratedClass* BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(ActorClass.LoadSynchronous());
	if (BlueprintGeneratedClass == NULL) {
		return false;
	}
	USimpleConstructionScript* SimpleConstructionScript = BlueprintGeneratedClass->SimpleConstructionScript;
	
	//We attach to the parent node and have no parent component
	if (ParentComponentName == NAME_None) {
		OutParentComponent.Type = EParentComponentType::SCS_ROOT_NODE;
		OutParentComponent.SimpleConstructionScript = SimpleConstructionScript;
		return true;
	}

	//Attempt to find SCS parent node first
	USCS_Node* ParentNode = SimpleConstructionScript->FindSCSNode(ParentComponentName);

	//If we have found an SCS node, attempt to mount to it right now
	if (ParentNode != NULL) {
		OutParentComponent.Type = EParentComponentType::SCS_NODE;
		OutParentComponent.SimpleConstructionScript = SimpleConstructionScript;
		OutParentComponent.ParentSCSNode = ParentNode;
		OutParentComponent.ParentActorComponent = ParentNode->ComponentTemplate;
		return true;
	}
	
	//Otherwise attempt to look up native parents or parents from other SCS
	const UClass* OwnerClass = SimpleConstructionScript->GetOwnerClass();
	UObject* DefaultClassObject = OwnerClass->GetDefaultObject();
	UActorComponent* NativeComponent = FindObjectFast<UActorComponent>(DefaultClassObject, ParentComponentName);

	//If we have a component with the exact same name as the variable name, it must be a native component,
	//Because SCS components will never be initialized on the CDO instance
	if (NativeComponent != NULL) {
		OutParentComponent.Type = EParentComponentType::NATIVE_PARENT_COMPONENT;
		OutParentComponent.ParentComponentOrVariableName = NativeComponent->GetFName();
		OutParentComponent.ParentActorComponent = NativeComponent;
		return true;
	}
	
	//Attempt to find a SCS node in a parent class hierarchy to parent to
	const UBlueprintGeneratedClass* CurrentClass = Cast<UBlueprintGeneratedClass>(BlueprintGeneratedClass->GetSuperClass());
	while (CurrentClass != NULL) {
		const USCS_Node* ParentComponentNode = CurrentClass->SimpleConstructionScript->FindSCSNode(ParentComponentName);

		if (ParentComponentNode != NULL) {
			OutParentComponent.Type = EParentComponentType::SUPER_BLUEPRINT_COMPONENT;
			OutParentComponent.ParentComponentOrVariableName = ParentComponentNode->GetVariableName();
			OutParentComponent.ParentComponentOwnerClassName = CurrentClass->GetFName();
			OutParentComponent.ParentActorComponent = ParentComponentNode->ComponentTemplate;
			return true;
		}
		CurrentClass = Cast<UBlueprintGeneratedClass>(CurrentClass->GetSuperClass());
	}

	//Found no matching SCS node, parent BP component or native BP component
	//Attempt to proceed as normal child hook
	return Super::ResolveParentComponentOnArchetype(OutParentComponent);
}

bool URootBlueprintSCSHookData::ResolveParentComponentOnInstance(AActor* ActorInstance, USceneComponent*& OutParentComponent) const {
	// Resolve the parent component by name if the name has been given
	if (ActorComponentClass && ActorComponentClass->IsChildOf(USceneComponent::StaticClass()) && ParentComponentName != NAME_None) {
		if (USceneComponent* ParentSceneComponent = FindObjectFast<USceneComponent>(ActorInstance, ParentComponentName)) {
			OutParentComponent = ParentSceneComponent;
			return true;
		}
		return false;
	}
	return true;
}

void URootBlueprintSCSHookData::ExecuteSCSHookOnInstanceRootComponent(AActor* InActorInstance) const {
	USceneComponent* ParentSceneComponent = nullptr;
	if (ResolveParentComponentOnInstance(InActorInstance, ParentSceneComponent)) {
		ExecuteSCSHookOnInstance(InActorInstance, ParentSceneComponent);
	}
}

static bool MountSCSNodeToParent(UBlueprintSCSHookData* HookData, USCS_Node* NewNode) {
	FParentComponentInfo ParentComponentInfo{};
	if (!HookData->ResolveParentComponentOnArchetype(ParentComponentInfo)) {
		return false;
	}
	
	//We attach to the parent node and have no parent component
	if (ParentComponentInfo.Type == EParentComponentType::SCS_ROOT_NODE) {
		ParentComponentInfo.SimpleConstructionScript->AddNode(NewNode);
		return true;
	}
	
	//If we have found a parent SCS node, attempt to mount to it right now
	if (ParentComponentInfo.Type == EParentComponentType::SCS_NODE) {
		ParentComponentInfo.ParentSCSNode->AddChildNode(NewNode);
		return true;
	}
	
	//If we have a component with the exact same name as the variable name, it must be a native component,
	//Because SCS components will never be initialized on the CDO instance
	if (ParentComponentInfo.Type == EParentComponentType::NATIVE_PARENT_COMPONENT) {
		NewNode->bIsParentComponentNative = true;
		NewNode->ParentComponentOrVariableName = ParentComponentInfo.ParentComponentOrVariableName;
		return true;
	}
	
	//If we have a matching property, we are parented to an SCS node in a parent class
	if (ParentComponentInfo.Type == EParentComponentType::SUPER_BLUEPRINT_COMPONENT) {
		NewNode->bIsParentComponentNative = false;
		NewNode->ParentComponentOrVariableName = ParentComponentInfo.ParentComponentOrVariableName;
		NewNode->ParentComponentOwnerClassName = ParentComponentInfo.ParentComponentOwnerClassName;
		return true;
	}

	//Found no matching SCS node, parent BP component or native BP component
	return false;
}

FGuid GenerateDeterministicGuid(const FString& HashString) {
	uint32 HashBuffer[5];
	uint32 BufferLength = HashString.Len() * sizeof(HashString[0]);
	FSHA1::HashBuffer(*HashString, BufferLength, reinterpret_cast<uint8*>(HashBuffer));

	FGuid Result;
	Result.A = HashBuffer[1];
	Result.B = HashBuffer[2];
	Result.C = HashBuffer[3];
	Result.D = HashBuffer[4];
	return Result;
}

USCS_Node* CreateNewTransientSCSNode(USimpleConstructionScript* SimpleConstructionScript, UClass* NewComponentClass, FName NewComponentVariableName, UActorComponent* ActorComponentTemplate = NULL) {
	UBlueprintGeneratedClass* BlueprintClass = CastChecked<UBlueprintGeneratedClass>(SimpleConstructionScript->GetOwnerClass());

	//In case of naming conflict, we bail out early and do not create the node
	if (SimpleConstructionScript->FindSCSNode(NewComponentVariableName) != NULL) {
		return NULL;
	}

	const FString NewComponentName = NewComponentVariableName.ToString() + USimpleConstructionScript::ComponentTemplateNameSuffix;

	//Make sure we never actually save hooked SCS components or nodes
	UActorComponent* NewComponentTemplate = NewObject<UActorComponent>(
		BlueprintClass, NewComponentClass, *NewComponentName, RF_ArchetypeObject | RF_Transient, ActorComponentTemplate);

	USCS_Node* NewNode = NewObject<USCS_Node>(
		SimpleConstructionScript, MakeUniqueObjectName(SimpleConstructionScript, USCS_Node::StaticClass()), RF_Transient);

	NewNode->ComponentClass = NewComponentTemplate->GetClass();
	NewNode->ComponentTemplate = NewComponentTemplate;
	NewNode->SetVariableName(NewComponentVariableName, false);
	NewNode->VariableGuid = GenerateDeterministicGuid(NewComponentVariableName.ToString());
	
	return NewNode;
}

bool MountSCSNodeToParent(USCS_Node* NewNode, const FParentComponentInfo& ParentComponentInfo, const FBPSCSHookDescriptor& HookDescriptor) {

	//We attach to the parent node and have no parent component
	if (ParentComponentInfo.Type == EParentComponentType::SCS_ROOT_NODE) {
		HookDescriptor.SimpleConstructionScript->AddNode(NewNode);
		return true;
	}
	
	//Attempt to find SCS parent node first
	if (ParentComponentInfo.Type == EParentComponentType::SCS_NODE) {
		USCS_Node* ParentNode = ParentComponentInfo.ParentSCSNode;
		ParentNode->AddChildNode(NewNode);
		return true;
	}

	//Otherwise attempt to look up native parents or parents from other SCS
	if (ParentComponentInfo.Type == EParentComponentType::NATIVE_PARENT_COMPONENT) {
		NewNode->bIsParentComponentNative = true;
		NewNode->ParentComponentOrVariableName = ParentComponentInfo.ParentComponentOrVariableName;

		HookDescriptor.SimpleConstructionScript->AddNode(NewNode);
		return true;
	}
	
	//Otherwise attempt to resolve it as an SCS variable
	if (ParentComponentInfo.Type == EParentComponentType::SUPER_BLUEPRINT_COMPONENT) {
		NewNode->bIsParentComponentNative = false;
		NewNode->ParentComponentOrVariableName = ParentComponentInfo.ParentComponentOrVariableName;
		NewNode->ParentComponentOwnerClassName = ParentComponentInfo.ParentComponentOwnerClassName;

		HookDescriptor.SimpleConstructionScript->AddNode(NewNode);
		return true;
	}

	//Check for parent hook node
	if (ParentComponentInfo.Type == EParentComponentType::SCS_HOOK_NODE) {
		USCS_Node* const* ParentSCSNode = HookDescriptor.InstalledNodes.Find(ParentComponentInfo.ParentHookData);
		if (ParentSCSNode != NULL) {
			(*ParentSCSNode)->AddChildNode(NewNode);
			return true;
		}
		return false;
	}

	//Found no matching SCS node, parent BP component or native BP component
	return false;
}

// Used when fast hook path is not available to bail out of actor spawns with minimal overhead
static TSet<FName> StaticSlowPathHookedBlueprintClassFNames;

void UBlueprintSCSHookManager::RegisterBlueprintSCSHook(URootBlueprintSCSHookData* HookData) {
	// This should not be done from anywhere other than the game thread
	check(IsInGameThread());

	// Silently ignore any hooking requests if hooking is not allowed in this environment
	if (!FSatisfactoryModLoader::IsAssetHookingAllowed()) {
		return;
	}
	// Validate the hook data before registering a hook
	if (!HookData) {
		UE_LOG(LogBlueprintSCSHookManager, Error, TEXT("InstallBlueprintSCSHook failed: Invalid hook data asset"));
		return;
	}
	if (!HookData->ActorComponentTemplate || !HookData->ActorComponentClass) {
		UE_LOG(LogBlueprintSCSHookManager, Error, TEXT("InstallBlueprintSCSHook(%s) failed: Invalid ActorComponent Template provided"), *HookData->GetPathName());
		return;
	}

	// Use fast path if possible instead of registering a slow soft hook
	if (GAllowUsingFastBlueprintSCSHookPath) {
		const UBlueprintGeneratedClass* BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(HookData->ActorClass.LoadSynchronous());
		if (!BlueprintGeneratedClass) {
			UE_LOG(LogBlueprintSCSHookManager, Error, TEXT("InstallBlueprintSCSHook(%s) failed: Provided Class %s is not a Blueprint"), *HookData->GetPathName(), *HookData->ActorClass->GetPathName());
			return;
		}

		FBPSCSHookDescriptor* CurrentRegistration = InstalledArchetypeHooks.FindByPredicate([&](const FBPSCSHookDescriptor& Other) {
			return Other.RootHookData == HookData;
		});

		// Only perform actual registration if we have no existing registration
		if (CurrentRegistration == nullptr) {
			CurrentRegistration = &InstalledArchetypeHooks.AddDefaulted_GetRef();
			CurrentRegistration->RootHookData = HookData;
			CurrentRegistration->SimpleConstructionScript = BlueprintGeneratedClass->SimpleConstructionScript;
			InstallArchetypeSCSHookRecursive(HookData, *CurrentRegistration);
		}
		CurrentRegistration->RegistrationCount++;
	} else {
		// We are in the editor, so we have to use a slow path that does not directly reference or load any assets, and does not modify the blueprints
		// TODO: This does not process core redirects, if class is not loaded but is redirected the hook will not fire in the editor
		TArray<FSoftEditorBPSCSHookRegistration>& HookRegistrations = InstalledSlowPerInstanceHooks.FindOrAdd(HookData->ActorClass.ToSoftObjectPath().GetAssetPath());
		FSoftEditorBPSCSHookRegistration* ExistingRegistration = HookRegistrations.FindByPredicate([&](const FSoftEditorBPSCSHookRegistration& Other) {
			return Other.HookAsset == HookData;
		});

		// Create a new registration if we do not have one already
		if (ExistingRegistration == nullptr) {
			ExistingRegistration = &HookRegistrations.AddDefaulted_GetRef();
			ExistingRegistration->HookAsset = HookData;
		}
		ExistingRegistration->RegistrationCount++;

		// Add the BPGC class name to the fast lookup. We never remove classes from there, even when hooks are unregistered
		StaticSlowPathHookedBlueprintClassFNames.Add( HookData->ActorClass.ToSoftObjectPath().GetAssetPath().GetAssetName() );
	}
}

void UBlueprintSCSHookManager::UnregisterBlueprintSCSHook(URootBlueprintSCSHookData* HookData) {
	// This should not be done from anywhere other than the game thread
	check(IsInGameThread());
	
	// Use fast path if possible instead of registering a slow soft hook
	if (GAllowUsingFastBlueprintSCSHookPath) {
		const int32 ExistingHookIndex = InstalledArchetypeHooks.IndexOfByPredicate([&](const FBPSCSHookDescriptor& Other) {
			return HookData == Other.RootHookData;
		});

		// Remove the installed archetype hook if registration count reached zero
		if (ExistingHookIndex != INDEX_NONE && --InstalledArchetypeHooks[ExistingHookIndex].RegistrationCount == 0) {
			const FBPSCSHookDescriptor HookDescriptor = InstalledArchetypeHooks[ExistingHookIndex];
			InstalledArchetypeHooks.RemoveAt(ExistingHookIndex);
			RemoveArchetypeSCSHookOrdered(HookDescriptor);
		}
	} else {
		// We are in the editor, so we have to use a slow path that does not directly reference or load any assets, and does not modify the blueprints
		TArray<FSoftEditorBPSCSHookRegistration>& HookRegistrations = InstalledSlowPerInstanceHooks.FindOrAdd(HookData->ActorClass.ToSoftObjectPath().GetAssetPath());
		const int32 CurrentRegistrationIndex = HookRegistrations.IndexOfByPredicate([&](const FSoftEditorBPSCSHookRegistration& Other) {
			return Other.HookAsset == HookData;
		});

		// Remove the hook registration completely if registration count reaches zero
		if (CurrentRegistrationIndex != INDEX_NONE && --HookRegistrations[CurrentRegistrationIndex].RegistrationCount == 0) {
			HookRegistrations.RemoveAt(CurrentRegistrationIndex);
		}
	}
}

void UBlueprintSCSHookManager::InstallArchetypeSCSHookRecursive(UBlueprintSCSHookData* HookData, FBPSCSHookDescriptor& OutHookDescriptor) {
	USimpleConstructionScript* SimpleConstructionScript = OutHookDescriptor.SimpleConstructionScript;
	USCS_Node* NewNode = CreateNewTransientSCSNode(SimpleConstructionScript, HookData->ActorComponentClass, HookData->VariableName, HookData->ActorComponentTemplate);
	if (NewNode == NULL) {
		UE_LOG(LogBlueprintSCSHookManager, Error, TEXT("Failed to instance SCS hook %s: cannot create new SCSNode"), *HookData->GetPathName());
		return;
	}
	NewNode->AttachToName = HookData->AttachToName;

	FParentComponentInfo ParentComponentInfo{};
	if (!HookData->ResolveParentComponentOnArchetype(ParentComponentInfo) || !MountSCSNodeToParent(NewNode, ParentComponentInfo, OutHookDescriptor)) {
		UE_LOG(LogBlueprintSCSHookManager, Error, TEXT("Failed to instance SCS hook %s: cannot mount Node %s declared by hook %s"),
			*OutHookDescriptor.RootHookData->GetPathName(), *NewNode->GetPathName(), *HookData->GetPathName());
		return;
	}
	OutHookDescriptor.InstalledNodes.Add(HookData, NewNode);
	OutHookDescriptor.InstalledNodesOrdered.Add(NewNode);

	UE_LOG(LogBlueprintSCSHookManager, Log, TEXT("Successfully installed SCS Hook %s Subhook %s at Blueprint %s"),
			*OutHookDescriptor.RootHookData->GetPathName(), *HookData->GetPathName(), *OutHookDescriptor.SimpleConstructionScript->GetOwnerClass()->GetPathName());

	for (UBlueprintSCSHookData* ChildHook : HookData->Children) {
		InstallArchetypeSCSHookRecursive(ChildHook, OutHookDescriptor);
	}
}

void UBlueprintSCSHookManager::RemoveArchetypeSCSHookOrdered(const FBPSCSHookDescriptor& HookDescriptor) {
	//Uninstall hooks in the reverse order of their installation
	for (int32 i = HookDescriptor.InstalledNodesOrdered.Num() - 1; i >= 0; i--) {
		USCS_Node* SCSNode = HookDescriptor.InstalledNodesOrdered[i];
		HookDescriptor.SimpleConstructionScript->RemoveNode(SCSNode);
		const UBlueprintSCSHookData* HookData = *HookDescriptor.InstalledNodes.FindKey(SCSNode);
		
		UE_LOG(LogBlueprintSCSHookManager, Log, TEXT("Removed SCS hook %s subhook %s from Blueprint %s"),
			*HookDescriptor.RootHookData->GetPathName(), *HookData->GetPathName(), *HookDescriptor.SimpleConstructionScript->GetOwnerClass()->GetPathName());
	}
}

void UBlueprintSCSHookManager::RegisterStaticHooks()
{
	// If we are not allowed to use the fast SCS hooking path in this environment, we need to install a global hook on
	// UBlueprintGeneratedClass::CreateComponentsFromActor to support dynamic component creation on the instances instead of the archetypes
	//if (!GAllowUsingFastBlueprintSCSHookPath && FSatisfactoryModLoader::IsAssetHookingAllowed()) {
		//SUBSCRIBE_METHOD_AFTER(UBlueprintGeneratedClass::CreateComponentsForActor, [](const UClass* ThisClass, AActor* Actor) {
			// Only forward the components creation to the classes that actually have hooks registered to reduce the overhead
		//	if (StaticSlowPathHookedBlueprintClassFNames.Contains(ThisClass->GetFName())) {
		//		BlueprintGeneratedClassCreateComponentsFromActor(ThisClass, Actor);
		//	}
		//});
	//}
}

void UBlueprintSCSHookManager::BlueprintGeneratedClassCreateComponentsFromActor(const UClass* ThisClass, AActor* Actor) {
	// This logic should only run on actors in game worlds, never in Editor or EditorPreview worlds
	const UWorld* OwnerWorld = Actor->GetWorld();
	if (OwnerWorld != nullptr && (OwnerWorld->WorldType == EWorldType::PIE || OwnerWorld->WorldType == EWorldType::Game)) {
		if (UBlueprintSCSHookManager* HookManager = GEngine->GetEngineSubsystem<UBlueprintSCSHookManager>()) {

			// Retrieve all registrations for the class in question and process them
			if (const TArray<FSoftEditorBPSCSHookRegistration>* AllRegistrationsForThisClass = HookManager->InstalledSlowPerInstanceHooks.Find(ThisClass->GetClassPathName())) {
				for (const FSoftEditorBPSCSHookRegistration& Registration : *AllRegistrationsForThisClass) {
					if (const URootBlueprintSCSHookData* BlueprintHookData = Registration.HookAsset.LoadSynchronous()) {
						BlueprintHookData->ExecuteSCSHookOnInstanceRootComponent(Actor);
					}
				}
			}
		}
	}
}
